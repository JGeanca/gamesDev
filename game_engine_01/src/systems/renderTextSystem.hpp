#ifndef RENDER_TEXT_SYSTEM_HPP
#define RENDER_TEXT_SYSTEM_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <memory>

#include "../assetManager/assetManager.hpp"
#include "../components/textComponent.hpp"
#include "../components/transformComponent.hpp"
#include "../ecs/ecs.hpp"

/**
 * @class RenderTextSystem
 * @brief This class is responsible for rendering text to the screen.
 */

class RenderTextSystem : public System {
 public:
  /**
   * @brief Construct a new Render Text System object
   */
  RenderTextSystem() {
    requireComponent<TransformComponent>();
    requireComponent<TextComponent>();
  }

  void update(SDL_Renderer* renderer,
              const std::unique_ptr<AssetManager>& assetManager) {
    for (auto& entity : getEntities()) {
      auto& text = entity.getComponent<TextComponent>();
      auto& transform = entity.getComponent<TransformComponent>();

      TTF_Font* font = assetManager->getFont(text.fontAssetId);
      if (font == nullptr) {
        std::cerr << "[RenderSystem] Font not found: " << text.fontAssetId
                  << std::endl;
        return;
      }

      SDL_Surface* surface =
          TTF_RenderText_Blended(font, text.text.c_str(), text.color);

      if (surface == nullptr) {
        std::cerr << "[RenderSystem] Failed to create surface: "
                  << TTF_GetError() << std::endl;
        return;
      }
      text.width = surface->w;
      text.height = surface->h;
      SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
      SDL_FreeSurface(surface);
      if (texture == nullptr) {
        std::cerr << "[RenderSystem] Failed to create texture: "
                  << SDL_GetError() << std::endl;
        return;
      }

      SDL_Rect destRect = {static_cast<int>(transform.position.x),
                           static_cast<int>(transform.position.y),
                           text.width * static_cast<int>(transform.scale.x),
                           text.height * static_cast<int>(transform.scale.y)};

      SDL_RenderCopy(renderer, texture, nullptr, &destRect);
      SDL_DestroyTexture(texture);
    }
  }
};

#endif  // RENDER_TEXT_SYSTEM_HPP