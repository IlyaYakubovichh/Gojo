#include "Managers/WindowManager/Window.h"
#include "Managers/LogManager/LogManager.h"

#include <GLFW/glfw3.h>

namespace GojoEngine
{

	Window::Window(const WindowSettings& settings)
		: mSettings(settings)
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
	}

	Window::~Window()
	{
		if (mWindow)
		{
			glfwDestroyWindow(mWindow);
			mWindow = nullptr;
		}
	}

	b8 Window::ShouldClose() const
	{
		if (!mWindow)
			return true;

		return glfwWindowShouldClose(mWindow);
	}


}
