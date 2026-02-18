#include "Managers/WindowManager/WindowManager.h"
#include "Managers/LogManager/LogManager.h"

#include <GLFW/glfw3.h>

namespace GojoEngine
{
	std::expected<WindowId, WindowError> WindowManager::CreateWindow(const WindowSettings& settings)
	{
		GOJO_ASSERT_MESSAGE((settings.Width > 0) && (settings.Height > 0), "Window width and height must be > 0!");

		if (!mInitialized)
		{
			GOJO_LOG_ERROR("WindowManager", "Cannot create window. GLFW is not initialized!");
			return std::unexpected(WindowError::ManagerIsNotInitialized);
		}

		auto window = std::make_shared<Window>(settings);
		if (!window->IsValid())
		{
			GOJO_LOG_ERROR("WindowManager", "Window creation failed for '{}'", settings.Title);
			return std::unexpected(WindowError::CreationFailed);
		}

		const WindowId id( ++mWindowCounter );
		mWindows[id] = window;

		GOJO_LOG_INFO("WindowManager", "Window '{}' created with id={}", settings.Title, id.mId);

		return id;
	}

	void WindowManager::OnUpdate()
	{
		if (!mInitialized)
			return;

		glfwPollEvents();
		CleanupClosedWindows();
	}

	void WindowManager::CleanupClosedWindows()
	{
		auto it = mWindows.begin();
		while (it != mWindows.end())
		{
			if (it->second->ShouldClose())
			{
				GOJO_LOG_INFO("WindowManager", "Erased '{}' window!", it->second->GetTitle());
				it = mWindows.erase(it);
				continue;
			}
			++it;
		}
	}

	void WindowManager::CloseAllWindows()
	{
		for (auto& [id, window] : mWindows)
		{
			if (window && window->IsValid())
			{
				glfwSetWindowShouldClose(window->GetRaw(), GLFW_TRUE);
			}
		}
	}

	b8 WindowManager::AreAllWindowsClosed()
	{
		return mWindows.empty();
	}

	std::shared_ptr<Window> WindowManager::GetWindowById(WindowId id) const
	{
		auto it = mWindows.find(id);
		if (it != mWindows.end())
			return it->second;

		GOJO_LOG_WARNING("WindowManager", "Requested window with invalid id={}", id.mId);

		return nullptr;
	}

	WindowManager::WindowManager()
	{
		glfwSetErrorCallback([](int errorCode, const char* description)
			{
				GOJO_LOG_ERROR("GLFW", "GLFW Error [{}]: {}", errorCode, description);
			});

		if (!glfwInit())
		{
			GOJO_LOG_ERROR("GLFW", "GLFW initialization failed!");
			return;
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		mInitialized = true;
	}

	WindowManager::~WindowManager()
	{
		CloseAllWindows();
		CleanupClosedWindows();

		mWindows.clear();

		if (mInitialized)
		{
			glfwTerminate();
			mInitialized = false;
		}

		GOJO_LOG_INFO("WindowManager", "WindowManager ShutDown complete!");
	}
}