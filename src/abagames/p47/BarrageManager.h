/*
 * $Id:BarrageManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * BarrageManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef BARRAGEMANAGER_H
#define BARRAGEMANAGER_H

#include <string>
#include <tr1/array>
using namespace std;


class BulletMLParserTinyXML;


class BarrageManager {
 public:
  enum {
    MORPH, SMALL, SMALLMOVE, SMALLSIDEMOVE,
    MIDDLE, MIDDLESUB, MIDDLEMOVE, MIDDLEBACKMOVE,
    LARGE, LARGEMOVE,
    MORPH_LOCK, SMALL_LOCK, MIDDLESUB_LOCK,
  };
  enum {
    BARRAGE_TYPE = 13,
    BARRAGE_MAX = 64
  };
  
  tr1::array<tr1::array<BulletMLParserTinyXML*, BARRAGE_MAX>, BARRAGE_TYPE> parser;
  tr1::array<int, BARRAGE_TYPE> parserNum;

 private:
  static tr1::array<const string, BARRAGE_TYPE> dirName;

 public:
  string getFileExt(const string& str);
  void loadBulletMLs();
  void unloadBulletMLs();
};

#endif
