#include "Core/Engine.h"
#include "Managers/LogManager/LogManager.h"
#include "Managers/WindowManager/WindowManager.h"	   
#include "Managers/EventManager/EventManager.h"
#include "Managers/EventManager/Events/WindowEvents.h"

namespace GojoEngine
{

	Engine& Engine::GetInstance()
	{
		static Engine engine;
		return engine;
	}

	void Engine::StartUp()
	{
		LogManager::StartUp();		GOJO_LOG_INFO("Engine", "LogManager StartUp complete!");
		WindowManager::StartUp();	GOJO_LOG_INFO("Engine", "WindowManager StartUp complete!");
		EventManager::StartUp();	GOJO_LOG_INFO("Engine", "EventManager StartUp complete!");

		GOJO_LOG_INFO("Engine", "Engine StartUp complete!");
	}

	void Engine::Run()
	{
		auto& windowManager = WindowManager::GetInstance();

		GOJO_LOG_INFO("Engine", "Entering Main Loop...");
		while (!windowManager.AreAllWindowsClosed())
		{
			windowManager.OnUpdate();
		}
	}

	void Engine::ShutDown()
	{
		GOJO_LOG_INFO("Engine", "Engine ShutDown...");

		EventManager::ShutDown();
		WindowManager::ShutDown();
		LogManager::ShutDown();
	}

}