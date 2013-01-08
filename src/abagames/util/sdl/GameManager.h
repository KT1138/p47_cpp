/*
 * $Id: GameManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * GameManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <tr1/memory>
using namespace std;


class MainLoop;
class Input;
class Screen;
class PrefManager;


class GameManager {
 private:
  int status;

 protected:
  tr1::shared_ptr<MainLoop> mainLoop;
  tr1::shared_ptr<Input> input;
  tr1::shared_ptr<Screen> abstScreen;
  tr1::shared_ptr<PrefManager> abstPrefManager;

 public:
  virtual ~GameManager() {};
  void setMainLoop(tr1::shared_ptr<MainLoop> mainLoop);
  void setUIs(tr1::shared_ptr<Screen> screen, tr1::shared_ptr<Input> input);
  void setPrefManager(tr1::shared_ptr<PrefManager> prefManager);
  virtual void init() = 0;
  virtual void start() = 0;
  virtual void close() = 0;
  virtual void move() = 0;
  virtual void draw() = 0;
};

#endif
