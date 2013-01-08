/*
 * $Id:Title.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Title.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef TITLE_H
#define TITLE_H

#include <tr1/array>
#include <tr1/memory>
#include <gl.h>
#include <abagames/p47/P47PrefManager.h>
using namespace std;


class Pad;
class Texture;
class P47GameManager;
class P47PrefManager;
class Field;


class Title {
 private:
  tr1::shared_ptr<Pad> pad;
  tr1::shared_ptr<P47GameManager> gameManager;
  tr1::shared_ptr<P47PrefManager> prefManager;
  tr1::shared_ptr<Field> field;
  tr1::array<tr1::array<int, P47PrefManager::DIFFICULTY_NUM + 1>, P47PrefManager::MODE_NUM> slotNum;
  tr1::array<tr1::array<int, P47PrefManager::DIFFICULTY_NUM>, P47PrefManager::MODE_NUM> startReachedParsec;
  int curX, curY;
  int mode;
  enum {
    BOX_COUNT = 16
  };
  int boxCnt;
  auto_ptr<Texture> titleTexture;
  bool padPrsd;
  const int BOX_SMALL_SIZE;
  static tr1::array<const string, 5> DIFFICULTY_SHORT_STR;
  static tr1::array<const string, 5> DIFFICULTY_STR;
  static tr1::array<const string, 2> MODE_STR;
  
 public:
 Title() : padPrsd(true), BOX_SMALL_SIZE(24) {};
  void init(tr1::shared_ptr<Pad> p, tr1::shared_ptr<P47GameManager> gm, 
	    tr1::shared_ptr<P47PrefManager> pm, tr1::shared_ptr<Field> fl);
  void close();
  void start();
  int getStartParsec(int dif, int psl);
  void move();
  void setStatus();
  void changeMode();
  void draw();
  
 private:
  Title(const Title& other);
  Title& operator=(const Title& other);
  void drawBox(int x, int y, int w, int h);
  void drawBoxLight(int x, int y, int w, int h);
  void drawTitleBoard();
};

#endif
