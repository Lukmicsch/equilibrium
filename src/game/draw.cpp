//
// Created by Lukas Schmidt on 3/2/21.
//

#include "draw.h"

draw::draw(resource_manager *pResourceManager)
{
    mResourceManager = pResourceManager;
};

draw::~draw() = default;

void draw::draw_font(const char* msg, int x, int y, int r, int g, int b)
{
    SDL_Surface* surf;
    SDL_Texture* tex;
    SDL_Color color;

    TTF_Font *font = mResourceManager->get_font();
    SDL_Renderer *ren = mResourceManager->get_ren();
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg, color);
    tex = SDL_CreateTextureFromSurface(ren, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;
    SDL_FreeSurface(surf);
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

void draw::draw_object(object *pObject)
{
    SDL_Rect *clip = pObject->get_clip();
    SDL_Rect *dest = pObject->get_dest();
    SDL_Texture *surf = pObject->get_tex();
    SDL_Renderer *ren = mResourceManager->get_ren();

    SDL_RenderCopyEx(ren, surf, clip, dest, 0, NULL, SDL_FLIP_NONE);
}

void draw::draw_map(map pMap)
{
    std::vector<tile> *map = pMap.get_map();

    // Only draw the parts that are within our window
    for(auto & i : *map) {
        tile *tmpTile = &i;
        draw_object(tmpTile);
    }
}