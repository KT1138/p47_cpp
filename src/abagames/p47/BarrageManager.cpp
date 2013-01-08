/*
 * $Id:BarrageManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * BarrageManager.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <bulletml.h>
#include <bulletmlparser.h>
#include <bulletmlparser-tinyxml.h>
#include <dirent_d.c>
#include <abagames/util/Logger.hpp>
#include <abagames/p47/BarrageManager.h>
#include <abagames/p47/MorphBullet.h>


tr1::array<const string, BarrageManager::BARRAGE_TYPE> BarrageManager::dirName =
  {"morph", "small", "smallmove", "smallsidemove", 
   "middle", "middlesub", "middlemove", "middlebackmove",
   "large", "largemove",
   "morph_lock", "small_lock", "middlesub_lock"};

string BarrageManager::getFileExt(const string& s) {
    size_t i = s.rfind('.', s.length());
    if (i != string::npos) {
        return (s.substr(i+1, s.length() - i));
    }   
    return ("");
}

void BarrageManager::loadBulletMLs() {
    for (int i = 0; i < BARRAGE_TYPE; ++i) {
        DIR* d = opendir(dirName[i].c_str());
        struct dirent* dp;
        int j = 0;
            while ((dp = readdir(d)) != 0) {
                string fileName = static_cast<string>(dp->d_name);
                if (getFileExt(fileName) != "xml")
                    continue;
                Logger::info(string("Load BulletML: ") + dirName[i] + string("/") + fileName);
                parser[i][j] = 
                     BulletMLParserTinyXML_new(const_cast<char*>((dirName[i] + string("/") + fileName).c_str()));
                BulletMLParserTinyXML_parse(parser[i][j]);                
                ++j;
            }
        closedir(d);
        parserNum[i] = j;
    }
}

void BarrageManager::unloadBulletMLs() {
  for (int i = 0; i< BARRAGE_TYPE; ++i) {
    for (int j = 0; j < parserNum[i]; ++j) {
        delete parser[i][j];
        parser[i][j] = 0;
    }
  }
}
