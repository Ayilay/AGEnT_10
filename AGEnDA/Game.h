/*
 * Copyright (c) 2017 Georges Troulis
 *
 * Game.h
 *
 * Defines an Abstract Class interface for all playable games on the device
 *
 * Current list of implementing classes includes the following:
 *  -> KOTHGame
 *  -> CSGOGame
*/

#ifndef _AGENDA_GAME_H
#define _AGENDA_GAME_H

#define NUMGAMES 2

typedef struct
{
    String optionName;          // Display name of option
    int* optionPossibilities;   // Array of possible options (time values in seconds)
    int* optionVar;             // Pointer to variable that stores this option for modification purposes
} GameOption;

class Game
{
    protected:
        const int gameID;       // Unique numeric index for storing games in array
        const int numSettings;  // Number of settings for the game settings menu
        const String gameName;  // String that belongs to game for display purposes
        const String shortName; // A shorter version of gameName that's displayed for the settings menu

        HardwareMap* hardware;

    public:
        Game(HardwareMap* hw, String _gameName, String _shortName, int _gameID, int _numSettings)
            : hardware(hw), gameName(_gameName), shortName(_shortName), gameID(_gameID), numSettings(_numSettings) {}

        String getGameName()
        { return gameName; };

        String getShortName()
        { return shortName; };

        int getNumSettings()
        { return numSettings; };

        int getID()
        { return gameID; };

        // Abstract methods implemented by specific games
        virtual void init()       = 0;
        virtual bool isPlaying()  = 0;
        virtual void doGameLoop() = 0;
        virtual void doEndGame()  = 0;

        // Return the options of a specific game for display/modification purposes
        virtual GameOption* getGameOptions() = 0;
};

#endif
