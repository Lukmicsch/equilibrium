//
// Created by Lukas Schmidt on 3/20/21.
//

#ifndef EQUILIBRIUM_DQN_MANAGER_H
#define EQUILIBRIUM_DQN_MANAGER_H

#include "dqn.h"

class dqn_manager {
public:
    dqn_manager();
    ~dqn_manager();

    int get_action_from_state(torch::Tensor pStates, double pEpsilon);
    torch::Tensor get_qvals_from_state(torch::Tensor pStates);
    torch::Tensor get_qvals_from_state_with_grad(torch::Tensor pStates);
    void load_model(std::string pCheckpoint);
    void save_model(std::string pCheckpoint);
    std::vector<torch::Tensor> get_model_params();

private:
    std::shared_ptr<dqn> mDqn;
};


#endif //EQUILIBRIUM_DQN_MANAGER_H