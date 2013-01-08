/*
 * $Id:Vector.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Vector.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
using namespace std;


class Vector {
 public:
  float x, y;

 public:
 Vector() : x(0), y(0) {};
 Vector(float xx, float yy) : x(xx), y(yy) {};
  float innerProduct(const Vector& v);
  Vector* getElement(const Vector& v);
  void equal(const Vector& v);
  void add(const Vector& v);
  void sub(const Vector& v);
  void mul(float a);
  void div(float a);
  float checkSide(const Vector& pos1, const Vector& pos2);
  float checkSide(const Vector& pos1, const Vector& pos2, const Vector& ofs);
  float size();
  float dist(const Vector& v);
};

#endif
