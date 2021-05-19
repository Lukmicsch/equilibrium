//
// Created by Lukas Schmidt on 3/2/21.
//

#include "player.h"

player::player() : mAnimManager(&mDest)
{

}

player::~player() = default;

bullet * player::get_bullet()
{
    return &mBullet;
}

bool player::get_cur_direction()
{
    return mCurDirection;
}

int player::get_health()
{
    return mHealth;
}

int player::get_last_action()
{
    /*
     *  0 - left
     *  1 - right
     *  2 - up
     *  3 - down
     *  4 - shoot
     */
    return mLastAction;
}

int player::get_max_health()
{
    return mMaxHealth;
}

int player::get_player_indicator()
{
    return mPlayerIndicator;
}

shadow *player::get_shadow()
{
    return &mShadow;
}

void player::init_objects(resource_manager *pResourceManager)
{
    mBullet.init(pResourceManager, "bullet", 1, BULLET_WIDTH, BULLET_HEIGHT, 0, 0, 0);
    mBullet.set_is_active(false);

    mShadow.init(pResourceManager, "shadow", 2, PLANE_WIDTH, PLANE_HEIGHT, !mCurDirection, get_dx(), get_dy() + SHADOW_OFFSET);
}

void player::init_self(resource_manager *pResourceManager, bool pDirection, int pHealth, int pMaxHealth, int pPlayerIndicator)
{
    mMaxHealth = pMaxHealth;
    mIsMovingLeft = false;
    mIsMovingRight = false;
    mIsMovingUp = false;
    mIsMovingDown = false;
    mPlayerIndicator = pPlayerIndicator;

    set_cur_direction(pDirection);
    set_health(pHealth);
    init_objects(pResourceManager);
    mAnimManager.set_cur_anim("idol");
}

void player::move(std::string pIndicatorDirection, std::string pIndicatorUpDown)
{
    if (pIndicatorDirection == "l")
    {
        if (pIndicatorUpDown == "u")
        {
            mIsMovingLeft = false;
        }
        else
        {
            set_cur_direction(false);
            mIsMovingLeft = true;
            mIsMovingRight = false;
            mLastAction = 0;
        }
    }
    if (pIndicatorDirection == "r")
    {
        if (pIndicatorUpDown == "u")
        {
            mIsMovingRight = false;
        }
        else
        {
            set_cur_direction(true);
            mIsMovingLeft = false;
            mIsMovingRight = true;
            mLastAction = 1;
        }
    }
    if (pIndicatorDirection == "u")
    {
        if (pIndicatorUpDown == "u")
        {
            mIsMovingUp = false;
        }
        else
        {
            mIsMovingUp = true;
            mIsMovingDown = false;
            mLastAction = 2;
        }
    }
    if (pIndicatorDirection == "d")
    {
        if(pIndicatorUpDown == "u")
        {
            mIsMovingDown = false;
        }
        else
        {
            mIsMovingUp = false;
            mIsMovingDown = true;
            mLastAction = 3;
        }
    }
    if (pIndicatorUpDown == "u")
    {
        mAnimManager.set_cur_anim("idol");
    }
    else
    {
        mAnimManager.set_cur_anim("run");
    }
}

void player::resolve_border_collision(int pBorderIndicator)
{
    /*
     *  0 - none, 1 - left, 2 - upper, 3 - right, 4 - lower
     */
    switch (pBorderIndicator) {
        case 1: set_dest(SCREEN_WIDTH - mWidth, get_dy());
            break;
        case 2: set_dest(get_dx(), 0);
            break;
        case 3: set_dest(0, get_dy());
            break;
        case 4: set_dest(get_dx(), SCREEN_HEIGHT - mHeight);
            break;
        default:
            break;
    }
}

void player::set_health(int pHealth)
{
    mHealth = pHealth;
}

void player::set_cur_direction(bool direction)
{
    /*
     *  left: false, right true
     */
    mCurDirection = direction;
    mShadow.set_cur_direction(direction);
}

void player::shoot()
{
    if (!mBullet.get_is_active())
    {
        mBullet.set_is_active(true);
        mBullet.set_cur_direction(mCurDirection);

        int x;
        if (mCurDirection)
        {
            x = mDest.x + PLANE_WIDTH;
        }
        else
        {
            x = mDest.x - BULLET_WIDTH;
        }
        int y = mDest.y + PLANE_HEIGHT/2;

        mBullet.set_dest(x, y);

        mLastAction = 4;
    }
}

void player::update()
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
    if (mIsMovingLeft) set_dest(mDest.x - PLAYER_SPEED, mDest.y);
    if (mIsMovingRight) set_dest(mDest.x + PLAYER_SPEED, mDest.y);
    if (mIsMovingUp) set_dest(mDest.x, mDest.y - PLAYER_SPEED);
    if (mIsMovingDown) set_dest(mDest.x, mDest.y + PLAYER_SPEED);

    mBullet.update();
    mAnimManager.update();
    mShadow.update(&mDest);
}