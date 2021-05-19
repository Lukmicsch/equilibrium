//
// Created by Lukas Schmidt on 3/2/21.
//

#include "bullet.h"

bullet::bullet()
{

}

bullet::~bullet() = default;

bool bullet::get_cur_direction()
{
    return mCurDirection;
}

bool bullet::get_is_active()
{
    return mIsActive;
}

void bullet::resolve_border_collision(int pBorderIndicator)
{
    /*
     *  0 - none, 1 - left, 2 - upper, 3 - right, 4 - lower
     */
    if (pBorderIndicator != 0) set_is_active(false);
}

void bullet::set_cur_direction(bool pDirection)
{
    mCurDirection = pDirection;
}

void bullet::set_is_active(bool pIsActive)
{
    mIsActive = pIsActive;
}

void bullet::update()
{
    if (mIsActive)
    {
        if (mCurDirection)
        {
            set_dest(mDest.x + BULLET_SPEED, mDest.y);
        }
        else
        {
            set_dest(mDest.x - BULLET_SPEED, mDest.y);
        }
    }
}