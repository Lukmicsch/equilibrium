//
// Created by Lukas Schmidt on 3/1/21.
//

#ifndef EQUILIBRIUM_RESOURCE_MANAGER_H
#define EQUILIBRIUM_RESOURCE_MANAGER_H

#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "game_config.h"

class resource_manager
{
public:
    resource_manager(std::string pCwdString);
    ~resource_manager();

    void close();
    void free_media();
    TTF_Font *get_font();
    SDL_Renderer *get_ren();
    SDL_Surface *get_surface(std::string pSurfaceName);
    bool init();
    bool load_media();
    SDL_Surface *load_surface_from_img(const char *pLocation, bool *pSuccess);

private:
    SDL_Surface *mBulletSurf;
    TTF_Font *mFont;
    SDL_Surface *mLeftPlayerSurf;
    SDL_Renderer *mRen;
    std::string mResource_path;
    SDL_Surface *mRightPlayerSurf;
    SDL_Surface *mShadowSurf;
    SDL_Surface *mTileSurf;
    SDL_Window *mWin;
};


#endif //EQUILIBRIUM_RESOURCE_MANAGER_H
