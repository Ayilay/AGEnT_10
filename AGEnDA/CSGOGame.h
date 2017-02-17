/*
 * Copyright (c) 2017 Georges Troulis
 *
 * CSGOGame.h
 *
 * Declares behavior for CSGO Game Mode
*/ 

#ifndef _AGENDA_CSGOGAME_H
#define _AGENDA_CSGOGAME_H

#include "HardwareInterface.h"
#include "Game.h"

class CSGOGame : public Game
{
    public:
        CSGOGame(HardwareInterface* hw);

        // Inherited virtual methods from Game
        bool isPlaying();
        void doGameLoop();

    private:
};

#endif
