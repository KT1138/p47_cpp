/*
 * $Id:Texture.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Texture.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/sdl/SDLInitFailedException.h>
#include <abagames/util/sdl/Texture.h>


const string Texture::imagesDir = "images/";


Texture::Texture(const string& name)
{
    string fileName;
    fileName += imagesDir + name;
    SDL_Surface* surface;
    const char* p_str = fileName.c_str();
    surface = SDL_LoadBMP(p_str);

    if (!surface) {
        throw SDLInitFailedException(string("Unable to load: ") + fileName);
    }
    glGenTextures(1, &num);
    glBindTexture(GL_TEXTURE_2D, num);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, surface->pixels);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    /*gluBuild2DMipmaps(GL_TEXTURE_2D, 3, surface.w, surface.h, 
      GL_RGB, GL_UNSIGNED_BYTE, surface.pixels);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);*/
}

void Texture::deleteTexture() {
    glDeleteTextures(1, &num);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, num);
}
