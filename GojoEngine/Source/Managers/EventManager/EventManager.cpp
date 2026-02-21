#include "Managers/EventManager/EventManager.h"
#include "Managers/LogManager/LogManager.h" 

#include <unordered_map>
#include <vector>

namespace GojoEngine
{
	// ====================================================================================================
	// EventManager Implementation (PIMPL)
	// ====================================================================================================

	class EventManager::Impl
	{
	public:
		// @brief Internal implementation to add a listener.
		void AddListener(const EventType& eventType, std::unique_ptr<IEventCallback>&& callback)
		{
			GOJO_ASSERT_MESSAGE(callback, "Cannot add null listener!");

			// Store the callback in the list associated with the event type
			mListeners[eventType].emplace_back(std::move(callback));

			GOJO_LOG_DEBUG("EventManager", "Listener added");
		}

		// @brief Internal implementation to dispatch events immediately.
		void DispatchEvent(const Event& event) const
		{
			auto it = mListeners.find(event.GetType());
			if (it != mListeners.end())
			{
				for (const auto& callback : it->second)
				{
					if (callback)
					{
						callback->Execute(event);
					}
					else
					{
						GOJO_LOG_ERROR("EventManager", "Encountered null callback during dispatch!");
					}
				}
			}
			else
			{
				GOJO_LOG_WARNING("EventManager", "No listeners found");
			}
		}

		// @brief Internal implementation to enqueue events.
		void EnqueueEvent(std::unique_ptr<Event>&& event)
		{
			GOJO_ASSERT_MESSAGE(event, "Cannot enqueue null event!");
			mEventQueue.emplace_back(std::move(event));
		}

		// @brief Internal implementation to process the queue.
		void DispatchEventsInQueue()
		{
			if (mEventQueue.empty())
				return;

			// Iterate through the queue and dispatch each event
			for (const auto& eventPtr : mEventQueue)
			{
				GOJO_ASSERT(eventPtr != nullptr);
				DispatchEvent(*eventPtr);
			}

			// Clear the queue after processing
			mEventQueue.clear();
		}

	private:
		std::unordered_map<EventType, std::vector<std::unique_ptr<IEventCallback>>> mListeners;
		std::vector<std::unique_ptr<Event>> mEventQueue;
	};

	// ====================================================================================================
	// EventManager Public API
	// ====================================================================================================

	EventManager::EventManager()
		: pImpl(std::make_unique<Impl>())
	{
		// PIMPL initialized
	}

	EventManager::~EventManager()
	{
		GOJO_LOG_INFO("EventManager", "EventManager ShutDown complete!");
	}

	void EventManager::AddListener(const EventType& eventType, std::unique_ptr<IEventCallback>&& callback)
	{
		pImpl->AddListener(eventType, std::move(callback));
	}

	void EventManager::DispatchEvent(const Event& event)
	{
		pImpl->DispatchEvent(event);
	}

	void EventManager::EnqueueEvent(std::unique_ptr<Event>&& event)
	{
		pImpl->EnqueueEvent(std::move(event));
	}

	void EventManager::DispatchEventsInQueue()
	{
		pImpl->DispatchEventsInQueue();
	}
}