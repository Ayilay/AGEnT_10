/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 George Troulis
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * GameInterface.cpp
 * 
 * Defines the game rules and behaviors
 */

#include "GameInterface.h"

// Return the index of the selected game
int GameInterface::showMenu()
{
    int selection = 0;
    String gameList[] = {
        "King of the Hill",
        "Counter Strike: GO"
    };

    hardware.clearDisplay();
    hardware.setMessage("Choose a game mode:");
    while(true)
    {
        // Print the games and a star next to the one that is selected
        for(int i = 0; i < 2; i++)
            hardware.setMessage((selection == i ? "*" : " ") + gameList[i], i + 1);

        // User is changing selected game
        if(hardware.isPressed(buttonSelectorPin))
        {
            while(hardware.isPressed(buttonSelectorPin));
            selection ++;
            selection %= 2;
        }

        // User has made a choice
        if(hardware.isPressed(buttonActionPin))
        {
            while(hardware.isPressed(buttonActionPin));
            return selection;
        }
    }
}

void GameInterface::playGame(int type)
{
    switch(type)
    {
        case KOTH:
            playKOTH();
            break;
        case CSGO:
            playCSGO();
            break;
        default:
            return;
    }
    hardware.setMessage("Done Playing\nPress any key to continue");

}

GameInterface::GameInterface() :
    hardware()
{
}

void GameInterface::playKOTH()
{
    hardware.clearDisplay();
    hardware.setMessage("Playing KOTH ...");
    delay(1000);
    hardware.clearDisplay();
    hardware.setMessage("Done playing KOTH!");
}

void GameInterface::playCSGO()
{
    hardware.clearDisplay();
    hardware.setMessage("Playing CSGO ...");
    delay(1000);
    hardware.clearDisplay();
    hardware.setMessage("Done playing CSGO!");
}
