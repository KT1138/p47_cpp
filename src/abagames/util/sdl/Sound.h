/*
 * $Id:Sound.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Sound.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
#include <abagames/util/sdl/SDLInitFailedException.h>
using namespace std;


class Sound {
 public:
  static bool noSound;
  enum {
    fadeOutSpeed = 1280
  };
  static const string soundsDir;
  static const string chunksDir;

 protected:
  Mix_Music* music;
  Mix_Chunk* chunk;
  int chunkChannel;
    
 public:
  Sound() {};
  static void init();
  static void close();
  void loadSound(const string& name);
  void loadChunk(const string&  name, int ch);
  void free();
  void playMusic();
  static void fadeMusic();
  static void stopMusic();
  void playChunk();
  void haltChunk();

 private:
  Sound(const Sound& other);
  Sound& operator=(const Sound& other);
};

#endif 
