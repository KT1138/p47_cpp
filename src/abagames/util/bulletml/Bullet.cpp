/*
 * $Id:Bullet.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Bullet.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <bulletml.h>
#include <bulletmlrunner.h>
#include <abagames/util/bulletml/Bullet.h>
#include <abagames/util/bulletml/BulletsManager.h>


Bullet* Bullet::now;
Vector Bullet::target;
Rand Bullet::rand;
BulletsManager* Bullet::manager = 0;


void Bullet::setBulletsManager(BulletsManager* bm) {
    manager = bm;
    target = Vector();
    target.x = target.y = 0;
}

double Bullet::getRand() {
    return rand.nextFloat(1);
}

void Bullet::addBullet(float deg, float speed) {
    manager->addBullet(deg, speed);
}

void Bullet::addBullet(BulletMLState* state, float deg, float speed) {
    manager->addBullet(state, deg, speed);
}

int Bullet::getTurn() {
    return manager->getTurn();
}

void Bullet::set(float x, float y, float deg, float speed, float rank) {
    pos.x = x; pos.y = y;
    acc.x = acc.y = 0;
    this->deg = deg;
    this->speed = speed;
    this->rank = rank;
//    delete runner;
    runner = 0;
}

void Bullet::setRunner(BulletMLRunner* runner) {
    this->runner = runner;
}

void Bullet::set(BulletMLRunner* runner, 
		 float x, float y, float deg, float speed, float rank) {
    set(x, y, deg, speed, rank);
    setRunner(runner);
}

void Bullet::move() {
//    delete now;  // "now"をデリートするとセグメ違反が起こる（"now"をtr1::shared_ptrにしても同様）
    now = this;

    if (!BulletMLRunner_isEnd(runner)) {
        BulletMLRunner_run(runner);
    }
    // if (runner->isEnd())
    //     runner->run();
}

bool Bullet::isEnd() {
    return BulletMLRunner_isEnd(runner);
//    return runner->isEnd();
}

void Bullet::kill() {
    manager->killMe(this);
}

void Bullet::remove() {
    if (runner) {
        BulletMLRunner_delete(runner);  // "delete runner;"と等価
//        delete runner;  //"delete"はしなくていいみたい（4/15）
//        runner = 0;
    }
}


const float VEL_SS_SDM_RATIO = 62.0 / 10;
const float VEL_SDM_SS_RATIO = 10.0 / 62;


float rtod(float a) {
    return a * 180 / M_PI;
}

float dtor(float a) {
    return a * M_PI / 180;
}


double getBulletDirection_(BulletMLRunner* r) {
    return rtod(Bullet::now->deg);
}
double getAimDirection_(BulletMLRunner* r) {
    Vector b = Bullet::now->pos;
    Vector t = Bullet::target;
    return rtod(atan2(t.x - b.x, t.y - b.y));
}
double getBulletSpeed_(BulletMLRunner* r) {
    return Bullet::now->speed * VEL_SS_SDM_RATIO;
}
double getDefaultSpeed_(BulletMLRunner* r) {
    return 1;
}
double getRank_(BulletMLRunner* r) {
    return Bullet::now->rank;
}
void createSimpleBullet_(BulletMLRunner* r, double d, double s) {
    Bullet::addBullet(dtor(d), s * VEL_SDM_SS_RATIO);
}
void createBullet_(BulletMLRunner* r, BulletMLState* state, double d, double s) {
    Bullet::addBullet(state, dtor(d), s * VEL_SDM_SS_RATIO);
}
int getTurn_(BulletMLRunner* r) {
    return Bullet::getTurn();
}
void doVanish_(BulletMLRunner* r) {
    Bullet::now->kill();
}
void doChangeDirection_(BulletMLRunner* r, double d) {
    Bullet::now->deg = dtor(d);
}
void doChangeSpeed_(BulletMLRunner* r, double s) {
    Bullet::now->speed = s * VEL_SDM_SS_RATIO;
}
void doAccelX_(BulletMLRunner* r, double sx) {
    Bullet::now->acc.x = sx * VEL_SDM_SS_RATIO;
}
void doAccelY_(BulletMLRunner* r, double sy) {
    Bullet::now->acc.y = sy * VEL_SDM_SS_RATIO;
}
double getBulletSpeedX_(BulletMLRunner* r) {
    return Bullet::now->acc.x;
}
double getBulletSpeedY_(BulletMLRunner* r) {
    return Bullet::now->acc.y;
}
double getRand_(BulletMLRunner *r) {
    return Bullet::getRand();
}


