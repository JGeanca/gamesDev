#include "ecs.hpp"

int IComponent::nextId = 0;

int Entity::getId() const { return id; }