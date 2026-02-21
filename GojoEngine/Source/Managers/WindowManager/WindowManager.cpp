#include "Managers/WindowManager/WindowManager.h"
#include "Managers/LogManager/LogManager.h"

#include <GLFW/glfw3.h>

namespace GojoEngine
{
	// ====================================================================================================
	// Public API
	// ====================================================================================================

	std::expected<WindowId, WindowError> WindowManager::CreateWindow(const WindowSettings& settings)
	{
		GOJO_ASSERT_MESSAGE((settings.Width > 0) && (settings.Height > 0), "Window dimensions must be > 0!");

		if (!mInitialized)
		{
			GOJO_LOG_ERROR("WindowManager", "Cannot create window. GLFW is not initialized!");
			return std::unexpected(WindowError::ManagerIsNotInitialized);
		}

		const WindowId id( ++mWindowCounter );

		auto window = std::make_shared<Window>(id, settings);
		if (!window->IsValid())
		{
			GOJO_LOG_ERROR("WindowManager", "Window creation failed for '{}'", settings.Title);
			return std::unexpected(WindowError::CreationFailed);
		}

		mWindows[id] = window;

		GOJO_LOG_INFO("WindowManager", "Window '{}' created with ID: {}", settings.Title, id.mId);

		return id;
	}

	void WindowManager::OnUpdate()
	{
		if (!mInitialized) return;

		glfwPollEvents();
		CleanupClosedWindows();
	}

	void WindowManager::CleanupClosedWindows()
	{
		std::erase_if(mWindows, [](const auto& pair)
			{
				if (pair.second->ShouldClose())
				{
					GOJO_LOG_INFO("WindowManager", "Erased '{}' window!", pair.second->GetTitle());
					return true;
				}
				return false;
			});
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

	bool WindowManager::AreAllWindowsClosed() const
	{
		return mWindows.empty();
	}

	std::shared_ptr<Window> WindowManager::GetWindowById(WindowId id) const
	{
		if (auto it = mWindows.find(id); it != mWindows.end())
		{
			return it->second;
		}

		GOJO_LOG_WARNING("WindowManager", "Requested window with invalid ID: {}", id.mId);
		return nullptr;
	}

	// ====================================================================================================
	// Constructor / Destructor
	// ====================================================================================================

	WindowManager::WindowManager()
	{
		glfwSetErrorCallback([](int errorCode, const char* description)
			{
				GOJO_LOG_ERROR("GLFW", "Error [{}]: {}", errorCode, description);
			});

		if (!glfwInit())
		{
			GOJO_LOG_FATAL("GLFW", "Initialization failed!");
			return;
		}

		// Basic generic hints
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

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

		GOJO_LOG_INFO("WindowManager", "ShutDown complete!");
	}
}