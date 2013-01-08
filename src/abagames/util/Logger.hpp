/*
 * $Id:Logger.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Logger.hpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;


/**
 * Logger(error/info).
 */
#ifdef _WIN32

#include <windows.h>

class Logger {
public:
    static void info(string msg) {
        // Win32 exe file crashes if it writes something to stderr.
        //stderr.writeLine("Info: " ~ msg);
    }

    static void info(int n) {
        /*if (n >= 0)
          stderr.writeLine("Info: " ~ std.string.toString(n));
          else
          stderr.writeLine("Info: -" ~ std.string.toString(-n));*/
    }

    static void putMessage(string msg) {
        MessageBoxA(NULL, TEXT(msg.c_str()), TEXT("Error"), MB_OK | MB_ICONEXCLAMATION);
    }

    static void error(string msg) {
        putMessage(string("Error: ") + msg);
    }

    static void error(const runtime_error& e) {
        putMessage(string("Error: ") + static_cast<string>(e.what()));
    }
};

#endif


#ifndef _WIN32

class Logger {
public:
    static void info(string msg) {
        cout << "Info: " << msg << endl;
    }

    static void info(int n) {
        if (n >= 0)
            cout << "Info: " << n << endl;
        else
            cout << "Info: " << -n << endl;
    }

    static void error(string msg) {
        cout << "Error: " << msg << endl;
    }

    static void error(const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }
};

#endif
