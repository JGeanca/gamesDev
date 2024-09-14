#include <iostream>
#include <sol/sol.hpp>
#include <string>

int Pow(int x, int y) {
  int result = 1;
  for (int i = 0; i < y; i++) {
    result *= x;
  }
  return result;
}

void lua_test() {
  sol::state lua;
  lua.open_libraries(sol::lib::base);
  lua["pow"] = Pow;

  try {
    lua.script_file("./scripts/script01.lua");
    std::string name = lua["var_name"];
    int age = lua["var_age"];
    std::cout << "[C++] var_name: " << name << std::endl;
    std::cout << "[C++] var_age: " << age << std::endl;

    sol::table config = lua["config"];
    std::string title = config["title"];
    std::cout << "[C++] config.title: " << title << std::endl;
    bool fullscreen = config["fullscreen"];
    std::cout << "[C++] config.fullscreen: " << fullscreen << std::endl;

    sol::function factorial = lua["factorial"];
    int result = factorial(5);
    std::cout << "[C++] factorial(5): " << result << std::endl;
  } catch (const sol::error& e) {
    std::cerr << "Lua error: " << e.what() << std::endl;
  }
}

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  std::cout << "Hello, Lua!\n";

  lua_test();
  return 0;
}