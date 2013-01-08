/*
 * $Id:Shot.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Shot.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Shot.h>


int Shot::displayListIdx;


tr1::shared_ptr<Actor> Shot::newActor() {
    return tr1::shared_ptr<Actor>(new Shot());
}

void Shot::init(tr1::shared_ptr<ActorInitializer> ini) {
    tr1::shared_ptr<ShotInitializer> si =
        tr1::dynamic_pointer_cast<ShotInitializer>(ini);
    field = si->field;
    pos = Vector();
    vel = Vector();
}

void Shot::set(Vector p, float d) {
    pos.x = p.x;
    pos.y = p.y;
    deg = d;
    vel.x = sin(deg) * SPEED;
    vel.y = cos(deg) * SPEED;
    cnt = 0;
    isExist = true;
}

void Shot::move() {
    pos.x += vel.x;
    pos.y += vel.y;
    if (field->checkHit(pos, FIELD_SPACE))
        isExist = false;
    cnt++;
}

void Shot::draw() {
    float r;
    if (cnt > RETRO_CNT)
        r = 1;
    else
        r = cnt / RETRO_CNT;
    P47Screen::setRetroParam(r, 0.2);
    P47Screen::drawBoxRetro(pos.x, pos.y, 0.2, 1, deg);
}
