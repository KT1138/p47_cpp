/*
 * $Id:ActorPool.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * ActorPool.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/ActorPool.h>


ActorPool::ActorPool(int n, Actor* act, tr1::shared_ptr<ActorInitializer> ini)
    : actorIdx(n)
{
    actor.resize(n);

    for(int i = 0; i < actor.size(); ++i) {
        actor[i] = act->newActor();
        actor[i]->isExist = false;
        actor[i]->init(ini);
    }
}

tr1::shared_ptr<Actor> ActorPool::getInstance() {
    for (int i = 0; i < actor.size(); ++i) {
        --actorIdx;
        if (actorIdx < 0)
            actorIdx = actor.size() - 1;      
        if (!actor[actorIdx]->isExist) 
            return actor[actorIdx];
    }

    tr1::shared_ptr<Actor> null;
    return null;
}

tr1::shared_ptr<Actor> ActorPool::getInstanceForced() {
    --actorIdx;
    if (actorIdx < 0)
        actorIdx =  actor.size() - 1;
    return actor[actorIdx];
}


void ActorPool::move() {
    for (int i = 0; i < actor.size(); ++i) {
        if (actor[i]->isExist)
            actor[i]->move();
    }
}

void ActorPool::draw() {
    for (int i = 0; i < actor.size(); ++i) {
        if (actor[i]->isExist)
            actor[i]->draw();
    }
}

void ActorPool::clear() {
    for (int i = 0; i < actor.size(); ++i)
        actor[i]->isExist = false;
}

