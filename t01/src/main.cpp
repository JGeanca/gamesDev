#include "game/game.hpp"
#include "game/configLoader.hpp"
#include <iostream>

// int main(int argc, char* argv[]) {
//   ConfigLoader configLoader;
//   if (!configLoader.loadConfig("config.txt")) {
//     std::cerr << "Error loading config file" << std::endl;
//     return 1;
//   }
//   for (const auto& entity : configLoader.entities) {
//     std::cout << "Entity: " << entity.name << std::endl;
//     std::cout << "Image path: " << entity.imagePath << std::endl;
//     std::cout << "Size: " << entity.size.x << " " << entity.size.y << std::endl;
//     std::cout << "Position: " << entity.position.x << " " << entity.position.y << std::endl;
//     std::cout << "Velocity: " << entity.velocity.x << " " << entity.velocity.y << std::endl;
//     std::cout << "Angle: " << entity.angle << std::endl;
//   }
//   return 0;
// }

int main(int argc, char* argv[]) {
  Game game;
  game.run();
  return 0;
}