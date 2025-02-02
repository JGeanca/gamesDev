#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>

/**
 * @class AssetManager
 * @brief This class is responsible for managing the assets of the game.
 */
class AssetManager {
 private:
  std::map<std::string, SDL_Texture*> textures;  // Map of all textures loaded
  std::map<std::string, TTF_Font*> fonts;        // Map of all fonts loaded

 public:
  /**
   * @brief AssetManager constructor
   */
  AssetManager();

  /**
   * @brief AssetManager destructor
   */
  ~AssetManager();

  /**
   * @brief Add a texture to the asset manager.
   * @param renderer SDL renderer pointer
   * @param assetId The id of the asset
   * @param path The path to the asset
   */
  void addTexture(SDL_Renderer* renderer, const std::string& assetId,
                  const std::string& path);
  SDL_Texture* getTexture(const std::string& assetId);

  /**
   * @brief Add a font to the asset manager.
   * @param assetId The id of the asset
   * @param path The path to the asset
   * @param fontSize The size of the font
   */
  void addFont(const std::string& assetId, const std::string& path,
               int fontSize);

  TTF_Font* getFont(const std::string& assetId);

  /**
   * @brief Clear all assets from the asset manager.
   */
  void clearAssets();
};

#endif  // ASSET_MANAGER_HPP