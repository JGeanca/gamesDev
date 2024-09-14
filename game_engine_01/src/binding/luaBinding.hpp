#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <string>

#include "../components/rigidBodyComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../game/game.hpp"

/**
 * @brief Verify if the action is activated. (controller input)
 * @param action The action to verify.
 * @return true If the action is activated, false otherwise.
 */
bool isActionActivated(const std::string& action) {
  return Game::getInstance().controllerManager->isActionActivated(action);
}

// RegidBodyComponent

void setVelocity(const Entity& entity, float x, float y) {
  auto& rigidBody = entity.getComponent<RigidBodyComponent>();
  rigidBody.velocity.x = x;
  rigidBody.velocity.y = y;
}

#endif  // LUA_BINDING_HPP