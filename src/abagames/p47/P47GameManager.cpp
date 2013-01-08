/*
 * $Id:P47GameManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47GameManager.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <bulletmlparser.h>
#include <abagames/util/sdl/MainLoop.h>
#include <abagames/util/sdl/Pad.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/util/sdl/Sound.h>
#include <abagames/util/sdl/Texture.h>
#include <abagames/p47/Enemy.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/Fragment.h>
#include <abagames/p47/BarrageManager.h>
#include <abagames/p47/Bonus.h>
#include <abagames/p47/BulletActor.h>
#include <abagames/p47/BulletActorPool.h>
#include <abagames/p47/LetterRender.h>
#include <abagames/p47/Lock.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47PrefManager.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Particle.h>
#include <abagames/p47/Roll.h>
#include <abagames/p47/Ship.h>
#include <abagames/p47/Shot.h>
#include <abagames/p47/SoundManager.h>
#include <abagames/p47/StageManager.h>
#include <abagames/p47/Title.h>
using namespace std;


const int P47GameManager::SLOWDOWN_START_BULLETS_SPEED[2] = {30, 42};


tr1::shared_ptr<P47GameManager> P47GameManager::returnSharedThis() {
    return shared_from_this();
}

void P47GameManager::init() {
    pad = tr1::dynamic_pointer_cast<Pad>(input);
    prefManager = tr1::dynamic_pointer_cast<P47PrefManager>(abstPrefManager);
    screen = tr1::dynamic_pointer_cast<P47Screen>(abstScreen);

    rand = Rand();

    Field::createDisplayLists();
    field.reset(new Field());
    field->init();

    Ship::createDisplayLists();
    ship.reset(new Ship());
    ship->init(pad, field, returnSharedThis());

    auto_ptr<Particle> particleClass(new Particle());
    tr1::shared_ptr<ParticleInitializer> pi(new ParticleInitializer());
    particles.reset(new LuminousActorPool(128, particleClass.get(), pi));

    auto_ptr<Fragment> fragmentClass(new Fragment());
    tr1::shared_ptr<FragmentInitializer> fi(new FragmentInitializer());
    fragments.reset(new LuminousActorPool(128, fragmentClass.get(), fi));  

    BulletActor::createDisplayLists();
    tr1::shared_ptr<BulletActorInitializer> bi(new BulletActorInitializer(field, ship)); 
    bullets.reset(new BulletActorPool(512, bi));

    LetterRender::createDisplayLists();

    auto_ptr<Shot> shotClass(new Shot());
    tr1::shared_ptr<ShotInitializer> shi(new ShotInitializer(field));
    shots.reset(new ActorPool(32, shotClass.get(), shi));  

    auto_ptr<Roll> rollClass(new Roll());
    tr1::shared_ptr<RollInitializer> ri(new RollInitializer(ship, field, returnSharedThis()));
    rolls.reset(new ActorPool(4, rollClass.get(), ri));  

    Lock::init();
    auto_ptr<Lock> lockClass(new Lock());
    tr1::shared_ptr<LockInitializer> li(new LockInitializer(ship, field, returnSharedThis()));
    locks.reset(new ActorPool(4, lockClass.get(), li));

    auto_ptr<Enemy> enemyClass(new Enemy());
    tr1::shared_ptr<EnemyInitializer> ei(new EnemyInitializer(field, bullets, shots, rolls, locks, ship, returnSharedThis()));
    enemies.reset(new ActorPool(ENEMY_MAX, enemyClass.get(), ei));

    Bonus::init();
    auto_ptr<Bonus> bonusClass(new Bonus());
    tr1::shared_ptr<BonusInitializer> bni(new BonusInitializer(field, ship, returnSharedThis()));
    bonuses.reset(new ActorPool(128, bonusClass.get(), bni));

    barrageManager.reset(new BarrageManager());
    barrageManager->loadBulletMLs();
    EnemyType::init(barrageManager);

    stageManager.reset(new StageManager());
    stageManager->init(returnSharedThis(), barrageManager, field);

    title.reset(new Title());
    title->init(pad, returnSharedThis(), prefManager, field);

    interval = mainLoop->INTERVAL_BASE;

    SoundManager::init(returnSharedThis());
}

void P47GameManager::start() {
    startTitle();
}

void P47GameManager::close() {
    barrageManager->unloadBulletMLs();
    title->close();
    SoundManager::close();
    LetterRender::deleteDisplayLists();
    Field::deleteDisplayLists();
    Ship::deleteDisplayLists();
    BulletActor::deleteDisplayLists();
}

void P47GameManager::addScore(int sc) {
    score += sc;
    if (score > extendScore) {
        if (left < LEFT_MAX) {
            SoundManager::playSe(SoundManager::EXTEND);
            left++;
        }
        if (extendScore <= FIRST_EXTEND)
            extendScore = EVERY_EXTEND;
        else
            extendScore += EVERY_EXTEND;
    }
}

void P47GameManager::shipDestroyed() {
    if (mode == ROLL)
        releaseRoll();
    else
        releaseLock();
    clearBullets();
    left--;
    if (left < 0)
        startGameover();
}

void P47GameManager::addParticle(const Vector& pos, float deg, float ofs, float speed) {
    tr1::shared_ptr<Particle> pt =
        tr1::dynamic_pointer_cast<Particle>(particles->getInstanceForced());
    assert(pt);
    pt->set(pos, deg, ofs, speed);
}

void P47GameManager::addFragments(int n, float x1, float y1, float x2, float y2, 
                                  float z, float speed, float deg) {
    for (int i = 0; i < n; ++i) {
        tr1::shared_ptr<Fragment> ft =
            tr1::dynamic_pointer_cast<Fragment>(fragments->getInstanceForced());
        assert(ft);
        ft->set(x1, y1, x2, y2, z, speed, deg);
    }
}


void P47GameManager::addEnemy(const Vector& pos, float d, tr1::shared_ptr<EnemyType> type, 
                              BulletMLParser* moveParser) {
    tr1::shared_ptr<Enemy> en = 
        tr1::dynamic_pointer_cast<Enemy>(enemies->getInstance());
    if (!en)
        return;
    en->set(pos, d, type, moveParser);
}

void P47GameManager::clearBullets() {
    for (int i = 0; i < bullets->actor.size(); i++) {
        if (!bullets->actor[i]->isExist)
            continue;
        tr1::dynamic_pointer_cast<BulletActor>(bullets->actor[i])->toRetro();
    }
}

void P47GameManager::addBoss(const Vector& pos, float d, tr1::shared_ptr<EnemyType> type) {
    tr1::shared_ptr<Enemy> en = 
        tr1::dynamic_pointer_cast<Enemy>(enemies->getInstance());
    if (!en)
        return;
    en->setBoss(pos, d, type);
}

void P47GameManager::addShot(const Vector& pos, float deg) {
    tr1::shared_ptr<Shot> shot =
        tr1::dynamic_pointer_cast<Shot>(shots->getInstance());

    if (!shot)
        return;
    shot->set(pos, deg);
}

void P47GameManager::addRoll() {
    tr1::shared_ptr<Roll> roll =
        tr1::dynamic_pointer_cast<Roll>(rolls->getInstance());

    if (!roll)
        return;
    roll->set();
}

void P47GameManager::addLock() {
    tr1::shared_ptr<Lock> lock =
        tr1::dynamic_pointer_cast<Lock>(locks->getInstance());

    if (!lock)
        return;
    lock->set();
}

void P47GameManager::releaseRoll() {
    for (int i = 0; i < rolls->actor.size(); ++i) {
        if (!rolls->actor[i]->isExist)
            continue;
        tr1::dynamic_pointer_cast<Roll>(rolls->actor[i])->released = true;
    }
}

void P47GameManager::releaseLock() {
    for (int i = 0; i < locks->actor.size(); ++i) {
        if (!locks->actor[i]->isExist)
            continue;
        tr1::dynamic_pointer_cast<Lock>(locks->actor[i])->released = true;
    }
}

void P47GameManager::addBonus(const Vector& pos, const Vector* ofs, int num) {
    for (int i = 0; i < num; ++i) {
        tr1::shared_ptr<Bonus> bonus =
            tr1::dynamic_pointer_cast<Bonus>(bonuses->getInstance());
        if (!bonus)
            return;
        bonus->set(pos, ofs);
    }
}

void P47GameManager::setBossShieldMeter(int bs, int s1, int s2, int s3, int s4, float r) {
    r *= 0.7;
    bossShield = static_cast<int>(bs * r);
    bossWingShield[0] = static_cast<int>(s1 * r);
    bossWingShield[1] = static_cast<int>(s2 * r);
    bossWingShield[2] = static_cast<int>(s3 * r);
    bossWingShield[3] = static_cast<int>(s4 * r);
}

void P47GameManager::startStage(int difficulty, int parsecSlot, int startParsec, int mode) {
    enemies->clear();
    bullets->clear();
    this->difficulty = difficulty;
    this->parsecSlot = parsecSlot;
    this->mode = mode;
    int stageType = rand.nextInt(99999);
    switch (difficulty) {
    case PRACTICE:
        stageManager->setRank(1, 4, startParsec, stageType);
        ship->setSpeedRate(0.7);
        Bonus::setSpeedRate(0.6);
        break;
    case NORMAL:
        stageManager->setRank(10, 8, startParsec, stageType);
        ship->setSpeedRate(0.9);
        Bonus::setSpeedRate(0.8);
        break;
    case HARD:
        stageManager->setRank(22, 12, startParsec, stageType);
        ship->setSpeedRate(1);
        Bonus::setSpeedRate(1);
        break;
    case EXTREME:
        stageManager->setRank(36, 16, startParsec, stageType);
        ship->setSpeedRate(1.2);
        Bonus::setSpeedRate(1.3);
        break;
    case QUIT:
        stageManager->setRank(0, 0, 0, 0);
        ship->setSpeedRate(1);
        Bonus::setSpeedRate(1);
        break;
    }
}

void P47GameManager::initShipState() {
    left = 2;
    score = 0;
    extendScore = FIRST_EXTEND;
    ship->start();
}

void P47GameManager::startInGame() {
    state = IN_GAME;
    initShipState();
    startStage(difficulty, parsecSlot, title->getStartParsec(difficulty, parsecSlot), mode);
}

void P47GameManager::startTitle() {
    state = TITLE;
    title->start();
    initShipState();
    bullets->clear();
    ship->cnt = 0;
    startStage(difficulty, parsecSlot, title->getStartParsec(difficulty, parsecSlot), mode);
    cnt = 0;
    Sound::stopMusic();
}

void P47GameManager::startGameover() {
    state = GAMEOVER;
    bonuses->clear();
    shots->clear();
    rolls->clear();
    locks->clear();
    setScreenShake(0, 0);
    mainLoop->interval = static_cast<int>(interval = mainLoop->INTERVAL_BASE);
    cnt = 0;
    if (score > prefManager->hiScore[mode][difficulty][parsecSlot])
        prefManager->hiScore[mode][difficulty][parsecSlot] = score;
    if (stageManager->parsec > prefManager->reachedParsec[mode][difficulty])
        prefManager->reachedParsec[mode][difficulty] = stageManager->parsec;
    Sound::fadeMusic();
}

void P47GameManager::startPause() {
    state = PAUSE;
    pauseCnt = 0;
}

void P47GameManager::resumePause() {
    state = IN_GAME;
}

void P47GameManager::stageMove() {
    stageManager->move();
}

void P47GameManager::inGameMove() {
    stageMove();
    field->move();
    ship->move();
    bonuses->move();
    shots->move();
    enemies->move();
    if (mode == ROLL)
        rolls->move();
    else
        locks->move();
    BulletActor::resetTotalBulletsSpeed();
    bullets->move();
    particles->move();
    fragments->move();
    moveScreenShake();
    if (pad->keys[SDLK_p] == SDL_PRESSED) {
        if (!pPrsd) {
            pPrsd = true;
            startPause();
        }
    } else {
        pPrsd = false;
    }
    if (!nowait) {
        // Intentional slowdown when the total speed of bullets is over SLOWDOWN_START_BULLETS_SPEED
        if (BulletActor::totalBulletsSpeed > SLOWDOWN_START_BULLETS_SPEED[mode]) {
            float sm = BulletActor::totalBulletsSpeed / SLOWDOWN_START_BULLETS_SPEED[mode];
            if (sm > 1.75)
                sm = 1.75;
            interval += (sm * mainLoop->INTERVAL_BASE - interval) * 0.1;
            mainLoop->interval = static_cast<int>(interval);
        } else {
            interval += (mainLoop->INTERVAL_BASE - interval) * 0.08;
            mainLoop->interval = static_cast<int>(interval);
        }
    }
}

void P47GameManager::titleMove() {
    title->move();
    if (cnt <= 8) {
        btnPrsd = true;
    } else {
        int btn = pad->getButtonState();
        if (btn & Pad::PAD_BUTTON1) {
            if (!btnPrsd) {
                title->setStatus();
                if (difficulty >= P47PrefManager::DIFFICULTY_NUM)
                    mainLoop->breakLoop();
                else
                    startInGame();
                return;
            }
        } else if (btn & Pad::PAD_BUTTON2) {
            if (!btnPrsd) {
                title->changeMode();
                btnPrsd = true;
            }
        } else {
            btnPrsd = false;
        }
    }
    stageMove();
    field->move();
    enemies->move();
    bullets->move();
}

void P47GameManager::gameoverMove() {
    bool gotoNextState = false;
    if (cnt <= 64) {
        btnPrsd = true;
    } else {
        if (pad->getButtonState() & (Pad::PAD_BUTTON1 | Pad::PAD_BUTTON2)) {
            if (!btnPrsd)
                gotoNextState = true;
        } else {
            btnPrsd = false;
        }
    }
    if (cnt > 64 && gotoNextState) {
        startTitle();
    } else if (cnt > 500) {
        startTitle();
    }
    field->move();
    enemies->move();
    bullets->move();
    particles->move();
    fragments->move();
}

void P47GameManager::pauseMove() {
    pauseCnt++;
    if (pad->keys[SDLK_p] == SDL_PRESSED) {
        if (!pPrsd) {
            pPrsd = true;
            resumePause();
        }
    } else {
        pPrsd = false;
    }
}

void P47GameManager::move() {
    if (pad->keys[SDLK_ESCAPE] == SDL_PRESSED) {
        mainLoop->breakLoop();
        return;
    }
    switch (state) {
    case IN_GAME:
        inGameMove();
        break;
    case TITLE:
        titleMove();
        break;
    case GAMEOVER:
        gameoverMove();
        break;
    case PAUSE:
        pauseMove();
        break;
    default:
        break;
    }
    cnt++;
}

void P47GameManager::inGameDraw() {
    field->draw();
    P47Screen::setRetroColor(0.2, 0.7, 0.5, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    bonuses->draw();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    Screen3D::setColor(Particle::R, Particle::G, Particle::B, 1);
    glBegin(GL_LINES);
    particles->draw();
    glEnd();
    P47Screen::setRetroColor(Fragment::R, Fragment::G, Fragment::B, 1);
    fragments->draw();
    P47Screen::setRetroZ(0);
    ship->draw();
    P47Screen::setRetroColor(0.8, 0.8, 0.2, 0.8);
    shots->draw();
    P47Screen::setRetroColor(1.0, 0.8, 0.5, 1);
    if (mode == ROLL)
        rolls->draw();
    else
        locks->draw();
    enemies->draw();
    bullets->draw();
}

void P47GameManager::titleDraw() {
    field->draw();
    enemies->draw();
    bullets->draw();
}

void P47GameManager::gameoverDraw() {
    field->draw();
    Screen3D::setColor(Particle::R, Particle::G, Particle::B, 1);
    glBegin(GL_LINES);
    particles->draw();
    glEnd();
    P47Screen::setRetroColor(Fragment::R, Fragment::G, Fragment::B, 1);
    fragments->draw();
    P47Screen::setRetroZ(0);
    enemies->draw();
    bullets->draw();
}

void P47GameManager::inGameDrawLuminous() {
    glBegin(GL_LINES);
    particles->drawLuminous();
    fragments->drawLuminous();
    glEnd();
}

void P47GameManager::titleDrawLuminous() {
}

void P47GameManager::gameoverDrawLuminous() {
    glBegin(GL_LINES);
    particles->drawLuminous();
    fragments->drawLuminous();
    glEnd();
}

void P47GameManager::drawBoard(int x, int y, int width, int height) {
    glColor4f(0, 0, 0, 1);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

void P47GameManager::drawSideBoards() {
    glDisable(GL_BLEND);
    drawBoard(0, 0, 160, 480);
    drawBoard(480, 0, 160, 480);
    glEnable(GL_BLEND);
}

void P47GameManager::drawScore() {
    LetterRender::drawNum(score, 120, 28, 25, LetterRender::TO_UP);
    LetterRender::drawNum(Bonus::bonusScore, 24, 20, 12, LetterRender::TO_UP);
}

void P47GameManager::drawLeft() {
    if (left < 0)
        return;
    LetterRender::drawString("LEFT", 520, 260, 25, LetterRender::TO_DOWN);
    LetterRender::changeColor(LetterRender::RED);
    LetterRender::drawNum(left, 520, 450, 25, LetterRender::TO_DOWN);
    LetterRender::changeColor(LetterRender::WHITE);
}

void P47GameManager::drawParsec() {
    int ps = stageManager->parsec;
    if (ps < 10)
        LetterRender::drawNum(stageManager->parsec, 600, 26, 25, LetterRender::TO_DOWN);
    else if (ps < 100)
        LetterRender::drawNum(stageManager->parsec, 600, 68, 25, LetterRender::TO_DOWN);
    else
        LetterRender::drawNum(stageManager->parsec, 600, 110, 25, LetterRender::TO_DOWN);
}

void P47GameManager::drawBox(int x, int y, int w, int h) {
    if (w <= 0)
        return;
    Screen3D::setColor(1, 1, 1, 0.5);
    P47Screen::drawBoxSolid(x, y, w, h);
    Screen3D::setColor(1, 1, 1, 1);
    P47Screen::drawBoxLine(x, y, w, h);
}

void P47GameManager::drawBossShieldMeter() {
    drawBox(165, 6, bossShield, 6);
    int y = 24;
    for (int i = 0; i < BOSS_WING_NUM; i++) {
        switch (i % 2) {
        case 0:
            drawBox(165, y, bossWingShield[i], 6);
            break;
        case 1:
            drawBox(475 - bossWingShield[i], y, bossWingShield[i], 6);
            y += 12;
            break;
        }
    }
}

void P47GameManager::drawSideInfo() {
    drawSideBoards();
    drawScore();
    drawLeft();
    drawParsec();
}

void P47GameManager::inGameDrawStatus() {
    drawSideInfo();
    if (stageManager->bossSection)
        drawBossShieldMeter();
}

void P47GameManager::titleDrawStatus() {
    drawSideBoards();
    drawScore();
    title->draw();
}

void P47GameManager::gameoverDrawStatus() {
    drawSideInfo();
    if (cnt > 64) {
        LetterRender::drawString("GAME OVER", 220, 200, 15, LetterRender::TO_RIGHT);
    }
}

void P47GameManager::pauseDrawStatus() {
    drawSideInfo();
    if ((pauseCnt % 60) < 30)
        LetterRender::drawString("PAUSE", 280, 220, 12, LetterRender::TO_RIGHT);
}

void P47GameManager::setScreenShake(int cnt, float intense) {
    screenShakeCnt = cnt;
    screenShakeIntense = intense;
}

void P47GameManager::moveScreenShake() {
    if (screenShakeCnt > 0)
        screenShakeCnt--;
}

void P47GameManager::setEyepos() {
    float x = 0, y = 0;
    if (screenShakeCnt > 0) {
        x = rand.nextSignedFloat(screenShakeIntense * (screenShakeCnt + 10));
        y = rand.nextSignedFloat(screenShakeIntense * (screenShakeCnt + 10));
    }
    glTranslatef(x, y, -field->eyeZ);
}

void P47GameManager::draw() {
    SDL_Event e = mainLoop->event;
    if (e.type == SDL_VIDEORESIZE) {
        SDL_ResizeEvent* re = &(e.resize);
        if (re->w > 150 && re->h > 100)
            screen->resized(re->w, re->h);
    }
    screen->startRenderToTexture();
    glPushMatrix();
    setEyepos();
    switch (state) {
    case IN_GAME:
    case PAUSE:
        inGameDrawLuminous();
        break;
    case TITLE:
        titleDrawLuminous();
        break;
    case GAMEOVER:
        gameoverDrawLuminous();
        break;
    default:
        break;
    }
    glPopMatrix();
    screen->endRenderToTexture();

    screen->clear();
    glPushMatrix();
    setEyepos();
    switch (state) {
    case IN_GAME:
    case PAUSE:
        inGameDraw();
        break;
    case TITLE:
        titleDraw();
        break;
    case GAMEOVER:
        gameoverDraw();
        break;
    default:
        break;
    }
    glPopMatrix();

    screen->drawLuminous();

    screen->viewOrthoFixed();
    switch (state) {
    case IN_GAME:
        inGameDrawStatus();
        break;
    case TITLE:
        titleDrawStatus();
        break;
    case GAMEOVER:
        gameoverDrawStatus();
        break;
    case PAUSE:
        pauseDrawStatus();
        break;
    default:
        break;
    }
    screen->viewPerspective();
}

