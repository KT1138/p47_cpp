/*
 * $Id:Ship.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Ship.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/bulletml/Bullet.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/p47/Bonus.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Ship.h>
#include <abagames/p47/SoundManager.h>


bool Ship::isSlow = false;
int Ship::displayListIdx;
const float Ship::SIZE = 0.3;
Rand Ship::rand;
const float Ship::BASE_SPEED = 0.6;
const float Ship::SLOW_BASE_SPEED = 0.3;
const float Ship::FIRE_WIDE_BASE_DEG = 0.7;
const float Ship::FIRE_NARROW_BASE_DEG = 0.5;
const float Ship::TURRET_INTERVAL_LENGTH = 0.2;
const float Ship::FIELD_SPACE = 1.5;


void Ship::init(tr1::shared_ptr<Pad> pad, tr1::shared_ptr<Field> field,
                tr1::shared_ptr<P47GameManager> manager) {
    this->pad = pad;
    this->field = field;
    this->manager = manager;
    pos = Vector();
    ppos = Vector();
    vel = Vector();
    firePos = Vector();

    ttlCnt = 0;
    fieldLimitX = field->size.x - FIELD_SPACE;
    fieldLimitY = field->size.y - FIELD_SPACE;
}

void Ship::start() {
    ppos.x = pos.x = 0;
    ppos.y = pos.y = -field->size.y / 2;
    vel.x = vel.y = 0;
    speed = BASE_SPEED;
    fireWideDeg = FIRE_WIDE_BASE_DEG;
    restart = true;
    cnt = -INVINCIBLE_CNT;
    fireCnt = 0;
    rollLockCnt = 0;
    bank = 0;
    rollCharged = false;
    Bonus::resetBonusScore();
}

void Ship::setSpeedRate(float rate) {
    if (!isSlow)
        baseSpeed = BASE_SPEED * rate;
    else
        baseSpeed = BASE_SPEED * 0.7;
    slowSpeed = SLOW_BASE_SPEED * rate;
}

void Ship::destroyed() {
    if (cnt <= 0)
        return;
    SoundManager::playSe(SoundManager::SHIP_DESTROYED);
    manager->shipDestroyed();
    manager->addFragments(30, pos.x, pos.y, pos.x, pos.y, 0, 0.08, M_PI);
    for (int i = 0; i < 45; i++)
        manager->addParticle(pos, rand.nextFloat(M_PI * 2), 0, 0.6);
    start();
    cnt = -RESTART_CNT;
}

void Ship::move() {
    cnt++;
    if (cnt < -INVINCIBLE_CNT) {
        return;
    }
    if (cnt == 0)
        restart = false;
    int btn = pad->getButtonState();
    if (btn & Pad::PAD_BUTTON2) {
        speed += (slowSpeed - speed) * 0.2;
        fireWideDeg += (FIRE_NARROW_BASE_DEG - fireWideDeg) * 0.1;
        rollLockCnt++;
        if (manager->mode == P47GameManager::ROLL) {
            if (rollLockCnt % 15 == 0) {
                manager->addRoll();
                SoundManager::playSe(SoundManager::ROLL_CHARGE);
                rollCharged = true;
            }
        } else {
            if (rollLockCnt % 10 == 0) {
                manager->addLock();
            }
        }
    } else {
        speed += (baseSpeed - speed) * 0.2;
        fireWideDeg += (FIRE_WIDE_BASE_DEG - fireWideDeg) * 0.1;
        if (manager->mode == P47GameManager::ROLL) {
            if (rollCharged) {
                rollLockCnt = 0;
                manager->releaseRoll();
                SoundManager::playSe(SoundManager::ROLL_RELEASE);
                rollCharged = false;
            }
        } else {
            rollLockCnt = 0;
            manager->releaseLock();
        }
    }
    int ps = pad->getPadState();
    vel.x = vel.y = 0;
    if (ps & Pad::PAD_UP)
        vel.y = speed;
    else if (ps & Pad::PAD_DOWN)
        vel.y = -speed;
    if (ps & Pad::PAD_RIGHT)
        vel.x = speed;
    else if (ps & Pad::PAD_LEFT)
        vel.x = -speed;
    if (vel.x != 0 && vel.y != 0) {
        vel.x *= 0.707;
        vel.y *= 0.707;
    }
    ppos.x = pos.x;
    ppos.y = pos.y;
    pos.x += vel.x;
    pos.y += vel.y;
    bank += (vel.x * BANK_BASE - bank) * 0.1;
    if (pos.x < -fieldLimitX)
        pos.x = -fieldLimitX;
    else if (pos.x > fieldLimitX)
        pos.x = fieldLimitX;
    if (pos.y < -fieldLimitY)
        pos.y = -fieldLimitY;
    else if (pos.y > fieldLimitY)
        pos.y = fieldLimitY;
    if (btn & Pad::PAD_BUTTON1) {
        float td;
        switch (fireCnt % 4) {
        case 0:
            firePos.x = pos.x + TURRET_INTERVAL_LENGTH;
            firePos.y = pos.y;
            td = 0;
            break;
        case 1:
            firePos.x = pos.x + TURRET_INTERVAL_LENGTH;
            firePos.y = pos.y;
            td = fireWideDeg * (fireCnt / 4 % 5) * 0.2;
            break;
        case 2:
            firePos.x = pos.x - TURRET_INTERVAL_LENGTH;
            firePos.y = pos.y;
            td = 0;
            break;
        case 3:
            firePos.x = pos.x - TURRET_INTERVAL_LENGTH;
            firePos.y = pos.y;
            td = - fireWideDeg * (fireCnt / 4 % 5) * 0.2;
            break;
        }
        manager->addShot(firePos, td);
        SoundManager::playSe(SoundManager::SHOT);
        fireCnt++;
    }
    Bullet::target.x = pos.x;
    Bullet::target.y = pos.y;
    ttlCnt++;
}

void Ship::draw() {
    if (cnt < -INVINCIBLE_CNT || (cnt < 0 && (-cnt % 32) < 16))
        return;
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glCallList(displayListIdx + 1);
    glRotatef(bank, 0, 1, 0);
    glTranslatef(-0.5, 0, 0);
    glCallList(displayListIdx);
    glTranslatef(0.2, 0.3, 0.2);
    glCallList(displayListIdx);
    glTranslatef(0, 0, -0.4);
    glCallList(displayListIdx);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(pos.x, pos.y, 0);
    glRotatef(bank, 0, 1, 0);
    glTranslatef(0.5, 0, 0);
    glCallList(displayListIdx);
    glTranslatef(-0.2, 0.3, 0.2);
    glCallList(displayListIdx);
    glTranslatef(0, 0, -0.4);
    glCallList(displayListIdx);
    glPopMatrix();
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(pos.x - 0.7, pos.y - 0.3, 0);
        glRotatef(bank, 0, 1, 0);
        glRotatef(180.0f / 2 - fireWideDeg * 100, 0, 0, 1);
        glRotatef(i * 180.0f / 3 - ttlCnt * 4, 1, 0, 0);
        glTranslatef(0, 0, 0.7);
        glCallList(displayListIdx + 2);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(pos.x + 0.7, pos.y - 0.3, 0);
        glRotatef(bank, 0, 1, 0);
        glRotatef(-180.0f / 2 + fireWideDeg * 100, 0, 0, 1);
        glRotatef(i * 180.0f / 3 - ttlCnt * 4, 1, 0, 0);
        glTranslatef(0, 0, 0.7);
        glCallList(displayListIdx + 2);
        glPopMatrix();
    }
}

void Ship::createDisplayLists() {
    displayListIdx = glGenLists(3);
    glNewList(displayListIdx, GL_COMPILE);
    Screen3D::setColor(0.5, 1, 0.5, 0.2);
    P47Screen::drawBoxSolid(-0.1, -0.5, 0.2, 1);
    Screen3D::setColor(0.5, 1, 0.5, 0.4);
    P47Screen::drawBoxLine(-0.1, -0.5, 0.2, 1);
    glEndList();
    glNewList(displayListIdx + 1, GL_COMPILE);
    Screen3D::setColor(1, 0.2, 0.2, 1);
    P47Screen::drawBoxSolid(-0.2, -0.2, 0.4, 0.4);
    Screen3D::setColor(1, 0.5, 0.5, 1);
    P47Screen::drawBoxLine(-0.2, -0.2, 0.4, 0.4);
    glEndList();
    glNewList(displayListIdx + 2, GL_COMPILE);
    Screen3D::setColor(0.7, 1, 0.5, 0.3);
    P47Screen::drawBoxSolid(-0.15, -0.3, 0.3, 0.6);
    Screen3D::setColor(0.7, 1, 0.5, 0.6);
    P47Screen::drawBoxLine(-0.15, -0.3, 0.3, 0.6);
    glEndList();
}

void Ship::deleteDisplayLists() {
    glDeleteLists(displayListIdx, 3);
}
