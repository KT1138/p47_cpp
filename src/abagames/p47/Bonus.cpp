/*
 * $Id:Bonus.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Bonus.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/p47/Bonus.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Ship.h>
#include <abagames/p47/SoundManager.h>


float Bonus::rate;
int Bonus::bonusScore;
const float Bonus::BASE_SPEED = 0.1;
const float Bonus::BOX_SIZE = 0.4;
float Bonus::speed;
Rand Bonus::rand;


void Bonus::init() {
    rand = Rand();
}

void Bonus::resetBonusScore() {
    bonusScore = 10;
}

void Bonus::setSpeedRate(float r) {
    rate = r;
    speed = BASE_SPEED * rate;
}

tr1::shared_ptr<Actor> Bonus::newActor() {
    return tr1::shared_ptr<Actor>(new Bonus());
}

void Bonus::init(tr1::shared_ptr<ActorInitializer> ini) {

    tr1::shared_ptr<BonusInitializer> bi =
        tr1::dynamic_pointer_cast<BonusInitializer>(ini);

    field = bi->field; 
    ship = bi->ship;
    manager = bi->manager;

    pos = Vector();
    vel = Vector();
    fieldLimitX = field->size.x / 6 * 5;
    fieldLimitY = field->size.y / 10 * 9;
}

void Bonus::set(const Vector& p, const Vector* ofs) {
    pos.x = p.x;
    pos.y = p.y;
    if (ofs) {
        pos.x += ofs->x;
        pos.y += ofs->y;
    }
    vel.x = rand.nextSignedFloat(0.07);
    vel.y = rand.nextSignedFloat(0.07);
    cnt = 0;
    inhaleCnt = 0;
    isDown = true;
    isInhaled = false;
    isExist = true;
}

void Bonus::missBonus() {
    resetBonusScore();
}

void Bonus::getBonus() {
    SoundManager::playSe(SoundManager::GET_BONUS);
    manager->addScore(bonusScore);
    if (bonusScore < 1000)
        bonusScore += 10;
}

void Bonus::move() {
    pos.x += vel.x;
    pos.y += vel.y;
    vel.x -= vel.x / 50;
    if (pos.x > fieldLimitX) {
        pos.x = fieldLimitX;
        if (vel.x > 0)
            vel.x = -vel.x;
    } else if (pos.x < -fieldLimitX) {
        pos.x = -fieldLimitX;
        if (vel.x < 0)
            vel.x = -vel.x;
    }
    if (isDown) {
        vel.y += (-speed - vel.y) / 50;
        if (pos.y < -fieldLimitY) {
            isDown = false;
            pos.y = -fieldLimitY;
            vel.y = speed;
        }
    } else {
        vel.y += (speed - vel.y) / 50;
        if (pos.y > fieldLimitY) {
            missBonus();
            isExist = false;
            return;
        }
    }
    ++cnt;
    if (cnt < RETRO_CNT)
        return;
    float d = pos.dist(ship->pos);
    if (d < ACQUIRE_WIDTH * (1 + static_cast<float>(inhaleCnt) * 0.2) && ship->cnt >= -Ship::INVINCIBLE_CNT) {
        getBonus();
        isExist = false;
        return;
    }
    if (isInhaled) {
        ++inhaleCnt;
        float ip = (INHALE_WIDTH - d) / 48;
        if (ip < 0.025)
            ip = 0.025;
        vel.x += (ship->pos.x - pos.x) * ip;
        vel.y += (ship->pos.y - pos.y) * ip;
        if (ship->cnt < -Ship::INVINCIBLE_CNT) {
            isInhaled = false;
            inhaleCnt = 0;
        }
    } else {
        if (d < INHALE_WIDTH && ship->cnt >= -Ship::INVINCIBLE_CNT)
            isInhaled = true;
    }
}

void Bonus::draw() {
    float retro;
    if (cnt < RETRO_CNT)
        retro = 1 - static_cast<float>(cnt) / RETRO_CNT;
    else
        retro = 0;
    float d = cnt * 0.1;
    float ox = sin(d) * 0.3;
    float oy = cos(d) * 0.3;
    if (retro > 0) {
        P47Screen::setRetroParam(retro, 0.2);
        P47Screen::drawBoxRetro(pos.x - ox, pos.y - oy, BOX_SIZE / 2, BOX_SIZE / 2, 0);
        P47Screen::drawBoxRetro(pos.x + ox, pos.y + oy, BOX_SIZE / 2, BOX_SIZE / 2, 0);
        P47Screen::drawBoxRetro(pos.x - oy, pos.y + ox, BOX_SIZE / 2, BOX_SIZE / 2, 0);
        P47Screen::drawBoxRetro(pos.x + oy, pos.y - ox, BOX_SIZE / 2, BOX_SIZE / 2, 0);
    } else {
        if (isInhaled)
            Screen3D::setColor(0.8, 0.6, 0.4, 0.7);
        else if (isDown)
            Screen3D::setColor(0.4, 0.9, 0.6, 0.7);
        else
            Screen3D::setColor(0.8, 0.9, 0.5, 0.7);
        P47Screen::drawBoxLine(pos.x - ox - BOX_SIZE / 2, pos.y - oy - BOX_SIZE / 2,
                               BOX_SIZE, BOX_SIZE);
        P47Screen::drawBoxLine(pos.x + ox - BOX_SIZE / 2, pos.y + oy - BOX_SIZE / 2,
                               BOX_SIZE, BOX_SIZE);
        P47Screen::drawBoxLine(pos.x - oy - BOX_SIZE / 2, pos.y + ox - BOX_SIZE / 2,
                               BOX_SIZE, BOX_SIZE);
        P47Screen::drawBoxLine(pos.x + oy - BOX_SIZE / 2, pos.y - ox - BOX_SIZE / 2,
                               BOX_SIZE, BOX_SIZE);
    }
}
