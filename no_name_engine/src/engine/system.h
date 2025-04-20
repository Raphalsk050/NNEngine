#pragma once

namespace nn {

class Scene;

// Base class for all systems in the engine
class System {
public:
  explicit System(Scene *scene) : scene_(scene) {}
  virtual ~System() = default;

  // Called every frame to update system logic
  virtual void OnUpdate(float dt) = 0;

protected:
  Scene *scene_;
};

} // namespace nn