/*
 * $Id:BulletsManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * BulletsManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef BULLETSMANAGER_H 
#define BULLETSMANAGER_H 


#include <bulletmlrunner.h>


class BulletsManager {
 public:
  virtual ~BulletsManager() {};
  virtual void addBullet(float deg, float speed) = 0;
  virtual void addBullet(BulletMLState* state, float deg, float speed) = 0;
  virtual int getTurn() = 0;
  virtual void killMe(Bullet* bullet) = 0;
};

#endif 
