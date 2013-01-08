/*
 * $Id:Fragment.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Fragment.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <gl.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/LuminousActor.h>
using namespace std;


class Actor;


class Fragment : public LuminousActor {
 public:
  static const float R;
  static const float G;
  static const float B;

 private:
  enum {
    POINT_NUM = 2
  };
  static Rand rand;
  tr1::array<Vector, POINT_NUM> pos;
  tr1::array<Vector, POINT_NUM> vel;
  Vector impact;
  float z;
  float lumAlp;
  float retro;
  int cnt;
  
 public:
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set(float x1, float y1, float x2, float y2, float z, float speed, float deg);
  void move();
  void draw();
  void drawLuminous();
};


class FragmentInitializer : public ActorInitializer {
};

#endif
