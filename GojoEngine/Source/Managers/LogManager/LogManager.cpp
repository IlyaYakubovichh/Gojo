#include "LogManager.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GojoEngine
{
	// ====================================================================================================
	// Internal Helpers
	// ====================================================================================================
	namespace
	{
		spdlog::level::level_enum ToSpdLogLvl(LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Trace:   return spdlog::level::trace;
			case LogLevel::Info:    return spdlog::level::info;
			case LogLevel::Debug:   return spdlog::level::debug;
			case LogLevel::Warning: return spdlog::level::warn;
			case LogLevel::Error:   return spdlog::level::err;
			case LogLevel::Fatal:   return spdlog::level::critical;
			case LogLevel::Off:     return spdlog::level::off;
			}
			return spdlog::level::off;
		}

		constexpr const char* cLogPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
	}

	// ====================================================================================================
	// LogManager Implementation (PIMPL)
	// ====================================================================================================

	class LogManager::Impl
	{
	public:
		Impl()
		{
			auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
			consoleSink->set_pattern(cLogPattern);

			mConsoleLogger = std::make_shared<spdlog::logger>("GojoConsole", consoleSink);
			mConsoleLogger->set_level(spdlog::level::trace);
			mConsoleLogger->set_pattern(cLogPattern);
		}

		~Impl()
		{
			if (mConsoleLogger)
			{
				mConsoleLogger->flush();
				mConsoleLogger.reset();
			}
			spdlog::shutdown();
		}

		void LogMessage(std::string_view categoryName, LogLevel level, std::string_view message) const
		{
			if (!mConsoleLogger) return;

			const auto spdLevel = ToSpdLogLvl(level);
			mConsoleLogger->log(spdLevel, "[{}] {}", categoryName, message);

			if (level == LogLevel::Fatal)
			{
				mConsoleLogger->flush();
#ifdef GOJO_DEBUG_BUILD
				GojoDebugBreak();
#endif
			}
		}

	private:
		std::shared_ptr<spdlog::logger> mConsoleLogger;
	};

	// ====================================================================================================
	// LogManager Public API
	// ====================================================================================================

	LogManager::LogManager()
		: mImpl(std::make_unique<Impl>())
	{
	}

	LogManager::~LogManager()
	{
		GOJO_LOG_INFO("LogManager", "ShutDown complete!");
	}

	void LogManager::LogMessage(std::string_view categoryName, LogLevel level, std::string_view message) const
	{
		mImpl->LogMessage(categoryName, level, message);
	}
}