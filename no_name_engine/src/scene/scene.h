#pragma once

#include "../engine/node.h"
#include "../engine/system.h"
#include "../event/dispatcher.h"
#include <filament/Engine.h>
#include <memory>
#include <vector>

namespace nn {

/*
 * This class is the base class for the engine scenes. In the future, we'll have
 * a scene manager that should control how the scenes are shown and things like
 * sub-scenes, activation, deactivation
 *
 * TODO(rafael): Add some logic to control the node tree. This is mandatory.
 * Don't forget this, Rafael!
 */

class RenderSystem;
class PhysicsSystem;

class Scene {
public:
  explicit Scene(filament::Engine *engine);
  ~Scene();

  std::shared_ptr<Node> CreateNode();
  void Update(float dt);
  void Render();

  Dispatcher &GetDispatcher() { return dispatcher_; }
  const std::vector<std::shared_ptr<Node>> &GetAllNodes() const {
    return nodes_;
  }

private:
  filament::Engine *engine_;
  Dispatcher dispatcher_;
  std::vector<std::shared_ptr<Node>> nodes_;
  std::unique_ptr<PhysicsSystem> physicsSystem_;
  std::unique_ptr<RenderSystem> renderSystem_;
};

} // namespace nn
