/*
 * $Id:LuminousScreen.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * LuminousScreen.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/Rand.h>
#include <abagames/p47/LuminousScreen.h>


int LuminousScreen::lmOfs[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};


void LuminousScreen::init(float luminous, int width, int height) {
    makeLuminousTexture();
    this->luminous = luminous;
    resized(width, height);
}

void LuminousScreen::resized(int width, int height) {
    screenWidth = width;
    screenHeight = height;
}

void LuminousScreen::close() {
    glDeleteTextures(1, &luminousTexture);
}

void LuminousScreen::startRenderToTexture() {
    glViewport(0, 0, luminousTextureWidth, luminousTextureHeight);
}

void LuminousScreen::endRenderToTexture() {
    glBindTexture(GL_TEXTURE_2D, luminousTexture);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                     0, 0, luminousTextureWidth, luminousTextureHeight, 0);
    glViewport(0, 0, screenWidth, screenHeight);
}

void LuminousScreen::draw() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, luminousTexture);
    viewOrtho();
    glColor4f(1, 0.8, 0.9, luminous);
    glBegin(GL_QUADS);
    for (int i = 0; i < 5; i++) {
        glTexCoord2f(0, 1);
        glVertex2f(0 + lmOfs[i][0] * lmOfsBs, 0 + lmOfs[i][1] * lmOfsBs);
        glTexCoord2f(0, 0);
        glVertex2f(0 + lmOfs[i][0] * lmOfsBs, screenHeight + lmOfs[i][1] * lmOfsBs);
        glTexCoord2f(1, 0);
        glVertex2f(screenWidth + lmOfs[i][0] * lmOfsBs, screenHeight + lmOfs[i][0] * lmOfsBs);
        glTexCoord2f(1, 1);
        glVertex2f(screenWidth + lmOfs[i][0] * lmOfsBs, 0 + lmOfs[i][0] * lmOfsBs);
    }
    glEnd();
    viewPerspective();
    glDisable(GL_TEXTURE_2D);
}

void LuminousScreen::makeLuminousTexture() {
    uint* data = td;
    int i;
    memset(data, 0, luminousTextureWidth * luminousTextureHeight * 4 * sizeof(uint));
    glGenTextures(1, &luminousTexture);
    glBindTexture(GL_TEXTURE_2D, luminousTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, luminousTextureWidth, luminousTextureHeight, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void LuminousScreen::viewOrtho() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, screenWidth, screenHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void LuminousScreen::viewPerspective() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
