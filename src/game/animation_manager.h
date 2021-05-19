//
// Created by Lukas Schmidt on 3/11/21.
//

#ifndef EQUILIBRIUM_ANIMATION_MANAGER_H
#define EQUILIBRIUM_ANIMATION_MANAGER_H

#include <iostream>

#include "SDL.h"

#include "game_config.h"
#include "shadow.h"

class animation_manager
{
public:
    animation_manager(SDL_Rect *pPlayerDest);
    ~animation_manager();

    void set_cur_anim(std::string pIndicator);
    void update();

private:
    std::string mCurAnim;
    SDL_Rect *mPlayerDest;
    int mTick;
};


#endif //EQUILIBRIUM_ANIMATION_MANAGER_H
