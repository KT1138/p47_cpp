/*
 * $Id:LuminousActorPool.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * LuminousActorPool.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/Actor.h>
#include <abagames/util/ActorInitializer.h>
#include <abagames/p47/LuminousActor.h>
#include <abagames/p47/LuminousActorPool.h>
using namespace std;


void LuminousActorPool::drawLuminous() {
    for (int i = 0; i < actor.size(); ++i) {
        if (actor[i]->isExist) {
            tr1::dynamic_pointer_cast<LuminousActor>(actor[i])->drawLuminous();
        }
    }
}
