//
// Created by Lukas Schmidt on 4/10/21.
//

#ifndef EQUILIBRIUM_DQN_H
#define EQUILIBRIUM_DQN_H

#include <torch/torch.h>

#include "train_config.h"

struct dqn : torch::nn::Module
{
    // Construct the net
    dqn(int pIn, int pH1, int pH2, int pH3, int pOut)
    {
        // Construct and register two Linear submodules.
        fullyConnected1 = register_module("fullyConnected1", torch::nn::Linear(pIn, pH1));
        fullyConnected2 = register_module("fullyConnected2", torch::nn::Linear(pH1, pH2));
        fullyConnected3 = register_module("fullyConnected3", torch::nn::Linear(pH2, pH3));
        stateValues = register_module("stateValues", torch::nn::Linear(pH3, 1));
        rawAdvantages = register_module("rawAdvantages", torch::nn::Linear(pH3, pOut));
    }

    // Implement the Net's algorithm.
    torch::Tensor forward(torch::Tensor pInput)
    {
        torch::Tensor x;

        // Use one of many tensor manipulation functions.
        x = torch::relu(fullyConnected1->forward(pInput));
        x = torch::relu(fullyConnected2->forward(x));
        x = torch::relu(fullyConnected3->forward(x));
        torch::Tensor stateVal = stateValues->forward(x);
        torch::Tensor rawAdv = rawAdvantages->forward(x);
        torch::Tensor adv = rawAdv - torch::max(rawAdv);
        torch::Tensor q_val = stateVal + adv;

        return q_val;
    }

    torch::nn::Linear fullyConnected1{nullptr}, fullyConnected2{nullptr},
                        fullyConnected3{nullptr}, stateValues{nullptr}, rawAdvantages{nullptr};
};

#endif //EQUILIBRIUM_DQN_H
