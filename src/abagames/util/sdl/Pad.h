/*
 * $Id:Pad.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Pad.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef PAD_H
#define PAD_H 

#include <SDL.h>
#include <abagames/util/sdl/Input.h>
using namespace std;


class Pad : public Input {
 public:
  enum {
    PAD_UP = 1,
    PAD_DOWN = 2,
    PAD_LEFT = 4,
    PAD_RIGHT = 8,
    PAD_BUTTON1 = 16,
    PAD_BUTTON2 = 32,
    JOYSTICK_AXIS = 16384
  };
  Uint8* keys;
  bool buttonReversed;
  
 private:
  SDL_Joystick* stick;

 public:
  Pad() {};
  ~Pad();
  void openJoystick();
  void handleEvent(SDL_Event* event);
  int getPadState();
  int getButtonState();

 private:
  Pad(const Pad& other);
  Pad& operator=(const Pad& other);
};

#endif
