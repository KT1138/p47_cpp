/*
 * $Id:BulletActor.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * BulletActor.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef BULLETACTOR_H
#define BULLETACTOR_H

#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <gl.h>
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/P47Bullet.h>
using namespace std;


class BulletMLRunner;
class BulletMLParser;
class Field;
class Ship;


class BulletActor : public Actor {
 public:
  tr1::shared_ptr<P47Bullet> bullet;
  static float totalBulletsSpeed;
  enum {
    BULLET_SHAPE_NUM = 7,
    BULLET_COLOR_NUM = 4,
  };

 private:
  enum {
    BULLET_DISAPPEAR_CNT = 180
  };
  static const float FIELD_SPACE;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<Ship> ship;
  static int nextId;
  static int displayListIdx;
  bool isSimple;
  bool isTop;
  bool isVisible;
  BulletMLParser* parser;
  Vector ppos;
  const float SHIP_HIT_WIDTH;
  int cnt;
  const float RETRO_CNT;
  float rtCnt;
  bool shouldBeRemoved;
  bool backToRetro;
  static const float shapePos[][8][2];
  static const float SHAPE_POINT_SIZE;
  static const float SHAPE_BASE_COLOR_R;
  static const float SHAPE_BASE_COLOR_G;
  static const float SHAPE_BASE_COLOR_B;
  static const float bulletColor[4][3];

 public:
 BulletActor() : SHIP_HIT_WIDTH(0.2), RETRO_CNT(24) {};
  static void init();
  static void resetTotalBulletsSpeed();
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set(BulletMLRunner* runner,
	   float x, float y, float deg, float speed, float rank,
	   float speedRank, int shape, int color, float size, float xReverse) ;
  void set(BulletMLRunner* runner,
	   float x, float y, float deg, float speed, float rank,
	   float speedRank, int shape, int color, float size, float xReverse,
	   tr1::array<BulletMLParser*, MorphBullet::MORPH_MAX> morph,
	   int morphNum, int morphIdx, int morphCnt);
  void set(float x, float y, float deg, float speed, float rank,
	   float speedRank, int shape, int color, float size, float xReverse);
  void setInvisible();
  void setTop(BulletMLParser* parser);
  void rewind();
  void remove();
  void toRetro();
  void move();
  void draw();
  static void createDisplayLists();
  static void deleteDisplayLists();

 private:
  BulletActor(const BulletActor& other);
  BulletActor& operator=(const BulletActor& other);
  void start(float speedRank, int shape, int color, float size, float xReverse);
  void removeForced();
  void checkShipHit();
  void drawRetro(float d);
};


class BulletActorInitializer : public ActorInitializer {
 public:
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<Ship> ship;

 public:
  BulletActorInitializer(tr1::shared_ptr<Field> field, tr1::shared_ptr<Ship> ship)
    : field(field), ship(ship) {};
};

#endif
