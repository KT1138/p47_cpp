/*
 * $Id:Lock.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Lock.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef LOCK_H
#define LOCK_H

#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
using namespace std;


class Ship;
class Field;
class P47GameManager;
class Enemy;


class Lock : public Actor {
 public:
  enum {
    SEARCH, SEARCHED, LOCKING, LOCKED, FIRED, HIT, CANCELED
  };
  int state;
  enum {
    LENGTH = 12,
    NO_COLLISION_CNT = 8
  };
  tr1::array<Vector,LENGTH> pos;
  int cnt;
  float lockMinY;
  tr1::shared_ptr<Enemy> lockedEnemy;
  int lockedPart;
  Vector lockedPos;
  bool released;
  
 private:
  static Rand rand;
  Vector vel;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<P47GameManager> manager;
  static const float SPEED;
  enum {
    LOCK_CNT = 8
  };

 public:
  Lock() {};
  static void init();
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set();
  void hit();
  void move();
  void draw();

 private:
  void reset();
};


class LockInitializer : public ActorInitializer {
 public:
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<P47GameManager> manager;

 public:
  LockInitializer(tr1::shared_ptr<Ship> ship, tr1::shared_ptr<Field> field, tr1::shared_ptr<P47GameManager> manager)
    : ship(ship), field(field), manager(manager) {};
};

#endif
