/*
 * $Id:Sound.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * Sound.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/util/sdl/Sound.h>


bool Sound::noSound = false;
const string Sound::soundsDir = "sounds/";
const string Sound::chunksDir = "sounds/";


void Sound::init() {
    if (noSound) return;

    int audio_rate;
    Uint16 audio_format;
    int audio_channels;
    int audio_buffers;

    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        noSound = 1;
        throw SDLInitFailedException
            (string("Unable to initialize SDL_AUDIO: ") + string(SDL_GetError()) );
    }

    audio_rate = 44100;
    audio_format = AUDIO_S16;
    audio_channels = 1;
    audio_buffers = 4096;
    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0) {
        noSound = 1;
        throw SDLInitFailedException
            (string("Couldn't open audio") + string(SDL_GetError()));
    }
    Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
}

void Sound::close() {
    if (noSound) return;
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();
    }
    Mix_CloseAudio();
}

void Sound::loadSound(const string& name) {
    if (noSound) return;
    string fileName = soundsDir + name;
    music = Mix_LoadMUS(fileName.c_str());
    if (!music) {
        noSound = true;
        throw SDLInitFailedException(string("Couldn't load: ") + string(fileName) + string(Mix_GetError()));
    }
}

void Sound::loadChunk(const string& name, int ch) {
    if (noSound) return;
    string fileName = chunksDir + name;
    chunk = Mix_LoadWAV(fileName.c_str());
    if (!chunk) {
        noSound = true;
        throw SDLInitFailedException(string("Couldn't load: ") + string(fileName) + string(Mix_GetError()));
    }
    chunkChannel = ch;
}

void Sound::free() {
    if (music) {
        stopMusic();
//        Mix_FreeMusic(music);
    }
    if (chunk) {
//        haltChunk();
//    Mix_FreeChunk(chunk);
    }
}

void Sound::playMusic() {
    if (noSound) return;
    Mix_PlayMusic(music, -1);
}

void Sound::fadeMusic() {
    if (noSound) return;
    Mix_FadeOutMusic(fadeOutSpeed);
}

void Sound::stopMusic() {
    if (noSound) return;
    if ( Mix_PlayingMusic() ) {
        Mix_HaltMusic();
    }
}

void Sound::playChunk() {
    if (noSound) return;
    Mix_PlayChannel(chunkChannel, chunk, 0);
}

void Sound::haltChunk() {
    if (noSound) return;
//    Mix_HaltChannel(chunkChannel);
}
