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
        LiquidCrystal* lcd;         // Points to the lcd stored in HardwareMap for convenience

        // Game Constants
        const int armTime;          // Time it takes to arm the bomb (seconds)
        const int defuseTime;       // Time it takes to defuse the bomb (seconds)
        const String password;      // The password that shows up on the screen while the bomb is arming

        // Game State Variables
        int timeUntilBoom;          // Time since armed until the bomb explodes (seconds)
        int prevButtonState;        // For arming/defusing: keeps track of if "button state" changes
        bool gameOver;              // Becomes true when the bomb is defused
        bool arming;                // True only while arming/defusing the bomb
        bool armed;

        unsigned long timeSinceArmStart;   // Time since we started arming (for arm/defuse countdown)
        unsigned long timeSpentArming;     // Time spent arming the bomb so far (for arm/defuse countdown)
        unsigned long timeArmComplete;     // Time since bomb was armed (for count down)

        // Gameplay Methods
        void updateDisplay(unsigned long globalTime);   // Updates the lcd with important game state stuff
        void updateArmStatus(unsigned long globalTime); // Handles real-time arming/defusing of the bomb
        void countDown(unsigned long globalTime);       // Counts down the bomb if it is armed
        String formatTime();                            // Formats the bomb time into mm:ss string
};

#endif
