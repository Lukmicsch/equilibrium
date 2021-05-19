//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_FPS_MANAGER_H
#define EQUILIBRIUM_FPS_MANAGER_H

#include "game_config.h"
#include "timer.h"

class fps_manager
{
public:
    fps_manager();
    ~fps_manager();

    float calculate_fps();
    void check_and_cap_fps();
    void start_cap_timer();

private:
    int start_fps_timer();

    timer mCapTimer;
    int mCountedFrames;
    timer mFpsTimer;
};


#endif //EQUILIBRIUM_FPS_MANAGER_H
