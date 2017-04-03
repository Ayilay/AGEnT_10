/*
 * Copyright (c) 2017 Georges Troulis
 *
 * HardwareMap.h
 *
 * Has references to all hardware elements (displays etc) such that they can be used
 * by the implementing Game classes.
*/

#ifndef _AGENDA_HARDWARE_H
#define _AGENDA_HARDWARE_H

#include <LiquidCrystal.h>

class HardwareMap
{
    private:
        LiquidCrystal* lcd;

    public:
        const int ledRED;
        const int ledBLU;
        const int buttonRED;
        const int buttonBLU;
        const int encoderPinA;
        const int encoderPinB;
        const int encoderButton;

        const int numLCDRows;
        const int numLCDCols;

        HardwareMap(int _ledRED, int _ledBLU, int _buttonRED, int _buttonBLU, int _encoderPinA, int _encoderPinB, int _encoderButton, LiquidCrystal* _lcd, int _numLCDRows, int _numLCDCols)
            : ledRED(_ledRED),
              ledBLU(_ledBLU),
              buttonRED(_buttonRED),
              buttonBLU(_buttonBLU),
              encoderPinA(_encoderPinA),
              encoderPinB(_encoderPinB),
              encoderButton(_encoderButton),
              lcd(_lcd),
              numLCDRows(_numLCDRows),
              numLCDCols(_numLCDCols)
        {};

        LiquidCrystal* getLCD()
        {   return lcd;  };
};

#endif
