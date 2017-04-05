/*
 * Copyright (c) 2017 Georges Troulis
 *
 * MenuManager.h
 *
 * Handles displaying the main game menu and all settings submenus for games
 *
*/

#ifndef _AGENDA_MENUMANAGER_H
#define _AGENDA_MENUMANAGER_H

#include <LiquidCrystal.h>

#include "HardwareMap.h"
#include "Game.h"

class MenuManager
{
    private:
        HardwareMap* hw;
        LiquidCrystal* lcd;
        Game** gameList;

        // Rotary Encoder direction handling
        int prevEncoderPinAState;
        int getEncoderScrollDirection();

    public:
        MenuManager(HardwareMap* _hw);

        void initGameList(Game** _gameList);
        int displayMainMenu();
        void displayGameMenu(int selectedGameID);
};

#endif
