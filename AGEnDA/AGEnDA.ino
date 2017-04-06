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
// Constants, IO pins, and other initializations
////////////////////////////////////////////////////////////

const int LCDNUMROWS =  4;
const int LCDNUMCOLS = 20;

const int buttonRED     =  8;
const int buttonBLU     =  9;
const int ledRED        = 10;
const int ledBLU        = 11;
const int encoderPinA   = 12;
const int encoderPinB   = 13;
const int encoderButton = A0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// For sharing all hardware pins across entire software
HardwareMap hardwareMap(ledRED, ledBLU, buttonRED, buttonBLU, encoderPinA, encoderPinB, encoderButton,  &lcd, LCDNUMROWS, LCDNUMCOLS);

// The individual games that we can play to be stored in gameList later
KOTHGame kothGame(&hardwareMap, 0);
CSGOGame csgoGame(&hardwareMap, 1);

// Stores all Games in an array for convenience of iteration
Game* gameList[NUMGAMES];

// The game that's currently selected to play
Game* gameSelected;

// Displays main menu and game settings menu for each game
MenuManager menuManager(&hardwareMap);

////////////////////////////////////////////////////////////
// Main Gameplay Methods
////////////////////////////////////////////////////////////

void setup()
{
    pinMode(ledRED,    OUTPUT);
    pinMode(ledBLU,    OUTPUT);
    pinMode(buttonRED,  INPUT);
    pinMode(buttonBLU,  INPUT);

    pinMode(encoderPinA,   INPUT);
    pinMode(encoderPinB,   INPUT);
    pinMode(encoderButton, INPUT);

    if (LCDNUMCOLS < 20 || LCDNUMROWS < 4)
    {
        Serial.begin(9600);
        Serial.println("Device only supports LCD screens of 20x4 or larger");

        // hopefully there is an at least 16x2 LCD
        lcd.begin(16, 2);
        lcd.clear();
        lcd.print("Unsupported");
        lcd.setCursor(0, 1);
        lcd.print("LCD Dimensions");

        exit(0);
    }

    lcd.begin(LCDNUMCOLS, LCDNUMROWS);

    // Manually add all games in array (gameList better be initialized correctly)
    gameList[kothGame.getID()] = &kothGame;
    gameList[csgoGame.getID()] = &csgoGame;

    menuManager.initGameList(gameList);

    // Display the menu, and grab the selected game
    gameSelected = gameList[menuManager.displayMainMenu()];
    gameSelected->init();

    digitalWrite(ledRED, LOW);
    digitalWrite(ledBLU, LOW);
    lcd.clear();
    lcd.print("Game Selected:");
    lcd.setCursor(0, 1);
    lcd.print(gameSelected->getGameName());
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
