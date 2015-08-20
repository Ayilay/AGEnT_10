/*
 *  Hardware.h
 *
 *  Defines the electronic components used
 */

#ifndef HARDWARE_H
#define HARDWARE_H

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

        static enum leds {LEDRed, LEDGreen};
        static enum buttons {buttonAction, buttonSelector};

        int getButtonState(int button);
        void setLED(int led, int mode);
        void setTone(int tone, int duration);
        void setMessage(String message);
};

#endif
