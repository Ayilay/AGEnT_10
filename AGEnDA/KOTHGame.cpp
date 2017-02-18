/*
 * Copyright (c) 2017 Georges Troulis
 *
 * KOTHGame.cpp
 *
 * Defines behavior for KOTH Game Mode
 *
 * TODO: Add instructions
*/

#include "KOTHGame.h"
#include "Game.h"
#include "HardwareInterface.h"

KOTHGame::KOTHGame(HardwareInterface* hw)
    : Game(hw, "King of the Hill")
{
    lcd = hardware->getLCD();
}

bool KOTHGame::isPlaying()
{
    // TODO
    return true;
}

void KOTHGame::doGameLoop()
{
    lcd->clear();
    lcd->print("Playing KOTH");
    lcd->setCursor(0, 1);
    lcd->print("(not really)");
}

void KOTHGame::doEndGame()
{
    lcd->print("KOTH Over :D");
}
