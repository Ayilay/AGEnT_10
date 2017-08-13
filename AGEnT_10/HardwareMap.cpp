/*
 * Copyright (c) 2017 Georges Troulis
 *
 * HardwareMap.h
 *
 * Has references to all hardware elements (displays etc) such that they can be used
 * by the implementing Game classes.
*/

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "HardwareMap.h"

const int HardwareMap::buttonRED     =  8;
const int HardwareMap::buttonBLU     =  9;
const int HardwareMap::ledRED        = 10;
const int HardwareMap::ledBLU        = 11;
const int HardwareMap::encoderPinA   = 12;
const int HardwareMap::encoderPinB   = 13;
const int HardwareMap::encoderButton = A0;

const int HardwareMap::numLCDRows =  4;
const int HardwareMap::numLCDCols = 20;

LiquidCrystal HardwareMap::lcd(2, 3, 4, 5, 6, 7);

void HardwareMap::init()
{
    pinMode(ledRED,    OUTPUT);
    pinMode(ledBLU,    OUTPUT);
    pinMode(buttonRED,  INPUT);
    pinMode(buttonBLU,  INPUT);

    pinMode(encoderPinA,   INPUT);
    pinMode(encoderPinB,   INPUT);
    pinMode(encoderButton, INPUT);

    lcd.begin(numLCDCols, numLCDRows);
}


LiquidCrystal* HardwareMap::getLCD()
{
    return &lcd;
}
