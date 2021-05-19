//
// Created by Lukas Schmidt on 3/24/21.
//

#ifndef EQUILIBRIUM_SHADOW_H
#define EQUILIBRIUM_SHADOW_H

#include "SDL.h"

#include "object.h"

class shadow: public object {
public:
    shadow();
    ~shadow();

    void set_cur_direction(bool pDirection);
    void update(SDL_Rect *pPlayerDest);

private:
    bool mCurDirection;
};


#endif //EQUILIBRIUM_SHADOW_H
