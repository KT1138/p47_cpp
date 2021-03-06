/*
 * $Id:Pad.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Pad.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <string>
#include <abagames/util/sdl/Pad.h>
#include <abagames/util/sdl/SDLInitFailedException.h>
using namespace std;


Pad::~Pad() 
{
    keys = 0;
    stick = 0;
}

void Pad::openJoystick() {
    if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) < 0) {
        throw SDLInitFailedException(
            string("Unable to init SDL joystick: ") + string(SDL_GetError()));
    }
    stick = SDL_JoystickOpen(0);
}

void Pad::handleEvent(SDL_Event* event) {
    keys = SDL_GetKeyState(NULL);
}

int Pad::getPadState() {
    int x = 0, y = 0;
    int pad = 0;
    if (stick) {
        x = SDL_JoystickGetAxis(stick, 0);
        y = SDL_JoystickGetAxis(stick, 1);
    }
    if (keys[SDLK_RIGHT] == SDL_PRESSED || keys[SDLK_KP6] == SDL_PRESSED || x > JOYSTICK_AXIS) {
        pad |= PAD_RIGHT;
    }
    if (keys[SDLK_LEFT] == SDL_PRESSED || keys[SDLK_KP4] == SDL_PRESSED || x < -JOYSTICK_AXIS) {
        pad |= PAD_LEFT;
    }
    if (keys[SDLK_DOWN] == SDL_PRESSED || keys[SDLK_KP2] == SDL_PRESSED || y > JOYSTICK_AXIS) {
        pad |= PAD_DOWN;
    }
    if (keys[SDLK_UP] == SDL_PRESSED ||  keys[SDLK_KP8] == SDL_PRESSED || y < -JOYSTICK_AXIS) {
        pad |= PAD_UP;
    }
    return pad;
}

int Pad::getButtonState() {
    int btn = 0;
    int btn1 = 0, btn2 = 0, btn3 = 0, btn4 = 0, btn5 = 0, btn6 = 0, btn7 = 0, btn8 = 0;

    if (stick) {
        btn1 = SDL_JoystickGetButton(stick, 0);
        btn2 = SDL_JoystickGetButton(stick, 1);
        btn3 = SDL_JoystickGetButton(stick, 2);
        btn4 = SDL_JoystickGetButton(stick, 3);
        btn5 = SDL_JoystickGetButton(stick, 4);
        btn6 = SDL_JoystickGetButton(stick, 5);
        btn7 = SDL_JoystickGetButton(stick, 6);
        btn8 = SDL_JoystickGetButton(stick, 7);
    }
    if (keys[SDLK_z] == SDL_PRESSED || keys[SDLK_LCTRL] == SDL_PRESSED || 
	btn1 || btn4 || btn5 || btn8) {
        if (!buttonReversed)
            btn |= PAD_BUTTON1;
        else
            btn |= PAD_BUTTON2;
    }
    if (keys[SDLK_x] == SDL_PRESSED ||
	keys[SDLK_LALT] == SDL_PRESSED || keys[SDLK_LSHIFT] == SDL_PRESSED ||
	btn2 || btn3 || btn6 || btn7) {
        if (!buttonReversed)
            btn |= PAD_BUTTON2;
        else
            btn |= PAD_BUTTON1;
    }
    return btn;
}

