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

const int ledRED    = 10;
const int ledBLU    = 11;
const int buttonRED = 12;
const int buttonBLU = 13;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

HardwareInterface hardwareInterface(ledRED, ledBLU, buttonRED, buttonBLU, &lcd);

KOTHGame kothGame(&hardwareInterface);
CSGOGame csgoGame(&hardwareInterface);

void setup()
{
    pinMode(ledRED,    OUTPUT);
    pinMode(ledBLU,    OUTPUT);
    pinMode(buttonRED,  INPUT);
    pinMode(buttonBLU,  INPUT);

    Game* gameList[2];


    gameList[0] = &kothGame;
    gameList[1] = &csgoGame;
}

void loop()
{
    // TODO List:
    // Display main menu (game selector)
    // Display game options (once game is selected)
    // Play game until completion
}
