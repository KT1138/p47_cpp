/*
 * $Id:Lock.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Lock.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/p47/Enemy.h>
#include <abagames/p47/EnemyType.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/Lock.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/Ship.h>
#include <abagames/p47/SoundManager.h>


Rand Lock::rand;
const float Lock::SPEED = 0.01;


void Lock::init() {
    rand = Rand();
}

tr1::shared_ptr<Actor> Lock::newActor() {
    return tr1::shared_ptr<Actor>(new Lock());
}

void Lock::init(tr1::shared_ptr<ActorInitializer> ini) {
    tr1::shared_ptr<LockInitializer> li =
        tr1::dynamic_pointer_cast<LockInitializer>(ini);

    ship = li->ship;
    field = li->field;
    manager = li->manager;
}

void Lock::reset() {
    for (int i = 0; i < pos.size(); ++i) {
        pos[i].x = ship->pos.x;
        pos[i].y = ship->pos.y;
    }

    vel.x = rand.nextSignedFloat(1.5);
    vel.y = -2;
    cnt = 0;
}

void Lock::set() {
    reset();
    state = SEARCH;
    lockMinY = field->size.y * 2;
    released = false;
    isExist = true;
}

void Lock::hit() {
   state = HIT;
   cnt = 0;
}

void Lock::move() {
    if (state == SEARCH) {
        isExist = false;
        return;
    } else if (state == SEARCHED) {
        state = LOCKING;
        SoundManager::playSe(SoundManager::LOCK);
    }
    if (state != HIT && state != CANCELED) {
        if (lockedPart < 0) {
            lockedPos.x = lockedEnemy->pos.x; 
            lockedPos.y = lockedEnemy->pos.y;
        } else {
            lockedPos.x = 
                lockedEnemy->pos.x + lockedEnemy->type->batteryType[lockedPart].collisionPos.x;
            lockedPos.y =
                lockedEnemy->pos.y + lockedEnemy->type->batteryType[lockedPart].collisionPos.y;
        }
    }
    switch (state) {
    case LOCKING:
        if (cnt >= LOCK_CNT) {
            state = LOCKED;
            SoundManager::playSe(SoundManager::LASER);
            cnt = 0;
        }
        break;
    case LOCKED:
        if (cnt >= NO_COLLISION_CNT)
            state = FIRED;
    case FIRED:
    case CANCELED:
    {
        if (state != CANCELED) { 
            if (!lockedEnemy->isExist || 
                lockedEnemy->shield <= 0 ||
                (lockedPart >= 0 && lockedEnemy->battery[lockedPart].shield <= 0) ) {
                state = CANCELED;
            } else {
                vel.x += (lockedPos.x - pos[0].x) * SPEED;
                vel.y += (lockedPos.y - pos[0].y) * SPEED;
            }
            vel.x *= 0.9;
            vel.y *= 0.9;
            pos[0].x += (lockedPos.x - pos[0].x) * 0.002 * cnt;
            pos[0].y += (lockedPos.y - pos[0].y) * 0.002 * cnt;
        } else {
            vel.y += (field->size.y * 2 - pos[0].y) * SPEED; 
        }
        for (int i = LENGTH - 1; i > 0; --i) {
            pos[i].x = pos[i-1].x;
            pos[i].y = pos[i-1].y;
        }
        pos[0].x += vel.x;
        pos[0].y += vel.y;
        if (pos[0].y > field->size.y + 5) {
            if (state == CANCELED) {
                isExist = false;
                return;
            } else {
                state = LOCKED;
                SoundManager::playSe(SoundManager::LASER);
                reset();
            }
        }
        float d = atan2(pos[1].x - pos[0].x, pos[1].y - pos[0].y); 
        manager->addParticle(pos[0], d, 0, SPEED * 32);
        break;
    }
    case HIT:
        for (int i = 1; i < LENGTH; ++i) {
            pos[i].x = pos[i-1].x;
            pos[i].y = pos[i-1].y;
        }
        if (cnt > 5) {
            if (!released) {
                state = LOCKED;
                SoundManager::playSe(SoundManager::LASER);
                reset();
            } else {
                isExist = false;
                return;
            }
        }
        break;
    }
    ++cnt;
}

void Lock::draw() {
    switch (state) {
    case LOCKING:
    {
        float y = lockedPos.y - (LOCK_CNT - cnt) * 0.5;
        float d = (LOCK_CNT - cnt) * 0.1;
        float r = (LOCK_CNT - cnt) * 0.5 + 0.8;
        P47Screen::setRetroParam((LOCK_CNT - cnt) / LOCK_CNT, 0.2);
        for (int i = 0; i < 3; i++, d += 6.28 / 3) {
            P47Screen::drawBoxRetro(lockedPos.x + sin(d) * r, 
                                    y + cos(d) * r, 
                                    0.2, 1, d + 3.14 / 2);
        }
        break;
    }
    case LOCKED:
    case FIRED:
    case CANCELED:
    case HIT:
    {
        float d = 0;
        float r = 0.8;
        P47Screen::setRetroParam(0, 0.2);
        for (int i = 0; i < 3; i++, d += 6.28 / 3) {
            P47Screen::drawBoxRetro(lockedPos.x + sin(d) * r, 
                                    lockedPos.y + cos(d) * r, 
                                    0.2, 1, d + 3.14 / 2);
        }
        r = cnt * 0.1;
        for (int i = 0; i < LENGTH - 1; i++, r -= 0.1) {
            float rr = r;
            if (rr < 0)
                rr = 0;
            else if (rr > 1)
                rr = 1;
            P47Screen::setRetroParam(rr, 0.33);
           P47Screen::drawLineRetro(pos[i].x, pos[i].y, pos[i + 1].x, pos[i + 1].y);
        }
    }
    }
}
