/*
 * $Id:Particle.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Particle.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef PARTICLE_H
#define PARTICLE_H

#include <cmath>
#include <tr1/memory>
#include <gl.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/util/Rand.h>
#include <abagames/util/Vector.h>
#include <abagames/p47/LuminousActor.h>
using namespace std;


class Actor;


class Particle : public LuminousActor {
 public:
  static const float R;
  static const float G;
  static const float B;

 private:
  static Rand rand;
  Vector pos;
  Vector ppos;
  Vector vel;
  float z, mz, pz;
  float lumAlp;
  int cnt;

 public:
  tr1::shared_ptr<Actor> newActor();
  void init(tr1::shared_ptr<ActorInitializer> ini);
  void set(const Vector& p, float d, float ofs, float speed);
  void move();
  void draw();
  void drawLuminous();
};


class ParticleInitializer : public ActorInitializer {
};

#endif 
