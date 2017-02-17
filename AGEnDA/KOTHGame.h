/*
 * Copyright (c) 2017 Georges Troulis
 *
 * KOTHGame.h
 *
 * Defines behavior for KOTH Game Mode
*/ 

#ifndef _AGENDA_KOTHGAME_H
#define _AGENDA_KOTHGAME_H

#include "HardwareInterface.h"
#include "Game.h"

class KOTHGame : public Game
{
    public:
        KOTHGame(HardwareInterface* hw);

        // Inherited virtual methods from Game
        bool isPlaying();
        void doGameLoop();

    private:
};

#endif
