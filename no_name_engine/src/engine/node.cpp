#include "node.h"
#include <filament/Engine.h>
#include <utils/EntityManager.h>

namespace nn {

Node::Node(filament::Engine *engine, Scene *scene)
    : engine_(engine), scene_(scene) {
  entity_ = utils::EntityManager::get().create();
}

Node::~Node() { utils::EntityManager::get().destroy(entity_); }

} // namespace nn