/*
 * $Id:Screen.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Screen.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SCREEN_H
#define SCREEN_H

class Screen {
 public:
  virtual ~Screen() {};
  virtual void initSDL() = 0;
  virtual void closeSDL() = 0;
  virtual void flip() = 0;
  virtual void clear() = 0;
};

#endif
