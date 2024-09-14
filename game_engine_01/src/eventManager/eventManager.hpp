#ifndef EVENT_MANAGER_HPP
#define EVENT_MANAGER_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>

#include "../utils/debug.hpp"
#include "event.hpp"

/**
 * @class IEventCallback
 * @brief Interface for event callbacks
 */
class IEventCallback {
 private:
  /**
   * @brief Call the callback
   * @param event Event to pass to the callback
   */
  virtual void call(Event& event) = 0;

 public:
  /**
   * @brief Destructor
   */
  virtual ~IEventCallback() = default;

  /**
   * @brief Execute the callback
   * @param event Event to pass to the callback
   */
  void execute(Event& event) { call(event); }
};

/**
 * @class EventCallback
 * @brief This class is for creating event callbacks
 * @tparam TOwner Owner of the callback (e.g: DamageSystem)
 * @tparam TEvent Event type (e.g: a collision event)
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
 private:
  TOwner* ownerInstance;  // Owner of the callback

  /**
   * @brief Callback function
   * @param TOwner Owner of the callback
   * @param TEvent Event to pass to the callback
   */
  typedef void (TOwner::*CallbackFunction)(TEvent&);

  CallbackFunction callbackFunction;  // Callback function

  /**
   * @brief Invoke or execute the callback function
   * @param event Event to pass to the callback
   */
  virtual void call(Event& event) override {
    // Cast the event to the correct type
    TEvent& castedEvent = static_cast<TEvent&>(event);

    std::invoke(callbackFunction, ownerInstance, castedEvent);
  }

 public:
  /**
   * @brief Constructor
   * @param ownerInstance Owner of the callback
   * @param callbackFunction Callback function
   */
  EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction)
      : ownerInstance(ownerInstance), callbackFunction(callbackFunction) {}
};

// typedef of List of event callbacks
typedef std::list<std::unique_ptr<IEventCallback>> handlerList;

/**
 * @class EventManager
 * @brief Manages events and their subscribers
 */
class EventManager {
 private:
  // Map of subscribers(type_index is the event type, handlerList is the list of
  // callbacks)
  std::map<std::type_index, std::unique_ptr<handlerList>> subscribers;

 public:
  EventManager() {
    // Debug message
    DEBUG_MSG("[EventManager] Constructor called");
  }

  /**
   * @brief Destructor
   */
  ~EventManager() {
    // Debug message
    DEBUG_MSG("[EventManager] Destructor called");
  }

  void reset() { subscribers.clear(); }

  /**
   * @brief Subscribe to an event
   * @tparam TEvent Event type
   * @tparam TOwner Owner of the callback
   * @param ownerInstance Owner of the callback
   * @param callbackFunction Callback function
   */
  template <typename TEvent, typename TOwner>
  void subscribeToEvent(TOwner* ownerInstance,
                        void (TOwner::*callbackFunction)(TEvent&)) {
    // Get the type of the event
    std::type_index eventType = typeid(TEvent);

    // Create a new event callback
    auto callback = std::make_unique<EventCallback<TOwner, TEvent>>(
        ownerInstance, callbackFunction);

    if (!subscribers[typeid(TEvent)].get()) {
      // Add the callback to the list of subscribers
      subscribers[typeid(TEvent)] = std::make_unique<handlerList>();
    }
    auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(
        ownerInstance, callbackFunction);
    subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
  }

  /**
   * @brief Emit an event
   * @tparam TEvent Event type
   * @tparam TArgs Arguments of the event
   * @param args Arguments of the event
   * @details This function emits an event to all subscribers of that event
   *
   */
  template <typename TEvent, typename... TArgs>
  void emitEvent(TArgs&&... args) {
    // get the list of handlers that are subscribed to the event
    auto handlers = subscribers[typeid(TEvent)].get();

    // if there are handlers
    if (handlers) {
      // iterate over the handlers(subscribers), get the callback fn
      // and execute it
      for (auto it = handlers->begin(); it != handlers->end(); ++it) {
        auto handler = it->get();
        TEvent event(std::forward<TArgs>(args)...);
        handler->execute(event);
      }
    }
  }
};

#endif  // EVENT_MANAGER_HPP