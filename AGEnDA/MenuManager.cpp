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
        int encoderDirection = getEncoderScrollDirection();
        if (encoderDirection == 1)
        {
            cursorY++;
            if (cursorY >= capacity) cursorY = 0;
        }
        else if (encoderDirection == -1)
        {
            cursorY--;
            if (cursorY < 0) cursorY = capacity - 1;
        }

        // Button detection
        if (!digitalRead(selectorButton))
        {
            return cursorY;
        }

        if (digitalRead(altMenuButton))
        {
            displayGameMenu(cursorY);
        }

        // Debounce encoder and eliminate screen flicker
        delay(50);
    }
}

void MenuManager::displayGameMenu(int selectedGameID)
{
    const int& backButton     = hw->buttonBLU;      // Goes back to the main menu
    const int& selectorButton = hw->encoderButton;  // Proceeds to gameplay for selected game

    // If the selected game doesn't have any editable game settings, exit this menu
    Game* selectedGame = gameList[selectedGameID];
    int numSettings = selectedGame->getNumSettings();
    if (numSettings == 0) return;

    int cursorY = 0;
    int capacity = min(numSettings, hw->numLCDRows-1);

    GameOption* options = selectedGame->getGameOptions();
    while (true)
    {
        lcd->clear();

        lcd->print("Options for ");
        lcd->print(selectedGame->getShortName());

        // Display as many game settings as can fit on a display at once
        for (int i = 0; i < capacity; i++)
        {
            lcd->setCursor(0, i+1);

            if (i == cursorY) lcd->print("> ");
            else              lcd->print("  ");

            lcd->print(options[i].optionName);

        }

        // Scroll Detection
        int encoderDirection = getEncoderScrollDirection();
        if (encoderDirection == 1)
        {
            cursorY++;
            if (cursorY >= capacity) cursorY = 0;
        }
        else if (encoderDirection == -1)
        {
            cursorY--;
            if (cursorY < 0) cursorY = capacity - 1;
        }

        // Select Button is encoder button and follows inverse logic (HIGH = not pressed)
        if (!digitalRead(selectorButton))
        {
            // TODO enter setting-specific tweak menu
        }

        if (digitalRead(backButton)) return;

        delay(50);
    }
}

// Returns -1, 0, or 1 depending on scroll direction of rotary encoder
int MenuManager::getEncoderScrollDirection()
{
    int pinAState = digitalRead(hw->encoderPinA);

    int dir = 0;

    if (prevEncoderPinAState == HIGH && pinAState != prevEncoderPinAState) // Signal A goes from high to low
    {
        if (digitalRead(hw->encoderPinB))
        {
            // Clockwise
            dir = 1;
        }
        else
        {
            // Counter Clockwise
            dir = -1;
        }
    }

    prevEncoderPinAState = pinAState;
    return dir;
}
