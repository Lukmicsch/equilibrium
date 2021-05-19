//
// Created by Lukas Schmidt on 3/2/21.
//

#include "object.h"

object::object()
{

}

object::~object() = default;

SDL_Rect *object::get_clip()
{
    return &mCurClip;
}

SDL_Rect *object::get_dest()
{
    return &mDest;
}

int object::get_dx()
{
    return mDest.x;
}

int object::get_dy()
{
    return mDest.y;
}

int object::get_height()
{
    return mDest.h;
}

SDL_Texture *object::get_tex()
{
    return  mTex;
}

int object::get_width()
{
    return mDest.w;
}

void object::init(resource_manager *pResourceManager, const std::string& pSurfIndicator, int pNoClips,
                  int pWidth, int pHeight, int pStartingClip, int pX, int pY)
{
    mWidth = pWidth;
    mHeight = pHeight;
    SDL_Surface *surf = pResourceManager->get_surface(pSurfIndicator);
    SDL_Renderer *ren = pResourceManager->get_ren();
    mTex = SDL_CreateTextureFromSurface(ren, surf);

    init_clips(pNoClips, pWidth, pHeight);
    set_clip(pStartingClip);
    set_dest(pX, pY);
}

void object::init_clips(int pNoClips, int pWidth, int pHeight)
{
    for (int i = 0; i < pNoClips; i++)
    {
        SDL_Rect tmpRect;
        tmpRect.x = 0;
        tmpRect.y = i * pHeight;
        tmpRect.w = pWidth;
        tmpRect.h = pHeight;
        mClips.push_back(tmpRect);
    }
}

void object::set_clip(int pId)
{
    mCurClip = mClips[pId];
}

void object::set_dest(int pX, int pY)
{
    mDest.x = pX;
    mDest.y = pY;
    mDest.w = mWidth;
    mDest.h = mHeight;
}