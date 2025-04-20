#pragma once

#include "../engine/entity.h"
#include "../engine/node.h"
#include <filament/RenderableManager.h>

namespace nn {

// Component that wraps Filament RenderableManager instance
class RenderComponent {
public:
  RenderComponent(filament::Engine *engine, Entity entity,
                  filament::RenderableManager::PrimitiveType type,
                  size_t primitiveCount = 1);
  ~RenderComponent();

  // Retrieve the associated Entity for the renderable
  Entity GetEntity() const { return entity_; }

private:
  filament::RenderableManager *renderableManager_;
  filament::RenderableManager::Instance instance_;
  Entity entity_;
};

} // namespace nn
