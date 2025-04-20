#pragma once

#include "connection.h"
#include "event.h"
#include <functional>
#include <vector>

namespace nn {

class Node;
using EventType = uint32_t;
using EventCallback = std::function<void(Event &)>;

// Usage example:
// // Subscribe to an event with a lambda callback
// Connection conn = dispatcher.Connect(node, EVENT_TYPE, [](Event& e) {
//     // Your handling code here
//     e.StopPropagation(); // optional: stop further propagation
// });
// // Unsubscribe from the event
// dispatcher.Disconnect(conn);

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
