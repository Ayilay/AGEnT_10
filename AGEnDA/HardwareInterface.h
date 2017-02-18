/*
 * Copyright (c) 2017 Georges Troulis
 *
 * HardwareInterface.h
 *
 * Has references to all hardware elements (displays etc) such that they can be used
 * by the implementing Game classes.
*/

#ifndef _AGENDA_HARDWARE_H
#define _AGENDA_HARDWARE_H

#include <LiquidCrystal.h>

class HardwareInterface
{
    private:
        LiquidCrystal* lcd;

    public:
        const int ledRED;
        const int ledBLU;
        const int buttonRED;
        const int buttonBLU;

        const int numLCDRows;
        const int numLCDCols;

        HardwareInterface(int _ledRED, int _ledBLU, int _buttonRED, int _buttonBLU, LiquidCrystal* _lcd, int _numLCDRows, int _numLCDCols);

        LiquidCrystal* getLCD();
};

#endif
