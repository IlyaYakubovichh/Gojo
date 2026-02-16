#pragma once

#include "Utility.h"
#include "Core/Macros.h"
#include "Managers/LogManager/LogManager.h"

namespace GojoEngine
{
	class GOJO_API Engine : public NonCopyable
	{
	public:
		static Engine& GetInstance() // Lazy creation
		{
			static Engine engine;
			return engine;
		}

		static void StartUp();
		static void ShutDown();

		static const LogManager* const GetLogManager() { return sLogManager; }

	private:
		Engine() = default;
		~Engine() = default;

	private:
		static LogManager* sLogManager;
	};
}