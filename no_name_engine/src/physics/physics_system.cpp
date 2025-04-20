#include "physics_system.h"
#include "../engine/node.h"
#include "../scene/scene.h"

namespace nn {

PhysicsSystem::PhysicsSystem(filament::Engine *engine, Scene *scene)
    : System(scene) {
  collisionConfig_ = new btDefaultCollisionConfiguration();
  dispatcher_ = new btCollisionDispatcher(collisionConfig_);
  broadphase_ = new btDbvtBroadphase();
  solver_ = new btSequentialImpulseConstraintSolver();
  dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_,
                                               solver_, collisionConfig_);
}

PhysicsSystem::~PhysicsSystem() {
  delete dynamicsWorld_;
  delete solver_;
  delete broadphase_;
  delete dispatcher_;
  delete collisionConfig_;
}

void PhysicsSystem::OnUpdate(float dt) {
  dynamicsWorld_->stepSimulation(dt);
  // TODO: synchronize btRigidBody transforms back to Node's TransformComponent
  // for each node in scene_->GetAllNodesWith<PhysicsComponent>() ...
}

} // namespace nn
