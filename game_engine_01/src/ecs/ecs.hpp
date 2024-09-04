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

  bool hasComponent(const Entity& entity) const;

  template <typename TComponent>
  TComponent& getComponent(const Entity& entity) const;

  // System Management
  template <typename TSystem, typename... TArgs>
  void addSystem(TArgs&&... args);

  template <typename TSystem>
  void removeSystem(System system);

  bool hasSystem(const System system) const;

  // Entity-System Management
  void addEntityToSystem(const Entity& entity);
  void removeEntityFromSystem(const Entity& entity);
};

#endif