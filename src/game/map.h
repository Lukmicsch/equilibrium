//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_MAP_H
#define EQUILIBRIUM_MAP_H

#include <random>
#include <vector>

#include "game_config.h"
#include "player.h"
#include "resource_manager.h"
#include "tile.h"


class map
{
public:
    map();
    ~map();

    std::vector<tile> *get_map();
    void populate_map(resource_manager *pResourceManager);
    void set_winner_tiles(int pIndicator);
    void update_player_tiles(player *pPlayer, int pTileSize);

private:
    std::vector<tile> mMap;
};


#endif //EQUILIBRIUM_MAP_H