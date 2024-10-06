#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <string>

#include "../components/rigidBodyComponent.hpp"
#include "../components/textComponent.hpp"
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

//* RigidBodyComponent

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

//* Text

/**
 * @brief Show or hide the text.
 * @param entity The entity.
 * @param isVisible The visibility of the text.
 */
void setTextVisibility(const Entity& entity, bool isVisible) {
  if (entity.hasComponent<TextComponent>()) {
    auto& textComponent = entity.getComponent<TextComponent>();
    textComponent.color.a = isVisible ? 255 : 1;
  }
}

//* Audio

/**
 * @brief Play a sound effect.
 * @param name
 */
void playSound(const std::string& name) {
  Game::getInstance().audioManager->playSoundEffect(name);
}

/**
 * @brief Play a music.
 * @param name
 */
void playMusic(const std::string& name) {
  Game::getInstance().audioManager->playMusic(name);
}

/**
 * @brief Stop the music.
 */
void stopMusic() { Game::getInstance().audioManager->stopMusic(); }

//* Tags

/**
 * @brief Get the tag of the entity.
 * @param entity The entity.
 * @return The tag of the entity.
 */
std::string getTag(const Entity& entity) {
  return entity.getComponent<TagComponent>().tag;
}

#endif  // LUA_BINDING_HPP