#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <deque>
#include <iostream>
#include <memory>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "../utils/pool.hpp"

const unsigned int MAX_COMPONENTS = 64;
typedef std::bitset<MAX_COMPONENTS> signature;

struct IComponent {
 protected:
  static int nextId;
};

// Assigns a unique id to each component type
template <typename TComponent>
class Component : public IComponent {
 public:
  static int getId() {
    static int id = ++nextId;
    return id;
  }
};

class Entity {
 private:
  int id;

 public:
  Entity(int id) : id(id) {}
  int getId() const;

  bool operator==(const Entity& other) const { return id == other.id; }
  bool operator!=(const Entity& other) const { return id != other.id; }
  bool operator<(const Entity& other) const { return id < other.id; }
  bool operator>(const Entity& other) const { return id > other.id; }

  template <typename TComponent, typename... TArgs>
  void addComponent(TArgs&&... args);

  template <typename TComponent>
  void removeComponent();

  template <typename TComponent>
  bool hasComponent() const;

  template <typename TComponent>
  TComponent& getComponent() const;

  class Register* registry;  // forward declaration and pointer
};

class System {
 private:
  signature componentSignature;
  std::vector<Entity> entities;

 public:
  System() = default;
  ~System() = default;
  void addEntityFromSystem(const Entity& entity);
  void removeEntityFromSystem(const Entity& entity);
  std::vector<Entity>& getEntities();
  const signature& getComponentSignature() const;

  template <typename TComponent>
  void requireComponent();
};

template <typename TComponent>
void System::requireComponent() {
  const int componentId = Component<TComponent>::getId();
  componentSignature.set(componentId);
}

class Register {
 private:
  int numEntities;
  std::vector<std::shared_ptr<IPool>> componentsPool;
  std::vector<signature> entityComponentSignatures;

  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

  std::set<Entity> entitiesToBeAdded;
  std::set<Entity> entitiesToBeRemoved;

  std::deque<int> freeIds;

 public:
  Register();
  ~Register();

  void update();

  // Entity Management
  Entity createEntity();
  void destroyEntity(const Entity& entity);

  // Component Management
  template <typename TComponent, typename... TArgs>
  void addComponent(const Entity& entity, TArgs&&... args);

  template <typename TComponent>
  void removeComponent(const Entity& entity);

  template <typename TComponent>
  bool hasComponent(const Entity& entity) const;

  template <typename TComponent>
  TComponent& getComponent(const Entity& entity) const;

  // System Management
  template <typename TSystem, typename... TArgs>
  void addSystem(TArgs&&... args);

  template <typename TSystem>
  void removeSystem(System system);

  template <typename TSystem>
  TSystem& getSystem();

  template <typename TSystem>
  bool hasSystem(const System system) const;

  // Entity-System Management
  void addEntityToSystem(const Entity& entity);
  void removeEntityFromSystem(const Entity& entity);
};

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

  if (entityId >= static_cast<int>(componentPool->getSize())) {
    componentPool->resize(entityId + 100);
  }

  TComponent newComponent(std::forward<TArgs>(args)...);

  componentPool->set(entityId, newComponent);
  entityComponentSignatures[entityId].set(componentId);
}

template <typename TComponent>
void Register::removeComponent(const Entity& entity) {
  const int componentId = Component<TComponent>::getId();
  const int entityId = entity.getId();

  entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Register::hasComponent(const Entity& entity) const {
  const int componentId = Component<TComponent>::getId();
  const int entityId = entity.getId();

  return entityComponentSignatures[entityId].test(componentId);
}

template <typename TComponent>
TComponent& Register::getComponent(const Entity& entity) const {
  const int componentId = Component<TComponent>::getId();
  const int entityId = entity.getId();

  auto componentPool =
      std::static_pointer_cast<Pool<TComponent>>(componentsPool[componentId]);

  return componentPool->get(entityId);
}

template <typename TSystem, typename... TArgs>
void Register::addSystem(TArgs&&... args) {
  std::shared_ptr<TSystem> newSystem =
      std::make_shared<TSystem>(std::forward<TArgs>(args)...);
  systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Register::removeSystem(System system) {
  systems.erase(std::type_index(typeid(TSystem)));
  // todo verify: ECS part 9 12:00
}

template <typename TSystem>
bool Register::hasSystem(const System system) const {
  return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem>
TSystem& Register::getSystem() {
  auto system = systems.find(std::type_index(typeid(TSystem)));
  return *std::static_pointer_cast<TSystem>(system->second);
}

template <typename TComponent, typename... TArgs>
void Entity::addComponent(TArgs&&... args) {
  registry->addComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::removeComponent() {
  registry->removeComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::hasComponent() const {
  return registry->hasComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent& Entity::getComponent() const {
  return registry->getComponent<TComponent>(*this);
}

#endif