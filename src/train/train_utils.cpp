//
// Created by Lukas Schmidt on 3/20/21.
//

#include "train_utils.h"

train_utils::train_utils() {

}

train_utils::~train_utils() = default;

void train_utils::add_to_replay_buffer(std::vector<experience> pExperiences)
{
    int replayBufferSize = mExperienceReplayBuffer.size();
    int experiencesSize = pExperiences.size();
    int newSize =  replayBufferSize + experiencesSize;

    if (newSize > REPLAY_BUFFER_MAX)
    {
        int overlap = newSize - REPLAY_BUFFER_MAX; // How many more it would be
        mExperienceReplayBuffer.erase(mExperienceReplayBuffer.end() - overlap, mExperienceReplayBuffer.end());
    }

    mExperienceReplayBuffer.insert(mExperienceReplayBuffer.begin(), pExperiences.begin(), pExperiences.end());
}

int train_utils::model_eval(std::string pCwdString)
{
    std::cout << "Starting Evaluation (" + std::to_string(EVAL_EPISODES) + " episodes): \n";

    int sumResults = 0;

    for (int i = 0; i < EVAL_EPISODES; i++)
    {
        game equilibrium = game(pCwdString);
        int result = equilibrium.game_loop_eval();
        sumResults = sumResults + result;
    }

    float avgResult = sumResults / EVAL_EPISODES;

    std::cout << "Apprentice's average result: " + std::to_string(avgResult) + "\n";

    return avgResult;
}

void train_utils::populate_exp_buffer(std::string pCwdString, double pEpsilon)
{
    while (mExperienceReplayBuffer.size() < REPLAY_BUFFER_MAX)
    {
        game equilibrium = game(pCwdString);
        std::vector<experience> tmpExperiences = equilibrium.game_loop_train(pEpsilon);
        add_to_replay_buffer(tmpExperiences);
    }

    std::cout << "Experience replay buffer filled with " + std::to_string(mExperienceReplayBuffer.size())
                    + " experiences." << std::endl;
}

std::vector<experience> train_utils::sample_experiences()
{
    std::vector<experience> sampleExperiences;
    torch::Tensor indices = torch::randint(mExperienceReplayBuffer.size(), {1, BATCH_SIZE});

    for (int i = 0; i < BATCH_SIZE; i++){
        int index = indices[0][i].item().to<int>();
        sampleExperiences.push_back(mExperienceReplayBuffer[index]);
    }

    // return the experiences
    return sampleExperiences;
}

std::vector<torch::Tensor> train_utils::transform_experiences(std::vector<experience> pBatch)
{
    std::vector<torch::Tensor> transformedBatch;

    std::vector<torch::Tensor> statesVector;
    torch::Tensor StatesTensor;
    std::vector<torch::Tensor> nextStatesVector;
    torch::Tensor nextStatesTensor;

    torch::Tensor actionsTensor = torch::empty({BATCH_SIZE, 1});
    torch::Tensor rewardsTensor = torch::empty({BATCH_SIZE, 1});
    torch::Tensor donesTensor = torch::empty({BATCH_SIZE, 1});

    for(int i = 0; i < BATCH_SIZE; i++) {
        statesVector.push_back(pBatch[i].state);
        actionsTensor[i][0] = pBatch[i].action;
        rewardsTensor[i][0] = pBatch[i].reward;
        nextStatesVector.push_back(pBatch[i].nextState);
        donesTensor[i][0] = pBatch[i].done;
    }

    for (int i = 0; i < nextStatesVector.size(); i++)
    {
        if (!nextStatesVector[i].defined())
        {
            std::cout << "done: " << donesTensor[i];
            std::cout << "state: " << statesVector[i];
        }
    }

    StatesTensor = torch::stack(statesVector);
    nextStatesTensor = torch::stack(nextStatesVector);

    transformedBatch.push_back(StatesTensor);
    transformedBatch.push_back(actionsTensor);
    transformedBatch.push_back(rewardsTensor);
    transformedBatch.push_back(nextStatesTensor);
    transformedBatch.push_back(donesTensor);

    return transformedBatch;
}