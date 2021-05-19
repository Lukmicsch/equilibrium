//
// Created by Lukas Schmidt on 3/20/21.
//

#include "dqn_manager.h"

dqn_manager::dqn_manager() {
    mDqn = std::make_shared<dqn>(INPUT_SIZE, HIDDEN_1_SIZE, HIDDEN_2_SIZE, HIDDEN_3_SIZE, OUTPUT_SIZE);
}

dqn_manager::~dqn_manager() = default;

int dqn_manager::get_action_from_state(torch::Tensor pStates, double pEpsilon) {

    int action;

    // Epsilon greedy policy
    if (torch::rand(1).item().to<float>() < pEpsilon)
    {
        action = torch::randint(5, 1).item().to<int>();
    }
    else
    {
        torch::Tensor qVals = get_qvals_from_state(pStates);
        action = torch::argmax(qVals).item().to<int>();
    }

    return action;
}

torch::Tensor dqn_manager::get_qvals_from_state(torch::Tensor pStates) {
    torch::NoGradGuard no_grad;

    torch::Tensor qVals = mDqn->forward(pStates);

    return qVals;
}

torch::Tensor dqn_manager::get_qvals_from_state_with_grad(torch::Tensor pStates) {
    torch::Tensor qVals = mDqn->forward(pStates);

    return qVals;
}

void dqn_manager::load_model(std::string pCheckpoint)
{
    torch::load(mDqn, pCheckpoint);
    std::cout << "Loading model from " + pCheckpoint + "\n";
}

void dqn_manager::save_model(std::string pCheckpoint)
{
    torch::save(mDqn, pCheckpoint);
    std::cout << "Saving model to " + pCheckpoint + "\n";
}

std::vector<torch::Tensor> dqn_manager::get_model_params()
{
    return mDqn->parameters();
}