/*
 * $Id:Bullet.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Bullet.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef BULLET_H
#define BULLET_H

#include <cmath>
#include <abagames/util/Vector.h>
#include <abagames/util/Rand.h>
using namespace std;


class BulletsManager;
class BulletMLRunner;
class BulletMLState;


class Bullet {
 public:
  static Bullet* now;
  static Vector target;
  Vector pos;
  Vector acc;
  float deg;
  float speed;
  float rank;
  int id;

 private:
  static Rand rand;
  static BulletsManager* manager;
  BulletMLRunner* runner;

 public:
  explicit Bullet(int id) : id(id) {};
  virtual ~Bullet() {};
  static void setBulletsManager(BulletsManager* bm);
  static double getRand();
  static void addBullet(float deg, float speed);
  static void addBullet(BulletMLState* state, float deg, float speed);
  static int getTurn();
  void set(float x, float y, float deg, float speed, float rank);
  void set(BulletMLRunner* runner,
	   float x, float y, float deg, float speed, float rank);
  void setRunner(BulletMLRunner* runner);
  void move();
  bool isEnd();
  void kill();
  void remove();

 private:
  Bullet(const Bullet&);
  Bullet& operator=(const Bullet&);
};

float rtod(float a);
float dtor(float a);

extern "C" {
  double getBulletDirection_(BulletMLRunner* r);
  double getAimDirection_(BulletMLRunner* r);
  double getBulletSpeed_(BulletMLRunner* r);
  double getDefaultSpeed_(BulletMLRunner* r);
  double getRank_(BulletMLRunner* r);
  void createSimpleBullet_(BulletMLRunner* r, double d, double s);
  void createBullet_(BulletMLRunner* r, BulletMLState* state, double d, double s);
  int getTurn_(BulletMLRunner* r);
  void doVanish_(BulletMLRunner* r);
  void doChangeDirection_(BulletMLRunner* r, double d);
  void doChangeSpeed_(BulletMLRunner* r, double s);
  void doAccelX_(BulletMLRunner* r, double sx);
  void doAccelY_(BulletMLRunner* r, double sy);
  double getBulletSpeedX_(BulletMLRunner* r);
  double getBulletSpeedY_(BulletMLRunner* r);
  double getRand_(BulletMLRunner *r);
}

#endif
