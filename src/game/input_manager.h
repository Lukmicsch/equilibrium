//
// Created by Lukas Schmidt on 3/2/21.
//

#ifndef EQUILIBRIUM_INPUT_MANAGER_H
#define EQUILIBRIUM_INPUT_MANAGER_H

#include <iostream>

#include "SDL.h"

#include "game_config.h"
#include "../train/experience_manager.h"
#include "../train/dqn_manager.h"
#include "player.h"
#include "timer.h"

class input_manager
{
public:
    input_manager(player *pLeftPlayer, player *pRightPlayer, experience_manager *pExpManager);
    ~input_manager();

    void init_ai(std::string pLeftPlayerCheckpoint, std::string pRightPlayerCheckpoint, double pEpsilon);
    void input_ai();
    void input_human(bool *pQuit, bool *pStarted, timer *pTimer);

private:
    float mEpsilon;
    experience_manager *mExpManager;
    dqn_manager mLeftDqnManager;
    dqn_manager mRightDqnManager;
    player *mLeftPlayer;
    player *mRightPlayer;

    void input_human_left(SDL_Event *e);
    void input_human_right(SDL_Event *e);
    std::string translate_action(int pAction);
};


#endif //EQUILIBRIUM_INPUT_MANAGER_H
