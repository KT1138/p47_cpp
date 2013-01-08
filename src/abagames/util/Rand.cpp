/*
 * $Id:Rand.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Rand.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <ctime>
#include <abagames/util/Rand.h>


Rand::Rand() {
    time_t timer;
    init_genrand(static_cast<uint>(timer));
}

void Rand::setSeed(long n) {
    init_genrand(static_cast<uint>(n));
}

int Rand::nextInt(int n) {
    return genrand_int32() % n;
}

int Rand::nextSignedInt(int n) {
    return genrand_int32() % (n * 2) -n;
}

float Rand::nextFloat(float n) {
    return genrand_real1() * n;
}

float Rand::nextSignedFloat(float n) {
    return genrand_real1() * (n * 2) - n;
}
