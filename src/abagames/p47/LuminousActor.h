/*
 * $Id:LuminousActor.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * LuminousActor.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef LUMINOUSACTOR_H
#define LUMINOUSACTOR_H

#include <abagames/util/Actor.h>

class LuminousActor : public Actor {
 public:
  virtual ~LuminousActor() {}
  virtual void drawLuminous() = 0;
};

#endif
