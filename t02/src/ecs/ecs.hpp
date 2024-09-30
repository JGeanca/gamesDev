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

#include "../utils/debug.hpp"
#include "../utils/pool.hpp"

const unsigned int MAX_COMPONENTS = 64;  // Maximum number of components

// Signature for each entity (64 bits)
typedef std::bitset<MAX_COMPONENTS> signature;

/**
 * @struct IComponent
 * @brief Interface for components.
 * @details This struct is used as an interface for components to assign a
 * unique id to each component type. The trick is to use a static variable to
 * make an only one instance of the variable shared among all instances of the
 * IComponents for all the execution of the program.
 */
struct IComponent {
 protected:
  static int nextId;  // Next id to assign to a component type
};

/**
 * @class Component
 * @brief Represents a component, a component is a feature of an entity for
 * example a position, a velocity, etc. -> Transform, Physics, etc.
 * @tparam TComponent The type of component.
 * @details This class is used to represent a component. It inherits from the
 * IComponent struct and assigns a unique id to each component type.
 */
template <typename TComponent>
class Component : public IComponent {
 public:
  /**
   * @brief Gets the unique id for the component.
   * @return The unique id for the component.
   * @details The id is unique because it is assigned from a static variable
   * and a static variable is shared among all instances of the class.
   */
  static int getId() {
    static int id = ++nextId;
    return id;
  }
};

/**
 * @class Entity
 * @brief Represents an entity (an object in the game).
 * @details This class is used to represent an entity. It contains an id that
 * uniquely identifies the entity and a pointer to the registry that the entity
 * belongs to.
 */
class Entity {
 private:
  int id;  // Unique identifier for the entity

 public:
  /**
   * @brief Constructs an Entity with the given ID.
   * @param id The unique identifier for this entity.
   * @param registry The registry that this entity belongs to.
   */
  Entity(int id) : id(id), registry(nullptr) {}

  /**
   * @brief Gets the unique id for the entity.
   * @return The unique id for the entity.
   */
  int getId() const;

  /**
   * @brief Destroys the entity.
   */
  void killEntity();

  /**
   * @brief Compares two entities for equality.
   * @param other The entity to compare against.
   * @return True if the entities are equal, false otherwise.
   */
  bool operator==(const Entity& other) const { return id == other.id; }

  /**
   * @brief Compares two entities for inequality.
   * @param other The entity to compare against.
   * @return True if the entities are not equal, false otherwise.
   */
  bool operator!=(const Entity& other) const { return id != other.id; }

  /**
   * @brief Compares two entities for less than.
   * @param other The entity to compare against.
   * @return True if this entity is less than the other, false otherwise.
   */
  bool operator<(const Entity& other) const { return id < other.id; }

  /**
   * @brief Compares two entities for greater than.
   * @param other The entity to compare against.
   * @return True if this entity is greater than the other, false otherwise.
   */
  bool operator>(const Entity& other) const { return id > other.id; }

  /**
   * @brief Adds a component to the entity.
   * @tparam TComponent The type of component to add.
   * @tparam TArgs The arguments to pass to the component constructor.
   * @param args The arguments to pass to the component constructor.
   */
  template <typename TComponent, typename... TArgs>
  void addComponent(TArgs&&... args);

  /**
   * @brief Removes a component from the entity.
   * @tparam TComponent The type of component to remove.
   */
  template <typename TComponent>
  void removeComponent();

  /**
   * @brief Checks if the entity has a component.
   * @tparam TComponent The type of component to check for.
   * @return True if the entity has the component, false otherwise.
   */
  template <typename TComponent>
  bool hasComponent() const;

  /**
   * @brief Gets the component from the entity.
   * @tparam TComponent The type of component to get.
   * @return The component.
   */
  template <typename TComponent>
  TComponent& getComponent() const;

  class Register* registry;  // forward declaration and pointer
};

/**
 * @class System
 * @brief Represents a system. A system is used to process/operate entities that
 * have specific components, for example rendering, physics, etc.
 * @details This class is used to represent a system. It contains a signature
 * that represents the components that the system requires and a list of
 * entities that the system is interested in.
 */
class System {
 private:
  // Signature of the components that the system requires (is a bitset of 64)
  signature componentSignature;

  // Entities that belong to the system: It means that they have the required
  // components to be processed by the system.
  std::vector<Entity> entities;

 public:
  /**
   * @brief Constructs a System.
   */
  System() = default;

  /**
   * @brief Destructs a System.
   */
  ~System() = default;

  /**
   * @brief Adds an entity to the system (to the entities vector).
   * @param entity The entity to add.
   */
  void addEntityFromSystem(const Entity& entity);

  /**
   * @brief Removes an entity from the system (from the entities vector).
   * @param entity The entity to remove.
   */
  void removeEntityFromSystem(const Entity& entity);

  /**
   * @brief Gets the entities that belong to the system.
   * @return The entities that belong to the system.
   */
  std::vector<Entity>& getEntities();

  /**
   * @brief Gets the signature of the components that the system requires.
   * @return The signature of the components that the system requires.
   */
  const signature& getComponentSignature() const;

  /**
   * @brief Requires a component for the system.
   * @tparam TComponent The type of component to require.
   * @details This method sets the bit in the component signature that
   * corresponds to the component id. This way the system knows which components
   * it requires.
   */
  template <typename TComponent>
  void requireComponent();
};

template <typename TComponent>
void System::requireComponent() {
  const int componentId = Component<TComponent>::getId();
  componentSignature.set(componentId);
}

/**
 * @class Register
 * @brief Represents a register. A register is used to manage entities,
 * components, and systems.
 * @details This class manage add, remove, and update entities, components, and
 * systems. It also manages the relationship between entities and systems.
 */
class Register {
 private:
  int numEntities;  // Total number of entities
  std::vector<std::shared_ptr<IPool>> componentsPool;  // Pool of components

  // Signature of the components that each entity has
  std::vector<signature> entityComponentSignatures;

  // Systems that the register has
  std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

  // Entities that need to be added or removed -> a queue of entities to be
  // added
  std::set<Entity> entitiesToBeAdded;

  // Entities that need to be removed -> a queue of entities to be removed
  std::set<Entity> entitiesToBeRemoved;

  // Free ids for entities, when an entity is destroyed, its id is added to this
  // list to be reused
  std::deque<int> freeIds;

 public:
  /**
   * @brief Constructs a Register.
   */
  Register();

  /**
   * @brief Destructs a Register.
   */
  ~Register();

  /**
   * @brief Updates the register.
   * @details This method updates the register by adding and removing entities
   * from systems (the queue of entities to be added and removed).
   */
  void update();

  /**
   * @brief Creates an entity.
   * @return The entity created.
   */
  Entity createEntity();

  /**
   * @brief Destroys an entity.
   * @param entity The entity to destroy.
   */
  void destroyEntity(const Entity& entity);

  /**
   * @brief Adds a component to an entity.
   * @tparam TComponent The type of component to add.
   * @tparam TArgs The arguments to pass to the component constructor.
   * @param entity The entity to add the component to.
   * @param args The arguments to pass to the component constructor.
   */
  template <typename TComponent, typename... TArgs>
  void addComponent(const Entity& entity, TArgs&&... args);

  /**
   * @brief Removes a component from an entity.
   * @tparam TComponent The type of component to remove.
   * @param entity The entity to remove the component from.
   */
  template <typename TComponent>
  void removeComponent(const Entity& entity);

  /**
   * @brief Checks if an entity has a component.
   * @tparam TComponent The type of component to check for.
   * @param entity The entity to check.
   * @return True if the entity has the component, false otherwise.
   */
  template <typename TComponent>
  bool hasComponent(const Entity& entity) const;

  /**
   * @brief Gets a component from an entity.
   * @tparam TComponent The type of component to get.
   * @param entity The entity to get the component from.
   * @return The component.
   */
  template <typename TComponent>
  TComponent& getComponent(const Entity& entity) const;

  /**
   * @brief Adds a system to the register.
   * @tparam TSystem The type of system to add.
   * @tparam TArgs The arguments to pass to the system constructor.
   * @param args The arguments to pass to the system constructor.
   */
  template <typename TSystem, typename... TArgs>
  void addSystem(TArgs&&... args);

  /**
   * @brief Removes a system from the register.
   * @tparam TSystem The type of system to remove.
   * @param system The system to remove.
   */
  template <typename TSystem>
  void removeSystem(System system);

  /**
   * @brief Gets a system from the register.
   * @tparam TSystem The type of system to get.
   * @return The system.
   */
  template <typename TSystem>
  TSystem& getSystem();

  /**
   * @brief Checks if the register has a system.
   * @tparam TSystem The type of system to check for.
   * @param system The system to check.
   * @return True if the register has the system, false otherwise.
   */
  template <typename TSystem>
  bool hasSystem(const System system) const;

  /**
   * @brief Adds an entity to a system.
   * @param entity The entity to add.
   */
  void addEntityToSystem(const Entity& entity);

  /**
   * @brief Removes an entity from a system.
   * @param entity The entity to remove.
   */
  void removeEntityFromSystem(const Entity& entity);

  /**
   * @brief Clears all entities from the register.
   */
  void clearAllEntities();
};

//* -----------------Implementation of template methods------------------------

// Register template methods <<

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

  DEBUG_MSG("[Register] Component added to entity with id: " +
            std::to_string(componentId) +
            " to entity with id: " + std::to_string(entityId));
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

// End of Register template methods >>

// Entity template methods <<
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

// End of Entity template methods >>

#endif  // ECS_HPP