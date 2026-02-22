#include "Platform/Vulkan/VulkanGraphicsContext.h"
#include "Managers/LogManager/LogManager.h"

#include <vulkan/vulkan.h>
#include <VkBootstrap.h>

namespace GojoEngine
{

#ifdef GOJO_DEBUG_BUILD
	constexpr bool gUseValidationLayers = true;
#else
	constexpr bool gUseValidationLayers = false;
#endif

	static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		const char* typePrefix = "";
		if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) typePrefix = "[General]";
		else if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) typePrefix = "[Validation]";
		else if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) typePrefix = "[Performance]";

		if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		{
			GOJO_LOG_ERROR("Vulkan", "{} {}", typePrefix, pCallbackData->pMessage);
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			GOJO_LOG_WARNING("Vulkan", "{} {}", typePrefix, pCallbackData->pMessage);
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		{
			GOJO_LOG_INFO("Vulkan", "{} {}", typePrefix, pCallbackData->pMessage);
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		{
			GOJO_LOG_TRACE("Vulkan", "{} {}", typePrefix, pCallbackData->pMessage);
		}

		return VK_FALSE;
	}

	class VulkanGraphicsContext::Impl
	{
	public:
		Impl() = default;

		~Impl()
		{
			// Гарантируем, что ShutDown был вызван перед разрушением объекта
			if (mInstance != VK_NULL_HANDLE)
			{
				GOJO_LOG_WARNING("Vulkan", "VulkanGraphicsContext::ShutDown was not called explicitly! Calling automatically.");
				ShutDown();
			}
		}

		void StartUp()
		{
			GOJO_ASSERT_MESSAGE(mInstance == VK_NULL_HANDLE, "Vulkan Instance already initialized!");

			GOJO_LOG_INFO("Vulkan", "Initializing Vulkan Graphics Context...");

			/* VK INSTANCE */
			vkb::InstanceBuilder instanceBuilder;
			auto instanceResult = instanceBuilder
				.set_app_name("GojoEngine")
				.set_engine_name("GojoEngine")
				.request_validation_layers(gUseValidationLayers)
				.set_debug_callback(VulkanDebugCallback)
				.require_api_version(1, 4, 0)
				.build();

			if (!instanceResult)
			{
				std::string errorMsg = instanceResult.error().message();
				GOJO_LOG_FATAL("Vulkan", "Failed to create Vulkan Instance! Error: {}", errorMsg);
				return;
			}

			vkb::Instance vkbInstance = instanceResult.value();
			mInstance = vkbInstance.instance;
			mDebugMessenger = vkbInstance.debug_messenger;

			GOJO_ASSERT_MESSAGE(mInstance != VK_NULL_HANDLE, "Vulkan Instance handle is null after creation!");

			if (gUseValidationLayers)
			{
				GOJO_ASSERT_MESSAGE(mDebugMessenger != VK_NULL_HANDLE, "Debug Messenger requested but handle is null!");
				GOJO_LOG_DEBUG("Vulkan", "Validation Layers Enabled.");
			}

			GOJO_LOG_INFO("Vulkan", "Vulkan Instance created successfully.");
		}

		void ShutDown()
		{
			if (mInstance == VK_NULL_HANDLE)
			{
				GOJO_LOG_WARNING("Vulkan", "Attempting to shut down Vulkan context that is not initialized or already shut down.");
				return;
			}

			GOJO_LOG_INFO("Vulkan", "Shutting down Vulkan Graphics Context...");

			/* SHUTDOWN DEBUG MESSENGER */
			if (mDebugMessenger != VK_NULL_HANDLE)
			{
				auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(mInstance, "vkDestroyDebugUtilsMessengerEXT");
				if (func != nullptr)
				{
					func(mInstance, mDebugMessenger, nullptr);
					GOJO_LOG_INFO("Vulkan", "Vulkan Debug Messenger ShutDown complete!");
				}
				else
				{
					GOJO_LOG_ERROR("Vulkan", "Failed to load vkDestroyDebugUtilsMessengerEXT function pointer!");
				}
				mDebugMessenger = VK_NULL_HANDLE;
			}

			/* SHUTDOWN INSTANCE */
			vkDestroyInstance(mInstance, nullptr);
			mInstance = VK_NULL_HANDLE;
			GOJO_LOG_INFO("Vulkan", "Vulkan Instance ShutDown complete!");

			GOJO_LOG_INFO("Vulkan", "Vulkan resources released.");
		}

	private:
		VkInstance mInstance{ VK_NULL_HANDLE };
		VkDebugUtilsMessengerEXT mDebugMessenger{ VK_NULL_HANDLE };
	};

	VulkanGraphicsContext::VulkanGraphicsContext()
		: pImpl(std::make_unique<Impl>())
	{
	}

	VulkanGraphicsContext::~VulkanGraphicsContext() = default;

	void VulkanGraphicsContext::StartUp()
	{
		GOJO_ASSERT(pImpl);
		pImpl->StartUp();
	}

	void VulkanGraphicsContext::ShutDown()
	{
		GOJO_ASSERT(pImpl);
		pImpl->ShutDown();
	}
}