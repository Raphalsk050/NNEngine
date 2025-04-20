#pragma once
#include "../engine/system.h"
#include "../scene/scene.h"
#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>

namespace nn {

// System responsible for physics simulation using Bullet
class PhysicsSystem : public System {
public:
  PhysicsSystem(filament::Engine *engine, Scene *scene);
  ~PhysicsSystem() override;

  void OnUpdate(float dt) override;

private:
  btDefaultCollisionConfiguration *collisionConfig_;
  btCollisionDispatcher *dispatcher_;
  btBroadphaseInterface *broadphase_;
  btSequentialImpulseConstraintSolver *solver_;
  btDiscreteDynamicsWorld *dynamicsWorld_;
};

} // namespace nn
