#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <SDL2/SDL_mixer.h>

#include <string>
#include <unordered_map>

#define FREQUENCY 44100
#define CHUNKSIZE 2048

/**
 * @class AudioManager
 * @brief This class is for managing the audio in the game
 */
class AudioManager {
 private:
  std::unordered_map<std::string, Mix_Chunk*> soundEffects;  // SFX map
  std::unordered_map<std::string, Mix_Music*> music;         // Music map
  int soundVolume;                                           // Sound volume
  int musicVolume;                                           // Music volume

  /**
   * @brief Clean up the audio manager resources
   */
  void cleanup();

 public:
  /**
   * @brief AudioManager constructor
   */
  AudioManager();

  /**
   * @brief AudioManager destructor
   */
  ~AudioManager();

  /**
   * @brief Initialize the audio manager
   */
  void init();

  /**
   * @brief Load a sound effect
   * @param name Name of the sound effect as an identifier
   * @param path Path to the sound effect file
   */
  void loadSoundEffect(const std::string& name, const std::string& path);

  /**
   * @brief Load a music track
   * @param name Name of the music track as an identifier
   * @param path Path to the music track file
   */
  void loadMusic(const std::string& name, const std::string& path);

  /**
   * @brief Play a sound effect
   * @param name Name of the sound effect to play
   * @param loops Number of times to loop the sound effect
   */
  void playSoundEffect(const std::string& name, int loops = 0);

  /**
   * @brief Play a music track
   * @param name Name of the music track to play
   * @param loops Number of times to loop the music track
   */
  void playMusic(const std::string& name, int loops = -1);

  /**
   * @brief Stop the currently playing music track
   */
  void stopMusic();

  /**
   * @brief Pause the currently playing music track
   */
  void pauseMusic();

  /**
   * @brief Resume the currently paused music track
   */
  void resumeMusic();

  /**
   * @brief Set the sound volume
   * @param volume Volume level to set
   */
  void setSoundVolume(int volume);

  /**
   * @brief Set the music volume
   * @param volume Volume level to set
   */
  void setMusicVolume(int volume);

  /**
   * @brief Toggle the music
   */
  void toggleMusic();
};

#endif  // AUDIO_MANAGER_HPP