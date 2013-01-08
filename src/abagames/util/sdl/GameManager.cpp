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
#include <abagames/util/PrefManager.h>
#include <abagames/util/sdl/GameManager.h>
#include <abagames/util/sdl/Input.h>
#include <abagames/util/sdl/MainLoop.h>
#include <abagames/util/sdl/Screen.h>


void GameManager::setMainLoop(tr1::shared_ptr<MainLoop> mainLoop) { 
    this->mainLoop = mainLoop;
}

void GameManager::setUIs(tr1::shared_ptr<Screen> screen, tr1::shared_ptr<Input> input) {
    abstScreen = screen;
    this->input = input;
}

void GameManager::setPrefManager(tr1::shared_ptr<PrefManager> prefManager) {
    abstPrefManager = prefManager;
}
