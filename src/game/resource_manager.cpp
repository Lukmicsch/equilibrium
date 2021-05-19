//
// Created by Lukas Schmidt on 3/1/21.
//

#include "resource_manager.h"


resource_manager::resource_manager(std::string pCwdString)
{
    std::string base = pCwdString.substr(0, pCwdString.find_last_of("/"));
    mResource_path = base + "/../res/";
}

resource_manager::~resource_manager() = default;

bool resource_manager::init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        // Create window
        if(SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &mWin, &mRen) < 0)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            SDL_SetWindowTitle(mWin, "Equilibrium");
            SDL_ShowCursor(0);
            //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

            // Initialize font lib and load font
            if(TTF_Init() < 0)
            {
                std::cout << "TTF could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                std::string font_path = mResource_path + "GameBoy.ttf";
                mFont = TTF_OpenFont(font_path.c_str(), 18);
            }
        }
    }

    return success;
}

void resource_manager::close()
{
    //Deallocate surface
    free_media();

    //Destroy window
    SDL_DestroyWindow( mWin );
    mWin = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

void resource_manager::free_media()
{
    SDL_FreeSurface(mLeftPlayerSurf);
    mLeftPlayerSurf = NULL;
    SDL_FreeSurface(mRightPlayerSurf);
    mRightPlayerSurf = NULL;
    SDL_FreeSurface(mShadowSurf);
    mShadowSurf = NULL;
    SDL_FreeSurface(mBulletSurf);
    mBulletSurf = NULL;
    SDL_FreeSurface(mTileSurf);
    mTileSurf = NULL;
}

TTF_Font *resource_manager::get_font()
{
    return mFont;
}

SDL_Renderer *resource_manager::get_ren()
{
    return mRen;
}

SDL_Surface *resource_manager::get_surface(std::string pSurfaceName)
{
    SDL_Surface *surf;

    if (pSurfaceName == "leftPlayer")
    {
        surf = mLeftPlayerSurf;
    }
    else if (pSurfaceName == "rightPlayer")
    {
        surf = mRightPlayerSurf;
    }
    else if (pSurfaceName == "shadow")
    {
        surf = mShadowSurf;
    }
    else if (pSurfaceName == "tile")
    {
        surf = mTileSurf;
    }
    else
    {
        surf = mBulletSurf;
    }

    return surf;
}

bool resource_manager::load_media()
{
    // Loading success flag
    bool success = true;

    // Init textures
    std::string leftPlayerLocation = mResource_path + "left-player.png";
    mLeftPlayerSurf = load_surface_from_img(leftPlayerLocation.c_str(), &success);

    std::string rightPlayerLocation = mResource_path + "right-player.png";
    mRightPlayerSurf = load_surface_from_img(rightPlayerLocation.c_str(), &success);

    std::string shadowLocation = mResource_path + "shadow.png";
    mShadowSurf = load_surface_from_img(shadowLocation.c_str(), &success);

    std::string bulletLocation = mResource_path + "bullet.png";
    mBulletSurf = load_surface_from_img(bulletLocation.c_str(), &success);

    std::string tileLocation = mResource_path + "tileset.png";
    mTileSurf = load_surface_from_img(tileLocation.c_str(), &success);

    return success;
}

SDL_Surface *resource_manager::load_surface_from_img(const char *pLocation, bool *pSuccess)
{
    SDL_Surface *surf = IMG_Load(pLocation);
    if( surf == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", pLocation, SDL_GetError() );
        *pSuccess = false;
    }

    return surf;
}