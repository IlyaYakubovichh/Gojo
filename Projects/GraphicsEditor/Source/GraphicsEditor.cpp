#include <GojoEngine.h>

int main()
{
    GojoEngine::Engine::StartUp();

    auto& windowManager = GojoEngine::WindowManager::GetInstance();
    const auto window1Result = windowManager.CreateWindow(GojoEngine::WindowSettings{50,50,800,600,"GojoWindow1"});
    if (!window1Result.has_value()) { GojoDebugBreak(); }
    const auto window2Result = windowManager.CreateWindow(GojoEngine::WindowSettings{100,100,800,600,"GojoWindow2"});
    if (!window2Result.has_value()) { GojoDebugBreak(); }
    const auto window3Result = windowManager.CreateWindow(GojoEngine::WindowSettings{200,200,800,600,"GojoWindow3"});
    if (!window3Result.has_value()) { GojoDebugBreak();                                               }

    GojoEngine::Engine::Run();

    auto window1Id = window1Result.value();
    auto window2Id = window2Result.value();
    auto window3Id = window3Result.value();

    GojoEngine::Engine::ShutDown();

    return 0;
}