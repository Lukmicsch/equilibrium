//
// Created by Lukas Schmidt on 3/20/21.
//

#ifndef EQUILIBRIUM_TRAIN_UTILS_H
#define EQUILIBRIUM_TRAIN_UTILS_H

#include "../game/game.h"

class train_utils {
public:
    train_utils();
    ~train_utils();

    void add_to_replay_buffer(std::vector<experience> pExperiences);
    int model_eval(std::string pCwdString);
    void populate_exp_buffer(std::string pCwdString, double pEpsilon);
    std::vector<experience> sample_experiences();
    std::vector<torch::Tensor> transform_experiences(std::vector<experience> pBatch);

    std::vector<experience> mExperienceReplayBuffer;
};


#endif //EQUILIBRIUM_TRAIN_UTILS_H
