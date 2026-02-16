#include "Core/Engine.h"

namespace GojoEngine
{
	LogManager* Engine::sLogManager = nullptr;

	void Engine::StartUp()
	{
		// Log manager
		sLogManager = new LogManager();
		sLogManager->StartUp();
	}

	void Engine::ShutDown()
	{
		// Log manager
		sLogManager->ShutDown();
		delete sLogManager;
	}
}