#pragma once

#include "connection.h"
#include "event.h"
#include <functional>
#include <vector>

namespace nn {

class Node;
using EventType = uint32_t;
using EventCallback = std::function<void(Event &)>;

/*
 * Usage example:
 * Subscribe to an event with a lambda callback:
 * Connection conn = dispatcher.Connect(node, 0, [](Event& e){
 *  dumb code here
 *  e.StopPropagation(); // this is a optional method to stop the propagation
 *  here instead of keeping this alive in the system
 * });
 * dispatcher.Disconnect(conn);
 * Refer to the event sample to see a functional example :)
 */

/*
 * TODO(rafael): Think a better way to put these events in a queue to trigger
 * then instead of stop the application to run an event or to notify an event.
 * Maybe a event buffer approach is the best option
 */

class Dispatcher {
public:
  Dispatcher() = default;
  ~Dispatcher() = default;

  // Subscribe to an event type on a specific node
  Connection Connect(Node *node, EventType type, EventCallback callback);

  // Unsubscribe using Connection
  void Disconnect(const Connection &conn);

  // Dispatch event to handlers on the target node
  void Dispatch(Node *target, EventType type, Event &event);

private:
  struct HandlerEntry {
    Node *node;
    EventType type;
    ConnectionId id;
    EventCallback callback;
  };

  std::vector<HandlerEntry> handlers_;
  ConnectionId nextId_ = 1;
};

} // namespace nn
