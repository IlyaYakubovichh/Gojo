#include "Managers/WindowManager/Window/Window.h"
#include "Managers/EventManager/EventManager.h"
#include "Managers/EventManager/Events/WindowEvents.h"
#include "Managers/EventManager/Events/KeyboardEvents.h"
#include "Managers/EventManager/Events/MouseEvents.h"
#include "Managers/LogManager/LogManager.h"

#include <GLFW/glfw3.h>

namespace GojoEngine
{
	Window::Window(WindowId id, const WindowSettings& settings)
		: mId(id), mSettings(settings)
	{
		mWindow = glfwCreateWindow(
			static_cast<int>(settings.Width),
			static_cast<int>(settings.Height),
			settings.Title.c_str(),
			nullptr,
			nullptr
		);

		if (!mWindow)
		{
			GOJO_LOG_ERROR("Window", "Failed to create GLFW window '{}'", settings.Title);
			return;
		}

		glfwSetWindowPos(
			mWindow,
			static_cast<int>(settings.XPos),
			static_cast<int>(settings.YPos)
		);

		InitializeCallbacks();
	}

	Window::~Window()
	{
		if (mWindow)
		{
			glfwDestroyWindow(mWindow);
			mWindow = nullptr;
		}
	}

	bool Window::ShouldClose() const
	{
		return mWindow ? glfwWindowShouldClose(mWindow) : true;
	}

	void Window::InitializeCallbacks()
	{
		glfwSetWindowUserPointer(mWindow, this);

		// ==========================================
		// Window Callbacks
		// ==========================================
		// Resize
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				self->mSettings.Width = static_cast<uint16_t>(width);
				self->mSettings.Height = static_cast<uint16_t>(height);

				WindowResizeEvent event(self->mId, width, height);
				DispatchEvent(event);
			});

		// Close
		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				WindowCloseEvent event(self->mId);
				DispatchEvent(event);
			});

		// Focus / Lost Focus
		glfwSetWindowFocusCallback(mWindow, [](GLFWwindow* window, int focused)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				if (focused)
				{
					WindowFocusEvent event(self->mId);
					DispatchEvent(event);
				}
				else
				{
					WindowLostFocusEvent event(self->mId);
					DispatchEvent(event);
				}
			});

		// Moved (Position changed)
		glfwSetWindowPosCallback(mWindow, [](GLFWwindow* window, int xpos, int ypos)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				self->mSettings.XPos = static_cast<uint16_t>(xpos);
				self->mSettings.YPos = static_cast<uint16_t>(ypos);

				WindowMovedEvent event(self->mId, xpos, ypos);
				DispatchEvent(event);
			});

		// ==========================================
		// Key Callbacks
		// ==========================================

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(self->mId, key);
					DispatchEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(self->mId, key);
					DispatchEvent(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(self->mId, key);
					DispatchEvent(event);
					break;
				}
				}
			});

		// Char (Typed)
		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				KeyTypedEvent event(self->mId, static_cast<int>(keycode));
				DispatchEvent(event);
			});

		// ==========================================
		// Mouse Callbacks
		// ==========================================
		// Mouse Button
		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(self->mId, button);
					DispatchEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(self->mId, button);
					DispatchEvent(event);
					break;
				}
				}
			});

		// Scroll
		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseScrolledEvent event(self->mId, static_cast<float>(xOffset), static_cast<float>(yOffset));
				DispatchEvent(event);
			});

		// Cursor Position (Mouse Moved)
		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos)
			{
				auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));

				MouseMovedEvent event(self->mId, static_cast<float>(xPos), static_cast<float>(yPos));
				DispatchEvent(event);
			});
	}

}