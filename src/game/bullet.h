//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_BULLET_H
#define EQUILIBRIUM_BULLET_H

#include "object.h"
#include "resource_manager.h"

class bullet: public object
{
public:
    bullet();
    ~bullet();

    bool get_cur_direction();
    bool get_is_active();
    void resolve_border_collision(int pBorderIndicator);
    void set_cur_direction(bool pDirection);
    void set_is_active(bool pIsActive);
    void update();

private:
    bool mCurDirection;
    bool mIsActive;
};


#endif //EQUILIBRIUM_BULLET_H
