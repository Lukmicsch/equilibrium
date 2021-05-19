//
// Created by Lukas Schmidt on 3/2/21.
//

#include "collision_detection.h"

collision_detection::collision_detection() = default;

collision_detection::~collision_detection() = default;

int collision_detection::border_collision(object *pObject)
{
    /*
     *  0 - none, 1 - left, 2 - upper, 3 - right, 4 - lower
     */
    int borderIndicator = 0;
    if (pObject->get_dy() <= 0) borderIndicator = 2;
    if (pObject->get_dy() >= SCREEN_HEIGHT - pObject->get_height()) borderIndicator = 4;
    if (pObject->get_dx() <= 0) borderIndicator = 1;
    if (pObject->get_dx() >= SCREEN_WIDTH - pObject->get_width()) borderIndicator = 3;

    return borderIndicator;
}

void collision_detection::border_collisions(player *pLeftPlayer, player *pRightPlayer)
{
    pLeftPlayer->resolve_border_collision(border_collision(pLeftPlayer));
    pRightPlayer->resolve_border_collision(border_collision(pRightPlayer));
    bullet *leftBullet = pLeftPlayer->get_bullet();
    leftBullet->resolve_border_collision(border_collision(leftBullet));
    bullet *rightBullet = pRightPlayer->get_bullet();
    rightBullet->resolve_border_collision(border_collision(rightBullet));
}

void collision_detection::bullet_collision(map *pMap, bullet *pBullet, player *pPlayer, player *pEnemyPlayer)
{
    if (collision(pBullet, pEnemyPlayer) && pBullet->get_is_active())
    {
        pBullet->set_is_active(false);
        pMap->update_player_tiles(pPlayer, DMG);
        if (pEnemyPlayer->get_health() > 0)
            pEnemyPlayer->set_health(std::max(0, pEnemyPlayer->get_health() - DMG));
        if (pPlayer->get_health() < pPlayer->get_max_health())
            pPlayer->set_health(std::min(pPlayer->get_max_health(), pPlayer->get_health() + DMG));
    }
}

void collision_detection::bullet_collisions(map *pMap, player *pLeftPlayer, player *pRightPlayer)
{
    bullet *leftBullet = pLeftPlayer->get_bullet();
    bullet_collision(pMap, leftBullet, pLeftPlayer, pRightPlayer);

    bullet *rightBullet = pRightPlayer->get_bullet();
    bullet_collision(pMap, rightBullet, pRightPlayer, pLeftPlayer);
}

void collision_detection::check_for_collision(map *pMap, player *pLeftPlayer, player *pRightPlayer)
{
    border_collisions(pLeftPlayer, pRightPlayer);
    map_collisions(pMap, pLeftPlayer, pRightPlayer);
    bullet_collisions(pMap, pLeftPlayer, pRightPlayer);
}

bool collision_detection::collision(object *pObjectOne, object *pObjectTwo)
{
    // Check if object two is in between object one
    if ((pObjectOne->get_dx() < (pObjectTwo->get_dx() + pObjectTwo->get_width())) &&
        ((pObjectOne->get_dx() + pObjectOne->get_width()) > pObjectTwo->get_dx()) &&
        (pObjectOne->get_dy() < (pObjectTwo->get_dy() + pObjectTwo->get_height())) &&
        ((pObjectOne->get_dy() + pObjectOne->get_height()) > pObjectTwo->get_dy()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void collision_detection::map_collisions(map *pMap, player *pLeftPlayer, player *pRightPlayer)
{
    std::vector<tile> *map = pMap->get_map();

    for(auto & i : *map) {
        tile *tmpTile = &i;
        tile_collision(tmpTile, pLeftPlayer, pRightPlayer);
        tile_collision(tmpTile, pRightPlayer, pLeftPlayer);
    }
}

void collision_detection::tile_collision(tile *pTile, player *pPlayer, player*pEnemyPlayer)
{
    int tileIndicator = pTile->get_indicator();
    int playerIndicator = pPlayer->get_player_indicator();
    if (collision(pTile, pPlayer) && tileIndicator != playerIndicator)
    {
        pTile->set_indicator(playerIndicator);
        pTile->set_clip(playerIndicator);
        if (pEnemyPlayer->get_health() > 0)
            pEnemyPlayer->set_health(std::max(0, pEnemyPlayer->get_health() - 1));
        if (pPlayer->get_health() < pPlayer->get_max_health())
            pPlayer->set_health(std::min(pPlayer->get_max_health(), pPlayer->get_health() + 1));
    }
}