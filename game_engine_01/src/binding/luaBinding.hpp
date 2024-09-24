#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <string>

#include "../components/rigidBodyComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../game/game.hpp"

//* Controls

/**
 * @brief Verify if the action is activated. (controller input)
 * @param action The action to verify.
 * @return true If the action is activated, false otherwise.
 */
bool isActionActivated(const std::string& action) {
  return Game::getInstance().controllerManager->isActionActivated(action);
}

//* RegidBodyComponent

/**
 * @brief Set the velocity of the entity.
 * @param entity The entity.
 * @param x The x velocity.
 * @param y The y velocity.
 */
void setVelocity(const Entity& entity, float x, float y) {
  auto& rigidBody = entity.getComponent<RigidBodyComponent>();
  rigidBody.velocity.x = x;
  rigidBody.velocity.y = y;
}

//* Scenes

/**
 * @brief Go to the scene.
 * @param scene The scene to go.
 */
void goToScene(const std::string& scene) {
  Game::getInstance().sceneManager->setNextScene(scene);
  Game::getInstance().sceneManager->stopScene();
}

#endif  // LUA_BINDING_HPP