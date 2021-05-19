//
// Created by Lukas Schmidt on 3/24/21.
//

#ifndef EQUILIBRIUM_EXPERIENCE_MANAGER_H
#define EQUILIBRIUM_EXPERIENCE_MANAGER_H

#include "torch/torch.h"

#include "vector"

#include "../game/bullet.h"
#include "../game/game_config.h"
#include "experience.h"
#include "../game/player.h"
#include "../game/map.h"
#include "../game/timer.h"
#include "train_config.h"

class experience_manager {
public:
    experience_manager(map *pMap, player *pLeftPlayer, player *pRightPlayer, int *pFrameCount);
    ~experience_manager();

    void add_experience(bool *pGameOver);
    torch::Tensor get_cur_state(bool pPlayer);
    std::vector<experience> get_experiences();
    int get_frames_waited();
    void new_experience();

private:
    void add_state_to_experience(torch::Tensor *pState, bool pPlayer);
    torch::Tensor create_cur_obs(bool pPlayer);
    int get_player_reward(bool pPlayer);
    void repeat_state_and_done();

    experience mExperienceLeft;
    experience mExperienceRight;
    std::vector<experience> mExperiences;
    int mFramesWaited;
    player *mLeftPlayer;
    int mLeftPlayerLastHealth;
    map *mMap;
    player *mRightPlayer;
    int mRightPlayerLastHealth;
    int *mFrameCount;
};


#endif //EQUILIBRIUM_EXPERIENCE_MANAGER_H
