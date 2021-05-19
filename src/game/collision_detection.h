//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_COLLISION_DETECTION_H
#define EQUILIBRIUM_COLLISION_DETECTION_H

#include "map.h"
#include "object.h"
#include "player.h"

class collision_detection
{
public:
    collision_detection();
    ~collision_detection();

    void check_for_collision(map *pMap, player *pLeftPlayer, player *pRightPlayer);

private:
    int border_collision(object *pObject);
    void border_collisions(player *pLeftPlayer, player *pRightPlayer);
    void bullet_collision(map *pMap, bullet *pBullet, player *pPlayer, player *pEnemyPlayer);
    void bullet_collisions(map *pMap, player *pLeftPlayer, player *pRightPlayer);
    bool collision(object *pObjectOne, object *pObjectTwo);
    void map_collisions(map *pMap, player *pLeftPlayer, player *pRightPlayer);
    void tile_collision(tile *pTile, player *pPlayer, player* pEnemyPlayer);
};


#endif //EQUILIBRIUM_COLLISION_DETECTION_H
