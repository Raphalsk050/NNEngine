#pragma once

#include "../event/connection.h"
#include "../event/dispatcher.h"
#include "entity.h"
#include "node_handle.h"
#include "../scene/scene.h"

#include <filament/Engine.h>
#include <memory>
#include <typeindex>
#include <unordered_map>


namespace nn {

class Component;

// Node is a wrapper over filament::Entity allowing Components and event
// handling
class Node {
public:
  // Constructor binds Entity and Scene dispatcher
  Node(filament::Engine *engine, Scene *scene);
  ~Node();

  // Add a component of type T to this Node
  template <typename T, typename... Args>
  std::shared_ptr<T> AddComponent(Args &&...args) {
    auto comp = std::make_shared<T>(std::forward<Args>(args)...);
    comp->OnAttach(*this);
    components_[std::type_index(typeid(T))] = comp;
    return comp;
  }

  // Retrieve a component of type T if it exists
  template <typename T> std::shared_ptr<T> GetComponent() const {
    auto it = components_.find(std::type_index(typeid(T)));
    if (it != components_.end()) {
      return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
  }

  // Access the underlying Filament entity
  Entity GetEntity() const { return entity_; }

  // Obtain a stable handle to this Node
  NodeHandle GetHandle() { return NodeHandle(this); }

  // Connect a callback to an event type on this Node
  Connection ConnectEvent(EventType type, EventCallback callback) {
    return scene_->GetDispatcher().Connect(this, type, std::move(callback));
  }

  // Disconnect a previously connected event
  void DisconnectEvent(const Connection &conn) const {
    scene_->GetDispatcher().Disconnect(conn);
  }

private:
  filament::Engine *engine_;
  Scene *scene_;
  Entity entity_;
  std::unordered_map<std::type_index, std::shared_ptr<Component>> components_;
};

} // namespace nn
