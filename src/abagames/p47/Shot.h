/*
 * $Id:Shot.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Shot.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SHOT_H
#define SHOT_H

#include <cmath>
#include <tr1/memory>
#include <abagames/util/Actor.h>
#include <abagames/util/Vector.h>
using namespace std;


class ActorInitializer;
class Field;


/**
 * Player's shots.
 */
class Shot : public Actor {
 public:
  Vector pos;
  enum {
    SPEED = 1
  };
  
 private:
  enum {
    FIELD_SPACE = 1
  };
  static int displayListIdx;
  tr1::shared_ptr<Field> field;
  Vector vel;
  float deg;
  int cnt;
  const int RETRO_CNT;

 public:
 Shot() : RETRO_CNT(4) {};
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set(Vector p, float d);
  void move();
  void draw();
};


class ShotInitializer : public ActorInitializer {
 public:
  tr1::shared_ptr<Field> field;

 public:
  explicit ShotInitializer(tr1::shared_ptr<Field> field) : field(field) {};
};

#endif 
