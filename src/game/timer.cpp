//
// Created by Lukas Schmidt on 3/1/21.
//

#include "timer.h"
timer::timer()
{
    mStartTicks = 0;
    mStoppedTicks = 0;
    mStarted = false;
    mStopped = false;
}

timer::~timer() = default;

int timer::get_seconds()
{
    int time = get_ticks();
    int seconds = time / 1000;

    return seconds;
}

int timer::get_ticks()
{
    //The actual timer time
    int time = 0;

    if (mStarted) time = SDL_GetTicks() - mStartTicks;
    if (mStopped) time = mStoppedTicks;

    return time;
}

bool timer::is_started()
{
    return mStarted;
}

bool timer::is_stopped()
{
    return mStopped;
}

void timer::start()
{
    mStarted = true;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
}

void timer::stop()
{
    mStarted = false;
    mStopped = true;

    mStoppedTicks = SDL_GetTicks() - mStartTicks;
    mStartTicks = 0;
}