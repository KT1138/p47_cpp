/*
 * $Id:Actor.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Actor.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef ACTOR_H
#define ACTOR_H

#include <tr1/memory>
#include <abagames/util/ActorInitializer.h>
using namespace std;


class Actor {
 public:
  bool isExist;

 public:
  virtual ~Actor() {};
  virtual tr1::shared_ptr<Actor> newActor() = 0;
  virtual void init(tr1::shared_ptr<ActorInitializer> ini) = 0;
  virtual void move() = 0;
  virtual void draw() = 0;
};

#endif
