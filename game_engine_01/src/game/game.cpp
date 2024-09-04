#include "game.hpp"

#include <iostream>

#include "../utils/debug.hpp"

Game::Game() {
  this->window = nullptr;
  this->renderer = nullptr;
  this->isRunning = false;
  DEBUG_MSG("[Game] Game constructor called");
  init();
}

Game::~Game() {
  DEBUG_MSG("[Game] Game destructor called");
  destroy();
}

Game &Game::getInstance() {
  static Game instance;
  return instance;
}

void Game::init() {
  this->windowWidth = 800;
  this->windowHeight = 600;
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return;
  }

  if (TTF_Init() != 0) {
    std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    return;
  }

  this->window = SDL_CreateWindow("Game Engine 01", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, windowWidth,
                                  windowHeight, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return;
  }

  this->renderer = SDL_CreateRenderer(this->window, SDL_DEFAULT_SCREEN_DRIVER,
                                      SDL_WITHOUT_FLAGS);
}

void Game::run() {
  this->isRunning = true;
  while (isRunning) {
    handleEvents();
    update();
    render();
  }
}

void Game::destroy() {
  DEBUG_MSG("[Game] Destroying game");
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  TTF_Quit();
  SDL_Quit();
}

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      this->isRunning = false;
      break;

    case SDL_KEYDOWN:
      if (event.key.keysym.sym == SDLK_ESCAPE) {
        this->isRunning = false;
        break;
      }

    default:
      break;
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(this->renderer, 12, 21, 235, 255);
  SDL_RenderClear(this->renderer);
  SDL_RenderPresent(this->renderer);
}

void Game::update() {
  // nothing to do here yet
  // todo
}