#include "configLoader.hpp"

bool ConfigLoader::loadConfig(const std::string& filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filePath << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream textLine(line); // convert the line into a stream
    std::string key; // key to identify the configuration
    textLine >> key;  // read the first word of the line and store it in key
    
    if (key == "window") {
      int r, g, b;
      // Get the window configuration
      textLine >> this->windowConfig.width 
        >> this->windowConfig.height
        >> r >> g >> b;
      this->windowConfig.backgroundColor = 
        {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b)};
    } else if (key == "font") {  // Get the font configuration
      int r, g, b;
      textLine >> this->fontConfig.fontPath
        >> r >> g >> b
        >> this->fontConfig.fontSize;
      this->fontConfig.fontColor = 
        {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b)};
    } else if (key == "entity") {
      EntityConfig entity; // create a new entity
      textLine >> entity.name
        >> entity.imagePath
        >> entity.size.x  // width
        >> entity.size.y  // height
        >> entity.position.x
        >> entity.position.y
        >> entity.velocity.x
        >> entity.velocity.y
        >> entity.angle;
      this->entities.push_back(entity);
    }
  }
  file.close();
  return true;
}