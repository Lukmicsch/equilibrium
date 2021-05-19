//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_OBJECT_H
#define EQUILIBRIUM_OBJECT_H

#include <vector>

#include "SDL.h"

#include "resource_manager.h"

class object
{
public:
    object();
    ~object();

    SDL_Rect *get_clip();
    SDL_Rect *get_dest();
    int get_dx();
    int get_dy();
    int get_height();
    SDL_Texture *get_tex();
    int get_width();
    void init(resource_manager *pResourceManager, const std::string& pSurfIndicator, int pNoClips,
              int pWidth, int pHeight, int pStartingClip, int pX, int pY);
    void init_clips(int pNoClips, int pWidth, int pHeight);
    void set_clip(int pId);
    void set_dest(int pX, int pY);

protected:
    std::vector<SDL_Rect> mClips;
    SDL_Rect mCurClip; // Which part of the sprite
    SDL_Rect mDest; // Where to draw
    int mHeight;
    int mWidth;
    SDL_Texture *mTex;
};


#endif //EQUILIBRIUM_OBJECT_H
