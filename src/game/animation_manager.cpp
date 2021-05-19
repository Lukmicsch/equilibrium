//
// Created by Lukas Schmidt on 3/11/21.
//

#include "animation_manager.h"

animation_manager::animation_manager(SDL_Rect *pPlayerDest)
{
    mPlayerDest = pPlayerDest;
    mTick = 0;
}

animation_manager::~animation_manager() = default;

void animation_manager::set_cur_anim(std::string pIndicator)
{
    mCurAnim = pIndicator;
}

void animation_manager::update()
{
    int curY = mPlayerDest->y;

    if (mCurAnim == "idol")
    {
        if (mTick < IDOL_AMPLITUDE/2)
        {
            mPlayerDest->y = curY + IDOL_SPEED;
            mTick++;
        }
        else if (mTick < IDOL_AMPLITUDE)
        {
            mPlayerDest->y = curY - IDOL_SPEED;
            mTick++;
        }
        else if (mTick == IDOL_AMPLITUDE) mTick = 0;
    }
};