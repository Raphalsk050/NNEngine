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

/*
 * TODO(rafael): Think a way to wrapper the filament framework here to maintain
 * a good render efficiency for different configurations. This class will grow
 * so fast because is the main system of the engine, we have to take care about
 * the optimization in the future too, not now.
 */

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
