/*
 * Copyright (c) 2017 Georges Troulis
 *
 * HardwareInterface.cpp
 *
 * Has references to all hardware elements (displays etc) such that they can be used
 * by the implementing Game classes.
*/

#include <LiquidCrystal.h>

#include "HardwareInterface.h"

HardwareInterface::HardwareInterface(int _ledRED, int _ledBLU, int _buttonRED, int _buttonBLU, LiquidCrystal* _lcd, int _numLCDRows, int _numLCDCols)
    : ledRED(_ledRED),
      ledBLU(_ledBLU),
      buttonRED(_buttonRED),
      buttonBLU(_buttonBLU),
      lcd(_lcd),
      numLCDRows(_numLCDRows),
      numLCDCols(_numLCDCols)
{
}

LiquidCrystal* HardwareInterface::getLCD()
{
    return lcd;
}
