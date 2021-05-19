//
// Created by Lukas Schmidt on 3/20/21.
//

#ifndef EQUILIBRIUM_TRAIN_H
#define EQUILIBRIUM_TRAIN_H

#include <sstream>

#include "../game/game.h"
#include "../game/game_config.h"
#include "dqn_manager.h"
#include "train_utils.h"

class train {
public:
    train(std::string pCwdString);
    ~train();

    void training_loop();

private:
    void training_step();

    std::string mCwdString;
    torch::optim::Adam *mOptimizer;
    std::vector<float> mOverallLoss;
    dqn_manager mPredictModel;
    dqn_manager mTargetModel;
    train_utils mTrainUtils;
};


#endif //EQUILIBRIUM_TRAIN_H
