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
 */

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
