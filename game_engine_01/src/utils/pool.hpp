#ifndef POOL_HPP
#define POOL_HPP

#include <vector>

class IPool {
 public:
  virtual ~IPool() = default;
};

template <typename TComponent>
class Pool : public IPool {
 private:
  std::vector<TComponent> data;

 public:
  Pool(int size = 1000) { data.resize(size); }
  virtual ~Pool() = default;
  bool isEmpty() const { return data.empty(); }
  size_t getSize() const { return data.size(); }
  void resize(int newSize) { data.resize(newSize); }
  void clear() { data.clear(); }
  void add(const TComponent& component) { data.push_back(component); }

  void set(unsigned int index, const TComponent& component) {
    data[index] = component;
  }

  TComponent& get(unsigned int index) {
    return static_cast<TComponent&>(data[index]);
  }

  TComponent& operator[](unsigned int index) {
    return static_cast<TComponent&>(data[index]);
  }
};

#endif