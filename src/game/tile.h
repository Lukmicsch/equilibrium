//
// Created by Lukas Schmidt on 3/20/21.
//

#ifndef EQUILIBRIUM_TILE_H
#define EQUILIBRIUM_TILE_H

#include "object.h"
#include "resource_manager.h"

class tile : public object
{
public:
    tile();
    ~tile();

    int get_indicator();
    void set_indicator(int pIndicator);

private:
    int mIndicator;
};


#endif //EQUILIBRIUM_TILE_H