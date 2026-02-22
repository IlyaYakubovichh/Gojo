#pragma once

#include "Utility.h"
#include "Core/Macros.h"
#include "Platform/Vulkan/VulkanGraphicsContext.h"

#include <memory>

namespace GojoEngine
{

	class GOJO_API Engine final : public NonCopyable
	{
	public:
		static Engine& GetInstance();

		static void StartUp();
		static void Run();
		static void ShutDown();

	private:
		Engine() = default;
		~Engine() = default;
	};

}