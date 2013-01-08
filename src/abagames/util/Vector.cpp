/*
 * $Id:Vector.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Vector.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/Vector.h>


float Vector::innerProduct(const Vector& v) {
    return x * v.x + y * v.y;
}

Vector* Vector::getElement(const Vector& v) {
    Vector* rsl = new Vector();
    float ll = v.x * v.x + v.y * v.y;
    if (ll != 0) {
        float mag = innerProduct(v);
        rsl->x = mag * v.x / ll;
        rsl->y = mag * v.y / ll;
    } else {
        rsl->x = rsl->y = 0;
    }
    return rsl;
}

void Vector::equal(const Vector& v) {
    x = v.x;
    y = v.y;
}

void Vector::add(const Vector& v) {
    x += v.x;
    y += v.y;
}

void Vector::sub(const Vector& v) {
    x -= v.x;
    y -= v.y;
}

void Vector::mul(float a) {
    x *= a;
    y *= a;
}

void Vector::div(float a) {
    x /= a;
    y /= a;
}

float Vector::checkSide(const Vector& pos1, const Vector& pos2) {
    float xo = pos2.x - pos1.x;
    float yo = pos2.y - pos1.y;
    if (xo == 0) {
        if (yo == 0)
            return 0;
        if (yo > 0)
            return x - pos1.x;
        else
            return pos1.x - x;
    } else if (yo == 0) {
        if (xo > 0)
            return pos1.y - y;
        else
            return y - pos1.y;
    } else {
        if (xo * yo > 0) { 
            return (x - pos1.x) / xo - (y - pos1.y) / yo;
        } else {
            return -(x - pos1.x) / xo + (y - pos1.y) / yo;
        }
    }
}

float Vector::checkSide(const Vector& pos1, const Vector& pos2, const Vector& ofs) {
    float xo = pos2.x - pos1.x;
    float yo = pos2.y - pos1.y;
    float mx = x - ofs.x;
    float my = y - ofs.y;
    if (xo == 0) {
        if (yo == 0)
            return 0;
        if (yo > 0)
            return mx - pos1.x;
        else
            return pos1.x - mx;
    } else if (yo == 0) {
        if (xo > 0)
            return pos1.y - my;
        else
            return my - pos1.y;
    } else {
        if (xo * yo > 0) { 
            return (mx - pos1.x) / xo - (my - pos1.y) / yo;
        } else {
            return -(mx - pos1.x) / xo + (my - pos1.y) / yo;
        }
    }
}

float Vector::size() {
    return sqrt(x * x - y * y);
}

float Vector::dist(const Vector& v) {
    float ax = fabs(x - v.x);
    float ay = fabs(y - v.y);
    if ( ax > ay ) {
        return ax + ay / 2;
    } else {
        return ay + ax / 2;
    }
}
