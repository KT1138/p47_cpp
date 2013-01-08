/*
 * $Id:Enemy.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Enemy.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef ENEMY_H
#define ENEMY_H

#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <SDL.h>
#include <gl.h>
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/EnemyType.h>
using namespace std;


class ActorPool;
class BulletActor;
class BulletActorPool;
class BulletMLParser;
class Field;
class Lock;
class P47GameManager;
class Ship;


class Enemy : public Actor, public tr1::enable_shared_from_this<Enemy>{
 private:
  struct Battery {
    tr1::array<tr1::shared_ptr<BulletActor>, BatteryType::WING_BATTERY_MAX> topBullet;
    int shield;
    bool damaged;
  };

 public:
  static const float FIELD_SPACE;
  Vector pos;
  tr1::shared_ptr<EnemyType> type;
  tr1::array<Battery, EnemyType::BATTERY_MAX> battery;
  int shield;

 private:
  enum {
    MOVE_POINT_MAX = 8,
    APPEARANCE_CNT = 90,
    APPEARANCE_Z = -15,
    DESTROYED_CNT = 90,
    DESTROYED_Z = -10,
    TIMEOUT_CNT = 90,
    BOSS_TIMEOUT = 1800,
    ENEMY_WING_SCORE = 1000,
    SHOT_DAMAGE = 1,
    ROLL_DAMAGE = 1,
    LOCK_DAMAGE = 7
  };
  static Rand rand;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<BulletActorPool> bullets;
  tr1::shared_ptr<ActorPool> shots;
  tr1::shared_ptr<ActorPool> rolls;
  tr1::shared_ptr<ActorPool> locks;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<P47GameManager> manager;
  int cnt;
  tr1::shared_ptr<BulletActor> topBullet;
  tr1::shared_ptr<BulletActor> moveBullet;
  tr1::array<Vector, MOVE_POINT_MAX> movePoint;
  int movePointNum, movePointIdx;
  float speed, deg;
  bool onRoute;
  float baseDeg;
  int fireCnt, barragePatternIdx;
  float fieldLimitX, fieldLimitY;
  int appCnt, dstCnt, timeoutCnt;
  float z;
  bool isBoss;
  Vector vel;
  int velCnt;
  bool damaged;
  int bossTimer;
  static const int ENEMY_TYPE_SCORE[];

 public:
  tr1::shared_ptr<Enemy> returnSharedThis();
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set(const Vector& p, float d, tr1::shared_ptr<EnemyType> type, BulletMLParser* moveParser);
  void setBoss(const Vector& p, float d, tr1::shared_ptr<EnemyType> type);
  void move();
  void draw();

 private:
  tr1::shared_ptr<BulletActor> setBullet(const Barrage& br, const Vector* ofs, float xr);
  tr1::shared_ptr<BulletActor> setBullet(const Barrage& br, const Vector* ofs);
  void setTopBullets();
  void addBonuses(const Vector* p, int sl);
  void addBonuses();
  void addWingFragments(const BatteryType& bt, int n, float z, float speed, float deg);
  void addFragments(int n, float z, float speed, float deg);
  void addDamage(int dmg);
  void removeBattery(Battery* b, const BatteryType& bt);
  void addDamageBattery(int idx, int dmg);
  enum { NOHIT = -2, HIT = -1 };
  int checkHit(const Vector& p, float xofs, float yofs);
  int checkLocked(const Vector& p, float xofs, tr1::shared_ptr<Lock> lock);
  void checkDamage();
  void removeTopBullets();
  void remove();
  static float BOSS_MOVE_DEG;
  void gotoNextPoint();
  void moveBoss();
  void controlFireCnt();
};


class EnemyInitializer : public ActorInitializer {
 public:
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<BulletActorPool> bullets;
  tr1::shared_ptr<ActorPool> shots;
  tr1::shared_ptr<ActorPool> rolls;
  tr1::shared_ptr<ActorPool> locks;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<P47GameManager> manager;
  
 public:
  EnemyInitializer(tr1::shared_ptr<Field> field, tr1::shared_ptr<BulletActorPool>  bullets, 
		   tr1::shared_ptr<ActorPool> shots, tr1::shared_ptr<ActorPool> rolls,
		   tr1::shared_ptr<ActorPool> locks, tr1::shared_ptr<Ship> ship, 
		   tr1::shared_ptr<P47GameManager> manager)
    : field(field), bullets(bullets), shots(shots), rolls(rolls), locks(locks), ship(ship), manager(manager) {};
};


#endif
