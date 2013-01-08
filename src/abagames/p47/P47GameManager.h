/*
 * $Id:P47GameManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47GameManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef P47GAMEMANAGER_H
#define P47GAMEMANAGER_H

#include <cassert>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <gl.h>
#include <SDL.h>
#include <abagames/util/ActorPool.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/util/sdl/GameManager.h>
#include <abagames/p47/EnemyType.h>
#include <abagames/p47/LuminousActorPool.h>
using namespace std;


class P47PrefManager;
class P47Screen;
class BulletMLParser;
class Pad;
class Ship;
class Field;
class Enemy;
class BulletActorPool;
class BarrageManager;
class StageManager;
class Title;


class P47GameManager : public GameManager, public tr1::enable_shared_from_this<P47GameManager> {
 public:
  bool nowait;
  int difficulty, parsecSlot;
  enum { 
    ROLL, LOCK 
  };
  int mode;
  enum {
    TITLE, IN_GAME, GAMEOVER, PAUSE
  };
  int state;

 private:
  tr1::shared_ptr<Pad> pad;
  enum {
    ENEMY_MAX = 32,
    FIRST_EXTEND = 200000,
    EVERY_EXTEND = 500000,
    LEFT_MAX = 4,
    BOSS_WING_NUM = 4
  };
  tr1::shared_ptr<P47PrefManager> prefManager;
  tr1::shared_ptr<P47Screen> screen;
  Rand rand;
  tr1::shared_ptr<Field> field;
  tr1::shared_ptr<Ship> ship;
  tr1::shared_ptr<ActorPool> enemies;
  tr1::shared_ptr<LuminousActorPool> particles;
  tr1::shared_ptr<LuminousActorPool> fragments;
  tr1::shared_ptr<BulletActorPool> bullets;
  tr1::shared_ptr<ActorPool> shots;
  tr1::shared_ptr<ActorPool> rolls;
  tr1::shared_ptr<ActorPool> locks;
  tr1::shared_ptr<ActorPool> bonuses;
  tr1::shared_ptr<BarrageManager> barrageManager;
  tr1::shared_ptr<StageManager> stageManager;
  int left;
  int score, extendScore;
  int cnt;
  int pauseCnt;
  int bossShield;
  tr1::array<int, BOSS_WING_NUM> bossWingShield;
  static const int SLOWDOWN_START_BULLETS_SPEED[2];
  float interval;
  auto_ptr<Title> title;
  bool pPrsd;
  bool btnPrsd;
  int screenShakeCnt;
  float screenShakeIntense;

 public:
  tr1::shared_ptr<P47GameManager> returnSharedThis();
  void init();
  void start();
  void close();
  void addScore(int sc);
  void shipDestroyed();
  void addParticle(const Vector& pos, float deg, float ofs, float speed);
  void addFragments(int n, float x1, float y1, float x2, float y2, 
		    float z, float speed, float deg);
  void addEnemy(const Vector& pos, float d, tr1::shared_ptr<EnemyType> type, BulletMLParser* moveParser);
  void clearBullets();
  void addBoss(const Vector& pos, float d, tr1::shared_ptr<EnemyType> type);
  void addShot(const Vector& pos, float deg);
  void addRoll();
  void addLock();
  void releaseRoll();
  void releaseLock();
  void addBonus(const Vector& pos, const Vector* ofs, int num);
  void setBossShieldMeter(int bs, int s1, int s2, int s3, int s4, float r);
  enum { PRACTICE, NORMAL, HARD, EXTREME, QUIT };
  void startStage(int difficulty, int parsecSlot, int startParsec, int mode);
  void move();
  void draw();
  void setScreenShake(int cnt, float intense);
  
 private:
  void initShipState();
  void startInGame();
  void startTitle();
  void startGameover();
  void startPause();
  void resumePause();
  void stageMove();
  void inGameMove();
  void titleMove();
  void gameoverMove();
  void pauseMove();
  void inGameDraw();
  void titleDraw();
  void gameoverDraw();
  void inGameDrawLuminous();
  void titleDrawLuminous();
  void gameoverDrawLuminous();
  void drawBoard(int x, int y, int width, int height);
  void drawSideBoards();
  void drawScore();
  void drawLeft();
  void drawParsec();
  void drawBox(int x, int y, int w, int h);
  void drawBossShieldMeter();
  void drawSideInfo();
  void inGameDrawStatus();
  void titleDrawStatus();
  void gameoverDrawStatus();
  void pauseDrawStatus();
  void moveScreenShake();
  void setEyepos();
};

#endif 
