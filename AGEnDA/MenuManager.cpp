/*
 * Copyright (c) 2017 Georges Troulis
 *
 * MenuManager.cpp
 *
 * Handles displaying the main game menu and all settings submenus for games
*/

#include <Arduino.h>

#include "HardwareMap.h"
#include "MenuManager.h"
#include "TimeManager.h"

MenuManager::MenuManager(HardwareMap* _hw)
    : hw(_hw), prevEncoderPinAState(LOW)
{
    lcd = hw->getLCD();
}

void MenuManager::initGameList(Game** _gameList)
{
    gameList = _gameList;
}

/*
 * Displays all the games in a scrollable way. Returns the index of the selected game
 * Rotary encoder scrolls clockwise/counterclockwise
 * Encoder button makes game selection and proceeds to gameplay
 * Red button opens settings menu for game mode under cursor
 *
 * TODO: Make this scroll nicely through the options
 * TODO: Support for more game modes
*/
int MenuManager::displayMainMenu()
{
    const int& altMenuButton  = hw->buttonRED;      // Opens menu for specific game
    const int& selectorButton = hw->encoderButton;  // Proceeds to gameplay for selected game

    int cursorY = 0;
    int capacity = min(NUMGAMES, hw->numLCDRows-1); // Scroll until out of rows, or out of games if NUMGAMES < numRows

    while (true)
    {
        // Update the LEDs in a sinusoidal fashion for fanciness
        int brightness = 101 + 100 * sin(TimeManager::getTime() * 2.0 * PI / 2500.0);
        analogWrite(hw->ledRED, brightness);
        analogWrite(hw->ledBLU, brightness);

        // Display everything on the screen
        lcd->clear();
        lcd->print("Select a Game Mode:");
        for (int i = 0; i < capacity; i++)
        {
            lcd->setCursor(0, i+1);

            if (i == cursorY) lcd->print("> ");
            else              lcd->print("  ");

            lcd->print(gameList[i]->getGameName());
        }

        // Scroll Detection
        int pinAState = digitalRead(hw->encoderPinA);
        if (prevEncoderPinAState == HIGH && pinAState != prevEncoderPinAState) // Signal A goes from high to low
        //if (pinAState)
        {
            Serial.println("Encoder moved!");
            // Clockwise
            if (digitalRead(hw->encoderPinB))
            {
                cursorY++;
                if (cursorY >= capacity) cursorY = 0;
            }
            // Counter Clockwise
            else
            {
                cursorY--;
                if (cursorY < 0) cursorY = capacity - 1;
            }
        }
        // Select Button is encoder button and follows inverse logic (HIGH = not pressed)
        if (!digitalRead(selectorButton))
        {
            return cursorY;
        }

        prevEncoderPinAState = pinAState;

        if (digitalRead(altMenuButton))
        {
            displayGameMenu(cursorY);
        }

        // Debounce encoder and eliminate screen flicker
        delay(50);
    }
}

void MenuManager::displayGameMenu(int selectedGame)
{
    const int& backButton     = hw->buttonBLU;      // Goes back to the main menu
    const int& selectorButton = hw->encoderButton;  // Proceeds to gameplay for selected game

    while (true)
    {
        lcd->clear();

        lcd->print("Options for ");
        lcd->print(gameList[selectedGame]->getShortName());

        if (digitalRead(backButton)) return;

        delay(50);
    }
}
