/*
 * $Id:Screen3D.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Screen3D.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SCREEN3D_H
#define SCREEN3D_H

#include <string>
#include <abagames/util/sdl/Screen.h>
using namespace std;


class Screen3D : public Screen {
 public:
  static float brightness;
  static int width;
  static int height;
  static bool lowres;
  static bool windowMode;
  static float nearPlane;
  static float farPlane;

 private:
  void screenResized();
  
 protected:
  virtual void init() = 0;
  virtual void close() = 0;
  void setCaption(string name);

 public:
  virtual ~Screen3D() {};
  void initSDL();
  void resized(int width, int height);
  void closeSDL();
  void flip();
  void clear();
  void handleError();
  static void setColor(float r, float g, float b, float a);
};

#endif
