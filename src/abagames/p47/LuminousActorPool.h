/*
 * $Id:LuminousActorPool.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * LuminousActorPool.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef LUMINOUSACTORPOOL_H
#define LUMINOUSACTORPOOL_H

#include <tr1/memory>
#include <abagames/util/ActorPool.h>
using namespace std;


class LuminousActorPool : public ActorPool {
 public:
  LuminousActorPool(int n, Actor* act, tr1::shared_ptr<ActorInitializer> ini)
    : ActorPool(n, act, ini) {};
  void drawLuminous();
};

#endif
