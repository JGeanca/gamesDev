#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

class AssetManager {
 private:
  std::map<std::string, SDL_Texture*> textures;

 public:
  AssetManager();
  ~AssetManager();

  void addTexture(SDL_Renderer* renderer, const std::string& assetId,
                  const std::string& path);
  SDL_Texture* getTexture(const std::string& assetId);

  void clearAssets();
};

#endif  // ASSET_MANAGER_HPP