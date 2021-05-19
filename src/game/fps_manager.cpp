//
// Created by Lukas Schmidt on 3/2/21.
//

#include "fps_manager.h"

fps_manager::fps_manager()
{
    mCountedFrames = 0;
    mFpsTimer.start();
}

fps_manager::~fps_manager() = default;

float fps_manager::calculate_fps()
{
    float avgFPS = mCountedFrames / ( mFpsTimer.get_ticks() / 1000.f );
    if (avgFPS > 2000000) avgFPS = 0;

    return avgFPS;
}

void fps_manager::check_and_cap_fps()
{
    // Check if frame finished early
    int frameTicks = mCapTimer.get_ticks();
    if( frameTicks < SCREEN_TICKS_PER_FRAME)
    {
        //Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    }

    mCountedFrames++;
}

void fps_manager::start_cap_timer() {
    mCapTimer.start();
}