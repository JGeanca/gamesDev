#include "assetManager.hpp"

#include <SDL2/SDL_image.h>

#include "../utils/debug.hpp"
AssetManager::AssetManager() {
  DEBUG_MSG("[AssetManager] AssetManager created");
}

AssetManager::~AssetManager() {
  DEBUG_MSG("[AssetManager] AssetManager destroyed");
  clearAssets();
}
void AssetManager::addTexture(SDL_Renderer* renderer,
                              const std::string& assetId,
                              const std::string& path) {
  SDL_Surface* surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    std::cerr << "Failed to load image: " << path << std::endl;
    return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr) {
    std::cerr << "Failed to create texture from: " << path << std::endl;
    return;
  }

  SDL_FreeSurface(surface);
  textures.emplace(assetId, texture);
}

SDL_Texture* AssetManager::getTexture(const std::string& assetId) {
  return textures[assetId];
}

void AssetManager::addFont(const std::string& assetId, const std::string& path,
                           int fontSize) {
  TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
  if (font == nullptr) {
    std::cerr << "[AssetManager] Failed to load font: " << path << std::endl;
    return;
  }
  fonts.emplace(assetId, font);
}

TTF_Font* AssetManager::getFont(const std::string& assetId) {
  return fonts[assetId];
}

void AssetManager::clearAssets() {
  for (auto& texture : textures) {
    SDL_DestroyTexture(texture.second);
  }

  for (auto& font : fonts) {
    TTF_CloseFont(font.second);
  }
  textures.clear();
  fonts.clear();
}