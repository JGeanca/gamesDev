#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../assetManager/assetManager.hpp"
#include "../components/spriteComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"

/**
 * @class RenderSystem
 * @brief This class represents the render system of the game.
 * @details Render system is responsible for rendering the entities of the game.
 */
class RenderSystem : public System {
 public:
  /**
   * @brief RenderSystem constructor
   * @details This constructor requires the SpriteComponent and
   * TransformComponent to be present in the entity. **Requires means that the
   * entity must have these components to be processed by the system.
   */
  RenderSystem() {
    requireComponent<SpriteComponent>();
    requireComponent<TransformComponent>();
  }

  /**
   * @brief Update the render system.
   * @param renderer SDL renderer pointer
   * @param AssetManager Asset manager pointer
   * @param camera The camera rectangle.
   * @details This method renders the entities of the game.
   */
  void update(SDL_Renderer* renderer, SDL_Rect& camera,
              const std::unique_ptr<AssetManager>& AssetManager) {
    for (auto entity : getEntities()) {
      const auto& sprite = entity.getComponent<SpriteComponent>();
      const auto& transform = entity.getComponent<TransformComponent>();

      SDL_Rect srcRect = sprite.srcRect;
      SDL_Rect destRect = {static_cast<int>(transform.position.x - camera.x),
                           static_cast<int>(transform.position.y - camera.y),
                           static_cast<int>(sprite.width * transform.scale.x),
                           static_cast<int>(sprite.height * transform.scale.y)};

      SDL_RenderCopyEx(renderer, AssetManager->getTexture(sprite.textureId),
                       &srcRect, &destRect, transform.rotation, NULL,
                       SDL_FLIP_NONE);
    }
  }
};

#endif  // RENDER_SYSTEM_HPP