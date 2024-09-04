#include "ecs.hpp"

#include <algorithm>

#include "../utils/debug.hpp"

int IComponent::nextId = 0;

int Entity::getId() const { return id; }

// System methods
void System::addEntityFromSystem(const Entity& entity) {
  entities.push_back(entity);
}
void System::removeEntityFromSystem(const Entity& entity) {
  auto it = std::remove_if(
      entities.begin(), entities.end(),
      [&entity](const Entity& other) { return entity == other; });
  entities.erase(it, entities.end());
}

std::vector<Entity>& System::getEntities() { return entities; }

const signature& System::getComponentSignature() const {
  return componentSignature;
}

// Register methods
Register::Register() : numEntities(0) {
  DEBUG_MSG("[Register] Register created");
};

Register::~Register() { DEBUG_MSG("[Register] Register destroyed"); }

Entity Register::createEntity() {
  int entityId = ++numEntities;
  if (entityId >= static_cast<int>(entityComponentSignatures.size())) {
    entityComponentSignatures.resize(entityId + 100);
  }
  Entity entity(entityId);
  entitiesToBeAdded.insert(entity);

  DEBUG_MSG("[Register] Entity created with id: " + std::to_string(entityId));
  return entity;
}

void Register::destroyEntity(const Entity& entity) {
  entitiesToBeRemoved.insert(entity);
}
