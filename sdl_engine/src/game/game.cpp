#include "game.hpp"

Game::Game() {
  init();
}

Game::~Game() {
  destroy();
}

void Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    this->running = false;
    return;
  }

  if (TTF_Init() != 0) {
    std::cout << "SDL TTF could not initialize! SDL_Error: " << TTF_GetError() << std::endl;
    this->running = false;
    return;
  }

  this->window = SDL_CreateWindow(
    "Game Motor Engine",
    SDL_WINDOWPOS_CENTERED, // x position
    SDL_WINDOWPOS_CENTERED, // y position
    this->screenWidth, // width
    this->screenHeight, // height
    SDL_WINDOW_SHOWN // flags
  );

  this->renderer = SDL_CreateRenderer(
    this->window,
    SDL_DEFAULT_SCREEN_DRIVER,
    SDL_WITHOUT_FLAGS
  );
  // Text initialization
  this->fontSize = 24;
  this->font = TTF_OpenFont("assets/fonts/press_start_2p.ttf", this->fontSize);


  // Image initialization
  this->imgWidth = 32;
  this->imgHeight = 32;
  this->position.x = (this->screenWidth - this->imgWidth) / 2;
  this->position.y = (this->screenHeight - this->imgHeight) / 2;

  SDL_Surface* imgSurface = IMG_Load("assets/images/skull_00.png");
  this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);

  SDL_FreeSurface(imgSurface);
  this->srcRect.x = 0;
  this->srcRect.y = 0;
  this->srcRect.w = this->imgWidth;
  this->srcRect.h = this->imgHeight;


  // text field
  this->text = "Hello, World!";
  this->fontColor = {255, 255, 255, 255};
  SDL_Surface* textSurface = TTF_RenderText_Solid(
    this->font,
    this->text.c_str(),
    this->fontColor
  );
  
  this->textTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
  this->txtWidth = textSurface->w;
  this->txtHeight = textSurface->h;
  this->textPosition.x = (this->screenWidth - this->txtWidth) / 2;
  this->textPosition.y = 20;
  SDL_FreeSurface(textSurface);
}

void Game::run() {
  this->running = true;
  while (this->running) {
    handleEvents();
    // update();
    render();
  }
}

void Game::destroy() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);
  SDL_DestroyTexture(this->imgTexture);
  SDL_DestroyTexture(this->textTexture);

  TTF_Quit();
  SDL_Quit();
}

void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        this->running = false;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE) {
          this->running = false;
          break;
        }
      default:
        break;
    }
  }
}

void Game::render() {
  SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255);
  SDL_RenderClear(this->renderer);

  SDL_Rect destImgRect = {
    static_cast<int>(this->position.x),
    static_cast<int>(this->position.y),
    static_cast<int>(this->imgWidth),
    static_cast<int>(this->imgHeight)
  };

  SDL_RenderCopyEx(
    this->renderer,
    this->imgTexture,
    &this->srcRect, // Section of the image to render
    &destImgRect, // Section of the screen to render the image
    this->angle,
    NULL, // Center of the image (null = center)
    SDL_FLIP_NONE
  );

  SDL_Rect destTxtRect = {
    static_cast<int>(this->textPosition.x),
    static_cast<int>(this->textPosition.y),
    static_cast<int>(this->txtWidth),
    static_cast<int>(this->txtHeight)
  };

  SDL_RenderCopyEx(
    this->renderer,
    this->textTexture,
    NULL, // if null the whole text will be rendered
    &destTxtRect,
    this->txtAngle,
    NULL,
    SDL_FLIP_NONE
  );

  SDL_RenderPresent(this->renderer);

}
