#pragma once

#include "Core/Macros.h"

#include <string>
#include <format>

namespace GojoEngine
{
	// ====================================================================================================
	// Event Types
	// ====================================================================================================

	enum class GOJO_API EventType
	{
		None = 0,
		KeyReleased, KeyPressed, KeyTyped,										// Keyboard
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,		// Mouse
		WindowClose, WindowResize, WindowMoved, WindowFocus, WindowLostFocus	// Window
	};

	// ====================================================================================================
	// Event Interface
	// ====================================================================================================

	class GOJO_API Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		[[nodiscard]] virtual std::string ToString() const = 0;
		[[nodiscard]] virtual EventType GetType() const = 0;
	};

}

// ====================================================================================================
// Event Generation Macros
// ====================================================================================================

#define EVENT_TYPE(eventType, toStringFormat, ...)						\
	static EventType GetStaticType()									\
	{																	\
		return EventType::eventType;									\
	}																	\
																		\
	virtual EventType GetType() const override							\
	{																	\
		return GetStaticType();											\
	}																	\
																		\
	virtual std::string ToString() const override						\
	{																	\
		return std::format(toStringFormat, ##__VA_ARGS__);				\
	}