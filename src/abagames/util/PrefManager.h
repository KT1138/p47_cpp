/*
 * $Id:PrefManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * PrefManager.h 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#ifndef PREFMANAGER_H
#define PREFMANAGER_H


class PrefManager {
 public:
  virtual ~PrefManager() {}
  virtual void save() = 0;
  virtual void load() = 0;
};

#endif
