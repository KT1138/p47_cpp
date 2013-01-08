/*
 * $Id:Rand.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Rand.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef RAND_H
#define RAND_H

#include <ctime>
#include <cstdlib>
#include <mt.h>


class Rand {
 public:
  Rand();
  ~Rand() {};
  void setSeed(long n);
  int nextInt(int n);
  int nextSignedInt(int n);
  float nextFloat(float n);
  float nextSignedFloat(float n);
};

#endif
