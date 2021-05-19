//
// Created by Lukas Schmidt on 3/1/21.
//

#ifndef EQUILIBRIUM_TIMER_H
#define EQUILIBRIUM_TIMER_H

#include "SDL.h"

class timer
{
public:
    timer();
    ~timer();

    int get_seconds();
    int get_ticks();
    bool is_started();
    bool is_stopped();
    void start();
    void stop();

private:
    bool mStarted;
    int mStartTicks;
    int mStoppedTicks;
    bool mStopped;
};


#endif //EQUILIBRIUM_TIMER_H
