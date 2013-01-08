/*
 * $Id:BulletActorPool.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * BulletActorPool.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef BULLETACTORPOOL_H
#define BULLETACTORPOOL_H


#include <cmath>
#include <tr1/array>
#include <tr1/memory>
#include <vector>
#include <abagames/util/ActorPool.h>
#include <abagames/util/bulletml/BulletsManager.h>
#include <abagames/p47/MorphBullet.h>
using namespace std;


class ActorInitializer;
class Bullet;
class BulletActor;
class BulletMLParser;
class BulletMLRunner;


class BulletActorPool : public ActorPool, public BulletsManager {
 private:
  int cnt;

 public:
  BulletActorPool(int n, tr1::shared_ptr<ActorInitializer> ini);
  void addBullet(float deg, float speed);
  void addBullet(BulletMLState* state, float deg, float speed);
  tr1::shared_ptr<BulletActor> addBullet(BulletMLRunner* runner,
				    float x, float y, float deg, float speed,
				    float rank,
				    float speedRank, int shape, int color, float size, float xReverse);
  tr1::shared_ptr<BulletActor> addBullet(BulletMLParser* parser,
				    BulletMLRunner* runner,
				    float x, float y, float deg, float speed,
				    float rank,
				    float speedRank, int shape, int color, float size, float xReverse);
  tr1::shared_ptr<BulletActor> addBullet(BulletMLParser* parser,
				    BulletMLRunner* runner,
				    float x, float y, float deg, float speed,
				    float rank,
				    float speedRank, int shape, int color, float size, float xReverse,
				    tr1::array<BulletMLParser*, MorphBullet::MORPH_MAX> morph,
				    int morphNum, int morphCnt);
  void move();
  int getTurn();
  void killMe(Bullet* bullet);
  void clear();
   static void registFunctions(BulletMLRunner* runner);
};

#ifdef __cplusplus
extern "C" {
#endif

  double getAimDirectionWithXRev_(BulletMLRunner* r);

#ifdef __cplusplus
}
#endif


#endif
