/*
 * Copyright (c) 2017 Georges Troulis
 *
 * TimeManager.h
 *
 * Helps all classes keep track of the global time
 *
*/

#include <Arduino.h>

class TimeManager
{
    public:
        // Return global time rounded to 50 ms intervals
        static unsigned long getTime()
        { return (millis() / 50) * 50; }
};
