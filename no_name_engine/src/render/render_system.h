#pragma once

#include "render_component.h"

#include "../engine/system.h"
#include "../scene/scene.h"
#include <filament/Engine.h>
#include <filament/Renderer.h>
#include <filament/Scene.h>
#include <filament/View.h>
#include <vector>

namespace nn {

// System responsible for submitting renderables to Filament
class RenderSystem : public System {
public:
  RenderSystem(filament::Engine *engine, Scene *scene);
  ~RenderSystem() override;

  void OnUpdate(float dt) override;
  void OnRender();

private:
  filament::Engine *engine_;
  filament::Renderer *renderer_;
  filament::Scene *filamentScene_;
  filament::View *view_;
};

} // namespace nn
