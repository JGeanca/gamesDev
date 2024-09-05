#ifndef RENDER_SYSTEM_HPP
#define RENDER_SYSTEM_HPP

#include <SDL2/SDL.h>

#include "../assetManager/assetManager.hpp"
#include "../components/spriteComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"

class RenderSystem : public System {
 public:
  RenderSystem() {
    requireComponent<SpriteComponent>();
    requireComponent<TransformComponent>();
  }

  void update(SDL_Renderer* renderer,
              const std::unique_ptr<AssetManager>& AssetManager) {
    for (auto entity : getEntities()) {
      const auto& sprite = entity.getComponent<SpriteComponent>();
      const auto& transform = entity.getComponent<TransformComponent>();

      SDL_Rect srcRect = sprite.srcRect;
      SDL_Rect destRect = {static_cast<int>(transform.position.x),
                           static_cast<int>(transform.position.y),
                           static_cast<int>(sprite.width * transform.scale.x),
                           static_cast<int>(sprite.height * transform.scale.y)};

      SDL_RenderCopyEx(renderer, AssetManager->getTexture(sprite.textureId),
                       &srcRect, &destRect, transform.rotation, NULL,
                       SDL_FLIP_NONE);
    }
  }
};

#endif  // RENDER_SYSTEM_HPP