/*
 * $Id:SoundManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * SoundManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <memory>
#include <tr1/array>
#include <tr1/memory>
#include <abagames/util/sdl/Sound.h>
using namespace std;


class P47GameManager;


class SoundManager {
 public:
  enum {
    SHOT, ROLL_CHARGE, ROLL_RELEASE, SHIP_DESTROYED, GET_BONUS, EXTEND,
    ENEMY_DESTROYED, LARGE_ENEMY_DESTROYED, BOSS_DESTROYED, LOCK, LASER,
  };
  enum {
    BGM_NUM = 4,
    SE_NUM = 11
  };

 private:
  static tr1::shared_ptr<P47GameManager> manager;
  static tr1::array<auto_ptr<Sound>, BGM_NUM> bgm;
  static tr1::array<auto_ptr<Sound>, SE_NUM> se;
  static const string bgmFileName[];
  static const string seFileName[];
  static const int seChannel[];
 public:
  static void init(tr1::shared_ptr<P47GameManager> mng);
  static void close();
  static void playBgm(int n);
  static void playSe(int n);
  static void stopSe(int n);
};

#endif
