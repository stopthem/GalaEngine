#pragma once
#include <memory>
#include <typeindex>
#include <map>
#include <list>
#include "../Events/CollisionEvent.h"

class Event;

namespace gala
{
    /*
 * IEventCallback
 *
 * A wrapper around EventCallback class.
 */
    class IEventCallback
    {
    public:
        virtual ~IEventCallback() = default;

    public:
        void Execute(Event& e)
        {
            Call(e);
        }

    private:
        virtual void Call(Event& e) = 0;
    };

    /*
 * EventCallback
 *
 * The actual event that calls the given function pointer.
 */
    template <typename TOwner, typename TEventCallback>
    class EventCallback : public IEventCallback
    {
    private:
        typedef void (TOwner::*CallbackFunction)(TEventCallback&);
        TOwner* OwnerInstance = nullptr;
        CallbackFunction StoredCallbackFunction;

        void Call(Event& e) override
        {
            std::invoke(StoredCallbackFunction, OwnerInstance, static_cast<TEventCallback&>(e));
        }

    public:
        EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction)
            : OwnerInstance(ownerInstance), StoredCallbackFunction(callbackFunction)
        {
        }

        ~EventCallback() override = default;
    };

    typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

    /*
 * EventBus
 *
 * "Event Manager" so to say.
 * Handles all about subscribing to a event to broadcasting to unsubscribing.
 */
    class EventBus
    {
    public:
        EventBus() = default;
        ~EventBus() = default;

    public:
        // Broadcast an event of type TEvent to all subscribes.
        template <typename TEvent, typename... TEventArgs>
        void BroadcastEvent(TEventArgs... eventArgs);

        // Subscribe to an event of type TEvent.
        template <typename TEvent, typename TOwner>
        void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&));

        // Subscribe to an event of type TEvent.
        template <typename TEvent, typename TOwner>
        void UnSubscribeFromEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&));

    private:
        std::map<std::type_index, std::unique_ptr<HandlerList>> EventsAndSubscribers;

        // A vector of subscribers to erase.
        // We hold this because we want to erase inside iterators to prevent errors.
        std::vector<std::type_index> SubscribersToBeErased;
    };

    template <typename TEvent, typename... TEventArgs>
    void EventBus::BroadcastEvent(TEventArgs... eventArgs)
    {
        const auto handlers = EventsAndSubscribers[typeid(TEvent)].get();

        if (!handlers)
        {
            return;
        }

        for (auto i = handlers->begin(); i != handlers->end();)
        {
            // Get pointer to the actual handler.
            auto handler = i->get();

            // Create event object with given args.
            TEvent event(std::forward<TEventArgs>(eventArgs)...);

            handler->Execute(event);

            // Try to find if current iterator element is wanted to be erased(unsubscribe) from the list. 
            auto foundSubToErase = std::find_if(SubscribersToBeErased.begin(), SubscribersToBeErased.end(), [&](const std::type_index& typeIndex)
            {
                return typeIndex == typeid(*handler);
            });
            if (foundSubToErase != SubscribersToBeErased.end())
            {
                // We have to equal iterator to erase in both cases. if we don't we get a error because
                // iterator will be referring to a invalid element.

                i = handlers->erase(i);
                foundSubToErase = SubscribersToBeErased.erase(foundSubToErase);
            }
            else
            {
                ++i;
            }
        }
    }

    template <typename TEvent, typename TOwner>
    void EventBus::SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&))
    {
        auto& callbacksList = EventsAndSubscribers[typeid(TEvent)];

        if (!callbacksList.get())
        {
            callbacksList = std::make_unique<HandlerList>();
        }

        // Create the subscriber.
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        // "Move" subscriber ownership to the added list element.
        callbacksList->push_back(std::move(subscriber));
    }

    template <typename TEvent, typename TOwner>
    void EventBus::UnSubscribeFromEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&))
    {
        const auto callbacksList = EventsAndSubscribers[typeid(TEvent)].get();
        if (!callbacksList)
        {
            return;
        }

        // Find the subscriber based on their typeids.
        auto subscriber = std::find_if(callbacksList->begin(), callbacksList->end(), [&](const std::unique_ptr<IEventCallback>& eventCallback)
        {
            return typeid(*eventCallback) == typeid(EventCallback<TOwner, TEvent>(ownerInstance, callbackFunction));
        });

        // Is iterator is valid ?
        if (subscriber == callbacksList->end())
        {
            return;
        }

        // Add it to the vector because if we erase it here, ongoing iterators will throw errors.
        SubscribersToBeErased.push_back(typeid(*subscriber->get()));
    }
}
