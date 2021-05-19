//
// Created by Lukas Schmidt on 3/20/21.
//

#include "train_config.h"
#include "train.h"

train::train(std::string pCwdString)
{
    mCwdString = pCwdString;

    // Save s.t. the game can load the AI for baseline eval
    mPredictModel.save_model(CHECKPOINT);
}

train::~train() = default;

void train::training_loop()
{
    // Fill replay_buffer
    mTrainUtils.populate_exp_buffer(mCwdString, 1.0);

    // Init optimizer
    auto optimizer = torch::optim::Adam(mTargetModel.get_model_params(), LEARNING_RATE);
    mOptimizer = &optimizer;

    std::cout << "Start training (" + std::to_string(NUM_EPISODES) + " episodes):" << std::endl;

    for (int i = 0; i < NUM_EPISODES; i++)
    {
        std::cout << "Episode " + std::to_string(i) << std::endl;

        // EVAL
        if (i % EVAL_FREQUENCY == 0)
        {
            // Save apprentice model
            mPredictModel.save_model(APPRENTICE_CHECKPOINT);
            int avgResult = mTrainUtils.model_eval(mCwdString);

            if (avgResult > PLAYER_HEALTH_BEGINNING)
            {
                std::cout << "New best player!" << std::endl;
                // Save new best Model
                mPredictModel.save_model(CHECKPOINT);
            }

            std::cout << "Continue training: " << std::endl;
        }

        // Update epsilon
        torch::Tensor epsTensor = torch::tensor({(double)(1 - (i / EPSILON_DECAY)), EPSILON});
        double epsilon = torch::max(epsTensor).item().to<double>();

        game equilibrium(mCwdString);
        std::vector<experience> tmpExperiences = equilibrium.game_loop_train(epsilon);

        // Add experiences to replay buffer
        mTrainUtils.add_to_replay_buffer(tmpExperiences);

        // Train the Network
        std::cout << "Start " + std::to_string(NUM_TRAINING_STEPS) + " training steps." << std::endl;

        for(int j = 0; j < NUM_TRAINING_STEPS; j++) {
            training_step();
        }
        training_step();

        // Update target model
        if (i % TRAINING_MODEL_SYNC_FREQUENCY == 0) {
            std::cout << "Update target model." << std::endl;
            mTargetModel.load_model(CHECKPOINT);
        }

        torch::Tensor overall_loss_tensor = torch::tensor(mOverallLoss);
        torch::Tensor lossAvg = torch::mean(overall_loss_tensor);

        std::cout << "Loss avg: " << lossAvg << std::endl;
    }
}

void train::training_step() {
    // Get experiences
    std::vector<experience> batchVector = mTrainUtils.sample_experiences();
    std::vector<torch::Tensor> batch = mTrainUtils.transform_experiences(batchVector);

    // Compute next Q-vals
    torch::Tensor nextStates = batch[3];
    torch::Tensor nextQvals = mPredictModel.get_qvals_from_state(nextStates);

    // Get the indices for responsible actions
    torch::Tensor responsibleNextActions = torch::empty({BATCH_SIZE,1});
    for(int i = 0; i < BATCH_SIZE; i++) {
        responsibleNextActions[i][0] = torch::argmax(nextQvals[i]);
    }

    // Next Q-vals as per target model
    torch::Tensor nextQvalsTarget = mTargetModel.get_qvals_from_state(nextStates);
    torch::Tensor nextBestQvals = torch::empty({BATCH_SIZE,1});

    // Get the Q-vals we would have chosen
    for(int i = 0; i < BATCH_SIZE; i++) {
        nextBestQvals[i][0] = nextQvalsTarget[i][responsibleNextActions[i].item().to<int>()];
    }

    // Use Bellman equation to comput the target Q-vals
    torch::Tensor rewards = batch[2];
    torch::Tensor dones = batch[4];
    torch::Tensor targetQvals = (rewards + (1 - dones) * GAMMA * nextBestQvals).requires_grad_(true); // TODO: CHECK IF THIS IS OKAY

    // So now we actually predict the Q-val for our state again but using our lossfunction to calculate the error and optimize our models variables via GD
    //torch::Tensor actions = batch[1];
    torch::Tensor states = batch[0];

    mOptimizer->zero_grad(); // Reset gradients

    torch::Tensor allQvals =  mPredictModel.get_qvals_from_state_with_grad(states); // Get all Q-vals

    torch::Tensor responsibleActions = torch::empty({BATCH_SIZE,1});
    for(int i = 0; i < BATCH_SIZE; i++) {
        responsibleActions[i][0] = torch::argmax(allQvals[i]); // Get the actions we took
    }

    torch::Tensor qVals = torch::empty({BATCH_SIZE,1});
    for(int i = 0; i < BATCH_SIZE; i++) {
        qVals[i][0] = allQvals[i][responsibleActions[i].item().to<int>()]; // Get the actual Q-vals we used
    }

    torch::Tensor loss = torch::mse_loss(qVals, targetQvals); // TODO: CHECK IF THE GRADS ARE OKAY

    loss.backward(); // Compute gradients of the loss w.r.t. the parameters of our model.

    mOptimizer->step();

    mOverallLoss.push_back(loss.item().to<float>());
}