/*
 * $Id:StageManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * StageManager.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <bulletmlparser.h>
#include <bulletmlparser-tinyxml.h>
#include <abagames/util/sdl/Sound.h>
#include <abagames/p47/Enemy.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/SoundManager.h>
#include <abagames/p47/StageManager.h>


const int StageManager::apparancePattern[][7][3] =
{
    {{1, 0, 0}, {2, 0, 0}, {1, 1, 0}, {1, 0, 1}, {2, 1, 0}, {2, 0, 1}, {0, 1, 1}},
    {{1, 0, 0}, {1, 1, 0}, {1, 1, 0}, {1, 0, 1}, {2, 1, 0}, {1, 1, 1}, {0, 1, 1}},
};


void StageManager::init(tr1::shared_ptr<P47GameManager> gm,
                        tr1::shared_ptr<BarrageManager> bm, 
                        tr1::shared_ptr<Field> f) {
    gameManager = gm;
    barrageManager = bm;
    field = f;

    rand = Rand();
    apos = Vector();

    for (int i = 0; i < smallType.size(); ++i)
        smallType[i].reset(new EnemyType());
    for (int i = 0; i < middleType.size(); ++i)
        middleType[i].reset(new EnemyType());
    for (int i = 0; i < largeType.size(); ++i)
        largeType[i].reset(new EnemyType());

    middleBossType.reset(new EnemyType()); 
    largeBossType.reset(new EnemyType());
}

void StageManager::createEnemyData() {
    for (int i = 0; i < smallType.size(); ++i)
        smallType[i]->setSmallEnemyType(rank, gameManager->mode);
    for (int i = 0; i < middleType.size(); ++i)
        middleType[i]->setMiddleEnemyType(rank, gameManager->mode);
    for (int i = 0; i < largeType.size(); ++i)
        largeType[i]->setLargeEnemyType(rank, gameManager->mode);
    middleBossType->setMiddleBossEnemyType(rank, gameManager->mode);
    largeBossType->setLargeBossEnemyType(rank, gameManager->mode);
}

void StageManager::setAppearancePattern(EnemyAppearance* ap) {
    switch (rand.nextInt(5)) {
    case 0:
        ap->pattern = ONE_SIDE;
        break;
    case 1:
    case 2:
        ap->pattern = ALTERNATE_;
        break;
    case 3:
    case 4:
        ap->pattern = BOTH_SIDES;
        break;
    }
    switch (rand.nextInt(3)) {
    case 0:
        ap->sequence = RANDOM;
        break;
    case 1:
    case 2:
        ap->sequence = FIXED;
        break;
    }
}

void StageManager::setSmallAppearance(EnemyAppearance* ap) {
    ap->type = smallType[rand.nextInt(smallType.size())];
    int mt;
    if (rand.nextFloat(1) > 0.2) {
        ap->point = TOP;
        mt = BarrageManager::SMALLMOVE;
    } else {
        ap->point = SIDE;
        mt = BarrageManager::SMALLSIDEMOVE;
    }
    ap->moveParser = barrageManager->parser[mt][rand.nextInt(barrageManager->parserNum[mt])];
    setAppearancePattern(ap);
    if (ap->pattern == ONE_SIDE)
        ap->pattern = ALTERNATE_;
    switch (rand.nextInt(4)) {
    case 0:
        ap->num = 7 + rand.nextInt(5);
        ap->groupInterval = 72 + rand.nextInt(15);
        ap->interval = 15 + rand.nextInt(5);
        break;
    case 1:
        ap->num = 5 + rand.nextInt(3);
        ap->groupInterval = 56 + rand.nextInt(10);
        ap->interval = 20 + rand.nextInt(5);
        break;
    case 2:
    case 3:
        ap->num = 2 + rand.nextInt(2);
        ap->groupInterval = 45 + rand.nextInt(20);
        ap->interval = 25 + rand.nextInt(5);
        break;
    }
}

void StageManager::setMiddleAppearance(EnemyAppearance* ap) {
    ap->type = middleType[rand.nextInt(middleType.size())];
    int mt;
    // Appearance from the backward is disabled.
    /*if (rand.nextFloat(1) > 0.1) {
      ap->point = TOP;
      mt = BarrageManager.MIDDLEMOVE;
      } else {
      ap->point = BACK;
      mt = BarrageManager.MIDDLEBACKMOVE;
      }*/
    ap->point = TOP;
    mt = BarrageManager::MIDDLEMOVE;
    ap->moveParser = barrageManager->parser[mt][rand.nextInt(barrageManager->parserNum[mt])];
    setAppearancePattern(ap);
    switch (rand.nextInt(3)) {
    case 0:
        ap->num = 4;
        ap->groupInterval = 240 + rand.nextInt(150);
        ap->interval = 80 + rand.nextInt(30);
        break;
    case 1:
        ap->num = 2;
        ap->groupInterval = 180 + rand.nextInt(60);
        ap->interval = 180 + rand.nextInt(20);
        break;
    case 2:
        ap->num = 1;
        ap->groupInterval = 150 + rand.nextInt(50);
        ap->interval = 100;
        break;
    }
}

void StageManager::setLargeAppearance(EnemyAppearance* ap) {
    ap->type = largeType[rand.nextInt(largeType.size())];
    int mt;
    ap->point = TOP;
    mt = BarrageManager::LARGEMOVE;
    ap->moveParser = barrageManager->parser[mt][rand.nextInt(barrageManager->parserNum[mt])];
    setAppearancePattern(ap);
    switch (rand.nextInt(3)) {
    case 0:
        ap->num = 3;
        ap->groupInterval = 400 + rand.nextInt(100);
        ap->interval = 240 + rand.nextInt(40);
        break;
    case 1:
        ap->num = 2;
        ap->groupInterval = 400 + rand.nextInt(60);
        ap->interval = 300 + rand.nextInt(20);
        break;
    case 2:
        ap->num = 1;
        ap->groupInterval = 270 + rand.nextInt(50);
        ap->interval = 200;
        break;
    }
}

void StageManager::setAppearance(EnemyAppearance* ap, int type) {
    switch (type) {
    case SMALL:
        setSmallAppearance(ap);
        break;
    case MIDDLE:
        setMiddleAppearance(ap);
        break;
    case LARGE:
        setLargeAppearance(ap);
        break;
    }
    ap->cnt = 0;
    ap->left = ap->num;
    ap->side = rand.nextInt(2) * 2 - 1;
    ap->pos = rand.nextFloat(1);
}

void StageManager::createSectionData() {
    apNum = 0;
    if (rank <= 0)
        return;
    field->aimSpeed = 0.1 + section * 0.02;
    if (section == 4) {
        // Set the middle boss.
        Vector pos;
        pos.x = 0; pos.y = field->size.y / 4 * 3;
        gameManager->addBoss(pos, M_PI, middleBossType);
        bossSection = true;
        sectionIntervalCnt = sectionCnt = 2 * 60;
        field->aimZ = 11;
        return;
    } else if (section == 9) {
        // Set the large boss.
        Vector pos;
        pos.x = 0; pos.y = field->size.y / 4 * 3;
        gameManager->addBoss(pos, M_PI, largeBossType);
        bossSection = true;
        sectionIntervalCnt = sectionCnt = 3 * 60;
        field->aimZ = 12;
        return;
    } else if (section == middleRushSectionNum) {
        // In this section, no small enemy.
        middleRushSection = true;
        field->aimZ = 9;
    } else {
        middleRushSection = false;
        field->aimZ = 10 + rand.nextSignedFloat(0.3);
    }
    bossSection = false;
    if (section == 3)
        sectionIntervalCnt = 2 * 60;
    else if (section == 3)
        sectionIntervalCnt = 4 * 60;
    else
        sectionIntervalCnt = 1 * 60;
    sectionCnt = sectionIntervalCnt + 10 * 60;
    int sp = section * 3 / 7 + 1;
    int ep = 3 + section * 3 / 10;
    int ap = sp + rand.nextInt(ep - sp + 1);
    if (section == 0)
        ap = 0;
    else if (middleRushSection)
        ap = MIDDLE_RUSH_SECTION_PATTERN;
    for (int i = 0; i < apparancePattern[gameManager->mode][ap][0]; ++i, ++apNum) {
        EnemyAppearance* ap = &appearance[apNum];
        setAppearance(ap, SMALL);
    }
    for (int i = 0; i < apparancePattern[gameManager->mode][ap][1]; ++i, ++apNum) {
        EnemyAppearance* ap = &appearance[apNum];
        setAppearance(ap, MIDDLE);
    }
    for (int i = 0; i < apparancePattern[gameManager->mode][ap][2]; ++i, ++apNum) {
        EnemyAppearance* ap = &appearance[apNum];
        setAppearance(ap, LARGE);
    }
}

void StageManager::createStage() {
    createEnemyData();
    middleRushSectionNum = 2 + rand.nextInt(6);
    if (middleRushSectionNum <= 4)
        middleRushSectionNum++;
    field->setType(stageType % Field::TYPE_NUM);
    SoundManager::playBgm(stageType % SoundManager::BGM_NUM);
    ++stageType;
}

void StageManager::gotoNextSection() {
    ++section;
    ++parsec;
    if (gameManager->state == P47GameManager::TITLE && section >= 4) {
        section = 0;
        parsec -= 4;
    }
    if (section >= 10) {
        section = 0;
        rank += rankInc;
        createStage();
    }
    createSectionData();
}

void StageManager::setRank(float baseRank, float inc, int startParsec, int type) {
    rank = baseRank;
    rankInc = inc;
    rank += rankInc * (startParsec / 10);
    section = -1;
    parsec = startParsec - 1;
    stageType = type;
    createStage();
    gotoNextSection();
}

void StageManager::move() {
    for (int i = 0; i < apNum; ++i) {
        EnemyAppearance* ap = &appearance[i];
        ap->cnt--;
        if (ap->cnt > 0) {
            // Add the extra enemy.
            if (!middleRushSection) {
                if (ap->type->type == EnemyType::SMALL && !EnemyType::isExist[ap->type->id]) {
                    ap->cnt = 0;
                    EnemyType::isExist[ap->type->id] = true;
                }
            } else {
                if (ap->type->type == EnemyType::MIDDLE && !EnemyType::isExist[ap->type->id]) {
                    ap->cnt = 0;
                    EnemyType::isExist[ap->type->id] = true;
                }
            }
            continue;
        }
        float p;
        switch (ap->sequence) {
        case RANDOM:
            p = rand.nextFloat(1);
            break;
        case FIXED:
            p = ap->pos;
            break;
        }
        float d;
        switch (ap->point) {
        case TOP:
            switch (ap->pattern) {
            case BOTH_SIDES:
                apos.x = (p - 0.5) * field->size.x * 1.8;
                break;
            default:
                apos.x = (p * 0.6 + 0.2) * field->size.x * ap->side;
                break;
            }
            apos.y = field->size.y - Enemy::FIELD_SPACE;
            d = M_PI;
            break;
        case BACK:
            switch (ap->pattern) {
            case BOTH_SIDES:
                apos.x = (p - 0.5) * field->size.x * 1.8;
                break;
            default:
                apos.x = (p * 0.6 + 0.2) * field->size.x * ap->side;
                break;
            }
            apos.y = -field->size.y + Enemy::FIELD_SPACE;
            d = 0;
            break;
        case SIDE:
            switch (ap->pattern) {
            case BOTH_SIDES:
                apos.x = (field->size.x - Enemy::FIELD_SPACE) * (rand.nextInt(2) * 2 - 1);
                break;
            default:
                apos.x = (field->size.x - Enemy::FIELD_SPACE) * ap->side;
                break;
            }
            apos.y = (p * 0.4 + 0.4) * field->size.y;
            if (apos.x < 0)
                d = M_PI / 2;
            else
                d = M_PI / 2 * 3;
            break;
        }
        apos.x *= 0.88;
        gameManager->addEnemy(apos, d, ap->type, ap->moveParser);
        ap->left--;
        if (ap->left <= 0) {
            ap->cnt = ap->groupInterval;
            ap->left = ap->num;
            if (ap->pattern != ONE_SIDE)
                ap->side *= -1;
            ap->pos = rand.nextFloat(1);
        } else {
            ap->cnt = ap->interval;
        }
    }
    if (!bossSection || 
        (!EnemyType::isExist[middleBossType->id] && !EnemyType::isExist[largeBossType->id]))
        --sectionCnt;
    if (sectionCnt < sectionIntervalCnt) {
        if (section == 9 && sectionCnt == sectionIntervalCnt - 1)
            Sound::fadeMusic();
        apNum = 0;
        if (sectionCnt <= 0)
            gotoNextSection();
    }
    EnemyType::clearIsExistList();
}

