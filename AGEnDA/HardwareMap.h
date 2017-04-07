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
        HardwareMap(); // Prevent construction as this is a static class
        static LiquidCrystal lcd;

    public:
        static const int buttonRED;
        static const int buttonBLU;
        static const int ledRED;
        static const int ledBLU;
        static const int encoderPinA;
        static const int encoderPinB;
        static const int encoderButton;

        static const int numLCDRows;
        static const int numLCDCols;

        static void init();

        static LiquidCrystal* getLCD();
};

#endif
