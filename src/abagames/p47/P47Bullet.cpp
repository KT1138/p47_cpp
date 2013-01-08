/*
 * $Id:P47Bullet.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47Bullet.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/p47/P47Bullet.h>


void P47Bullet::setParam(float sr, int sh, int cl, float sz, float xr) {
  speedRank = sr;
  shape = sh;
  color = cl;
  bulletSize = sz;
  xReverse = xr;
}
