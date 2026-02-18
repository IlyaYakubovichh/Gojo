#pragma once

#include "Core/Macros.h"
#include "Managers/Manager.h"

#include <string>
#include <string_view>
#include <memory>
#include <format>
#include <concepts>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// ================================================================================
// Log Configuration
// ================================================================================

// Default log levels
#define LOG_TRACE_ENABLED   1
#define LOG_INFO_ENABLED    1
#define LOG_DEBUG_ENABLED   1
#define LOG_WARNING_ENABLED 1
#define LOG_ERROR_ENABLED   1
#define LOG_FATAL_ENABLED   1

// No debug and trace logs in release build
#ifdef GOJO_RELEASE_BUILD
#undef LOG_TRACE_ENABLED
#undef LOG_DEBUG_ENABLED
#define LOG_TRACE_ENABLED 0
#define LOG_DEBUG_ENABLED 0
#endif

namespace GojoEngine
{
	enum class LogLevel : u8
	{
		Trace, 
		Info, 
		Debug,
		Warning, 
		Error, 
		Fatal, 
		Off
	};

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
		std::unique_ptr<Impl> pImpl;
	};

	// Concepts
	template<typename T>
	concept LoggableMessage = std::convertible_to<T, std::string_view> || std::convertible_to<T, std::string>;

	// Level boundaries
	constexpr LogLevel minLogLevel = LogLevel::Trace;
	constexpr LogLevel maxLogLevel = LogLevel::Fatal;
}

// ================================================================================
// Core Log Macro
// ================================================================================

#ifndef GOJO_LOG
#define GOJO_LOG(categoryName, logLevel, message, ...) 																									   \
do																																						   \
{																																						   \
	if constexpr (GojoEngine::LogLevel::logLevel >= GojoEngine::minLogLevel && GojoEngine::LogLevel::logLevel <= GojoEngine::maxLogLevel)				   \
	{																																					   \
		GOJO_STATIC_ASSERT(GojoEngine::LoggableMessage<decltype(message)>, "Message should be convertible to std::string or std::string_view!");		   \
		GOJO_STATIC_ASSERT(GojoEngine::LoggableMessage<decltype(categoryName)>, "Category should be convertible to std::string or std::string_view!");	   \
																																						   \
		GojoEngine::LogManager::GetInstance().LogMessage(	categoryName,																				   \
															GojoEngine::LogLevel::logLevel,																   \
															std::format(message, ##__VA_ARGS__)															   \
		);																																				   \
	}																																					   \
} while (0)
#endif

// ================================================================================
// Assert Log Macro
// ================================================================================

// This is called by GOJO_ASSERT in Macros.h
#ifndef GOJO_LOG_ASSERT
#define GOJO_LOG_ASSERT(expression, message, file, line) \
		GOJO_LOG("Assertions", Error, "Assertion {} Failed: {}\nSource: {}:{}", #expression, message, file, line)
#endif

// ================================================================================
// Level Macros
// ================================================================================

// Trace
#if LOG_TRACE_ENABLED == 1
	#define GOJO_LOG_TRACE(categoryName, message, ...) GOJO_LOG(categoryName, Trace, message, ##__VA_ARGS__)
#else
	#define GOJO_LOG_TRACE(categoryName, message, ...)
#endif

// Info
#if LOG_INFO_ENABLED == 1
	#define GOJO_LOG_INFO(categoryName, message, ...) GOJO_LOG(categoryName, Info, message, ##__VA_ARGS__)
#else
	#define GOJO_LOG_INFO(categoryName, message, ...)
#endif

// Debug
#if LOG_DEBUG_ENABLED == 1
	#define GOJO_LOG_DEBUG(categoryName, message, ...) GOJO_LOG(categoryName, Debug, message, ##__VA_ARGS__)
#else
	#define GOJO_LOG_DEBUG(categoryName, message, ...)
#endif

// Warning
#if LOG_WARNING_ENABLED == 1
	#define GOJO_LOG_WARNING(categoryName, message, ...) GOJO_LOG(categoryName, Warning, message, ##__VA_ARGS__)
#else
	#define GOJO_LOG_WARNING(categoryName, message, ...)
#endif

// Error
#if LOG_ERROR_ENABLED == 1
	#define GOJO_LOG_ERROR(categoryName, message, ...) GOJO_LOG(categoryName, Error, message, ##__VA_ARGS__)
#else
	#define GOJO_LOG_ERROR(categoryName, message, ...)
#endif

// Fatal
#if LOG_FATAL_ENABLED == 1
	#define GOJO_LOG_FATAL(categoryName, message, ...) GOJO_LOG(categoryName, Fatal, message, ##__VA_ARGS__)
#else
	#define GOJO_LOG_FATAL(categoryName, message, ...)
#endif