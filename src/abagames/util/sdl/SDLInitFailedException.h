/*
 * $Id:SDLInitFailedException.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * SDLInitFailedException.h.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef SDLINITFAILEDEXCEPTION_H
#define SDLINITFAILEDEXCEPTION_H 

#include <exception>
#include <stdexcept>
#include <string>
using namespace std;


class SDLInitFailedException : public runtime_error {
 public:
 SDLInitFailedException(const string& msg) 
   : runtime_error(msg) 
  {
  }
};

#endif
