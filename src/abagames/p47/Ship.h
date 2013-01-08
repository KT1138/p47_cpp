/*
 * $Id:Ship.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Ship.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SHIP_H
#define SHIP_H

#include <cmath>
#include <tr1/memory>
#include <gl.h>
#include <abagames/util/sdl/Pad.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/Field.h>
using namespace std;


class P47GameManager;


class Ship {
 public:
  static bool isSlow;
  static int displayListIdx;
  Vector pos;
  static const float SIZE;
  bool restart;
  enum {
    RESTART_CNT = 300,
    INVINCIBLE_CNT = 228
  };
  int cnt;

 private:
  static Rand rand;
  tr1::shared_ptr<Pad> pad;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<P47GameManager> manager;
  Vector ppos;
  static const float BASE_SPEED;
  static const float SLOW_BASE_SPEED;
  float baseSpeed, slowSpeed;
  float speed;
  Vector vel;
  enum {
    BANK_BASE = 50
  };
  float bank;
  Vector firePos;
  float fireWideDeg;
  static const float FIRE_WIDE_BASE_DEG;
  static const float FIRE_NARROW_BASE_DEG;
  int fireCnt;
  static const float TURRET_INTERVAL_LENGTH;
  int ttlCnt;
  static const float FIELD_SPACE;
  float fieldLimitX, fieldLimitY;
  int rollLockCnt;
  bool rollCharged;

 public:
  void init(tr1::shared_ptr<Pad> pad, tr1::shared_ptr<Field> field,
	    tr1::shared_ptr<P47GameManager> manager);
  void start();
  void setSpeedRate(float rate);
  void destroyed();
  void move();
  void draw();
  static void createDisplayLists();
  static void deleteDisplayLists();
};

#endif
