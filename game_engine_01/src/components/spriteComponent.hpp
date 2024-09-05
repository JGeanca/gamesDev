#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

struct SpriteComponent {
  std::string textureId;
  int width;
  int height;
  SDL_Rect srcRect;

  SpriteComponent(const std::string& textureId = "", int width = 0,
                  int height = 0, int srcX = 0, int srcY = 0)
      : textureId(textureId), width(width), height(height) {
    this->srcRect = {srcX, srcY, width, height};
  }
};

#endif  // SPRITE_COMPONENT_HPP