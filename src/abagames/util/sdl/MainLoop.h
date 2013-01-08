/*
 * $Id:MainLoop.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * MainLoop.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <tr1/memory>
#include <SDL.h>
#include <abagames/util/sdl/GameManager.h>
using namespace std;


class GameManager;
class Input;
class PrefManager;
class Screen;


class MainLoop {
 public:
  const int INTERVAL_BASE;
  int interval;
  int accframe;
  int maxSkipFrame;
  SDL_Event event;

 private:
  tr1::shared_ptr<Screen> screen;
  tr1::shared_ptr<Input> input;
  tr1::shared_ptr<GameManager> gameManager;
  tr1::shared_ptr<PrefManager> prefManager;
  bool done;

 public:
  MainLoop(tr1::shared_ptr<Screen> screen, tr1::shared_ptr<Input> input,
	   tr1::shared_ptr<GameManager> gameManager, tr1::shared_ptr<PrefManager> prefManager);
  virtual ~MainLoop() {};
  void breakLoop();
  void loop();

 private:
  void initFirst();
  void quitLast();
};

#endif
