//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_PLAYER_H
#define EQUILIBRIUM_PLAYER_H

#include "animation_manager.h"
#include "bullet.h"
#include "object.h"
#include "resource_manager.h"
#include "shadow.h"


class player : public object
{
public:
    player();
    ~player();

    bullet *get_bullet();
    bool get_cur_direction();
    int get_health();
    int get_last_action();
    int get_max_health();
    int get_player_indicator();
    shadow *get_shadow();
    void init_self(resource_manager *pResourceManager, bool pDirection, int pHealth, int pMaxHealth, int pPlayerIndicator);
    void move(std::string pIndicatorDirection, std::string pIndicatorUpDown);
    void resolve_border_collision(int pBorderIndicator);
    void set_cur_direction(bool pDirection);
    void set_health(int pHealth);
    void shoot();
    void update();

private:
    void init_objects(resource_manager *pResourceManager);

    animation_manager mAnimManager;
    bullet mBullet;
    bool mCurDirection;
    int mHealth;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool mIsMovingUp;
    bool mIsMovingDown;
    int mLastAction;
    int mMaxHealth;
    int mPlayerIndicator;
    shadow mShadow;
};


#endif //EQUILIBRIUM_PLAYER_H