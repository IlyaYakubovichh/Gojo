#pragma once

#include "Core/Macros.h"
#include "Managers/Manager.h"

#include <string>
#include <string_view>
#include <memory>
#include <format>
#include <concepts>

// ====================================================================================================
// Log Configuration
// ====================================================================================================

#define LOG_TRACE_ENABLED   1
#define LOG_INFO_ENABLED    1
#define LOG_DEBUG_ENABLED   1
#define LOG_WARNING_ENABLED 0
#define LOG_ERROR_ENABLED   1
#define LOG_FATAL_ENABLED   1

// Disable Debug and Trace logs in Release builds to save performance
#ifdef GOJO_RELEASE_BUILD
#undef LOG_TRACE_ENABLED
#undef LOG_DEBUG_ENABLED
#define LOG_TRACE_ENABLED 0
#define LOG_DEBUG_ENABLED 0
#endif

// Guard against Windows.h macros interfering with Enum
#ifdef Error
#undef Error
#endif

namespace GojoEngine
{
	enum class LogLevel : uint8_t
	{
		Trace,
		Info,
		Debug,
		Warning,
		Error,
		Fatal,
		Off
	};

	// Log Level boundaries for compile-time checks
	constexpr LogLevel MIN_LOG_LEVEL = LogLevel::Trace;
	constexpr LogLevel MAX_LOG_LEVEL = LogLevel::Fatal;

	/**
	 * @brief Concept ensuring the message can be converted to a string view.
	 */
	template<typename T>
	concept LoggableMessage = std::convertible_to<T, std::string_view> || std::convertible_to<T, std::string>;

	// ====================================================================================================
	// LogManager Interface
	// ====================================================================================================

	/**
	 * @brief Handles logging to console sink.
	 * Implements PIMPL idiom to hide spdlog dependencies.
	 */
	class GOJO_API LogManager final : public Manager<LogManager>
	{
		friend class Manager<LogManager>;

	public:
		void LogMessage(std::string_view categoryName, LogLevel level, std::string_view message) const;

	private:
		LogManager();
		~LogManager();

	private:
		class Impl;
		std::unique_ptr<Impl> mImpl;
	};
}

// ====================================================================================================
// Core Log Macros
// ====================================================================================================

#ifndef GOJO_LOG
#define GOJO_LOG(categoryName, logLevel, message, ...) 																										\
do 																																							\
{ 																																							\
	if constexpr (GojoEngine::LogLevel::logLevel >= GojoEngine::MIN_LOG_LEVEL && GojoEngine::LogLevel::logLevel <= GojoEngine::MAX_LOG_LEVEL) 				\
	{																																						\
		GOJO_STATIC_ASSERT(GojoEngine::LoggableMessage<decltype(message)>, "Message should be convertible to std::string or std::string_view!"); 			\
		GOJO_STATIC_ASSERT(GojoEngine::LoggableMessage<decltype(categoryName)>, "Category should be convertible to std::string or std::string_view!"); 		\
																																							\
		GojoEngine::LogManager::GetInstance().LogMessage( 																									\
			categoryName, 																																	\
			GojoEngine::LogLevel::logLevel, 																												\
			std::format(message, ##__VA_ARGS__) 																											\
		); 																																					\
	} 																																						\
} while (0)
#endif

// ====================================================================================================
// Assertion Log Macro
// ====================================================================================================

#ifndef GOJO_LOG_ASSERT
#define GOJO_LOG_ASSERT(expression, message, file, line) \
		GOJO_LOG("Assertions", Error, "Assertion '{}' Failed: {}\nSource: {}:{}", #expression, message, file, line)
#endif

// ====================================================================================================
// Utility Log Macros
// ====================================================================================================

#if LOG_TRACE_ENABLED
#define GOJO_LOG_TRACE(category, msg, ...) GOJO_LOG(category, Trace, msg, ##__VA_ARGS__)
#else
#define GOJO_LOG_TRACE(category, msg, ...)
#endif

#if LOG_INFO_ENABLED
#define GOJO_LOG_INFO(category, msg, ...)  GOJO_LOG(category, Info, msg, ##__VA_ARGS__)
#else
#define GOJO_LOG_INFO(category, msg, ...)
#endif

#if LOG_DEBUG_ENABLED
#define GOJO_LOG_DEBUG(category, msg, ...) GOJO_LOG(category, Debug, msg, ##__VA_ARGS__)
#else
#define GOJO_LOG_DEBUG(category, msg, ...)
#endif

#if LOG_WARNING_ENABLED
#define GOJO_LOG_WARNING(category, msg, ...) GOJO_LOG(category, Warning, msg, ##__VA_ARGS__)
#else
#define GOJO_LOG_WARNING(category, msg, ...)
#endif

#if LOG_ERROR_ENABLED
#define GOJO_LOG_ERROR(category, msg, ...) GOJO_LOG(category, Error, msg, ##__VA_ARGS__)
#else
#define GOJO_LOG_ERROR(category, msg, ...)
#endif

#if LOG_FATAL_ENABLED
#define GOJO_LOG_FATAL(category, msg, ...) GOJO_LOG(category, Fatal, msg, ##__VA_ARGS__)
#else
#define GOJO_LOG_FATAL(category, msg, ...)
#endif