/*
 * $Id:BulletActorPool.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * BulletActorPool.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <assert.h>
#include <bulletml.h>
#include <bulletmlparser.h>
#include <bulletmlrunner.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/ActorPool.h>
#include <abagames/util/Vector.h>
#include <abagames/util/bulletml/Bullet.h>
#include <abagames/p47/BulletActor.h>
#include <abagames/p47/BulletActorPool.h>
#include <abagames/p47/P47Bullet.h>


BulletActorPool::BulletActorPool(int n, tr1::shared_ptr<ActorInitializer> ini)
    : cnt(0),
      ActorPool::ActorPool(n, auto_ptr<BulletActor>(new BulletActor()).get(), ini)
{
    Bullet::setBulletsManager(this);
    BulletActor::init();
}

void BulletActorPool::addBullet(float deg, float speed) {
    tr1::shared_ptr<BulletActor> ba = 
        tr1::dynamic_pointer_cast<BulletActor>(getInstance());
    if (!ba)
        return;
    P47Bullet* rb = 
        dynamic_cast<P47Bullet*>(Bullet::now);
    if (rb->isMorph) {
        BulletMLRunner* runner = BulletMLRunner_new_parser(rb->morphParser[rb->morphIdx]);
        BulletActorPool::registFunctions(runner);
        ba->set(runner, Bullet::now->pos.x, Bullet::now->pos.y, deg, speed,
                Bullet::now->rank, 
                rb->speedRank, rb->shape, rb->color, rb->bulletSize, rb->xReverse,
                rb->morphParser, rb->morphNum, rb->morphIdx + 1, rb->morphCnt - 1);
    } else {
        ba->set(Bullet::now->pos.x, Bullet::now->pos.y, deg, speed, 
                Bullet::now->rank,
                rb->speedRank, rb->shape, rb->color, rb->bulletSize, rb->xReverse);
    }
}

void BulletActorPool::addBullet(BulletMLState* state, float deg, float speed) {
    tr1::shared_ptr<BulletActor> ba = 
        tr1::dynamic_pointer_cast<BulletActor>(getInstance());
    if (!ba)
        return;

    BulletMLRunner* runner = BulletMLRunner_new_state(state);
    registFunctions(runner);

    P47Bullet* rb = 
        dynamic_cast<P47Bullet*>(Bullet::now);

    if (rb->isMorph)
        ba->set(runner, Bullet::now->pos.x, Bullet::now->pos.y, deg, speed, 
                Bullet::now->rank, 
                rb->speedRank, rb->shape, rb->color, rb->bulletSize, rb->xReverse,
                rb->morphParser, rb->morphNum, rb->morphIdx, rb->morphCnt);
    else
        ba->set(runner, Bullet::now->pos.x, Bullet::now->pos.y, deg, speed, 
                Bullet::now->rank, 
                rb->speedRank, rb->shape, rb->color, rb->bulletSize, rb->xReverse);
}

tr1::shared_ptr<BulletActor> BulletActorPool::addBullet(BulletMLRunner* runner, 
                                                   float x, float y, float deg, float speed,
                                                   float rank, 
                                                   float speedRank, int shape, int color, 
                                                   float size, float xReverse) {
    tr1::shared_ptr<BulletActor> ba = 
        tr1::dynamic_pointer_cast<BulletActor>(getInstance());
    if (!ba) {
        tr1::shared_ptr<BulletActor> null;
        return null;
    }
    ba->set(runner, x, y, deg, speed, rank, speedRank, shape, color, size, xReverse);
    ba->setInvisible();
    return ba;
}

tr1::shared_ptr<BulletActor> BulletActorPool::addBullet(BulletMLParser* parser,
                                                   BulletMLRunner* runner, 
                                                   float x, float y, float deg, float speed,
                                                   float rank,
                                                   float speedRank, int shape, int color,
                                                   float size, float xReverse) {
    tr1::shared_ptr<BulletActor> ba = 
        addBullet(runner, x, y, deg, speed, rank, speedRank,
                  shape, color, size, xReverse);
    if (!ba) {
        tr1::shared_ptr<BulletActor> null;
        return null;
    }
    ba->setTop(parser);
    return ba;
}

tr1::shared_ptr<BulletActor> BulletActorPool::addBullet(BulletMLParser* parser,
                                                   BulletMLRunner* runner,
                                                   float x, float y, float deg, float speed, 
                                                   float rank,
                                                   float speedRank, int shape, int color,
                                                   float size, float xReverse,
                                                   tr1::array<BulletMLParser*, MorphBullet::MORPH_MAX> morph,
                                                   int morphNum, int morphCnt) {
    tr1::shared_ptr<BulletActor> ba = 
        tr1::dynamic_pointer_cast<BulletActor>(getInstance());
    if (!ba) {
        tr1::shared_ptr<BulletActor> null;
        return null;
    }
    ba->set(runner, x, y, deg, speed, rank, 
            speedRank, shape, color, size, xReverse,
            morph, morphNum, 0, morphCnt);
    ba->setTop(parser);
    return ba;
}

void BulletActorPool::move() {
    ActorPool::move();
    ++cnt;
}

int BulletActorPool::getTurn() {
    return cnt;
}

void BulletActorPool::killMe(Bullet* bullet) {
    assert(tr1::dynamic_pointer_cast<BulletActor>(actor[bullet->id])->bullet->id ==
           bullet->id);
    tr1::dynamic_pointer_cast<BulletActor>(actor[bullet->id])->remove();
}

void BulletActorPool::clear() {
    for (int i = 0; i < actor.size(); ++i) {
        if (actor[i]->isExist)
            tr1::dynamic_pointer_cast<BulletActor>(actor[i])->remove();
    }
}

void BulletActorPool::registFunctions(BulletMLRunner* runner) {
    BulletMLRunner_set_getBulletDirection(runner, &getBulletDirection_);
    BulletMLRunner_set_getAimDirection(runner, &getAimDirectionWithXRev_);
    BulletMLRunner_set_getBulletSpeed(runner, &getBulletSpeed_);
    BulletMLRunner_set_getDefaultSpeed(runner, &getDefaultSpeed_);
    BulletMLRunner_set_getRank(runner, &getRank_);
    BulletMLRunner_set_createSimpleBullet(runner, &createSimpleBullet_);
    BulletMLRunner_set_createBullet(runner, &createBullet_);
    BulletMLRunner_set_getTurn(runner, &getTurn_);
    BulletMLRunner_set_doVanish(runner, &doVanish_);

    BulletMLRunner_set_doChangeDirection(runner, &doChangeDirection_);
    BulletMLRunner_set_doChangeSpeed(runner, &doChangeSpeed_);
    BulletMLRunner_set_doAccelX(runner, &doAccelX_);
    BulletMLRunner_set_doAccelY(runner, &doAccelY_);
    BulletMLRunner_set_getBulletSpeedX(runner, &getBulletSpeedX_);
    BulletMLRunner_set_getBulletSpeedY(runner, &getBulletSpeedY_);
    BulletMLRunner_set_getRand(runner, &getRand_);
}

#ifdef __cplusplus
extern "C" {
#endif

    double getAimDirectionWithXRev_(BulletMLRunner* r) {
        Vector b = Bullet::now->pos;
        Vector t = Bullet::target;
        float xrev = dynamic_cast<P47Bullet*>(Bullet::now)->xReverse;
        return rtod(atan2(t.x - b.x, t.y - b.y) * xrev);
    }

#ifdef __cplusplus
}

#endif

