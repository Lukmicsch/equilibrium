//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_DRAW_H
#define EQUILIBRIUM_DRAW_H

#include "game_config.h"
#include "map.h"

class draw
{
public:
    draw(resource_manager *pResourcemanager);
    ~draw();

    void draw_font(const char* msg, int x, int y, int r, int g, int b);
    void draw_object(object *pObject);
    void draw_map(map pMap);

private:
    resource_manager *mResourceManager;
};


#endif //EQUILIBRIUM_DRAW_H
