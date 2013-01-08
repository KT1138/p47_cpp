/*
 * $Id:P47Boot.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47Boot.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <cstdlib>
#include <cstring>
#include <exception>
#include <tr1/memory>
#include <stdexcept>
#include <abagames/util/Logger.hpp>
#include <abagames/util/sdl/MainLoop.h>
#include <abagames/util/sdl/Pad.h>
#include <abagames/util/sdl/Screen3D.h>
#include <abagames/util/sdl/Sound.h>
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/P47PrefManager.h>
#include <abagames/p47/P47Screen.h>
#include <abagames/p47/Ship.h>
using namespace std;


tr1::shared_ptr<P47Screen> screen;
tr1::shared_ptr<Pad> pad;
tr1::shared_ptr<P47GameManager> gameManager;
tr1::shared_ptr<P47PrefManager> prefManager;
auto_ptr<MainLoop> mainLoop;


void usage(char* args0) {
    Logger::error
        ("Usage: " + string(args0) + " [-brightness [0-100]] [-luminous [0-100]] [-nosound] [-window] [-reverse] [-lowres] [-slowship] [-nowait]");
}

void parseArgs(int argc, char *args[]){
    for (int i = 1; i < argc; ++i) {
        if (strcmp(args[i], "-brightness") == 0) {
            if (i >= argc - 1) {
                usage(args[0]);
                throw runtime_error("Invalid options");
            }
            i++;
            float b = static_cast<float>(atoi(args[i])) / 100;
            if (b < 0 || b > 1) {
                usage(args[0]);
                throw runtime_error("Invalid options");
            }
            Screen3D::brightness = b;
        }
        else if (strcmp(args[i], "-luminous") == 0) {
            if (i >= argc - 1) {
                usage(args[0]);
                throw runtime_error("Invalid options");
            }
            i++;
            float l = static_cast<float>(atoi(args[i])) / 100;
            if (l < 0 || l > 1) {
                usage(args[0]);
                throw runtime_error("Invalid options");
            }
            P47Screen::luminous = l;
        }
        else if (strcmp(args[i], "-nosound") == 0)
            Sound::noSound = true;
        else if (strcmp(args[i], "-window") == 0)
            Screen3D::windowMode = true;
        else if (strcmp(args[i], "-reverse") == 0)
            pad->buttonReversed = true;
        else if (strcmp(args[i], "-lowres") == 0)
            Screen3D::lowres = true;
        else if (strcmp(args[i], "-slowship") == 0)
            Ship::isSlow = true;
        else if (strcmp(args[i], "-nowait") == 0)
            gameManager->nowait = true;
        else if (strcmp(args[i], "-accframe") == 0)
            mainLoop->accframe = 1;
        else {
            usage(args[0]);
            throw runtime_error("Invalid options");
        }
    }
}

int boot(int argc, char *args[]) {
    screen.reset(new P47Screen());
    pad.reset(new Pad());
    try {
        pad->openJoystick();
    } catch (const exception& e) {}
    gameManager.reset(new P47GameManager());
    prefManager.reset(new P47PrefManager());
    mainLoop.reset(new MainLoop(screen, pad, gameManager, prefManager));
    try {
        parseArgs(argc, args);
    } catch (const exception& e) {
        return EXIT_FAILURE;
    }
    mainLoop->loop();
    return EXIT_SUCCESS;
}

#ifdef _WIN32

// Boot as the Windows executable.
#include <windows.h>


int WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR lpCmdLine,
            int nCmdShow) {
    int result;

    try {
        char exe[4096];
        GetModuleFileNameA(NULL, exe, 4096);

        char* args[30];
        char* cp;
        const char* delim = " ";
        cp = exe;

        int argc;
        for (int i = 0; i < 30; ++i) {
            if ((args[i] = strtok(cp, delim)) == 0) {
                argc = i;
                break;
            }
            cp = 0;
        }

        result = boot(argc, args);
    } catch (const runtime_error& e) {
        Logger::info(string("Exception: ") + string(e.what()));
        result = EXIT_FAILURE;
    }
    return result;
}

#endif

#ifndef _WIN32

int main(int argc, char *argv[]) {
    return boot(argc, argv);
}

#endif
