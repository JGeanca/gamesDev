#include "ecs.hpp"

#include <algorithm>

#include "../utils/debug.hpp"

int IComponent::nextId = 0;

int Entity::getId() const { return id; }

void Entity::killEntity() { registry->destroyEntity(*this); }

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
  int entityId;

  if (freeIds.empty()) {
    entityId = numEntities++;
    if (entityId >= static_cast<int>(entityComponentSignatures.size())) {
      entityComponentSignatures.resize(entityId + 100);
    }
  } else {
    entityId = freeIds.front();
    freeIds.pop_front();
  }

  Entity entity(entityId);
  entity.registry = this;
  entitiesToBeAdded.insert(entity);

  DEBUG_MSG("[Register] Entity created with id: " + std::to_string(entityId));
  return entity;
}

void Register::destroyEntity(const Entity& entity) {
  entitiesToBeRemoved.insert(entity);
}

void Register::addEntityToSystem(const Entity& entity) {
  const int entityId = entity.getId();
  const auto& entitySignature = entityComponentSignatures[entityId];

  for (const auto& system : systems) {
    const auto& systemSignature = system.second->getComponentSignature();
    bool isInterested = (entitySignature & systemSignature) == systemSignature;
    if (isInterested) {
      system.second->addEntityFromSystem(entity);
    }
  }
}

void Register::removeEntityFromSystem(const Entity& entity) {
  for (const auto& system : systems) {
    system.second->removeEntityFromSystem(entity);
  }
}

void Register::clearAllEntities() {
  for (int i = 0; i < numEntities; i++) {
    removeEntityFromSystem(Entity(i));
    entityComponentSignatures[i].reset();
    freeIds.push_back(i);
  }
}

void Register::update() {
  for (const auto& entity : entitiesToBeAdded) {
    addEntityToSystem(entity);
  }
  entitiesToBeAdded.clear();

  for (const auto& entity : entitiesToBeRemoved) {
    removeEntityFromSystem(entity);
    entityComponentSignatures[entity.getId()].reset();

    freeIds.push_back(entity.getId());
  }
  entitiesToBeRemoved.clear();
}

bool Register::entityExists(int entityId) const {
  if (entityId < 0 || entityId >= numEntities) {
    return false;
  }

  if (std::find(freeIds.begin(), freeIds.end(), entityId) != freeIds.end()) {
    return false;
  }

  return !isEntityMarkedForRemoval(Entity(entityId));
}

bool Register::isEntityMarkedForRemoval(const Entity& entity) const {
  return entitiesToBeRemoved.find(entity) != entitiesToBeRemoved.end();
}