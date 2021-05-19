//
// Created by Lukas Schmidt on 3/24/21.
//

#include "shadow.h"

shadow::shadow() {

}

shadow::~shadow() = default;

void shadow::set_cur_direction(bool pDirection)
{
    /*
     *  left: false, right true
     */
    mCurDirection = pDirection;
}

void shadow::update(SDL_Rect *pPlayerDest)
{
    // Update texture
    if (mCurDirection)
    {
        set_clip(0);
    }
    else
    {
        set_clip(1);
    }

    // Update destination
    mDest.x = pPlayerDest->x;
    mDest.y = pPlayerDest->y + SHADOW_OFFSET;
}