#ifndef SCENE_MANAGER_CPP
#define SCENE_MANAGER_CPP

#include <map>
#include <memory>
#include <sol/sol.hpp>
#include <string>

#include "../sceneManager/sceneLoader.hpp"

/**
 * @class SceneManager
 * @brief This class is for managing scenes
 */
class SceneManager {
 private:
  std::map<std::string, std::string> scenes;  // scene name, script path
  std::string nextScene;                      // next scene to load
  bool isRunning = false;                     // is the scene running
  std::unique_ptr<SceneLoader> sceneLoader;   // scene loader pointer

 public:
  /**
   * @brief Construct a new Scene Manager object
   */
  SceneManager();

  /**
   * @brief Destroy the Scene Manager object
   */
  ~SceneManager();

  /**
   * @brief Load the scene from the script
   * @param scriptPath Path to the script
   * @param lua Lua state
   */
  void loadSceneFromScript(const std::string& scriptPath, sol::state& lua);

  /**
   * @brief Load the scene
   */
  void loadScene();

  /**
   * @brief Get the next scene
   * @return std::string Next scene
   */
  std::string getNextScene() const;

  /**
   * @brief Set the next scene
   * @param nextScene Next scene
   */
  void setNextScene(const std::string& nextScene);

  /**
   * @brief Check if the scene is running
   * @return true Scene is running
   * @return false Scene is not running
   */
  bool isSceneRunning() const;

  /**
   * @brief Start the scene
   */
  void startScene();

  /**
   * @brief Stop the scene
   */
  void stopScene();
};

#endif  // SCENE_MANAGER_CPP