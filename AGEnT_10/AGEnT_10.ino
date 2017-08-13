/*
 * Copyright (c) 2017 Georges Troulis
 *
 * Arduino
 * Game
 * ENhancement
 * Device for
 * Airsoft
 *
 * An Arduino Device that allows for several video-game style game modes
 * to be played in real life during Airsoft/Paintball/Nerf/etc matches.
 *
 * Current list of gamemodes includes the following:
 *  -> KOTH by Team Fortress 2
 *  -> CSGO Competitive mode (plant the bomb) by Counter Strike Global Offensive
 *
 * Instructions of how to play these game modes is included in the respective .h files
 *
 * This sketch produces a main menu at boot time that allows for selection of a
 * gamemode to play. When a game is selected, the "Menu" button can be clicked to
 * open a "game settings menu" that allows for modification of certain in-game variables.
 * After the user is satisfied with the settings, the game then starts andproceeds 
 * once until completion, and the device must be rebooted to play again.
 *
 * Behaviour of each Game Mode is defined in the respective <GameMode> class.
 * All Game Modes implement the Game interface, defined in Game.h
 *
 * Concept and Software by George Troulis
 * email: georgetroulis@gmail.com
*/

#include <LiquidCrystal.h>

#include "HardwareMap.h"
#include "MenuManager.h"
#include "TimeManager.h"

#include "Game.h"
#include "KOTHGame.h"
#include "CSGOGame.h"

////////////////////////////////////////////////////////////
// GameMode Initializations
////////////////////////////////////////////////////////////

// The individual games that we can play to be stored in gameList later
// Initialized statically for convenience of memory handling
KOTHGame kothGame(0);
CSGOGame csgoGame(1);

// Stores all Games in an array for convenience of iteration
Game* gameList[NUMGAMES];

// The game that's currently selected to play
Game* gameSelected;

////////////////////////////////////////////////////////////
// Main Gameplay Methods
////////////////////////////////////////////////////////////

void setup()
{
    // Initialize all the I/O and the LCD
    HardwareMap::init();

    if (HardwareMap::numLCDCols < 20 || HardwareMap::numLCDRows < 4)
    {
        Serial.begin(9600);
        Serial.println("Device only supports LCD screens of 20x4 or larger");

        HardwareMap::getLCD()->clear();
        HardwareMap::getLCD()->print("Unsupported");
        HardwareMap::getLCD()->setCursor(0, 1);
        HardwareMap::getLCD()->print("LCD Dimensions");

        exit(0);
    }

    // Manually add all games in array (gameList better be initialized correctly)
    gameList[kothGame.getID()] = &kothGame;
    gameList[csgoGame.getID()] = &csgoGame;

    // Displays main menu and game settings menu for each game
    MenuManager menuManager;
    menuManager.initGameList(gameList);

    // Display the menu, and grab the selected game
    gameSelected = gameList[menuManager.displayMainMenu()];
    gameSelected->init();

    digitalWrite(HardwareMap::ledRED, LOW);
    digitalWrite(HardwareMap::ledBLU, LOW);
    HardwareMap::getLCD()->clear();
    HardwareMap::getLCD()->print("Game Selected:");
    HardwareMap::getLCD()->setCursor(0, 1);
    HardwareMap::getLCD()->print(gameSelected->getGameName());
    delay(1000);
}

void loop()
{
    while(gameSelected->isPlaying())
    {
        gameSelected->doGameLoop();
        delay(10);
    }

    gameSelected->doEndGame();
    delay(10);
}
