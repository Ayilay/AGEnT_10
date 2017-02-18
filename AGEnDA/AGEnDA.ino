/*
 * Copyright (c) 2016 Georges Troulis
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
 * gamemode to play. A "Game Mode Menu" shows up that allows for configuration of
 * certain game-state variables. The game then proceeds once until completion,
 * and the device must be rebooted to play again.
 *
 * Behaviour of each Game Mode is included in the respective <GameMode> class.
 * All Game Modes implement the Game interface, defined in Game.h
 *
 * Concept and Software by George Troulis
 * email: georgetroulis@gmail.com
*/

#include <LiquidCrystal.h>

#include "HardwareInterface.h"
#include "Game.h"
#include "KOTHGame.h"
#include "CSGOGame.h"

const int LCDNUMROWS =  4;
const int LCDNUMCOLS = 20;

const int ledRED     = 10;
const int ledBLU     = 11;
const int buttonRED  = 12;
const int buttonBLU  = 13;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

HardwareInterface hardwareInterface(ledRED, ledBLU, buttonRED, buttonBLU, &lcd, LCDNUMROWS, LCDNUMCOLS);

KOTHGame kothGame(&hardwareInterface);
CSGOGame csgoGame(&hardwareInterface);

// Stores all Games in an array for convenience of iteration
const int numGames = 2;
Game* gameList[numGames];

// The game that's currently selected to play
Game* gameSelected;

void setup()
{
    pinMode(ledRED,    OUTPUT);
    pinMode(ledBLU,    OUTPUT);
    pinMode(buttonRED,  INPUT);
    pinMode(buttonBLU,  INPUT);

    if (LCDNUMCOLS < 20 || LCDNUMROWS < 4)
    {
        Serial.begin(9600);
        Serial.println("Device only supports LCD screens of 20x4 or larger");
        return;
    }

    lcd.begin(LCDNUMCOLS, LCDNUMROWS);

    // Manually add all games in array (numGames better be initialized correctly)
    gameList[0] = &kothGame;
    gameList[1] = &csgoGame;

    // Display the menu, and grab the selected game
    gameSelected = gameList[displayMainMenu()];

    lcd.clear();
    lcd.print("Game Selected:");
    lcd.setCursor(0, 1);
    lcd.print(gameSelected->getGameName());
    delay(2000);

    // TODO List:
    // Display game options (once game is selected)
}

void loop()
{
    while(gameSelected->isPlaying())
    {
        gameSelected->doGameLoop();
        delay(10);
    }

    gameSelected->doEndGame();
}

////////////////////////////////////////////////////////////
// Menu Selection and Helper methods
////////////////////////////////////////////////////////////

/*
 * Displays all the games in a scrollable way. Returns the index of the selected game
 * Blue Button Scrolls clockwise
 * Red Button makes selection
 *
 * TODO: Make this scroll nicely through the options
*/
int displayMainMenu()
{
    int cursorY = 0;
    int capacity = min(numGames, LCDNUMROWS); // Scroll until out of rows, or out of games if numGames < numRows

    const int& buttonSelect = buttonRED;
    const int& buttonScroll = buttonBLU;

    while (true)
    {
        // Display everything on the screen
        lcd.clear();
        for (int i = 0; i < capacity; i++)
        {
            lcd.setCursor(0, i);

            if (i == cursorY) lcd.print("> ");
            else              lcd.print("  ");
            lcd.print(gameList[i]->getGameName());
        }

        // Check for button press
        if (digitalRead(buttonScroll))
        {
            while (digitalRead(buttonScroll)) delay(1);

            cursorY++;
            if (cursorY >= capacity) cursorY = 0;
        }

        if (digitalRead(buttonSelect))
        {
            while (digitalRead(buttonSelect)) delay(1);

            // TODO this will later have to be replaced with something that's not cursorY
            return cursorY;
        }

        delay(20);
    }
}
