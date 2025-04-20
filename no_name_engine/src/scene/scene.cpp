#include "scene.h"
#include "../physics/physics_system.h"
#include "../render/render_system.h"

namespace nn {

Scene::Scene(filament::Engine *engine) : engine_(engine) {
  physicsSystem_ = std::make_unique<PhysicsSystem>(engine_, this);
  renderSystem_ = std::make_unique<RenderSystem>(engine_, this);
}

std::shared_ptr<Node> Scene::CreateNode() {
  auto node = std::make_shared<Node>(engine_, this);
  nodes_.push_back(node);
  return node;
}

void Scene::Update(float dt) {
  physicsSystem_->OnUpdate(dt);
  renderSystem_->OnUpdate(dt);
}

void Scene::Render() { renderSystem_->OnRender(); }

} // namespace nn