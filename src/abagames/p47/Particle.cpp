/*
 * $Id:Particle.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Particle.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/Actor.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Particle.h>


const float Particle::R = 1;
const float Particle::G = 1;
const float Particle::B = 0.5;
Rand Particle::rand;


tr1::shared_ptr<Actor> Particle::newActor() {
    return tr1::shared_ptr<Actor>(new Particle());
}

void Particle::init(tr1::shared_ptr<ActorInitializer> ini) {
    pos = Vector();
    ppos = Vector();
    vel = Vector();
}

void Particle::set(const Vector& p, float d, float ofs, float speed) {
    if (ofs > 0) {
        pos.x = p.x + sin(d) * ofs;
        pos.y = p.y + cos(d) * ofs;
    } else {
        pos.x = p.x;
        pos.y = p.y;
    }
    z = 0;
    float sb = rand.nextFloat(0.5) + 0.75;
    vel.x = sin(d) * speed * sb;
    vel.y = cos(d) * speed * sb;
    mz = rand.nextSignedFloat(0.7);
    cnt = 12 + rand.nextInt(48);
    lumAlp = 0.8 + rand.nextFloat(0.2);
    isExist = true;
}

void Particle::move() {
    --cnt;
    if (cnt < 0) {
        isExist = false;
        return;
    }
    ppos.x = pos.x;
    ppos.y = pos.y;
    pz = z;
    pos.add(vel);
    vel.mul(0.98);
    z += mz;
    lumAlp *= 0.98;
}

void Particle::draw() {
    glVertex3f(ppos.x, ppos.y, pz);
    glVertex3f(pos.x, pos.y, z);
}

void Particle::drawLuminous() {
    if (lumAlp < 0.2) return;
    Screen3D::setColor(R, G, B, lumAlp);
    glVertex3f(ppos.x, ppos.y, pz);
    glVertex3f(pos.x, pos.y, z);
}
