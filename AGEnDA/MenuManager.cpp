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
            while(digitalRead(altMenuButton));
            displayGameMenu(cursorY);
        }

        // Debounce encoder and eliminate screen flicker
        delay(50);
    }
}

void MenuManager::displayGameMenu(int selectedGameID)
{
    const int& backButton     = hw->buttonBLU;      // Goes back to the main menu
    const int& selectorButton = hw->encoderButton;  // Proceeds to modify selected game option

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
            while(!digitalRead(selectorButton));
            displaySettingTweakMenu(selectedGameID, cursorY);
        }

        // Return to the Main Menu
        if (digitalRead(backButton))
        {
            while (digitalRead(backButton));
            return;
        }

        delay(50);
    }
}

void MenuManager::displaySettingTweakMenu(int gameID, int settingID)
{
    const int& backButton     = hw->buttonBLU;      // Goes back to the game settings menu
    const int& selectorButton = hw->encoderButton;  // Goes back to the game settings menu

    Game* selectedGame = gameList[gameID];
    GameOption option = (selectedGame->getGameOptions())[settingID];

    // Count the number of possibilities for each option (last optionPossibility should be a 0)
    int* optionPossibilities = option.optionPossibilities;
    int numPossibleOptions = 0;
    for (; numPossibleOptions < 10; numPossibleOptions++)
    {
        if (optionPossibilities[numPossibleOptions] == 0) break;
    }

    // Determine which option is currently selected and display it first
    int optionIndex = 0;
    for (; optionPossibilities[optionIndex] != *option.optionVar; optionIndex++);

    // Display the options and scroll through them using the encoder
    while (true)
    {
        lcd->clear();
        lcd->setCursor((hw->numLCDCols - option.optionName.length()) / 2, 0);
        lcd->print(option.optionName);

        String option_str = formatSecondsToMMSS(optionPossibilities[optionIndex]);
        lcd->setCursor((hw->numLCDCols - option_str.length()) / 2, 1);
        lcd->print(option_str);

        // Scroll Detection
        int encoderDirection = getEncoderScrollDirection();
        if (encoderDirection == 1)
        {
            optionIndex++;
            if (optionIndex >= numPossibleOptions) optionIndex = 0;
        }
        else if (encoderDirection == -1)
        {
            optionIndex--;
            if (optionIndex < 0) optionIndex = numPossibleOptions - 1;
        }

        // Update option variable and return to settings menu
        if (!digitalRead(selectorButton))
        {
            while (!digitalRead(selectorButton));

            *option.optionVar = optionPossibilities[optionIndex];
            return;
        }

        // Return to the Main Menu (hopefully it will be held down long enough)
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

String MenuManager::formatSecondsToMMSS(int seconds)
{
    String result = "";
    int min = seconds / 60;
    int sec = seconds % 60;

    // add the minutes, and a leading 0 if necessary
    if(min < 10)
        result += '0';
    result += min;

    result += ':';

    // add the seconds, and a leading 0 if necessary
    if(sec < 10)
        result += '0';
    result += sec;

    return result;
}
