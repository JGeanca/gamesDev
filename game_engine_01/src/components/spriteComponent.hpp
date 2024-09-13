#ifndef SPRITE_COMPONENT_HPP
#define SPRITE_COMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

/**
 * @struct SpriteComponent
 * @brief This structure represents the sprite component of an entity.
 * @details Sprite component represents the sprite of an entity.
 */
struct SpriteComponent {
  std::string textureId;  // Texture id
  int width;              // Width of the sprite
  int height;             // Height of the sprite
  SDL_Rect srcRect;       // Source rectangle of the sprite

  /**
   * @brief SpriteComponent constructor
   * @param textureId The id of the texture
   * @param width The width of the sprite
   * @param height The height of the sprite
   * @param srcX The x position of the source rectangle
   * @param srcY The y position of the source rectangle
   */
  SpriteComponent(const std::string& textureId = "", int width = 0,
                  int height = 0, int srcX = 0, int srcY = 0)
      : textureId(textureId), width(width), height(height) {
    this->srcRect = {srcX, srcY, width, height};
  }
};

#endif  // SPRITE_COMPONENT_HPP