#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <iostream>

#define SDL_DEFAULT_SCREEN_DRIVER -1
#define SDL_WITHOUT_FLAGS 0

class Game {
  
  private: // attributes
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    size_t screenWidth = 800;
    size_t screenHeight = 600;
    bool running;

    SDL_Texture* imgTexture = nullptr;
    glm::vec2 position = glm::vec2();
    size_t imgWidth = 0;
    size_t imgHeight = 0;
    SDL_Rect srcRect= {0, 0, 0, 0};
    double angle = 0.0;

  private: // methods
    void handleEvents();
    void update();
    void render();
  public:
    Game();
    ~Game();
    void init();
    void run();
    void destroy();
    inline bool isRunning() const { return running; }
};

#endif
