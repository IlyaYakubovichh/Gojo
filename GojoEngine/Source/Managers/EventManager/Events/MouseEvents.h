#pragma once
#include "Managers/EventManager/Events/Event.h"
#include "Managers/WindowManager/WindowManager.h"

namespace GojoEngine
{
	// ====================================================================================================
	// Mouse Events
	// ====================================================================================================
	// @brief Triggered when the mouse cursor moves.
	class GOJO_API MouseMovedEvent final : public Event
	{
	public:
		explicit MouseMovedEvent(WindowId id, float x, float y)
			: mWindowId(id), mMouseX(x), mMouseY(y) {}

		[[nodiscard]] float GetX() const { return mMouseX; }
		[[nodiscard]] float GetY() const { return mMouseY; }
		[[nodiscard]] WindowId GetWindowId() const { return mWindowId; }

		EVENT_TYPE(MouseMoved, "MouseMoved: ID[{}] Pos[{}, {}]", mWindowId.mId, mMouseX, mMouseY);

	private:
		WindowId mWindowId;
		float mMouseX{ 0.f }, mMouseY{ 0.f };
	};


	// @brief Triggered when the mouse wheel is scrolled.
	class GOJO_API MouseScrolledEvent final : public Event
	{
	public:
		explicit MouseScrolledEvent(WindowId id, float xOffset, float yOffset)
			: mWindowId(id), mXOffset(xOffset), mYOffset(yOffset) {}

		[[nodiscard]] float GetXOffset() const { return mXOffset; }
		[[nodiscard]] float GetYOffset() const { return mYOffset; }
		[[nodiscard]] WindowId GetWindowId() const { return mWindowId; }

		EVENT_TYPE(MouseScrolled, "MouseScrolled: ID[{}] Offset[{}, {}]", mWindowId.mId, mXOffset, mYOffset);

	private:
		WindowId mWindowId;
		float mXOffset{ 0.f }, mYOffset{ 0.f };
	};


	// @brief Base class for mouse button events.
	class GOJO_API MouseButtonEvent : public Event
	{
	public:
		[[nodiscard]] int GetButton() const { return mButton; }
		[[nodiscard]] WindowId GetWindowId() const { return mWindowId; }

	protected:
		explicit MouseButtonEvent(WindowId id, int button)
			: mWindowId(id), mButton(button) {}

		WindowId mWindowId;
		int mButton{ 0 };
	};


	// @brief Triggered when a mouse button is pressed.
	class GOJO_API MouseButtonPressedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressedEvent(WindowId id, int button)
			: MouseButtonEvent(id, button) {}

		EVENT_TYPE(MouseButtonPressed, "MouseButtonPressed: ID[{}] Button[{}]", mWindowId.mId, mButton);
	};


	// @brief Triggered when a mouse button is released.
	class GOJO_API MouseButtonReleasedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonReleasedEvent(WindowId id, int button)
			: MouseButtonEvent(id, button) {}

		EVENT_TYPE(MouseButtonReleased, "MouseButtonReleased: ID[{}] Button[{}]", mWindowId.mId, mButton);
	};
}