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
        String gameID;
        HardwareInterface* hardware;

    public:
        Game(HardwareInterface* hw, String gameName)
            : hardware(hw), gameID(gameName) {}

        String getGameName()
        { return gameID; };

        // Abstract methods implemented by specific games
        virtual bool isPlaying()  = 0;
        virtual void doGameLoop() = 0;
        virtual void doEndGame()  = 0;
};

#endif
