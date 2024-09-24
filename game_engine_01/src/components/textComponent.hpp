#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP

#include <SDL2/SDL.h>

#include <string>

/**
 * @struct TextComponent
 * @brief The component that contains the text information
 */
struct TextComponent {
  std::string text;         // The text to display
  std::string fontAssetId;  // The font asset id
  SDL_Color color;          // The color of the text
  int width;                // The width of the text
  int height;               // The height of the text

  /**
   * @brief TextComponent constructor
   * @param text The text to display
   * @param fontAssetId The font asset id
   * @param color The color of the text
   * @param width The width of the text
   * @param height The height of the text
   */
  TextComponent(const std::string& text = "",
                const std::string& fontAssetId = "",
                const SDL_Color& color = {u_char(255), u_char(255), u_char(255),
                                          u_char(255)},
                int width = 0, int height = 0)
      : text(text),
        fontAssetId(fontAssetId),
        color(color),
        width(width),
        height(height) {}
};

#endif  // TEXT_COMPONENT_HPP