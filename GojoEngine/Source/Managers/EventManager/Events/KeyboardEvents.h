#pragma once

#include "Managers/EventManager/Events/Event.h"
#include "Managers/WindowManager/WindowManager.h"

namespace GojoEngine
{
	// ====================================================================================================
	// Key Events
	// ====================================================================================================
	// @brief Base class for keyboard events.
	class GOJO_API KeyEvent : public Event
	{
	public:
		[[nodiscard]] int GetKeyCode() const { return mKeyCode; }

		// @brief Returns the ID of the window where the key event occurred.
		[[nodiscard]] WindowId GetWindowId() const { return mWindowId; }

	protected:
		explicit KeyEvent(WindowId id, int keyCode)
			: mWindowId(id), mKeyCode(keyCode) {}

		WindowId mWindowId;
		int mKeyCode{ 0 };
	};


	// @brief Triggered when a keyboard key is released.
	class GOJO_API KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(WindowId id, int keyCode) : KeyEvent(id, keyCode) {}
		EVENT_TYPE(KeyReleased, "KeyReleased: ID[{}] Key[{}]", mWindowId.mId, mKeyCode);
	};


	// @brief Triggered when a keyboard key is pressed.
	class GOJO_API KeyPressedEvent final : public KeyEvent
	{
	public:
		explicit KeyPressedEvent(WindowId id, int keyCode) : KeyEvent(id, keyCode) {}
		EVENT_TYPE(KeyPressed, "KeyPressed: ID[{}] Key[{}]", mWindowId.mId, mKeyCode);
	};


	// @brief Triggered when a character is typed (useful for text input).
	class GOJO_API KeyTypedEvent final : public KeyEvent
	{
	public:
		explicit KeyTypedEvent(WindowId id, int keyCode) : KeyEvent(id, keyCode) {}
		EVENT_TYPE(KeyTyped, "KeyTyped: ID[{}] Key[{}]", mWindowId.mId, mKeyCode);
	};
}