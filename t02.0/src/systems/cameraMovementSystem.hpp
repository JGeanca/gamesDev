#ifndef CAMERA_MOVEMENT_SYSTEM_HPP
#define CAMERA_MOVEMENT_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../components/cameraFollowComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"
#include "../game/game.hpp"

/**
 * @class CameraMovementSystem
 * @brief This class represents the camera movement system of the game.
 * @details Camera movement system is responsible for moving the camera of the
 * game.
 */
class CameraMovementSystem : public System {
 public:
  /**
   * @brief CameraMovementSystem constructor
   * @details This constructor requires the CameraFollowComponent and
   * TransformComponent to be present in the entity. **Requires means that the
   * entity must have these components to be processed by the system.
   */
  CameraMovementSystem() {
    requireComponent<CameraFollowComponent>();
    requireComponent<TransformComponent>();
  }

  /**
   * @brief Update the camera movement system.
   * @param camera The camera rectangle.
   * @details This method updates the camera position to follow the entity with
   * the CameraFollowComponent.
   */
  void update(SDL_Rect& camera) {
    auto entities = getEntities();
    for (auto& entity : entities) {
      const auto& transform = entity.getComponent<TransformComponent>();

      if (transform.position.x + (camera.w / 2) <
          static_cast<float>(Game::getInstance().mapWidth)) {
        camera.x = static_cast<int>(transform.position.x) - (camera.w / 2);
      }

      if (transform.position.y + (camera.h / 2) <
          static_cast<float>(Game::getInstance().mapHeight)) {
        camera.y = static_cast<int>(transform.position.y) - (camera.h / 2);
      }

      camera.x = camera.x < 0 ? 0 : camera.x;
      camera.y = camera.y < 0 ? 0 : camera.y;
    }
  }
};

#endif  // CAMERA_MOVEMENT_SYSTEM_HPP