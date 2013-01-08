/*
 * $Id:SoundManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * SoundManager.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/p47/P47GameManager.h>
#include <abagames/p47/SoundManager.h>


tr1::shared_ptr<P47GameManager> SoundManager::manager(new P47GameManager());
tr1::array<auto_ptr<Sound>, SoundManager::BGM_NUM> SoundManager::bgm;
tr1::array<auto_ptr<Sound>, SoundManager::SE_NUM> SoundManager::se;

const string SoundManager::bgmFileName[] =
{"ptn0.ogg", "ptn1.ogg", "ptn2.ogg", "ptn3.ogg"};

const string SoundManager::seFileName[] =
{"shot.wav", "rollchg.wav", "rollrls.wav", "shipdst.wav", "getbonus.wav", "extend.wav",
 "enemydst.wav", "largedst.wav", "bossdst.wav", "lock.wav", "laser.wav"};

const int SoundManager::seChannel[] =
{0, 1, 2, 1, 3, 4,
 5, 6, 7, 1, 2};


void SoundManager::init(tr1::shared_ptr<P47GameManager> mng) {
    manager = mng;
    if (Sound::noSound)
        return;
    for (int i = 0; i < bgm.size(); ++i) {
        bgm[i].reset(new Sound());
        bgm[i]->loadSound(bgmFileName[i]);
    }
    for (int i = 0; i < se.size(); i++) {
        se[i].reset(new Sound());
        se[i]->loadChunk(seFileName[i], seChannel[i]);
    }
}

void SoundManager::close() {
    if (Sound::noSound)
        return;
    for (int i = 0; i < bgm.size(); i++)
        bgm[i]->free();
    for (int i = 0; i < se.size(); i++)
        se[i]->free();
}

void SoundManager::playBgm(int n) {
    if (Sound::noSound || manager->state != P47GameManager::IN_GAME)
        return;
    bgm[n]->playMusic();
}

void SoundManager::playSe(int n) {
    if (Sound::noSound || manager->state != P47GameManager::IN_GAME)
        return;
    se[n]->playChunk();
}

void SoundManager::stopSe(int n) {
    if (Sound::noSound)
        return;
    se[n]->haltChunk();
}
