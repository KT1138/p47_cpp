/*
 * $Id:MorphBullet.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * MorphBullet.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef MORPHBULLET_H
#define MORPHBULLET_H

#include <vector>
#include <tr1/array>
#include <abagames/util/bulletml/Bullet.h>
using namespace std;


class BulletMLParser;


class MorphBullet : public Bullet {
 public:
  enum {
    MORPH_MAX = 8
  };
  tr1::array<BulletMLParser*, MORPH_MAX> morphParser;
  int morphNum;
  int morphIdx;
  int morphCnt;
  int baseMorphIdx;
  int baseMorphCnt;
  bool isMorph;

 public:
  explicit MorphBullet(int id) : Bullet(id) {};
  void setMorph(tr1::array<BulletMLParser*, MORPH_MAX> mrp,
		int num, int idx, int cnt);  
  void resetMorph();

 private:
  MorphBullet(const MorphBullet& other);
  MorphBullet& operator=(const MorphBullet& other);
};

#endif
