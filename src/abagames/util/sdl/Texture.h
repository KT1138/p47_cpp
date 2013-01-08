/*
 * $Id:Texture.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Texture.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <gl.h>
#include <SDL.h>
using namespace std;


class Texture {
 public:
  static const string imagesDir;

 private:
  GLuint num;

 public:
  explicit Texture(const string& name);
  void deleteTexture();
  void bind();
};

#endif
