/*
 * $Id:LuminousScreen.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * LuminousScreen.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef LUMINOUSSCREEN_H
#define LUMINOUSSCREEN_H

#include <cmath>
#include <string.h>
#include <gl.h>

class LuminousScreen {
 private:
  enum {
    LUMINOUS_TEXTURE_WIDTH_MAX = 64,
    LUMINOUS_TEXTURE_HEIGHT_MAX = 64,
    lmOfsBs = 5
  };
  static int lmOfs[5][2];
  
  GLuint luminousTexture;
  GLuint td[LUMINOUS_TEXTURE_WIDTH_MAX * LUMINOUS_TEXTURE_HEIGHT_MAX * 4 * sizeof(unsigned int)];
  int luminousTextureWidth;
  int luminousTextureHeight;
  int screenWidth;
  int screenHeight;
  float luminous;

 public:
  bool isExist;
  
 public:
 LuminousScreen() : luminousTextureWidth(64), luminousTextureHeight(64) {};
  void init(float luminous, int width, int height);
  void resized(int width, int height);
  void close();
  void startRenderToTexture();
  void endRenderToTexture();
  void draw();

 private:
  void makeLuminousTexture();
  void viewOrtho();
  void viewPerspective();

};

#endif
