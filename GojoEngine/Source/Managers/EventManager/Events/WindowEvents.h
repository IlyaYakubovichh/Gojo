#pragma once
#include "Managers/EventManager/Events/Event.h"
#include "Managers/WindowManager/WindowManager.h"

namespace GojoEngine
{
	// ====================================================================================================
	// Window Events
	// ====================================================================================================
	// @brief Base class for all window-related events.
	class WindowEvent : public Event
	{
	public:
		// @brief Returns the ID of the window that generated this event.
		[[nodiscard]] WindowId GetWindowId() const { return mWindowId; }

	protected:
		explicit WindowEvent(WindowId id) : mWindowId(id) {}

		WindowId mWindowId;
	};


	// @brief Triggered when a window is resized.
	class WindowResizeEvent : public WindowEvent
	{
	public:
		explicit WindowResizeEvent(WindowId id, int width, int height)
			: WindowEvent(id), mWidth(width), mHeight(height) {}

		[[nodiscard]] int GetWidth() const { return mWidth; }
		[[nodiscard]] int GetHeight() const { return mHeight; }

		EVENT_TYPE(WindowResize, "WindowResize: ID[{}] Size[{} - {}]", mWindowId.mId, mWidth, mHeight)

	private:
		int mWidth{ 0 }, mHeight{ 0 };
	};


	// @brief Triggered when a window is closed.
	class GOJO_API WindowCloseEvent final : public WindowEvent
	{
	public:
		explicit WindowCloseEvent(WindowId id) : WindowEvent(id) {}

		EVENT_TYPE(WindowClose, "WindowClose: ID[{}]", mWindowId.mId);
	};


	// @brief Triggered when a window gains focus.
	class GOJO_API WindowFocusEvent final : public WindowEvent
	{
	public:
		explicit WindowFocusEvent(WindowId id) : WindowEvent(id) {}

		EVENT_TYPE(WindowFocus, "WindowFocus: ID[{}]", mWindowId.mId);
	};


	// @brief Triggered when a window loses focus.
	class GOJO_API WindowLostFocusEvent final : public WindowEvent
	{
	public:
		explicit WindowLostFocusEvent(WindowId id) : WindowEvent(id) {}

		EVENT_TYPE(WindowLostFocus, "WindowLostFocus: ID[{}]", mWindowId.mId);
	};


	// @brief Triggered when a window is moved on the screen.
	class GOJO_API WindowMovedEvent final : public WindowEvent
	{
	public:
		explicit WindowMovedEvent(WindowId id, int x, int y)
			: WindowEvent(id), mX(x), mY(y) {}

		[[nodiscard]] int GetX() const { return mX; }
		[[nodiscard]] int GetY() const { return mY; }

		EVENT_TYPE(WindowMoved, "WindowMoved: ID[{}] Moved[{}, {}]", mWindowId.mId, mX, mY);

	private:
		int mX{ 0 }, mY{ 0 };
	};

}