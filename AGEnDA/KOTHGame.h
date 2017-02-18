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
        void doGameLoop(unsigned long globalTime);
        void doEndGame();

    private:
        LiquidCrystal* lcd;               // Points to the lcd stored in HardwareInterface for convenience

        // Game Constants
        const int timeToCap;    // The time necessary to capture the control point (in seconds)
        const int timePerTeam;  // The initial time that each team is given (in minutes)

        // Game state variables
        int redTime, bluTime;
        int prevButtonState;              // For capturing: keeps track of if "button state" changes
        bool gameIsInProgress;            // When false, game ends
        String activeTeam;                // Team whoose timer is currently counting down
        String capturingTeam;             // Team currently capping the point
        unsigned long timeInitCapturing;  // Used in reference to globalTime to properly time captures
        unsigned long capturingTime;      // The time elapsed while capturing (used for progress bar)

        // Gameplay Methods
        void updateDisplay();
        void updateCaptureProgress(unsigned long globalTime);
        String formatTime(int seconds);
        void printCaptureMessage();
};

#endif
