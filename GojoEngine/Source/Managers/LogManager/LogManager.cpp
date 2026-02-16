#include "Managers/LogManager/LogManager.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GojoEngine
{
	namespace
	{
		// Mapping Gojo LogLevel to spdlog level
		const std::unordered_map<LogLevel, spdlog::level::level_enum> levelMap =
		{
			{LogLevel::NoLogging,	spdlog::level::off},
			{LogLevel::Trace,		spdlog::level::trace},
			{LogLevel::Info,		spdlog::level::info},
			{LogLevel::Debug,		spdlog::level::debug},
			{LogLevel::Warning,		spdlog::level::warn},
			{LogLevel::Error,		spdlog::level::err},
			{LogLevel::Fatal,		spdlog::level::critical}
		};

		constexpr const char* clogPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
	}

	// ================================================================================
	// LogManager Implementation (PIMPL)
	// ================================================================================
	class LogManager::Impl
	{
	public:
		Impl() = default;
		~Impl() = default;

		void StartUp()
		{
			// Create a color sink
			auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			consoleSink->set_level(spdlog::level::trace);

			// Create a console logger
			mConsoleLogger = std::make_unique<spdlog::logger>("console", consoleSink);
			mConsoleLogger->set_level(spdlog::level::trace);
			mConsoleLogger->set_pattern(clogPattern);
		}

		void ShutDown()
		{
			if (mConsoleLogger)
			{
				mConsoleLogger->flush();
				mConsoleLogger.reset();
			}
			spdlog::shutdown();
		}

		void LogMessage(std::string_view categoryName, LogLevel logLevel, std::string_view message) const
		{
			// If no logging - return
			if (logLevel == LogLevel::NoLogging || !mConsoleLogger)
				return;

			// Find corresponding spdlog level
			const auto it = levelMap.find(logLevel);
			if (it == levelMap.end())
				return;

			// Log
			mConsoleLogger->log(it->second, "[{}] {}", categoryName, message);

			if (logLevel == LogLevel::Fatal)
			{
				// Flush before breaking to ensure the message is visible
				mConsoleLogger->flush();
#ifdef GOJO_DEBUG_BUILD
				GojoDebugBreak();
#endif
			}
		}

	private:
		std::unique_ptr<spdlog::logger> mConsoleLogger;
	};

	// ================================================================================
	// LogManager Interface
	// ================================================================================
	LogManager::LogManager()
		: pImpl(std::make_unique<LogManager::Impl>())
	{
	}

	LogManager::~LogManager()
	{
	}

	void LogManager::StartUp()
	{
		pImpl->StartUp();
	}

	void LogManager::ShutDown()
	{
		pImpl->ShutDown();
	}

	void LogManager::LogMessage(std::string_view categoryName, LogLevel logLevel, std::string_view message) const
	{
		pImpl->LogMessage(categoryName, logLevel, message);
	}

}