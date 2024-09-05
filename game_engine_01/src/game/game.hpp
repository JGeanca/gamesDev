#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <memory>

#include "../assetManager/assetManager.hpp"
#include "../ecs/ecs.hpp"

#define SDL_DEFAULT_SCREEN_DRIVER -1
#define SDL_WITHOUT_FLAGS 0
class Game {
 private:  // attributes
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool isRunning;
  int windowWidth;
  int windowHeight;

  std::unique_ptr<Register> registry;
  std::unique_ptr<AssetManager> assetManager;

 private:  // methods
  void setUp();
  void handleEvents();
  void update();
  void render();
  Game();
  ~Game();

 public:
  static Game &getInstance();
  void init();
  void run();
  void destroy();
};

#endif