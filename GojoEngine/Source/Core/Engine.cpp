#include "Core/Engine.h"
#include "Managers/LogManager/LogManager.h"
#include "Managers/WindowManager/WindowManager.h"	   
#include "Managers/EventManager/EventManager.h"
#include "Managers/EventManager/Events/WindowEvents.h"

#include "Platform/Vulkan/VulkanGraphicsContext.h"

namespace GojoEngine
{

	std::shared_ptr<VulkanGraphicsContext> mContext;

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

		mContext = std::make_shared<VulkanGraphicsContext>();
		mContext->StartUp();

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

		mContext->ShutDown();

		EventManager::ShutDown();
		WindowManager::ShutDown();
		LogManager::ShutDown();
	}

}