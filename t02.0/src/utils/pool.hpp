#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

/**
 * @class IPool
 * @brief This class represents an interface for a pool of components.
 */
class IPool {
 public:
  /**
   * @brief IPool destructor
   */
  virtual ~IPool() = default;
};

/**
 * @class Pool
 * @brief This class represents a pool of components.
 * @details A pool is a collection of components, is useful because it prevents
 * the need that each entity stores its own components, instead, the entity
 * has an index that points to the component in the pool.
 */
template <typename TComponent>
class Pool : public IPool {
 private:
  std::vector<TComponent> data;  // Vector of components

 public:
  /**
   * @brief Pool constructor
   * @param size The size of the pool
   */
  Pool(int size = 1000) { data.resize(size); }

  /**
   * @brief Pool destructor
   */
  virtual ~Pool() = default;

  /**
   * @brief Check if the pool is empty.
   * @return True if the pool is empty, false otherwise
   */
  bool isEmpty() const { return data.empty(); }

  /**
   * @brief Get the size of the pool.
   * @return The size of the pool
   */
  size_t getSize() const { return data.size(); }

  /**
   * @brief Resize the pool.
   * @param newSize The new size of the pool
   */
  void resize(int newSize) { data.resize(newSize); }

  /**
   * @brief Clear the pool.
   */
  void clear() { data.clear(); }

  /**
   * @brief Add a component to the pool.
   * @param component The component to add
   */
  void add(const TComponent& component) { data.push_back(component); }

  /**
   * @brief Remove a component from the pool.
   * @param index The index of the component to remove
   */
  void set(unsigned int index, const TComponent& component) {
    data[index] = component;
  }

  /**
   * @brief Get a component from the pool.
   * @param index The index of the component to get
   * @return The component
   */
  TComponent& get(unsigned int index) {
    return static_cast<TComponent&>(data[index]);
  }

  /**
   * @brief Get a component from the pool.
   * @param index The index of the component to get
   * @return The component
   */
  TComponent& operator[](unsigned int index) {
    return static_cast<TComponent&>(data[index]);
  }
};

#endif