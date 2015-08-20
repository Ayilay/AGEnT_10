#include "Hardware.h"
#include <Arduino.h>

Hardware::Hardware() :
    redLED(8), greenLED(9), speaker(11), actionButton(12), selectorButton(13),
    lcd(2, 3, 4, 5, 6, 7)
{

}

int Hardware::getButtonState(int button)
{

}

void Hardware::setLED(int led, int mode)
{
    digitalWrite(led, mode);
}

void Hardware::setTone(int tone, int duration)
{
    tone(speaker, tone, duration);
}

void Hardware::setMessage(String message)
{

}
