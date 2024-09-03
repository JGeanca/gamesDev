#ifndef ECS_HPP
#define ECS_HPP

#include <bitset>
#include <memory>
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
};

#endif