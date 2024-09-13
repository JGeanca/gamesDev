#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

/**
 * @class AssetManager
 * @brief This class is responsible for managing the assets of the game.
 */
class AssetManager {
 private:
  std::map<std::string, SDL_Texture*> textures;  // Map of all textures loaded

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
   * @brief Clear all assets from the asset manager.
   */
  void clearAssets();
};

#endif  // ASSET_MANAGER_HPP