/*
 * $Id:Field.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Field.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef FIELD_H
#define FIELD_H

#include <cmath>
#include <string>
#include <tr1/array>
#include <SDL.h>
#include <gl.h>
#include <abagames/util/Vector.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/p47/P47Screen.h>
using namespace std;


class P47GameManager;


class Field {
 public:
  enum {
    TYPE_NUM = 4
  };
  Vector size;
  float eyeZ;
  float aimZ;
  float aimSpeed;

 private:
  enum {
    RING_NUM = 16,
    RING_ANGLE_INT = 10,
    RING_POS_NUM = 16,
    RING_RADIUS = 10
  };
  static int displayListIdx;
  static tr1::array<Vector, RING_POS_NUM> ringPos;
  static const float RING_DEG;
  static const float RING_SIZE;
  float roll, yaw;
  float z;
  float speed;
  float yawYBase, yawZBase;
  float aimYawYBase, aimYawZBase;
  float r, g, b;

 public:
  static void createDisplayLists();
  static void deleteDisplayLists();
  void init();
  void setColor(int mode);
  void move();
  void setType(int type);
  void draw();
  bool checkHit(const Vector& p);
  bool checkHit(const Vector& p, float space);

 private:
  static void writeOneRing();
};

#endif
