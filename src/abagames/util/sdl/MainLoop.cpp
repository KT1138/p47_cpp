/*
 * $Id:MainLoop.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * MainLoop.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/PrefManager.h>
#include <abagames/util/Logger.hpp>
#include <abagames/util/sdl/MainLoop.h>
#include <abagames/util/sdl/GameManager.h>
#include <abagames/util/sdl/Screen.h>
#include <abagames/util/sdl/Sound.h>
#include <abagames/util/sdl/Input.h>


MainLoop::MainLoop(tr1::shared_ptr<Screen> screen, tr1::shared_ptr<Input> input,
		   tr1::shared_ptr<GameManager> gameManager, tr1::shared_ptr<PrefManager> prefManager)
    : INTERVAL_BASE(16), interval(INTERVAL_BASE), accframe(0), maxSkipFrame(5)
{
    this->screen = screen;
    this->input = input;
    gameManager->setMainLoop(tr1::shared_ptr<MainLoop>(this));
    gameManager->setUIs(screen, input);
    gameManager->setPrefManager(prefManager);
    this->gameManager = gameManager;
    this->prefManager = prefManager;
}

void MainLoop::initFirst() {
    prefManager->load();
    try {
        Sound::init();
    } catch (const SDLInitFailedException& e) {
        Logger::error(e);
    }
    gameManager->init();
}

void MainLoop::quitLast() {
    prefManager->save();
    gameManager->close();
    Sound::close();
    prefManager->save();
    screen->closeSDL();
    SDL_Quit();
    Sound::close();
}

void MainLoop::breakLoop() {
    done = true;
}

void MainLoop::loop() {
    done = false;
    long prvTickCount = 0;
    int i;
    long nowTick;
    int frame;
    
    screen->initSDL();
    initFirst();
    gameManager->start();

    while (!done) {
        SDL_PollEvent(&event);
        input->handleEvent(&event);
        if (event.type == SDL_QUIT)
            breakLoop();
        nowTick = SDL_GetTicks();
        frame = (int) (nowTick-prvTickCount) / interval;
        if (frame <= 0) {
            frame = 1;
            SDL_Delay(prvTickCount+interval-nowTick);
            if (accframe) {
                prvTickCount = SDL_GetTicks();
            } else {
                prvTickCount += interval;
            }
        } else if (frame > maxSkipFrame) {
            frame = maxSkipFrame;
            prvTickCount = nowTick;
        } else {
            prvTickCount += frame * interval;
        }
        for (i = 0; i < frame; i++) {
            gameManager->move();
        }
        screen->clear();
        gameManager->draw();
        screen->flip();
    }
    quitLast();
}
