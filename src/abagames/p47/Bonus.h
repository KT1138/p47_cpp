/*
 * $Id:Bonus.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Bonus.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef BONUS_H
#define BONUS_H

#include <cmath>
#include <tr1/memory>
#include <gl.h>
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
using namespace std;


class Field;
class P47GameManager;
class Ship;


class Bonus : public Actor {
 public:
  static float rate;
  static int bonusScore;

 private:
  enum {
    INHALE_WIDTH = 3,
 ACQUIRE_WIDTH = 1,
    RETRO_CNT = 20,
  };
  static const float BASE_SPEED;
  static const float BOX_SIZE;
  static float speed;
  static Rand rand;
  float fieldLimitX, fieldLimitY;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<P47GameManager> manager;
  Vector pos;
  Vector vel;
  int cnt;
  bool isDown;
  bool isInhaled;
  int inhaleCnt;

 public:
  static void init();
  static void resetBonusScore();
  static void setSpeedRate(float r);
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set(const Vector& p, const Vector* ofs);
  void move();
  void draw();

 private:
  void missBonus();
  void getBonus();
};


class BonusInitializer : public ActorInitializer {
 public:
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<P47GameManager> manager;

 public:
  BonusInitializer(tr1::shared_ptr<Field> field, tr1::shared_ptr<Ship> ship, tr1::shared_ptr<P47GameManager> manager)
    : field(field), ship(ship), manager(manager) {}; 
};

#endif
