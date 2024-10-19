#include "audioManager.hpp"

#include <iostream>

#include "../utils/debug.hpp"

AudioManager::AudioManager()
    : soundVolume(MIX_MAX_VOLUME), musicVolume(MIX_MAX_VOLUME) {
  init();
  DEBUG_MSG("[AudioManager] AudioManager created and initialized");
}

AudioManager::~AudioManager() {
  cleanup();
  DEBUG_MSG("[AudioManager] AudioManager destroyed");
}

void AudioManager::init() {
  if (Mix_OpenAudio(FREQUENCY, MIX_DEFAULT_FORMAT, 2, CHUNKSIZE) < 0) {
    std::cerr << "SDL_mixer could not initialize! " << Mix_GetError()
              << std::endl;
    return;
  }
}

void AudioManager::cleanup() {
  for (auto& effect : soundEffects) {
    Mix_FreeChunk(effect.second);
  }
  soundEffects.clear();

  for (auto& track : music) {
    Mix_FreeMusic(track.second);
  }
  music.clear();

  Mix_CloseAudio();
}

void AudioManager::loadSoundEffect(const std::string& name,
                                   const std::string& path) {
  Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
  if (chunk == nullptr) {
    std::cerr << "[AudioManager] Failed to load: " << path
              << " SDL_mixer Error: " << Mix_GetError() << std::endl;
    return;
  }
  soundEffects[name] = chunk;
}

void AudioManager::loadMusic(const std::string& name, const std::string& path) {
  Mix_Music* music_track = Mix_LoadMUS(path.c_str());
  if (music_track == nullptr) {
    std::cerr << "[AudioManager] Failed to load: " << path
              << " SDL_mixer Error: " << Mix_GetError() << std::endl;
    return;
  }
  music[name] = music_track;
}

void AudioManager::playSoundEffect(const std::string& name, int loops) {
  if (soundEffects.find(name) != soundEffects.end()) {
    Mix_PlayChannel(-1, soundEffects[name], loops);
  } else {
    std::cerr << "[AudioManager] Sound effect not found: " << name << std::endl;
  }
}

void AudioManager::playMusic(const std::string& name, int loops) {
  if (music.find(name) != music.end()) {
    Mix_PlayMusic(music[name], loops);
  } else {
    std::cerr << "[AudioManager] Music not found: " << name << std::endl;
  }
}

void AudioManager::stopMusic() { Mix_HaltMusic(); }

void AudioManager::pauseMusic() { Mix_PauseMusic(); }

void AudioManager::resumeMusic() { Mix_ResumeMusic(); }

void AudioManager::setSoundVolume(int volume) {
  soundVolume = volume;
  Mix_Volume(-1, soundVolume);
}

void AudioManager::setMusicVolume(int volume) {
  musicVolume = volume;
  Mix_VolumeMusic(musicVolume);
}

void AudioManager::toggleMusic() {
  if (Mix_PausedMusic() == 1) {
    Mix_ResumeMusic();
  } else {
    Mix_PauseMusic();
  }
}
