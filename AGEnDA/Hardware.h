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
 * Hardware.cpp
 *
 * Defines the electronic components used
 *
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#define LEDRedPin 8
#define LEDGreenPin 9
#define speakerPin 11
#define buttonActionPin 12
#define buttonSelectorPin 13

#include <Arduino.h>
#include <LiquidCrystal.h>

class Hardware
{
    private:
        const int redLED;
        const int greenLED;
        const int speaker;
        const int actionButton;
        const int selectorButton;
        LiquidCrystal lcd;

    public:
        Hardware();

        bool isPressed(int button);
        void setLED(int led, int mode);
        void setTone(int tone, int duration);
        void clearDisplay();
        void setMessage(String message);
        void setMessage(String message, int row);
};

#endif
