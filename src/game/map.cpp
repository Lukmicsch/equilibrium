//
// Created by Lukas Schmidt on 3/2/21.
//

#include "map.h"

map::map()
{

}

map::~map() = default;

std::vector<tile> *map::get_map()
{
    return &mMap;
}

void map::populate_map(resource_manager *pResourceManager)
{
    // create tmp tile and indicator
    tile tmp;
    int tmpIndicator;

    // Now loop through the values
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        tmpIndicator = LEFT_PLAYER_INDICATOR;
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            // Check which tile we are on right now
            if (j >= MAP_WIDTH/2) tmpIndicator = RIGHT_PLAYER_INDICATOR;

            int tmpX = (j * TILE_SIZE);
            int tmpY = (i * TILE_SIZE);
            tmp.init(pResourceManager, "tile", 2, TILE_SIZE, TILE_SIZE, tmpIndicator, tmpX, tmpY);
            tmp.set_indicator(tmpIndicator); // Set ID for the objects
            mMap.push_back(tmp); // map is vector full of tiles (Objects)
        }
    }
}

void map::set_winner_tiles(int pIndicator)
{
    // Only draw the parts that are within our window
    for(auto & i : mMap) {
        i.set_indicator(pIndicator);
    }
}

void map::update_player_tiles(player *pPlayer, int pTileSize)
{
    int playerIndicator = pPlayer->get_player_indicator();
    std::vector<int> enemy_tiles;
    std::vector<int> random_choices;

    for (int i = 0; i < mMap.size(); i++) {
        if (pTileSize > 0 && mMap[i].get_indicator() != playerIndicator)
        {
            enemy_tiles.push_back(i);
        }
    }

    // Sample randomly from enemy tiles
    std::sample(
            enemy_tiles.begin(),
            enemy_tiles.end(),
            std::back_inserter(random_choices),
            pTileSize,
            std::mt19937{std::random_device{}()}
    );

    for (auto i : random_choices)
    {
        mMap[i].set_indicator(playerIndicator);
        mMap[i].set_clip(playerIndicator);
    }
}