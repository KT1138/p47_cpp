/*
 * $Id:Screen3D.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Screen3D.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <iostream>
#include <sstream>
#include <string>
#include <SDL.h>
#include <gl.h>
#include <abagames/util/sdl/SDLInitFailedException.h>
#include <abagames/util/sdl/Screen3D.h>
using namespace std;


float Screen3D::brightness = 1;
int Screen3D::width = 640;
int Screen3D::height = 480;
bool Screen3D::lowres = false;
bool Screen3D::windowMode = false;
float Screen3D::nearPlane = 0.1;
float Screen3D::farPlane = 1000;


void Screen3D::initSDL() {
    if (lowres) {
        width /= 2;
        height /= 2;
    }
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDLInitFailedException(
            string("Unable to initialize SDL: ") + string(SDL_GetError()));
    }
    Uint32 videoFlags;
    if (windowMode) {
        videoFlags = SDL_OPENGL | SDL_RESIZABLE;
    } else {
//        videoFlags = SDL_OPENGL | SDL_FULLSCREEN;
        videoFlags = SDL_OPENGL | SDL_RESIZABLE;
    }
    if (SDL_SetVideoMode(width, height, 0, videoFlags) == NULL) {
        throw SDLInitFailedException(
            string("Unable to create SDL screen: ") + string(SDL_GetError()));
    }
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    resized(width, height);
    SDL_ShowCursor(SDL_DISABLE);
    init();
}

// Reset viewport when the screen is resized.
void Screen3D::screenResized() {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-nearPlane,
              nearPlane,
              -nearPlane * (GLfloat)height / (GLfloat)width,
              nearPlane * (GLfloat)height / (GLfloat)width,
              0.1f, farPlane);
    glMatrixMode(GL_MODELVIEW);
}

void Screen3D::resized(int width, int height) {
    this->width = width; this->height = height;
    screenResized();
}

void Screen3D::closeSDL() {
    close();
    SDL_ShowCursor(SDL_ENABLE);
}

void Screen3D::flip() {
    handleError();
    SDL_GL_SwapBuffers();
}

void Screen3D::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Screen3D::handleError() {
    GLenum error = glGetError();
    if (error == GL_NO_ERROR) return;
    closeSDL();
}

void Screen3D::setCaption(std::string name) {
    const char* p_str = name.c_str();
    SDL_WM_SetCaption(p_str, NULL);
}

void Screen3D::setColor(float r, float g, float b, float a) {
    glColor4f(r * brightness, g * brightness, b * brightness, a);
}
