/*
 * $Id:EnemyType.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * EnemyType.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef ENEMYTYPE_H
#define ENEMYTYPE_H

#include <cassert>
#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/BarrageManager.h>
#include <abagames/p47/MorphBullet.h>
using namespace std;


class BulletMLParser;


class Barrage {
 public:
  BulletMLParser* parser;
  tr1::array<BulletMLParser*, MorphBullet::MORPH_MAX> morphParser;
  int morphNum, morphCnt;
  float rank, speedRank, morphRank;
  int shape, color;
  float bulletSize;
  float xReverse;

 public:
  Barrage();

 private:
  Barrage(const Barrage& other);
  Barrage& operator=(const Barrage& other);
};


class BatteryType {
 public:
  enum {
    WING_SHAPE_POINT_NUM = 3,
    WING_BATTERY_MAX = 3,
    BARRAGE_PATTERN_MAX = 8
  };
  tr1::array<Vector, WING_SHAPE_POINT_NUM> wingShapePos;
  Vector collisionPos;
  Vector collisionSize;
  tr1::array<Vector, WING_BATTERY_MAX> batteryPos;
  int batteryNum;
  float r, g, b;
  tr1::array<Barrage, BARRAGE_PATTERN_MAX> barrage;
  bool xReverseAlternate;
  int shield;
};


class EnemyType {
 public:
  enum {
    BARRAGE_PATTERN_MAX = BatteryType::BARRAGE_PATTERN_MAX,
    BODY_SHAPE_POINT_NUM = 4,
    BATTERY_MAX = 4,
    ENEMY_TYPE_MAX = 32,
    BULLET_SHAPE_NUM = 7,
    BULLET_COLOR_NUM = 4
  };
  // Whether each type of the enemy is exist or not.
  static tr1::array<bool, ENEMY_TYPE_MAX> isExist;
  tr1::array<Vector, BODY_SHAPE_POINT_NUM> bodyShapePos;
  tr1::array<Barrage, BARRAGE_PATTERN_MAX> barrage;
  Vector collisionSize;
  bool wingCollision;
  float r, g, b;
  float retroSize;
  tr1::array<BatteryType, BATTERY_MAX> batteryType;
  int batteryNum;
  int shield;
  int fireInterval, firePeriod, barragePatternNum;
  int id;
  enum {
    SMALL, MIDDLE, LARGE, MIDDLEBOSS, LARGEBOSS,
  };
  int type;
  // To avoid the forward reference.
  enum { ROLL, LOCK };

 private:
  static Rand rand;
  static tr1::shared_ptr<BarrageManager> barrageManager;
  static int idCnt;
  static tr1::array<bool, BarrageManager::BARRAGE_MAX> usedMorphParser;
  // To avoid using the same morph pattern.
  //  private static bool usedMorphParser[BarrageManager.BARRAGE_MAX];
  // Barrage intense.
  enum {
    NORMAL, WEAK, VERYWEAK, MORPHWEAK
  };
  float er, eg, eb;
  int ect;
  static const float enemySize[][9];

 public:
  EnemyType();
  static void init(tr1::shared_ptr<BarrageManager> manager);
  static void clearIsExistList();
  void setSmallEnemyType(float rank, int mode);
  void setMiddleEnemyType(float rank, int mode);
  void setLargeEnemyType(float rank, int mode);
  void setMiddleBossEnemyType(float rank, int mode);
  void setLargeBossEnemyType(float rank, int mode);

  
 private:
  void setBarrageType(Barrage* br, int btn, int mode);
  void setBarrageRank(Barrage* br, float rank, int intense, int mode);
  void setBarrageRankSlow(Barrage* br, float rank, int intense, int mode, float slow);
  void setBarrageShape(Barrage* br, float size);
  void setEnemyColorType();
  void createEnemyColor();
  void setEnemyShapeAndWings(int size);
  void setBattery(float rank, int n, int barrageType, int barrageIntense,
		  int idx, int ptnIdx, float slow, int mode);
};

#endif
