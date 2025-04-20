#include "dispatcher.h"
#include <algorithm>

namespace nn {

Connection Dispatcher::Connect(Node *node, EventType type,
                               EventCallback callback) {
  Connection conn(nextId_++);
  handlers_.push_back({node, type, conn.GetId(), std::move(callback)});
  return conn;
}

void Dispatcher::Disconnect(const Connection &conn) {
  if (!conn.IsValid())
    return;
  handlers_.erase(std::remove_if(handlers_.begin(), handlers_.end(),
                                 [&conn](const HandlerEntry &entry) {
                                   return entry.id == conn.GetId();
                                 }),
                  handlers_.end());
}

void Dispatcher::Dispatch(Node *target, EventType type, Event &event) {
  for (auto &entry : handlers_) {
    if (entry.type == type && entry.node == target) {
      entry.callback(event);
      if (event.IsHandled())
        break;
    }
  }
}

} // namespace nn