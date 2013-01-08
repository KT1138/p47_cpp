/*
 * $Id:LetterRender.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * LetterRender.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef LETTERRENDER_H
#define LETTERRENDER_H

#include <string>
#include <gl.h>
using namespace std;


class LetterRender {
 public:
  static int displayListIdx;
  static int colorIdx;

 private:
  enum {
    LETTER_NUM = 42
  };
  static float spData[][16][5];

 public:
  enum {WHITE, RED};
  enum {TO_RIGHT, TO_DOWN, TO_LEFT, TO_UP};
  //  static void drawString(char str[], float lx, float y, float s, int d);
  static void drawString(string str, float lx, float y, float s, int d);
  static void drawNum(int num, float lx, float y, float s, int d);
  static void createDisplayLists();
  static void deleteDisplayLists();
  static void changeColor(int c);

 private:
  //  static void changeColor(int c);
  static void drawLetter(int n, float x, float y, float s, float d);
  static void drawBox(float x, float y, float width, float height,
		      float r, float g, float b);
  static void drawLetter(int idx, float r, float g, float b);

};

#endif
