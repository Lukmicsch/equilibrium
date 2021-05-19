//
// Created by Lukas Schmidt on 3/20/21.
//

#include "tile.h"

tile::tile() {

}

tile::~tile() = default;

int tile::get_indicator()
{
    return mIndicator;
}

void tile::set_indicator(int pIndicator)
{
    mIndicator = pIndicator;
}
