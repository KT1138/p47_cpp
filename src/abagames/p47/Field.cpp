/*
 * $Id:Field.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Field.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/Vector.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/p47/Field.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47Screen.h>


int Field::displayListIdx;
tr1::array<Vector, Field::RING_POS_NUM> Field::ringPos;
const float Field::RING_DEG = M_PI / 3 / ((float) (RING_POS_NUM / 2) + 0.5);
const float Field::RING_SIZE = 0.5;


void Field::init() {
  size = Vector();
  size.x = 11;
  size.y = 16;
  eyeZ = 20;
  roll = yaw = 0;
  z = aimZ = 10;
  speed = aimSpeed = 0.1;
  yawYBase = yawZBase = 0;
}

void Field::setColor(int mode) {
  switch (mode) {
  case P47GameManager::ROLL:
    r = 0.2;
    g = 0.2;
    b = 0.7;
    break;
  case P47GameManager::LOCK:
    r = 0.5;
    g = 0.3;
    b = 0.6;
    break;
  }
}

void Field::move() {
  roll += speed;
  if (roll >= RING_ANGLE_INT) 
    roll -= RING_ANGLE_INT;
  yaw += speed;
  z += (aimZ - z) * 0.003;
  speed += (aimSpeed - speed) * 0.004;
  yawYBase += (aimYawYBase - yawYBase) * 0.002;
  yawZBase += (aimYawZBase - yawZBase) * 0.002;
}

void Field::setType(int type) {
  switch (type) {
  case 0:
    aimYawYBase = 30;
    aimYawZBase = 0;
    break;
  case 1:
    aimYawYBase = 0;
    aimYawZBase = 20;
    break;
  case 2:
    aimYawYBase = 50;
    aimYawZBase = 10;
    break;
  case 3:
    aimYawYBase = 10;
    aimYawZBase = 30;
    break;
  }
}

void Field::draw() {
  Screen3D::setColor(r, g, b, 0.7);
  float d = -RING_NUM * RING_ANGLE_INT / 2 + roll;
  for (int i = 0; i < RING_NUM; i++) {
    for (int j = 1; j < 8; j++) {
      float sc = (float) j / 16 + 0.5;
      glPushMatrix();
      glTranslatef(0, 0, z);
      glRotatef(d, 1, 0, 0);
      glRotatef(sin(yaw / 180 * M_PI) * yawYBase, 0, 1, 0);
      glRotatef(sin(yaw / 180 * M_PI) * yawZBase, 0, 0, 1);
      glScalef(1, 1, sc);
      glCallList(displayListIdx);
      glPopMatrix();
    }
    d += RING_ANGLE_INT;
  }
}

bool Field::checkHit(const Vector& p) {
  if (p.x < -size.x || p.x > size.x || p.y < -size.y || p.y > size.y)
    return true;
  return false;
}

bool Field::checkHit(const Vector& p, float space) {
  if (p.x < -size.x + space || p.x > size.x - space || p.y < -size.y + space || p.y > size.y - space)
    return true;
  return false;
}

void Field::writeOneRing() {
  glBegin(GL_LINE_STRIP);
  for (int i = 0; i <= RING_POS_NUM / 2 - 2; i++) {
    glVertex3f(ringPos[i].x, RING_SIZE, ringPos[i].y);    
  }
  for (int i = RING_POS_NUM / 2 - 2; i >= 0; i--) {
    glVertex3f(ringPos[i].x, -RING_SIZE, ringPos[i].y);
  }
  glVertex3f(ringPos[0].x, RING_SIZE, ringPos[0].y);
  glEnd();
  glBegin(GL_LINE_STRIP);
  glVertex3f(ringPos[RING_POS_NUM / 2 - 1].x, RING_SIZE, ringPos[RING_POS_NUM / 2 - 1].y);
  glVertex3f(ringPos[RING_POS_NUM / 2].x, RING_SIZE, ringPos[RING_POS_NUM / 2].y);
  glVertex3f(ringPos[RING_POS_NUM / 2].x, -RING_SIZE, ringPos[RING_POS_NUM / 2].y);
  glVertex3f(ringPos[RING_POS_NUM / 2 - 1].x, -RING_SIZE, ringPos[RING_POS_NUM / 2 - 1].y);
  glVertex3f(ringPos[RING_POS_NUM / 2 - 1].x, RING_SIZE, ringPos[RING_POS_NUM / 2 - 1].y);
  glEnd();
  glBegin(GL_LINE_STRIP);
  for (int i = RING_POS_NUM / 2 + 1;  i <= RING_POS_NUM - 1; i++) {
    glVertex3f(ringPos[i].x, RING_SIZE, ringPos[i].y);
  }
  for (int i = RING_POS_NUM - 1; i >= RING_POS_NUM / 2 + 1; i--) {
    glVertex3f(ringPos[i].x, -RING_SIZE, ringPos[i].y);
  }
  glVertex3f(ringPos[RING_POS_NUM / 2 + 1].x, RING_SIZE, ringPos[RING_POS_NUM / 2 + 1].y);
  glEnd();
}

void Field::createDisplayLists() {
  float d = -RING_DEG * ((float) (RING_POS_NUM / 2) - 0.5);
  for (int i = 0; i < RING_POS_NUM; i++, d += RING_DEG) {
    ringPos[i] = Vector();
    ringPos[i].x = sin(d) * RING_RADIUS;
    ringPos[i].y = cos(d) * RING_RADIUS;
  }
  displayListIdx = glGenLists(1);
  glNewList(displayListIdx, GL_COMPILE);
  writeOneRing();
  glEndList();
}

void Field::deleteDisplayLists() {
  glDeleteLists(displayListIdx, 1);
}
