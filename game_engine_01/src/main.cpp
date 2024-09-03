#include <iostream>

#include "game/game.hpp"
int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  std::cout << "Hello, World!" << std::endl;
  Game& game = Game::getInstance();
  game.run();
  return 0;
}
