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

template <typename TComponent, typename... TArgs>
void Register::addComponent(const Entity& entity, TArgs&&... args) {
  const int componentId = Component<TComponent>::getId();
  const int entityId = entity.getId();

  if (componentId >= static_cast<int>(componentsPool.size())) {
    componentsPool.resize(componentId + 10, nullptr);
  }

  if (!componentsPool[componentId]) {
    componentsPool[componentId] = std::make_shared<Pool<TComponent>>();
  }

  std::shared_ptr<Pool<TComponent>> componentPool =
      std::static_pointer_cast<Pool<TComponent>>(componentsPool[componentId]);

  if (entityId >= componentPool->getSize()) {
    componentPool->resize(entityId + 100);
  }

  TComponent newComponent(std::forward<TArgs>(args)...);

  componentPool->set(entityId, newComponent);
  entityComponentSignatures[entityId].set(componentId);
}