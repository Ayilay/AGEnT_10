/*
 * Copyright (c) 2017 Georges Troulis
 *
 * KOTHGame.cpp
 *
 * Defines behavior for KOTH Game Mode
 *
 * Instructions for gameplay:
 * Two teams, RED and BLU, fight for the "Control Point" (this device), placed in the center of the map. Each team
 * is given a timer of some time, and the objective of each team is to make their timer count down to 0.
 * For a team to make their timer count down, a team must approach the control point and hold down the button
 * of their color for a pre-determined capture time. The control point then switches possession and counts down
 * until it is captured by the opposing team or until time runs out.
 *
 * Tweakable Game Settings:
 *  -> Cap Time: The amount of time it takes each team to capture the control point
 *  -> Team Time: The starting amount of time that each team is given. When it reaches zero for a team, that team wins
*/

#include <Arduino.h>

#include "KOTHGame.h"
#include "Game.h"
#include "HardwareMap.h"
#include "TimeManager.h"

KOTHGame::KOTHGame(int kothID)
    : Game("King of the Hill", "KOTH", kothID, KOTH_NUM_SETTINGS),
      timeToCap(5),
      timePerTeam(600),
      activeTeam("none"),
      capturingTeam("none"),
      gameIsInProgress(true),
      timeInitCapturing(0L),
      capturingTime(0L),
      timeInitCountDown(0L),
      prevButtonState(0)
{
    // Initialize Tweakable Game Settings
    GameOption capTimeOpt  = {"Cap Time",   &capTimeOpts[0],    &timeToCap};
    GameOption teamTimeOpt = {"Team Time",  &teamTimeOpts[0],   &timePerTeam};

    gameSettings[0] = capTimeOpt;
    gameSettings[1] = teamTimeOpt;
}

////////////////////////////////////////////////////////////
// Public interface methods
////////////////////////////////////////////////////////////

void KOTHGame::init()
{
    lcd = HardwareMap::getLCD();

    // timePerTeam was set during the gameSettings menu, still need to update the team times
    bluTime = redTime = timePerTeam;
}

bool KOTHGame::isPlaying()
{
    return gameIsInProgress;
}

void KOTHGame::doGameLoop()
{
    unsigned long globalTime = TimeManager::getTime();
    updateDisplay(globalTime);
    updateCaptureProgress(globalTime);
    updateTimers(globalTime);
}

void KOTHGame::doEndGame()
{
    digitalWrite(HardwareMap::ledRED, HIGH);
    digitalWrite(HardwareMap::ledBLU, HIGH);

    String message = activeTeam + " won!";
    lcd->clear();
    lcd->setCursor((HardwareMap::numLCDCols - message.length()) / 2, 1);
    lcd->print(message);
}

GameOption* KOTHGame::getGameOptions()
{
    return gameSettings;
}

////////////////////////////////////////////////////////////
// Private Gameplay methods
////////////////////////////////////////////////////////////

void KOTHGame::updateDisplay(unsigned long globalTime)
{
    lcd->clear();

    lcd->setCursor(0, 2);
    lcd->print("BLU Time   RED Time");

    // Print the capture progress if we are capturing
    if (capturingTime > 0)
    {
        int captureProgress = ((HardwareMap::numLCDCols-2)/((double) timeToCap * 1000)) * capturingTime;

        // Display who is capturing
        lcd->setCursor(0, 0);
        lcd->print(capturingTeam);
        lcd->print(" Capturing...");

        // Progress Bar
        lcd->setCursor(0, 1);
        lcd->print("|");

        // Blink the RED or BLU LEDs based on who's capturing
        int brightness = 1 + sin(capturingTime * 2.0 * PI / 500);

        if (capturingTeam == "BLU")
        {
            // For BLU team, display capture progress from left to right
            for(int i = 0; i < captureProgress; i++)
                lcd->print('-');

            digitalWrite(HardwareMap::ledBLU, brightness);
        }
        else
        {
            // For RED team, display capture progress from right to left
            lcd->setCursor(HardwareMap::numLCDCols - 1 - captureProgress, 1);
            for(int i = 0; i < captureProgress; i++)
                lcd->print('-');

            digitalWrite(HardwareMap::ledRED, brightness);
        }


        lcd->setCursor(HardwareMap::numLCDCols - 1, 1);
        lcd->print("|");
    }
    else
    {
        lcd->setCursor(0, 0);
        if (activeTeam != "none")
        {
            lcd->print("Owned by ");
            lcd->print(activeTeam);
        }
        else
        {
            lcd->print("Capture the Point!");
        }
    }

    // Times of the teams
    lcd->setCursor(2, 3);
    lcd->print(formatTime(bluTime));

    lcd->setCursor(13, 3);
    lcd->print(formatTime(redTime));
}

// Detects buttons being pushed down and reacts accordingly
void KOTHGame::updateCaptureProgress(unsigned long globalTime)
{
    int currentButtonState = digitalRead(HardwareMap::buttonRED) ^ digitalRead(HardwareMap::buttonBLU);
    if (currentButtonState == HIGH)
    {
        capturingTeam = digitalRead(HardwareMap::buttonRED) ? "RED" : "BLU";

        if (capturingTeam != activeTeam)
        {
            // Update the timeInitCaputing only the first time the capture button is being pressed
            if (currentButtonState != prevButtonState) timeInitCapturing = globalTime;

            capturingTime = globalTime - timeInitCapturing;

            // Time is over, done capturing
            if (capturingTime > timeToCap * 1000)
            {
                activeTeam = capturingTeam;
                capturingTime = 0;

                timeInitCountDown = globalTime;

                if (activeTeam == "RED")
                {
                    digitalWrite(HardwareMap::ledRED, HIGH);
                    digitalWrite(HardwareMap::ledBLU, LOW);
                }
                else if (activeTeam == "BLU")
                {
                    digitalWrite(HardwareMap::ledBLU, HIGH);
                    digitalWrite(HardwareMap::ledRED, LOW);
                }
                else
                {
                    digitalWrite(HardwareMap::ledRED, LOW);
                    digitalWrite(HardwareMap::ledBLU, LOW);
                }
            }
        }
    }
    else
    {
        capturingTime = 0;
    }

    prevButtonState = currentButtonState;
}

void KOTHGame::updateTimers(unsigned long globalTime)
{
    if (activeTeam == "none") return;

    // Helps with avoiding redundant code
    int& activeTime = activeTeam == "RED" ? redTime : bluTime;
    if (activeTime <= 0)
    {
        gameIsInProgress = false;
        return;
    }

    unsigned long timeOwnedElapsed = globalTime - timeInitCountDown;

    if (timeOwnedElapsed > 1000)
    {
        timeInitCountDown += 1000;
        activeTime--;
    }
}

// Convert time from 'int seconds' to 'mm:ss string'
String KOTHGame::formatTime(int seconds)
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

// Clear the screen and display a friendly capture message
void KOTHGame::printCaptureMessage()
{
    lcd->clear();
    lcd->setCursor(3, 1);
    // BLU Captured!
    lcd->print(activeTeam);
    lcd->print(" captured");

    lcd->setCursor(1, 2);
    lcd->print("the control point!");
    delay(1500);

    // TODO: add sounds too
}
