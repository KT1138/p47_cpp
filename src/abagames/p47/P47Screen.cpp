/*
 * $Id:P47Screnn.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47Screen.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/p47/LuminousScreen.h>
#include <abagames/p47/P47Screen.h>


std::string P47Screen::CAPTION = "PARSEC47";
float P47Screen::luminous = 0;
float P47Screen::retroR;
float P47Screen::retroG;
float P47Screen::retroB;
float P47Screen::retroA;
float P47Screen::retro;
float P47Screen::retroSize;
float P47Screen::retroZ = 0;
Rand P47Screen::rand;


void P47Screen::init() {
    setCaption(CAPTION);
    glLineWidth(1);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
    rand = Rand();
    if (luminous > 0) {
        luminousScreen.reset(new LuminousScreen());
        luminousScreen->init(luminous, width, height);
    } else {
        luminousScreen.reset();
    }
}

void P47Screen::close() {
    if (luminousScreen)
        luminousScreen->close();
}

void P47Screen::startRenderToTexture() {
    if (luminousScreen)
        luminousScreen->startRenderToTexture();
}

void P47Screen::endRenderToTexture() {
    if (luminousScreen)
        luminousScreen->endRenderToTexture();
}

void P47Screen::drawLuminous() {
    if (luminousScreen)
        luminousScreen->draw();
}

void P47Screen::resized(int width, int height) {
    if (luminousScreen)
        luminousScreen->resized(width, height);
    Screen3D::resized(width, height);
}

void P47Screen::viewOrthoFixed() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void P47Screen::viewPerspective() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void P47Screen::setRetroParam(float r, float sz) {
    retroR = r; retroSize = sz;
}

void P47Screen::setRetroColor(float r, float g, float b, float a) {
    retroR = r; retroG = g; retroB = b; retroA = a;
}

void P47Screen::setRetroZ(float z) {
    retroZ = z;
}

void P47Screen::drawLineRetro(float x1, float y1, float x2, float y2) {
    float cf = (1 - retro) * 0.5;
    float r = retroR + (1 - retroR) * cf;
    float g = retroG + (1 - retroG) * cf;
    float b = retroB + (1 - retroB) * cf;
    float a = retroA * (cf + 0.5);
    if (rand.nextInt(7) == 0) {
        r *= 1.5; if (r > 1) r = 1;
        g *= 1.5; if (g > 1) g = 1;
        b *= 1.5; if (b > 1) b = 1;
        a *= 1.5; if (a > 1) a = 1;
    }
    setColor(r, g, b, a);
    if (retro < 0.2f) {
        glBegin(GL_LINES);
        glVertex3f(x1, y1, retroZ);
        glVertex3f(x2, y2, retroZ);
        glEnd();
    } else {
        float ds = retroSize * retro;
        float ds2 = ds / 2;
        float lx = fabs(x2 - x1);
        float ly = fabs(y2 - y1);
        glBegin(GL_QUADS);
        if (lx < ly) {
            int n = static_cast<int>(ly / ds);
            if (n > 0) {
                float xo = (x2 - x1) / n, xos  = 0;
                float yo;
                if (y2 < y1)
                    yo = -ds;
                else
                    yo = ds;
                float x = x1, y = y1;
//                for (int i = 0; i <= n; i++, xos += xo, y += yo) {
                for (int i = 0; i <= n; ++i, xos += xo, y += yo) {
                    if (xos >= ds) {
                        x += ds;
                        xos -= ds;
                    } else if (xos <= -ds) {
                        x -= ds;
                        xos += ds;
                    }
                    glVertex3f(x - ds2, y - ds2, retroZ);
                    glVertex3f(x + ds2, y - ds2, retroZ);
                    glVertex3f(x + ds2, y + ds2, retroZ);
                    glVertex3f(x - ds2, y + ds2, retroZ);
                }
            }
        } else {
            int n = static_cast<int>(lx / ds);
            if (n > 0) {
                float yo = (y2 - y1) / n, yos = 0;
                float xo;
                if (x2 < x1)
                    xo = -ds;
                else
                    xo = ds;
                float x = x1, y = y1;
                for (int i = 0; i <= n; ++i, x += xo, yos += yo) {
                    if (yos >= ds) {
                        y += ds;
                        yos -= ds;
                    } else if (yos <= -ds) {
                        y -= ds;
                        yos += ds;
                    }
                    glVertex3f(x - ds2, y - ds2, retroZ);
                    glVertex3f(x + ds2, y - ds2, retroZ);
                    glVertex3f(x + ds2, y + ds2, retroZ);
                    glVertex3f(x - ds2, y + ds2, retroZ);
                }
            }
        }
        glEnd();
    }
}

void P47Screen::drawBoxRetro(float x, float y, float width, float height, float deg) {
    float w1, h1, w2, h2;
    w1 = width * cos(deg) - height * sin(deg);
    h1 = width * sin(deg) + height * cos(deg);
    w2 = -width * cos(deg) - height * sin(deg);
    h2 = -width * sin(deg) + height * cos(deg);
    drawLineRetro(x + w2, y - h2, x + w1, y - h1);
    drawLineRetro(x + w1, y - h1, x - w2, y + h2);
    drawLineRetro(x - w2, y + h2, x - w1, y + h1);
    drawLineRetro(x - w1, y + h1, x + w2, y - h2);
}

void P47Screen::drawBoxSolid(float x, float y, float width, float height) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0);
    glVertex3f(x + width, y, 0);
    glVertex3f(x + width, y + height, 0);
    glVertex3f(x, y + height, 0);
    glEnd();
}

void P47Screen::drawBoxLine(float x, float y, float width, float height) {
    glBegin(GL_LINE_LOOP);
    glVertex3f(x, y, 0);
    glVertex3f(x + width, y, 0);
    glVertex3f(x + width, y + height, 0);
    glVertex3f(x, y + height, 0);
    glEnd();
}

