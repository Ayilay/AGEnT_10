/*
 * Copyright (c) 2017 Georges Troulis
 *
 * CSGOGame.cpp
 *
 * Defines behavior for CSGO Game Mode
 *
 * TODO: Add instructions
*/

#include <Arduino.h>

#include "CSGOGame.h"
#include "Game.h"
#include "HardwareMap.h"

CSGOGame::CSGOGame(HardwareMap* hw)
    : Game(hw, "CS:GO Competitive"),
      armTime(5),
      defuseTime(7),
      password("7355608"),
      timeUntilBoom(120),
      prevButtonState(0),
      gameOver(false),
      arming(false),
      armed(false),
      timeSinceArmStart(0L),
      timeSpentArming(0L),
      timeArmComplete(0L)
{
    lcd = hardware->getLCD();
}

////////////////////////////////////////////////////////////
// Public interface methods
////////////////////////////////////////////////////////////

bool CSGOGame::isPlaying()
{
    return !gameOver;
}

void CSGOGame::doGameLoop(unsigned long globalTime)
{
    updateDisplay();
    updateArmStatus(globalTime);
    countDown(globalTime);
}

void CSGOGame::doEndGame()
{
    lcd->clear();

    // Bomb was defused
    if (!armed)
    {
        lcd->print("Bomb Defused");
        lcd->setCursor(0, 1);
        lcd->print("Counter Terrorists");
        lcd->setCursor(0, 2);
        lcd->print("win");
    }
    else
    {
        lcd->print("Bomb Blew Up");
        lcd->setCursor(0, 1);
        lcd->print("Terrorists win");
    }
}

////////////////////////////////////////////////////////////
// Private Gameplay methods
////////////////////////////////////////////////////////////

void CSGOGame::updateDisplay()
{
    lcd->clear();

    // Phase 1: Waiting for bomb to become armed
    if (!arming)
    {
        lcd->setCursor(7, 1);
        lcd->print(formatTime());
    }
    else if (arming)
    {
        // Displays the status of arming/disarming
        int armProgress = 0;

        // Display status message
        if (!armed)
        {
            lcd->setCursor(5, 1);
            lcd->print("Arming...");

            armProgress = ((password.length())/((double) armTime * 1000)) * timeSpentArming + 1;
            lcd->setCursor(5, 2);
            lcd->print("|");
            for(int i = 0; i < armProgress; i++)
                lcd->print(password[i]);
            for(int i = 0; i < 7 - armProgress; i++)
                lcd->print("*");
            lcd->print("|");

        }
        else
        {
            lcd->setCursor(4, 0);
            lcd->print("Defusing...");

            lcd->setCursor(7, 1);
            lcd->print(formatTime());

            armProgress = ((password.length())/((double) defuseTime * 1000)) * timeSpentArming;
            lcd->setCursor(5, 2);
            lcd->print("|");
            for(int i = 0; i < armProgress; i++)
                lcd->print("#");
            for(int i = 0; i < 7 - armProgress; i++)
                lcd->print("*");
            lcd->print("|");
        }
    }
}

void CSGOGame::updateArmStatus(unsigned long globalTime)
{
    int currentButtonState = digitalRead(hardware->buttonRED) & digitalRead(hardware->buttonBLU);

    // Commence the arming/defusing process if it's the first time pushing the button OR if we've already started
    if (currentButtonState == HIGH && (arming || prevButtonState == LOW))
    {
        arming = true;

        // Update the timeSinceArmStart only in the beginning
        if (prevButtonState == LOW && currentButtonState == HIGH)
            timeSinceArmStart = globalTime;

        timeSpentArming = globalTime - timeSinceArmStart;

        if (!armed && (timeSpentArming > armTime * 1000))
        {
            armed  = true;
            arming = false;

            timeSpentArming      = 0;
            timeArmComplete = globalTime;
        }
        else if (armed && (timeSpentArming > defuseTime * 1000))
        {
            arming = false;
            armed  = false;
            gameOver = true;
        }
    }
    else
    {
        arming = false;
    }

    prevButtonState = currentButtonState;
}

void CSGOGame::countDown(unsigned long globalTime)
{
    if (!armed) return;
    if (timeUntilBoom <= 0) gameOver = true;

    unsigned long timeSinceArmComplete = globalTime - timeArmComplete;
    if (timeSinceArmComplete > 1000)
    {
        timeArmComplete += 1000;
        timeUntilBoom --;
    }

}

// Returns the bomb time formatted as a mm:ss string
String CSGOGame::formatTime()
{
    String result = "";
    int min = timeUntilBoom / 60;
    int sec = timeUntilBoom % 60;

    // add the minutes, and a leading 0 if necessary
    if(min < 10)
        result += '0';
    result += min;

    result += ':';

    // add the timeUntilBoom, and a leading 0 if necessary
    if(sec < 10)
        result += '0';
    result += sec;

    return result;
}
