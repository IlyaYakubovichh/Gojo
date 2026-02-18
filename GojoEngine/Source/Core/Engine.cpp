#include "Core/Engine.h"
#include "Managers/LogManager/LogManager.h"
#include "Managers/WindowManager/WindowManager.h"

namespace GojoEngine
{
	void Engine::StartUp()
	{
		LogManager::StartUp();		GOJO_LOG_INFO("LogManager", "LogManager StartUp complete!");
		WindowManager::StartUp();	GOJO_LOG_INFO("WindowManager", "WindowManager StartUp complete!");
	}

	void Engine::Run()
	{
		auto& windowManager = WindowManager::GetInstance();
		while (!windowManager.AreAllWindowsClosed())
		{
			windowManager.OnUpdate();
		}
	}

	void Engine::ShutDown()
	{
		WindowManager::ShutDown();
		LogManager::ShutDown();
	}
}