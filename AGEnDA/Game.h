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

class Game
{
    protected:
        int gameID;       // Unique numeric index for storing games in array
        String gameName;  // String that belongs to game for display purposes
        HardwareMap* hardware;

    public:
        Game(HardwareMap* hw, String _gameName, int _gameID)
            : hardware(hw), gameName(_gameName), gameID(_gameID) {}

        String getGameName()
        { return gameName; };

        int getID()
        { return gameID; };

        // Abstract methods implemented by specific games
        virtual bool isPlaying()  = 0;
        virtual void doGameLoop() = 0;
        virtual void doEndGame()  = 0;
};

#endif
