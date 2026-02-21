#include <GojoEngine.h>

using namespace GojoEngine;

int main()
{
	Engine::StartUp();

	auto& windowManager = GojoEngine::WindowManager::GetInstance();
	const auto window1Result = windowManager.CreateWindow(GojoEngine::WindowSettings{ 50,50,800,600,"GojoWindow1" });
	if (!window1Result.has_value()) { GojoDebugBreak(); }
	const auto window2Result = windowManager.CreateWindow(GojoEngine::WindowSettings{ 100,100,800,600,"GojoWindow2" });
	if (!window2Result.has_value()) { GojoDebugBreak(); }
	const auto window3Result = windowManager.CreateWindow(GojoEngine::WindowSettings{ 200,200,800,600,"GojoWindow3" });
	if (!window3Result.has_value()) { GojoDebugBreak(); }

	auto window1Id = window1Result.value();
	auto window2Id = window2Result.value();
	auto window3Id = window3Result.value();

	// Local listeners for window with Id = 1
	AddWindowListener<WindowResizeEvent>(window1Id, [](const WindowResizeEvent& event)
		{
			GOJO_LOG_INFO("Engine", "{}", event.ToString());
		});

	AddWindowListener<KeyReleasedEvent>(window1Id, [](const KeyReleasedEvent& event)
		{
			GOJO_LOG_INFO("Engine", "{}", event.ToString());
		});

	// Global listener (for all windows)
	AddListener<WindowCloseEvent>([](const WindowCloseEvent& event) 
		{
			GOJO_LOG_INFO("Engine", "{}", event.ToString());
		});

	Engine::Run();

	Engine::ShutDown();

    return 0;
}