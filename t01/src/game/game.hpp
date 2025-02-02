#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "configLoader.hpp"

#define SDL_DEFAULT_SCREEN_DRIVER -1
#define SDL_WITHOUT_FLAGS 0

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
const double MAX_DELTA_TIME = 0.05;

struct Entity {
  SDL_Texture* imgTexture = nullptr;
  SDL_Texture* textTexture = nullptr;
  SDL_Rect srcRect;
  SDL_Color fontColor;
  std::string name;
  std::string imagePath;
  glm::vec2 size;
  glm::vec2 position;
  glm::vec2 velocity;
  double angle;
  int imgWidth;
  int imgHeight;
  int txtWidth;
  int txtHeight;
};
class Game {
  
  private: // attributes
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font* font;

    int miliPreviousFrame;
    int miliPausedTime;
    size_t screenWidth;
    size_t screenHeight;
    bool running;
    bool paused;

    ConfigLoader* configLoader;
    std::vector<Entity> entities;

  private: // methods
    void handleEvents();
    void update();
    void render();
    void loadEntities();
    void screenBounce(double deltaTime);
    void renderEntities();
    void renderText(const Entity& entity);
    void renderImage(const Entity& entity);
    void renderBackground();
  public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
    inline bool isRunning() const { return running; }
    inline bool isPaused() const { return paused; }
};

#endif
