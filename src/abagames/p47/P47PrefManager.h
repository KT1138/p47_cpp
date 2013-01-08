/*
 * $Id:P47PrefManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47PrefManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef P47PREFMANAGER_H
#define P47PREFMANAGER_H

#include <exception>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <abagames/util/PrefManager.h>
using namespace std;


class P47PrefManager : public PrefManager {
 public:
  enum {
    PREV_VERSION_NUM = 10,
    VERSION_NUM = 20,
    MODE_NUM = 2,
    DIFFICULTY_NUM = 4,
    REACHED_PARSEC_SLOT_NUM = 10
  };
  static const char* PREF_FILE;

  int hiScore[MODE_NUM][DIFFICULTY_NUM][REACHED_PARSEC_SLOT_NUM];
  int reachedParsec[MODE_NUM][DIFFICULTY_NUM];
  int selectedDifficulty, selectedParsecSlot, selectedMode;
  
 public:
  void load();
  void save();

 private:
  void init();
  void loadPrevVersionData(FILE* fp);
};

#endif
