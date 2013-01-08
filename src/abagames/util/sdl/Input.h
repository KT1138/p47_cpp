/*
 * $Id:Input.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Input.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>


class Input {
 public:
  virtual ~Input() {};
  virtual void handleEvent(SDL_Event* event) = 0;
};

#endif
