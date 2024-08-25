#ifndef CONFIG_LOADER_H
#define CONFIG_LOADER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <glm/glm.hpp>

struct EntityConfig {
    std::string name;
    std::string imagePath;
    glm::vec2 size;
    glm::vec2 position;
    glm::vec2 velocity;
    double angle;
};

struct WindowConfig {
    int width;
    int height;
    SDL_Color backgroundColor;
};

struct FontConfig {
    std::string fontPath;
    SDL_Color fontColor;
    int fontSize;
};

class ConfigLoader {
public:
    WindowConfig windowConfig;
    FontConfig fontConfig;
    std::vector<EntityConfig> entities;

    bool loadConfig(const std::string& filePath);
};

#endif