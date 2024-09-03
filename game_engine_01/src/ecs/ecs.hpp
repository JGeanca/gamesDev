#ifndef ECS_HPP
#define ECS_HPP

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
};

class Register {
 private:
  int numEntities;
};

#endif