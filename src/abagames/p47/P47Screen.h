/*
 * $Id:P47Screnn.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47Screen.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef P47SCREEN_H
#define P47SCREEN_H 

#include <string>
#include <cmath>
#include <tr1/memory>
#include <SDL.h>
#include <gl.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/util/Rand.h>
using namespace std;


class Rand;
class LuminousScreen;

class P47Screen :  public Screen3D {
 public:
  static string CAPTION;
  static float luminous;
  static float retroR, retroG, retroB, retroA;

 private:
  static float retro, retroSize;
  static float retroZ;
  static Rand rand;
  tr1::shared_ptr<LuminousScreen> luminousScreen;

 public:
  void startRenderToTexture();
  void endRenderToTexture();
  void drawLuminous();
  void resized(int width, int height);
  void viewOrthoFixed();
  void viewPerspective();
  static void setRetroParam(float r, float sz);
  static void setRetroColor(float r, float g, float b, float a);
  static void setRetroZ(float z);
  static void drawLineRetro(float x1, float y1, float x2, float y2);
  static void drawBoxRetro(float x, float y, float width, float height, float deg);
  static void drawBoxSolid(float x, float y, float width, float height);
  static void drawBoxLine(float x, float y, float width, float height);

 protected:
  void init();
  void close();
};

#endif
