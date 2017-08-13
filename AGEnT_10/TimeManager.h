/*
 * Copyright (c) 2017 Georges Troulis
 *
 * TimeManager.h
 *
 * Helps all classes keep track of the global time
 *
*/

#ifndef _AGENDA_TIME_MANAGER_H
#define _AGENDA_TIME_MANAGER_H

#include <Arduino.h>

class TimeManager
{
    private:
        TimeManager(); // Prevent initialization since this is a static class

    public:
        // Return global time rounded to 50 ms intervals
        static unsigned long getTime()
        { return (millis() / 50) * 50; }
};

#endif
