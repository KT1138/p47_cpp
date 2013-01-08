/*
 * $Id:Roll.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Roll.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/p47/Roll.h>
#include <abagames/p47/Ship.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47Screen.h>


const float Roll::BASE_LENGTH = 1.0;
const float Roll::BASE_RESISTANCE = 0.8;
const float Roll::BASE_SPRING = 0.2;
const float Roll::BASE_SIZE = 0.2;
const float Roll::BASE_DIST = 3;
const float Roll::SPEED = 0.75;


tr1::shared_ptr<Actor> Roll::newActor() {
    return tr1::shared_ptr<Actor>(new Roll());
}

void Roll::init(tr1::shared_ptr<ActorInitializer> ini) {
    tr1::shared_ptr<RollInitializer> ri =
        tr1::dynamic_pointer_cast<RollInitializer>(ini);

    ship = ri->ship;
    field = ri->field;
    manager = ri->manager;

    for (int i = 0; i < LENGTH; ++i) {
        pos[i] = Vector();
        vel[i] = Vector();
    }
}

void Roll::set() {
    for (int i = 0; i < LENGTH; ++i) {
        pos[i].x = ship->pos.x;
        pos[i].y = ship->pos.y;
        vel[i].x = vel[i].y = 0;
    }
    cnt = 0;
    dist = 0;
    released = false;
    isExist = true;
}

void Roll::move() {
    if (released) {
        pos[0].y += SPEED;
        if (pos[0].y > field->size.y) {
            isExist = false;
            return;
        }
        manager->addParticle(pos[0], M_PI, 
                             BASE_SIZE * LENGTH, SPEED / 8);
    } else {
        if (dist < BASE_DIST)
            dist += BASE_DIST / 90;
        pos[0].x = ship->pos.x + sin(cnt * 0.1) * dist; 
        pos[0].y = ship->pos.y + cos(cnt * 0.1) * dist;
    }
    float dist, deg, v;
    for (int i = 1; i < LENGTH; ++i) {
        pos[i].x += vel[i].x;
        pos[i].y += vel[i].y;
        vel[i].x *= BASE_RESISTANCE; 
        vel[i].y *= BASE_RESISTANCE;
        dist = pos[i].dist(pos[i - 1]);
        if (dist <= BASE_LENGTH)
            continue;
        v = (dist - BASE_LENGTH) * BASE_SPRING;
        deg = atan2(pos[i - 1].x - pos[i].x, pos[i - 1].y - pos[i].y);
        vel[i].x += sin(deg) * v;
        vel[i].y += cos(deg) * v;
    }
    cnt++; 
}

void Roll::draw() {
    if (released)
        P47Screen::setRetroParam(1, 0.2);
    else
        P47Screen::setRetroParam(0.5, 0.2);
    for (int i = 0; i < LENGTH; i++) {
        P47Screen::drawBoxRetro(pos[i].x, pos[i].y, 
                                BASE_SIZE * (LENGTH - i),  BASE_SIZE * (LENGTH - i),
                                cnt * 0.1);
    }
}
