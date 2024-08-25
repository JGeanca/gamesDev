#include "game.hpp"
#include <iostream>

Game::Game() : configLoader(new ConfigLoader()) {
  init();
}

Game::~Game() {
  destroy();
  delete this->configLoader;
}

void Game::init() {

  if (!this->configLoader->loadConfig("config.txt")) {
    std::cerr << "Error loading config file" << std::endl;
    this->running = false;
    return;
  }

  this->screenWidth = this->configLoader->windowConfig.width;
  this->screenHeight = this->configLoader->windowConfig.height;

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

  this->font = TTF_OpenFont(
    this->configLoader->fontConfig.fontPath.c_str(),
    this->configLoader->fontConfig.fontSize
  );

  loadEntities();

  this->paused = false;
}

void Game::run() {
  this->running = true;
  while (this->running) {
    handleEvents();
    if (!isPaused()) {   
      update();
    }  
    render();
  }
}

void Game::destroy() {
  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);

  for (auto& entity : this->entities) {
    SDL_DestroyTexture(entity.imgTexture);
    SDL_DestroyTexture(entity.textTexture);
  }

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
        } else if (event.key.keysym.sym == SDLK_p) {
          if (!this->paused) {
            this->miliPausedTime = SDL_GetTicks();
          } else {
            this->miliPreviousFrame += SDL_GetTicks() - this->miliPausedTime;
          }
          this->paused = !this->paused;
        }
        
      default:
        break;
    }
  }
}

void Game::render() {
  int r, g, b;
  r = this->configLoader->windowConfig.backgroundColor.r;
  g = this->configLoader->windowConfig.backgroundColor.g;
  b = this->configLoader->windowConfig.backgroundColor.b;

  SDL_SetRenderDrawColor(this->renderer, r, g, b, 0);
  SDL_RenderClear(this->renderer);

  // render one entity test
  SDL_Rect destRectImg = {
    static_cast<int>(this->entities[0].position.x),
    static_cast<int>(this->entities[0].position.y),
    this->entities[0].imgWidth,
    this->entities[0].imgHeight
  };

  SDL_RenderCopyEx(
    this->renderer,
    this->entities[0].imgTexture,
    &this->entities[0].srcRect,
    &destRectImg,
    2.5,
    NULL,
    SDL_FLIP_NONE
  );
  
  SDL_Rect destRectText = {
    // Center the text in the image
    this->entities[0].position.x + (this->entities[0].imgWidth - this->entities[0].txtWidth) / 2,
    this->entities[0].position.y + (this->entities[0].imgHeight - this->entities[0].txtHeight) / 2,
    this->entities[0].txtWidth,
    this->entities[0].txtHeight
  };

  SDL_RenderCopyEx(
    this->renderer,
    this->entities[0].textTexture,
    NULL,
    &destRectText,
    0,
    NULL,
    SDL_FLIP_NONE
  );

  //for (const auto& entity : this->entities) {

    // SDL_Rect destRectImg = {
    //   static_cast<int>(entity.position.x),
    //   static_cast<int>(entity.position.y),
    //   entity.imgWidth,
    //   entity.imgHeight
    // };

    // SDL_RenderCopyEx(
    //   this->renderer,
    //   entity.imgTexture,
    //   &entity.srcRect,
    //   &destRectImg,
    //   entity.angle,
    //   NULL,
    //   SDL_FLIP_NONE
    // );

    // SDL_Rect destRectText = {
    //   entity.position.x + (entity.imgWidth - entity.txtWidth) / 2,
    //   entity.position.y + (entity.imgHeight - entity.txtHeight) / 2,
    //   entity.txtWidth,
    //   entity.txtHeight
    // };

    // SDL_RenderCopyEx(
    //   this->renderer,
    //   entity.imgTexture,
    //   NULL,
    //   &destRectText,
    //   entity.angle,
    //   NULL,
    //   SDL_FLIP_NONE
    // );
  //}
  //std::cout << "Hi I am: Gean" << std::endl;
   
  SDL_RenderPresent(this->renderer);

}

void Game::update() {
  if (isPaused()) {
    return;
  }

  // milliseconds since the program started
  int miliCurrentFrame = SDL_GetTicks();  

  // milliseconds since the last frame
  int miliFrameTime = miliCurrentFrame - this->miliPreviousFrame;

  // milliseconds to sleep -> the frame delay to maintain the FPS constant rate
  int miliSleep = FRAME_DELAY - miliFrameTime;

  // if the frame time is less than the frame delay, sleep the difference
  // to maintain the FPS constant rate
  if (miliSleep > 0 && miliSleep <= FRAME_DELAY) {
    SDL_Delay(miliSleep);
  }

  // time between frames in seconds
  // is used to calculate the movement of the image in function of the time
  double deltaTime = miliFrameTime / 1000.0;

  // update the previous frame time to the current frame time
  this->miliPreviousFrame = miliCurrentFrame;

  // update the position of the image in function of the time to
  this->entities[0].position.x += this->entities[0].velocity.x * deltaTime;
  this->entities[0].position.y += this->entities[0].velocity.y * deltaTime;

  // check if the image reaches the left or right side of the screen
  if (this->entities[0].position.x <= 0 
    || this->entities[0].position.x + this->entities[0].size.x 
    >= this->screenWidth) {
    this->entities[0].velocity.x = -this->entities[0].velocity.x;
  }
  
  // check if the image reaches the top or bottom side of the screen
  if (this->entities[0].position.y <= 0 || 
    this->entities[0].position.y + this->entities[0].size.y >= this->screenHeight) {
    this->entities[0].velocity.y = -this->entities[0].velocity.y;
  }

  if (this->entities[0].position.x <= 0) {
    this->entities[0].position.x = 0;
  } else if (this->entities[0].position.x + this->entities[0].size.x >= this->screenWidth) {
    this->entities[0].position.x = this->screenWidth - this->entities[0].size.x;
  }

  if (this->entities[0].position.y <= 0) {
    this->entities[0].position.y = 0;
  } else if (this->entities[0].position.y + this->entities[0].size.y >= this->screenHeight) {
    this->entities[0].position.y = this->screenHeight - this->entities[0].size.y;
  }
}

void Game::loadEntities() {
  for (auto& entityCfg : this->configLoader->entities) {
    Entity newEntity;
    newEntity.name = entityCfg.name;
    newEntity.imagePath = entityCfg.imagePath;
    newEntity.size = entityCfg.size;
    newEntity.position = entityCfg.position;
    newEntity.velocity = entityCfg.velocity;
    newEntity.angle = entityCfg.angle;
    newEntity.imgWidth = entityCfg.size.x;
    newEntity.imgHeight = entityCfg.size.y;

    SDL_Surface* imgSurface = IMG_Load(entityCfg.imagePath.c_str());
    if (imgSurface) {
      newEntity.imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
      SDL_FreeSurface(imgSurface);
    } else {
      std::cerr << "Failed to load image: " << entityCfg.imagePath << std::endl;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(
      this->font,
      entityCfg.name.c_str(),
      this->configLoader->fontConfig.fontColor
    );
    if (textSurface) {
      newEntity.textTexture = SDL_CreateTextureFromSurface(this->renderer, textSurface);
      newEntity.txtWidth = textSurface->w;
      newEntity.txtHeight = textSurface->h;
      SDL_FreeSurface(textSurface);
    } else {
      std::cerr << "Failed to render text: " << entityCfg.name << std::endl;
    }
    // set the source rectangle to the size of the image
    newEntity.srcRect = {0, 0, newEntity.imgWidth, newEntity.imgHeight};
    this->entities.push_back(newEntity);
  }
}