/*
 * $Id:Roll.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Roll.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef ROLL_H
#define ROLL_H

#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Vector.h>
using namespace std;


class Ship;
class Field;
class P47GameManager;


/**
 * Roll shot.
 */
class Roll : public Actor {
 public:
  bool released;
  enum {
    LENGTH = 4,
    NO_COLLISION_CNT = 45
  };
  tr1::array<Vector, LENGTH> pos;
  int cnt;

 private:
  static const float BASE_LENGTH;
  static const float BASE_RESISTANCE;
  static const float BASE_SPRING;
  static const float BASE_SIZE;
  static const float BASE_DIST;
  static const float SPEED;
  tr1::array<Vector, LENGTH> vel;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<P47GameManager> manager;
  float dist;

 public:
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set();
  void move();
  void draw();
};


class RollInitializer : public ActorInitializer {
 public:
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<P47GameManager> manager;

 public:
  RollInitializer(tr1::shared_ptr<Ship> ship, tr1::shared_ptr<Field> field,
		  tr1::shared_ptr<P47GameManager> manager)
    : ship(ship), field(field), manager(manager) {};
};
#endif
