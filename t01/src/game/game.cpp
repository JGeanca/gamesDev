#include "game.hpp"
#include <iostream>

/**
 * @brief  Constructor, initialize the config loader
 */
Game::Game() : configLoader(new ConfigLoader()) {
  init();
}

/**
 * @brief  Destructor
 */
Game::~Game() {
  destroy();
  delete this->configLoader;
}

/**
 * @brief  Initialize the game
 */
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

/**
 * @brief  Run the game loop
 */
void Game::run() {
  this->running = true;
  while (this->running) {
    handleEvents(); 
    update();
    render();
  }
}

/**
 * @brief  Free the resources used by the game
 */
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

/**
 * @brief  Handle the events of the game
 */
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

/**
 * @brief  Render the entities on the screen
 */
void Game::render() {
  renderBackground();
  renderEntities();
  SDL_RenderPresent(this->renderer);
}

/**
 * @brief  Render the background of the screen
 */
void Game::renderBackground() {
  SDL_SetRenderDrawColor(this->renderer,
    this->configLoader->windowConfig.backgroundColor.r,
    this->configLoader->windowConfig.backgroundColor.g,
    this->configLoader->windowConfig.backgroundColor.b,
    0 // opacity
  );
  SDL_RenderClear(this->renderer);
}

/**
 * @brief  Render the entities on the screen
 */
void Game::renderEntities() {
  for (const auto& entity : this->entities) {
    renderImage(entity);
    renderText(entity);
  }
}

/**
 * @brief  Render the image on the screen
 * @param  entity: entity with the image to render
 */
void Game::renderImage(const Entity& entity) {
  SDL_Rect destRect = {
    static_cast<int>(entity.position.x),
    static_cast<int>(entity.position.y),
    entity.imgWidth,
    entity.imgHeight
  };

  SDL_RenderCopyEx(
    this->renderer,
    entity.imgTexture,
    &entity.srcRect,
    &destRect,
    entity.angle,
    NULL,
    SDL_FLIP_NONE
  );
}

/**
 * @brief  Render the text on the screen
 * @param  entity: entity with the text to render
 */
void Game::renderText(const Entity& entity) {
  SDL_Rect destRect = {
    static_cast<int>(entity.position.x 
      + (entity.imgWidth - entity.txtWidth) / 2),
    static_cast<int>(entity.position.y 
      + (entity.imgHeight - entity.txtHeight) / 2),
    entity.txtWidth,
    entity.txtHeight
  };

  SDL_RenderCopyEx(
    this->renderer,
    entity.textTexture,
    NULL,
    &destRect,
    entity.angle,
    NULL,
    SDL_FLIP_NONE
  );
}

/**
 * @brief  Update the game state and the entities, calculating 
 * the time between frames to maintain the FPS constant rate
 */
void Game::update() {
    if (isPaused()) {
      return;
    }
    // Time (miliseconds) since the SDL library was initialized
    Uint32 miliCurrentFrame = SDL_GetTicks();

    // Time between the current frame and the previous frame in seconds
    // used to calculate the movement of the entities in function of the time
    double deltaTime = (miliCurrentFrame - this->miliPreviousFrame) / 1000.0;

    // Limit the maximum deltaTime to avoid large jumps
    if (deltaTime > MAX_DELTA_TIME) {
      deltaTime = MAX_DELTA_TIME;
    }

    // Update the previous frame time
    this->miliPreviousFrame = miliCurrentFrame;

    // Update the entities position
    screenBounce(deltaTime);

    // The time it took to render the frame
    Uint32 frameTime = SDL_GetTicks() - miliCurrentFrame;
    // Check if the rendering frame time was less than the frame delay
    if (frameTime < FRAME_DELAY) { // if it was, wait the remaining time
      SDL_Delay(FRAME_DELAY - frameTime);
    }
}

/**
 * @brief  Bounce the image when it reaches the screen limits
 * @param  deltaTime: time between frames in seconds
 */
void Game::screenBounce(double deltaTime) {
  for (auto& entity : this->entities) {
    entity.position.x += entity.velocity.x * deltaTime;
    entity.position.y += entity.velocity.y * deltaTime;

    // check if the image reaches the left or right side of the screen
    // and invert the velocity in the x axis
    if (entity.position.x <= 0 
      || entity.position.x + entity.size.x 
      >= this->screenWidth) {
      entity.velocity.x = entity.velocity.x * -1;
    }

    // check if the image reaches the top or bottom side of the screen
    // and invert the velocity in the y axis
    if (entity.position.y <= 0 || 
      entity.position.y + entity.size.y >= this->screenHeight) {
      entity.velocity.y = entity.velocity.y * -1;
    }

    // check if the image reaches the screen limits (x) and adjust the position
    if (entity.position.x <= 0) {
      entity.position.x = 0;
    } else if (entity.position.x + entity.size.x >= this->screenWidth) {
      entity.position.x = this->screenWidth - entity.size.x;
    }

    // check if the image reaches the screen limits (y) and adjust the position
    if (entity.position.y <= 0) {
      entity.position.y = 0;
    } else if (entity.position.y + entity.size.y >= this->screenHeight) {
      entity.position.y = this->screenHeight - entity.size.y;
    }
  }
}

/**
 * @brief  Load the entities from the config file
 */
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