#pragma once
#include "Core/Macros.h"
#include "Managers/Manager.h"
#include "Managers/EventManager/Events/Event.h"
#include "Managers/WindowManager/WindowManager.h"
#include <functional>
#include <memory>
#include <type_traits>
#include <concepts>

namespace GojoEngine
{
	// ====================================================================================================
	// Concepts
	// ====================================================================================================
	
	// @brief Ensures the type is derived from the base Event class.
	template<typename T>
	concept DerivedFromEvent = std::derived_from<T, Event>;

	// @brief Ensures the type is a valid event (derived from Event and copy constructible for queueing).
	template<typename T>
	concept ValidEvent = DerivedFromEvent<T> && std::copy_constructible<T>;

	// ====================================================================================================
	// Type Definitions & Interfaces
	// ====================================================================================================

	template<typename EventT>
	using EventCallback = std::function<void(const EventT&)>;

	// @brief Interface for type-erased event callbacks.
	class IEventCallback
	{
	public:
		virtual ~IEventCallback() = default;
		virtual void Execute(const Event& event) const = 0;
	};

	// @brief Type-safe wrapper that casts the generic Event back to the specific EventT.
	template<typename EventT>
	class EventCallbackWrapper final : public IEventCallback
	{
	public:
		explicit EventCallbackWrapper(EventCallback<EventT> callback)
			: mEventCallback(std::move(callback)) {}

		void Execute(const Event& event) const override
		{
			// Verify type safety
			if (EventT::GetStaticType() == event.GetType())
			{
				mEventCallback(static_cast<const EventT&>(event));
			}
		}

	private:
		EventCallback<EventT> mEventCallback;
	};

	// ====================================================================================================
	// Event Manager
	// ====================================================================================================

	class GOJO_API EventManager final : public Manager<EventManager>
	{
		friend class Manager<EventManager>;

	public:
		// @brief Registers a listener for a specific event type.
		// @param eventType The type ID of the event.
		// @param callback Unique pointer to the callback interface (ownership transfer).
		void AddListener(const EventType& eventType, std::unique_ptr<IEventCallback>&& callback);

		// @brief Immediately dispatches an event to all registered listeners.
		// @param event The event instance to dispatch.
		void DispatchEvent(const Event& event);

		// @brief Adds an event to the queue for later processing.
		// @param event Unique pointer to the event (ownership transfer).
		void EnqueueEvent(std::unique_ptr<Event>&& event);

		// @brief Processes all events currently in the queue.
		void DispatchEventsInQueue();

	private:
		EventManager();
		~EventManager();

	private:
		// PIMPL idiom to hide implementation details and STL containers
		class Impl;
		std::unique_ptr<Impl> pImpl;
	};

	// ====================================================================================================
	// Global Helper Templates (Wrappers)
	// ====================================================================================================

	// @brief Global helper to easily register a lambda or function as an event listener.
	//        Automatically handles type deduction and wrapper creation.
	// @tparam EventT The specific Event type to listen for.
	// @param eventCallback The function to call when the event triggers.
	template<typename EventT>
		requires DerivedFromEvent<EventT>
	inline void AddListener(const EventCallback<EventT>& eventCallback)
	{
		GOJO_ASSERT_MESSAGE(eventCallback, "Attempting to add an empty event callback!");

		EventManager::GetInstance().AddListener(
			EventT::GetStaticType(),
			std::make_unique<EventCallbackWrapper<EventT>>(eventCallback)
		);
	}

	// @brief Concept to check if an Event type has a GetWindowId() method.
	template<typename T>
	concept HasWindowId = requires(T t)
	{
		{ t.GetWindowId() } -> std::same_as<WindowId>;
	};

	// @brief Global helper to register a listener for a specific Window ID.
	//        The callback will only execute if the event's WindowId matches the target.
	//        Useful for multi-window applications to filter events.
	// @tparam EventT The specific Event type (Must have GetWindowId()).
	// @param targetWindowId The specific Window ID to listen to.
	// @param callback The function to call.
	template<typename EventT>
		requires DerivedFromEvent<EventT> && HasWindowId<EventT>
	inline void AddWindowListener(WindowId targetWindowId, const EventCallback<EventT>& callback)
	{
		// Wrap the callback in a lambda that checks the Window ID first
		AddListener<EventT>(
			[targetWindowId, callback](const EventT& event)
			{
				if (targetWindowId == event.GetWindowId())
				{
					callback(event);
				}
			}
		);
	}

	// @brief Global helper to dispatch an event immediately (blocking).
	// @param event The event object.
	inline void DispatchEvent(const Event& event)
	{
		EventManager::GetInstance().DispatchEvent(event);
	}

	// @brief Global helper to enqueue an event for later processing (non-blocking).
	//        Creates a copy of the event on the heap.
	// @tparam EventT The type of event.
	// @param event The event object to copy and queue.
	template<typename EventT>
		requires ValidEvent<EventT>
	inline void EnqueueEvent(const EventT& event)
	{
		EventManager::GetInstance().EnqueueEvent(std::make_unique<EventT>(event));
	}

	// @brief Global helper to process all queued events.
	//        Should be called once per frame (e.g., in the Application loop).
	inline void DispatchEventsInQueue()
	{
		EventManager::GetInstance().DispatchEventsInQueue();
	}
}