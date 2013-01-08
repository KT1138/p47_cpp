/*
 * $Id:P47Bullet.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47Bullet.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef P47BULLET_H
#define P47BULLET_H

#include <abagames/p47/MorphBullet.h>


class P47Bullet : public MorphBullet {
 public:
  float speedRank;
  int shape, color;
  float bulletSize;
  float xReverse;

 public:
  explicit P47Bullet(int id) : MorphBullet(id) {};
  void setParam(float sr, int sh, int cl, float sz, float xr);

 private:
  P47Bullet(const P47Bullet& other);
  P47Bullet& operator=(const P47Bullet& other);
};

#endif
