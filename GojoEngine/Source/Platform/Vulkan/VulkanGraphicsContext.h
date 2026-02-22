#pragma once

#include "Core/Macros.h" 
#include "Core/Utility.h"

#include <memory>

namespace GojoEngine
{
	class GOJO_API VulkanGraphicsContext final : public NonCopyable
	{
	public:
		explicit VulkanGraphicsContext();
		~VulkanGraphicsContext();

		void StartUp();
		void ShutDown();

	private:
		class Impl;
		std::unique_ptr<Impl> pImpl;
	};
}