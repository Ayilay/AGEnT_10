/*
 * Copyright (c) 2017 Georges Troulis
 *
 * CSGOGame.h
 *
 * Declares behavior for CSGO Game Mode
*/

#ifndef _AGENDA_CSGOGAME_H
#define _AGENDA_CSGOGAME_H

#include "HardwareMap.h"
#include "Game.h"

class CSGOGame : public Game
{
    public:
        CSGOGame(HardwareMap* hw);

        // Inherited virtual methods from Game
        bool isPlaying();
        void doGameLoop(unsigned long globalTime);
        void doEndGame();

    private:
        LiquidCrystal* lcd;     // Points to the lcd stored in HardwareMap for convenience

        // Game Constants
        int armTime;
        int defuseTime;
        int timeUntilBoom;

        // Game State Variables
        // Gameplay Methods
};

#endif
