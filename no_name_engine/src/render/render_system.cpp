#include "render_system.h"

#include "../engine/node.h"
#include "render_component.h"

namespace nn {

RenderSystem::RenderSystem(filament::Engine *engine, Scene *scene)
    : System(scene), engine_(engine) {
  // Create renderer, scene and view instances
  renderer_ = engine_->createRenderer();
  filamentScene_ = engine_->createScene();
  view_ = engine_->createView();
  view_->setScene(filamentScene_);
  // TODO: configure camera from CameraComponent if present
}

RenderSystem::~RenderSystem() {
  engine_->destroy(view_);
  engine_->destroy(filamentScene_);
  engine_->destroy(renderer_);
}

void RenderSystem::OnUpdate(float /*dt*/) {
  // Nothing to update per-frame before render
}

void RenderSystem::OnRender() {
  // Submit all render components to scene
  for (auto &nodePtr : scene_->GetAllNodes()) {
    auto rc = nodePtr->GetComponent<RenderComponent>();
    if (rc) {
      // attach each entity to filamentScene_
      filamentScene_->addEntity(rc->GetEntity());
    }
  }
  // Execute render pass
  renderer_->render(view_);
}

} // namespace nn
