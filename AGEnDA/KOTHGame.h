/*
 * Copyright (c) 2017 Georges Troulis
 *
 * KOTHGame.h
 *
 * Defines behavior for KOTH Game Mode
*/

#ifndef _AGENDA_KOTHGAME_H
#define _AGENDA_KOTHGAME_H

#include "HardwareMap.h"
#include "Game.h"

#define KOTH_NUM_SETTINGS 2

class KOTHGame : public Game
{
    public:
        KOTHGame(HardwareMap* hw, int KOTH_ID);

        // Inherited virtual methods from Game
        void init();
        bool isPlaying();
        void doGameLoop();
        void doEndGame();

        GameOption* getGameOptions();

    private:
        LiquidCrystal* lcd;     // Points to the lcd stored in HardwareMap for convenience

        // Game Options
        GameOption gameSettings[KOTH_NUM_SETTINGS];

        int capTimeOpts[5]  = {2, 3, 5, 10, 0};
        int teamTimeOpts[5] = {120, 180, 300, 600, 0};

        // Game Constants
        const int timeToCap;    // The time necessary to capture the control point (in seconds)
        const int timePerTeam;  // The initial time that each team is given (in minutes)

        // Game State Variables
        int redTime, bluTime;   // Stores the times of the 2 teams
        int prevButtonState;    // For capturing: keeps track of if "button state" changes
        bool gameIsInProgress;  // When false, game ends
        String activeTeam;      // Team whoose timer is currently counting down
        String capturingTeam;   // Team currently capping the point

        unsigned long timeInitCapturing;  // Used in reference to globalTime to properly time captures
        unsigned long capturingTime;      // The time elapsed while capturing (used for progress bar)
        unsigned long timeInitCountDown;  // The time since a new team captured the point (to count down)

        // Gameplay Methods
        void updateDisplay(unsigned long globalTime);
        void updateCaptureProgress(unsigned long globalTime);
        void updateTimers(unsigned long globalTime);
        void printCaptureMessage();
        String formatTime(int seconds);
};

#endif
