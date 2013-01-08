/*
 * $Id:Fragment.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Fragment.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/Actor.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/Fragment.h>
#include <abagames/p47/P47Screen.h>


const float Fragment::R = 1;
const float Fragment::G = 0.8;
const float Fragment::B = 0.6;
Rand Fragment::rand;


tr1::shared_ptr<Actor> Fragment::newActor() {
    return tr1::shared_ptr<Actor>(new Fragment());
}

void Fragment::init(tr1::shared_ptr<ActorInitializer> ini) {
    tr1::shared_ptr<FragmentInitializer> fi =
        tr1::dynamic_pointer_cast<FragmentInitializer>(ini);

    for (int i = 0; i < POINT_NUM; ++i) {
        pos[i] = Vector();
        vel[i] = Vector();
    }
    impact = Vector();
}

void Fragment::set(float x1, float y1, float x2, float y2, float z, float speed, float deg) {
    float r1 = rand.nextFloat(1);
    float r2 = rand.nextFloat(1);
    pos[0].x = x1 * r1 + x2 * (1 - r1);
    pos[0].y = y1 * r1 + y2 * (1 - r1);
    pos[1].x = x1 * r2 + x2 * (1 - r2);
    pos[1].y = y1 * r2 + y2 * (1 - r2);
    for (int i = 0; i < POINT_NUM; i++) {
        vel[i].x = rand.nextSignedFloat(1) * speed;
        vel[i].y = rand.nextSignedFloat(1) * speed;
    }
    impact.x = sin(deg) * speed * 4;
    impact.y = cos(deg) * speed * 4;
    this->z = z;
    cnt = 32 + rand.nextInt(24);
    lumAlp = 0.8 + rand.nextFloat(0.2);
    retro = 1;
    isExist = true;
}

void Fragment::move() {
    --cnt;
    if (cnt < 0) {
        isExist = false;
        return;
    }
    for (int i = 0; i < POINT_NUM; i++) {
        pos[i].add(vel[i]);
        pos[i].add(impact);
        vel[i].mul(0.98);
    }
    impact.mul(0.95);
    lumAlp *= 0.98;
    retro *= 0.97;
}

void Fragment::draw() {
    P47Screen::setRetroZ(z);
    P47Screen::setRetroParam(retro, 0.2);
    P47Screen::drawLineRetro(pos[0].x, pos[0].y, pos[1].x, pos[1].y);
}

void Fragment::drawLuminous() {
    if (lumAlp < 0.2) return;
    Screen3D::setColor(R, G, B, lumAlp);
    glVertex3f(pos[0].x, pos[0].y, z);
    glVertex3f(pos[1].x, pos[1].y, z);
}
