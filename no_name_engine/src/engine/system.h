#pragma once

namespace nn {

class Scene;

// Base class for all systems in the engine

/*
 * This class is the base class for all the engine system.
 * This class contains the logic to maintain the engine decoupled and running
 * in every system. This is good because every system will be auto contained
 * and, in the future, the engine will manage the system by events instead of
 * couple them in a single class.
 *
 * TODO(rafael): think a better way in the future to implement some priorities
 * to the system. This will be useful to define a execution order to avoid race
 * possible race conditions.
 */

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