/*
 * $Id:MorphBullet.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * MorphBullet.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <bulletmlparser.h>
#include <abagames/p47/MorphBullet.h>


void MorphBullet::setMorph(tr1::array<BulletMLParser*, MorphBullet::MORPH_MAX > mrp,
                           int num, int idx, int cnt) {
    if (cnt <= 0) {
        isMorph = false;
        return;
    }
    isMorph = true;
    baseMorphCnt = morphCnt = cnt;
    morphNum = num;
    for (int i = 0; i < num; ++i) {
        morphParser[i] = mrp[i];
    }
    morphIdx = idx;
    if (morphIdx >= morphNum)
        morphIdx = 0;
    baseMorphIdx = morphIdx;
}

void MorphBullet::resetMorph() {
    morphIdx = baseMorphIdx;
    morphCnt = baseMorphCnt;
}
