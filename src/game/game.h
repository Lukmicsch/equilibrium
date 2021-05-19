//
// Created by Lukas Schmidt on 2/28/21.
//

#ifndef EQUILIBRIUM_GAME_H
#define EQUILIBRIUM_GAME_H

#include <sstream>

#include "collision_detection.h"
#include "game_config.h"
#include "../train/train_config.h"
#include "draw.h"
#include "../train/experience_manager.h"
#include "fps_manager.h"
#include "input_manager.h"
#include "map.h"
#include "player.h"
#include "resource_manager.h"
#include "timer.h"


class game
{
public:
    game(std::string pCwdString);
    ~game();

    void game_loop();
    std::vector<experience> game_loop_train(double pEpsilon);
    int game_loop_eval();
    void is_done(bool *pGameOver, int *pWinner);
    void process_input(bool *pQuit, bool *pGameStarted, bool *pStarted);
    void render(bool *pStarted, bool *pGameOver, int *pWinner);
    void update();

private:
    collision_detection mCollisionDetection;
    draw mDraw;
    bool mEval;
    experience_manager mExpManager;
    TTF_Font *mFont;
    fps_manager mFpsManager;
    int mFrameCount;
    input_manager mInputManager;
    map mMap;
    player mLeftPlayer;
    SDL_Renderer *mRen;
    player mRightPlayer;
    resource_manager mResourceManager;
    timer mTimer;
};

#endif //EQUILIBRIUM_GAME_H