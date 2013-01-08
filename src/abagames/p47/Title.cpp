/*
 * $Id:Title.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Title.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/sdl/Pad.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/util/sdl/Texture.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/LetterRender.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47PrefManager.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Title.h>


tr1::array<const string, 5> Title::DIFFICULTY_SHORT_STR = {"P", "N", "H", "E", "Q"};
tr1::array<const string, 5> Title::DIFFICULTY_STR = {"PRACTICE", "NORMAL", "HARD", "EXTREME", "QUIT"};
tr1::array<const string, 2> Title::MODE_STR = {"ROLL", "LOCK"};


void Title::init(tr1::shared_ptr<Pad> p, tr1::shared_ptr<P47GameManager> gm,
                 tr1::shared_ptr<P47PrefManager> pm, tr1::shared_ptr<Field> fl) {
    pad = p;
    gameManager = gm;
    prefManager = pm;
    field = fl;
    gameManager->difficulty = prefManager->selectedDifficulty;
    gameManager->parsecSlot = prefManager->selectedParsecSlot;
    gameManager->mode = prefManager->selectedMode;
    titleTexture.reset(new Texture("title.bmp"));
}

void Title::close() {
    titleTexture->deleteTexture();
}

void Title::start() {
    for (int k = 0; k < P47PrefManager::MODE_NUM; ++k) {
        for (int i = 0; i < P47PrefManager::DIFFICULTY_NUM; ++i) {
            slotNum[k][i] = (prefManager->reachedParsec[k][i] - 1) / 10 + 1;
            startReachedParsec[k][i] = slotNum[k][i] * 10 + 1;
            if (slotNum[k][i] > 10)
                slotNum[k][i] = 10;
        }
        slotNum[k][P47PrefManager::DIFFICULTY_NUM] = 1;
    }
    curX = gameManager->parsecSlot;
    curY = gameManager->difficulty;
    mode = gameManager->mode;
    boxCnt = BOX_COUNT;
    field->setColor(mode);
}

int Title::getStartParsec(int dif, int psl) {
    if (psl < P47PrefManager::REACHED_PARSEC_SLOT_NUM - 1) {
        return psl * 10 + 1;
    } else {
        int rp = prefManager->reachedParsec[mode][dif];
        rp--;
        rp /= 10;
        rp *= 10;
        rp++;
        return rp;
    }
}

void Title::move() {
    int ps = pad->getPadState();
    if (!padPrsd) {
        if (ps & Pad::PAD_DOWN) {
            curY++;
            if (curY >= slotNum[mode].size())
                curY = 0;
            if (curX >= slotNum[mode][curY])
                curX = slotNum[mode][curY] - 1;
        } else if (ps & Pad::PAD_UP) {
            curY--;
            if (curY < 0)
                curY = slotNum[mode].size() - 1;
            if (curX >= slotNum[mode][curY])
                curX = slotNum[mode][curY] - 1;
        } else if (ps & Pad::PAD_RIGHT) {
            curX++;
            if (curX >= slotNum[mode][curY])
                curX = 0;
        } else if (ps & Pad::PAD_LEFT) {
            curX--;
            if (curX < 0)
                curX = slotNum[mode][curY] - 1;
        }
        if (ps != 0) {
            boxCnt = BOX_COUNT;
            padPrsd = true;
            gameManager->startStage(curY, curX, getStartParsec(curY, curX), mode);
        }
    } else {
        if (ps == 0)
            padPrsd = false;
    }
    if (boxCnt >= 0)
        boxCnt--;
}

void Title::setStatus() {
    gameManager->difficulty = curY;
    gameManager->parsecSlot = curX;
    gameManager->mode = mode;
    if (curY < P47PrefManager::DIFFICULTY_NUM) {
        prefManager->selectedDifficulty = curY;
        prefManager->selectedParsecSlot = curX;
        prefManager->selectedMode = mode;
    }
}

void Title::changeMode() {
    ++mode;
    if (mode >= P47PrefManager::MODE_NUM)
        mode = 0;
    if (curX >= slotNum[mode][curY])
        curX = slotNum[mode][curY] - 1;
    field->setColor(mode);
    gameManager->startStage(curY, curX, getStartParsec(curY, curX), mode);
}

void Title::drawBox(int x, int y, int w, int h) {
    Screen3D::setColor(1, 1, 1, 1);
    P47Screen::drawBoxLine(x, y, w, h);
    Screen3D::setColor(1, 1, 1, 0.5);
    P47Screen::drawBoxSolid(x, y, w, h);
}

void Title::drawBoxLight(int x, int y, int w, int h) {
    Screen3D::setColor(1, 1, 1, 0.7);
    P47Screen::drawBoxLine(x, y, w, h);
    Screen3D::setColor(1, 1, 1, 0.3);
    P47Screen::drawBoxSolid(x, y, w, h);
}

void Title::drawTitleBoard() {
    glEnable(GL_TEXTURE_2D);
    titleTexture->bind();
    P47Screen::setColor(1, 1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0, 0);
    glVertex3f(180, 20, 0);
    glTexCoord2f(1, 0);
    glVertex3f(308, 20, 0);
    glTexCoord2f(1, 1);
    glVertex3f(308, 148, 0);
    glTexCoord2f(0, 1);
    glVertex3f(180, 148, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Title::draw() {
    int sx, sy;
    LetterRender::drawString
        (DIFFICULTY_STR[curY], 470 - DIFFICULTY_STR[curY].size() * 14, 150, 
         10, LetterRender::TO_RIGHT);
    LetterRender::drawString
        (MODE_STR[mode], 470 - MODE_STR[mode].size() * 14, 450, 
         10, LetterRender::TO_RIGHT);
    if (curX > 0) {
        LetterRender::drawString("START AT PARSEC", 290, 180, 6, LetterRender::TO_RIGHT);
        LetterRender::drawNum(getStartParsec(curY, curX), 470, 180, 6, LetterRender::TO_RIGHT);
    }
    if (curY < P47PrefManager::DIFFICULTY_NUM)
        LetterRender::drawNum
            (prefManager->hiScore[mode][curY][curX], 470, 210, 10, LetterRender::TO_RIGHT);
    sy = 260;
    for (int y = 0; y < P47PrefManager::DIFFICULTY_NUM + 1; y++) {
        sx = 180;
        for (int x = 0; x < slotNum[mode][y]; x++) {
            if (x == curX && y == curY) {
                int bs = (BOX_COUNT - boxCnt) / 2;
                drawBox(sx - bs, sy - bs, BOX_SMALL_SIZE + bs * 2, BOX_SMALL_SIZE + bs * 2);
                if (x == 0) {
                    LetterRender::drawString
                        (DIFFICULTY_SHORT_STR[y], sx + 13, sy + 13, 12, LetterRender::TO_RIGHT);
                } else {
                    LetterRender::drawString
                        (DIFFICULTY_SHORT_STR[y], sx + 4, sy + 13, 12, LetterRender::TO_RIGHT);
                    if (x >= P47PrefManager::REACHED_PARSEC_SLOT_NUM - 1) {
                        LetterRender::drawString("X", sx + 21, sy + 14, 12, LetterRender::TO_RIGHT);
                    } else {
                        LetterRender::drawNum(x, sx + 22, sy + 13, 12, LetterRender::TO_RIGHT);
                    }
                }
            } else {
                drawBoxLight(sx, sy, BOX_SMALL_SIZE, BOX_SMALL_SIZE);
            }
            sx += 28;
        }
        sy += 32;
        if (y == P47PrefManager::DIFFICULTY_NUM - 1)
            sy += 15;
    }
    drawTitleBoard();
}

