/*
 * $Id:ActorPool.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * ActorPool.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef ACTORPOOL_H
#define ACTORPOOL_H

#include <vector>
#include <tr1/memory>
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
using namespace std;


class ActorPool {
 public:
  vector< tr1::shared_ptr<Actor> > actor;
  int actorIdx;

 public:
  ActorPool(int n, Actor* act, tr1::shared_ptr<ActorInitializer> ini);
  virtual ~ActorPool() {};
  tr1::shared_ptr<Actor> getInstance();
  tr1::shared_ptr<Actor> getInstanceForced();
  void move();
  void draw();
  void clear();
};

#endif
