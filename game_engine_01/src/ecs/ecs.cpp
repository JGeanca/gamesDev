#include "ecs.hpp"

#include <algorithm>

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