#ifndef LUA_BINDING_HPP
#define LUA_BINDING_HPP

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

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

// Enum class for collision types
enum class CollisionType { None, Left, Right, Top, Bottom };

/**
 * @brief Get the collision type between two entities.
 * @param entity The first entity involved in the collision.
 * @param other The second entity involved in the collision.
 * @return The type of collision (Left, Right, Top, or Bottom).
 */
CollisionType getCollisionType(const Entity& entity, const Entity& other) {
  // Get the BoxColliderComponent and TransformComponent for both entities
  auto& eBoxCollider = entity.getComponent<BoxColliderComponent>();
  auto& eTransform = entity.getComponent<TransformComponent>();

  auto& otherBoxCollider = other.getComponent<BoxColliderComponent>();
  auto& otherTransform = other.getComponent<TransformComponent>();

  // Extract position and size information for both entities
  float entityX = eTransform.position.x;
  float entityY = eTransform.position.y;
  float entityW = static_cast<float>(eBoxCollider.width);
  float entityH = static_cast<float>(eBoxCollider.height);

  float otherX = otherTransform.position.x;
  float otherY = otherTransform.position.y;
  float otherW = static_cast<float>(otherBoxCollider.width);
  float otherH = static_cast<float>(otherBoxCollider.height);

  // Calculate the overlap between the two entities on both axes
  float overlapX =
      std::min(entityX + entityW, otherX + otherW) - std::max(entityX, otherX);
  float overlapY =
      std::min(entityY + entityH, otherY + otherH) - std::max(entityY, otherY);

  // Determine the collision type based on the overlap
  if (overlapX < overlapY) {
    // If the X overlap is smaller, it's a horizontal collision
    if (entityX < otherX) {
      return CollisionType::Right;  // The entity collided with the right side
                                    // of the other
    } else {
      return CollisionType::Left;  // The entity collided with the left side of
                                   // the other
    }
  } else {
    // If the Y overlap is smaller or equal, it's a vertical collision
    if (entityY < otherY) {
      return CollisionType::Bottom;  // The entity collided with the bottom of
                                     // the other
    } else {
      return CollisionType::Top;  // The entity collided with the top of the
                                  // other
    }
  }
}

/**
 * @brief Get the collision type as a string.
 * @param entity The entity.
 * @param other The other entity.
 * @return The collision type as a string.
 */
std::string getCollisionTypeString(const Entity& entity, const Entity& other) {
  CollisionType type = getCollisionType(entity, other);
  switch (type) {
    case CollisionType::Left:
      return "left";
    case CollisionType::Right:
      return "right";
    case CollisionType::Top:
      return "top";
    case CollisionType::Bottom:
      return "bottom";
    default:
      return "none";
  }
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

// * Entities

/**
 * @brief Kill the entity.
 * @param entity The entity.
 */
void killEntity(Entity& entity) { entity.killEntity(); }

/**
 * @brief Create an entity.
 * @param x The x position.
 * @param y The y position.
 * @param width The width.
 * @param height The height.
 * @param textureId The texture id.
 * @param tag The tag.
 * @return The id of the entity.
 */
int createEntity(int x, int y, int width, int height,
                 const std::string& textureId, const std::string& tag) {
  Entity newEntity = Game::getInstance().registry->createEntity();
  newEntity.addComponent<SpriteComponent>(textureId, width, height, 0.0, 0.0);
  newEntity.addComponent<BoxColliderComponent>(width * 2, height * 2,
                                               glm::vec2(0.0, 0.0));
  newEntity.addComponent<TagComponent>(tag);
  newEntity.addComponent<TransformComponent>(glm::vec2(x, y),
                                             glm::vec2(2.0, 2.0), 0.0);

  return newEntity.getId();
}

/**
 * @brief Verify if the entity exists.
 * @param entity The entity.
 * @return true If the entity exists, false otherwise.
 */
int entityExists(Entity& entity) {
  return Game::getInstance().registry->entityExists(entity.getId());
}

/**
 * @brief Verify if the entity exists by id.
 * @param entityId The id of the entity.
 * @return true If the entity exists, false otherwise.
 */
int entityExistsById(int entityId) {
  return Game::getInstance().registry->entityExists(entityId);
}

/**
 * @brief Get the entity by id.
 * @param entityId The id of the entity.
 * @return The entity id.
 */
int getEntityId(Entity& entity) { return entity.getId(); }

/**
 * @brief Kill the entity by id.
 * @param entityId The id of the entity.
 */
void killEntityById(int entityId) {
  Game::getInstance().registry->killEntityById(entityId);
}

/**
 * @brief Create a text entity.
 * @param x The x position.
 * @param y The y position.
 * @param text The text.
 * @param font The font.
 * @param size The size.
 * @param tag The tag.
 * @return The id of the entity.
 */
int createTextEntity(int x, int y, const std::string& text,
                     const std::string& font, int size,
                     const std::string& tag) {
  Entity newEntity = Game::getInstance().registry->createEntity();
  newEntity.addComponent<TextComponent>(text, font, size, 255);
  newEntity.addComponent<TagComponent>(tag);
  newEntity.addComponent<TransformComponent>(glm::vec2(x, y),
                                             glm::vec2(1.0, 1.0), 0.0);

  return newEntity.getId();
}

#endif  // LUA_BINDING_HPP