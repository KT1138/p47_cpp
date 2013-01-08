/*
 * $Id:StageManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * StageManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/BarrageManager.h>
#include <abagames/p47/EnemyType.h>
using namespace std;


class BulletMLParser;
class P47GameManager;
class Field;


class StageManager {
 public:
  enum { TOP, SIDE, BACK };
  enum { ONE_SIDE, ALTERNATE_, BOTH_SIDES };
  enum { RANDOM, FIXED };
  enum { SMALL, MIDDLE, LARGE };

 private:
  struct EnemyAppearance {
  public:
    tr1::shared_ptr<EnemyType> type;
    BulletMLParser* moveParser;
    int point, pattern, sequence;
    float pos;
    int num, interval, groupInterval;
    int cnt, left, side;
  };

 public:
  enum {
    STAGE_TYPE_NUM = 4,
    SIMULTANEOUS_APPEARANCE_MAX = 4,
    SMALL_ENEMY_TYPE_MAX = 3,
    MIDDLE_ENEMY_TYPE_MAX = 4,
    LARGE_ENEMY_TYPE_MAX = 2
  };
  int parsec;
  bool bossSection;

 private:
  Rand rand;
  tr1::shared_ptr<P47GameManager> gameManager;
  tr1::shared_ptr<BarrageManager> barrageManager;
  tr1::shared_ptr<Field> field;
  tr1::array<EnemyAppearance, SIMULTANEOUS_APPEARANCE_MAX> appearance;
  tr1::array<tr1::shared_ptr<EnemyType>, SMALL_ENEMY_TYPE_MAX> smallType;
  tr1::array<tr1::shared_ptr<EnemyType>, MIDDLE_ENEMY_TYPE_MAX> middleType;
  tr1::array<tr1::shared_ptr<EnemyType>, LARGE_ENEMY_TYPE_MAX> largeType;
  tr1::shared_ptr<EnemyType> middleBossType;
  tr1::shared_ptr<EnemyType> largeBossType;
  int apNum;
  Vector apos;
  int sectionCnt, sectionIntervalCnt, section;
  float rank, rankInc;
  int middleRushSectionNum;
  bool middleRushSection;
  int stageType;
  enum {
    MIDDLE_RUSH_SECTION_PATTERN = 6
  };
  static const int apparancePattern[][7][3];

 public:
  void init(tr1::shared_ptr<P47GameManager> gm, tr1::shared_ptr<BarrageManager> bm, 
	    tr1::shared_ptr<Field> f);
  void setRank(float baseRank, float inc, int startParsec, int type);
  void move();

 private:
  void createEnemyData();
  void setAppearancePattern(EnemyAppearance* ap);
  void setSmallAppearance(EnemyAppearance* ap);
  void setMiddleAppearance(EnemyAppearance* ap);
  void setLargeAppearance(EnemyAppearance* ap);
  void setAppearance(EnemyAppearance* ap, int type);
  void createSectionData();
  void createStage();
  void gotoNextSection();
};

#endif
