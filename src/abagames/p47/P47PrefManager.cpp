/*
 * $Id:P47PrefManager.d,v 1.2 2004/01/01 11:26:43 kenta Exp $
 *
 * Copyright 2003 Kenta Cho. All rights reserved.
 */
/*
 * P47PrefManager.cpp 2012/04/24
 *
 * Copyright 2012 Koichi Yazawa. All rights reserved.
 */
#include <abagames/p47/P47PrefManager.h>


const char* P47PrefManager::PREF_FILE = "p47.prf"; 


void P47PrefManager::init() {
    for (int k = 0; k < MODE_NUM; ++k) {
        for (int i = 0; i < DIFFICULTY_NUM; ++i) {
            reachedParsec[k][i] = 0;
            for (int j = 0; j < REACHED_PARSEC_SLOT_NUM; ++j) {
                hiScore[k][i][j] = 0;
            }
        }
    }
    selectedDifficulty = 1;
    selectedParsecSlot = 0;
    selectedMode = 0;
}

void P47PrefManager::loadPrevVersionData(FILE* fp) {
    for (int i = 0; i < DIFFICULTY_NUM; ++i) {
        fscanf(fp, "%d", reachedParsec[0][i]);
        for (int j = 0; j < REACHED_PARSEC_SLOT_NUM; ++j) {
            fscanf(fp, "%d", hiScore[0][i][j]);
        }
    }
    fscanf(fp, "%d", selectedDifficulty);
    fscanf(fp, "%d", selectedParsecSlot);
}

void P47PrefManager::load() {
    FILE* fp = fopen("p47.prf", "r");
    try {
        int ver = 0;
        if (!fp) {
            init();
            save();
        }
        fscanf(fp, "%d", &ver);
        if (ver == PREV_VERSION_NUM) {
            init();
            loadPrevVersionData(fp);
            return;
        }
        else if (ver != VERSION_NUM) {
            throw runtime_error("Wrong version num");
        }
        for (int k = 0; k < MODE_NUM; ++k) {
            for (int i = 0; i < DIFFICULTY_NUM; ++i) {
                fscanf(fp, "%d", &reachedParsec[k][i]);
                for (int j = 0; j < REACHED_PARSEC_SLOT_NUM; ++j) {
                    fscanf(fp, "%d", &hiScore[k][i][j]);
                }
            }
        }
    } catch (const runtime_error& e) {
        init();
    }
    fclose(fp);
}

void P47PrefManager::save() {
    FILE* fp = fopen(PREF_FILE, "w");
    fprintf(fp, "%d ", VERSION_NUM);
    for (int k = 0; k < MODE_NUM; ++k) {
        for (int i = 0; i < DIFFICULTY_NUM; ++i) {
            fprintf(fp, "%d ", reachedParsec[k][i]);
            for (int j = 0; j < REACHED_PARSEC_SLOT_NUM; j++) {
                fprintf(fp, "%d ", hiScore[k][i][j]);
            }
        }
    }
    fprintf(fp, "%d ", selectedDifficulty);
    fprintf(fp, "%d ", selectedParsecSlot);
    fprintf(fp, "%d ", selectedMode);
    fclose(fp);
}
