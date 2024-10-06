#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <string>
#include <tuple>

#include "../components/boxColliderComponent.hpp"
#include "../components/rigidBodyComponent.hpp"
#include "../components/spriteComponent.hpp"
#include "../components/tagComponent.hpp"
#include "../components/textComponent.hpp"
#include "../components/transformComponent.hpp"
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

/**
 * @brief Get the velocity of the entity.
 * @param entity The entity.
 * @return The velocity of the entity.
 */
std::tuple<int, int> getVelocity(const Entity& entity) {
  auto& rigidBody = entity.getComponent<RigidBodyComponent>();
  return {static_cast<int>(rigidBody.velocity.x),
          static_cast<int>(rigidBody.velocity.y)};
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

//* Collisions

/**
 * @brief Verify if the left side of the entity is colliding with the right side
 * of the other entity.
 * @param entity The entity.
 * @param other The other entity.
 * @return true If the left side of the entity is colliding with the right side
 * of the other entity, false otherwise.
 */
bool leftCollision(const Entity& entity, const Entity& other) {
  auto& eBoxCollider = entity.getComponent<BoxColliderComponent>();
  auto& otherBoxCollider = other.getComponent<BoxColliderComponent>();

  auto& eTransform = entity.getComponent<TransformComponent>();
  auto& otherTransform = other.getComponent<TransformComponent>();

  float entityX = eTransform.position.x;
  float entityY = eTransform.position.y;
  float entityH = static_cast<float>(eBoxCollider.height);

  float otherX = otherTransform.position.x;
  float otherY = otherTransform.position.y;
  float otherH = static_cast<float>(otherBoxCollider.height);

  // If the left side of the entity is colliding with the right side of the
  // other

  return (otherY < entityY + entityH && otherY + otherH > entityY &&
          otherX < entityX);
}

/**
 * @brief Verify if the right side of the entity is colliding with the left side
 * of the other entity.
 * @param entity The entity.
 * @param other The other entity.
 * @return true If the right side of the entity is colliding with the left side
 * of the other entity, false otherwise.
 */
bool rightCollision(const Entity& entity, const Entity& other) {
  auto& eBoxCollider = entity.getComponent<BoxColliderComponent>();
  auto& otherBoxCollider = other.getComponent<BoxColliderComponent>();

  auto& eTransform = entity.getComponent<TransformComponent>();
  auto& otherTransform = other.getComponent<TransformComponent>();

  float entityX = eTransform.position.x;
  float entityY = eTransform.position.y;
  float entityH = static_cast<float>(eBoxCollider.height);

  float otherX = otherTransform.position.x;
  float otherY = otherTransform.position.y;
  float otherH = static_cast<float>(otherBoxCollider.height);

  // If the right side of the entity is colliding with the left side of the
  // other

  return (otherY < entityY + entityH && otherY + otherH > entityY &&
          otherX > entityX);
}

/**
 * @brief Verify if the top side of the entity is colliding with the bottom side
 * of the other entity.
 * @param entity The entity.
 * @param other The other entity.
 * @return true If the top side of the entity is colliding with the bottom side
 * of the other entity, false otherwise.
 */
bool topCollision(const Entity& entity, const Entity& other) {
  auto& eBoxCollider = entity.getComponent<BoxColliderComponent>();
  auto& otherBoxCollider = other.getComponent<BoxColliderComponent>();

  auto& eTransform = entity.getComponent<TransformComponent>();
  auto& otherTransform = other.getComponent<TransformComponent>();

  float entityX = eTransform.position.x;
  float entityY = eTransform.position.y;
  float entityW = static_cast<float>(eBoxCollider.width);

  float otherX = otherTransform.position.x;
  float otherY = otherTransform.position.y;
  float otherW = static_cast<float>(otherBoxCollider.width);

  // If the top side of the entity is colliding with the bottom side of the
  // other

  return (otherX < entityX + entityW && otherX + otherW > entityX &&
          otherY < entityY);
}

/**
 * @brief Verify if the bottom side of the entity is colliding with the top side
 * of the other entity.
 * @param entity The entity.
 * @param other The other entity.
 * @return true If the bottom side of the entity is colliding with the top side
 * of the other entity, false otherwise.
 */
bool bottomCollision(const Entity& entity, const Entity& other) {
  auto& eBoxCollider = entity.getComponent<BoxColliderComponent>();
  auto& otherBoxCollider = other.getComponent<BoxColliderComponent>();

  auto& eTransform = entity.getComponent<TransformComponent>();
  auto& otherTransform = other.getComponent<TransformComponent>();

  float entityX = eTransform.position.x;
  float entityY = eTransform.position.y;
  float entityW = static_cast<float>(eBoxCollider.width);

  float otherX = otherTransform.position.x;
  float otherY = otherTransform.position.y;
  float otherW = static_cast<float>(otherBoxCollider.width);

  return (otherX < entityX + entityW && otherX + otherW > entityX &&
          otherY > entityY);
}

//* Position

/**
 * @brief Get the position of the entity.
 * @param entity The entity.
 * @return The position of the entity.
 */
std::tuple<int, int> getPosition(const Entity& entity) {
  auto& transform = entity.getComponent<TransformComponent>();
  return {static_cast<int>(transform.position.x),
          static_cast<int>(transform.position.y)};
}

/**
 * @brief Set the position of the entity.
 * @param entity The entity.
 * @param x The x position.
 * @param y The y position.
 */
void setPosition(Entity& entity, int x, int y) {
  auto& transform = entity.getComponent<TransformComponent>();
  transform.position.x = static_cast<float>(x);
  transform.position.y = static_cast<float>(y);
}

/**
 * @brief Get the size of the entity.
 * @param entity The entity.
 * @return The size of the entity.
 */
std::tuple<int, int> getSize(const Entity& entity) {
  auto& spriteComponent = entity.getComponent<SpriteComponent>();
  auto& transform = entity.getComponent<TransformComponent>();
  return {static_cast<int>(spriteComponent.width * transform.scale.x),
          static_cast<int>(spriteComponent.height * transform.scale.y)};
}

#endif  // LUA_BINDING_HPP