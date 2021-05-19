//
// Created by Lukas Schmidt on 3/24/21.
//

#ifndef EQUILIBRIUM_TRAIN_CONFIG_H
#define EQUILIBRIUM_TRAIN_CONFIG_H

#include "sstream"

// Train hyperparameters
const int NUM_EPISODES = 1200; // For a total of 1.08 mio experiences
const int NUM_TRAINING_STEPS = 3600; // Which is equal to one step per frame //
const int TRAINING_MODEL_SYNC_FREQUENCY = 3; // Every 10.800 frames
const float LEARNING_RATE = 0.001;
const int BATCH_SIZE = 32;
const float GAMMA = 0.99;
const double EPSILON = 0.01;
const int EPSILON_DECAY = 42; // After 151.200 frames
const int REPLAY_BUFFER_MAX = 10000;

// Model checkpoint name
const std::string CHECKPOINT = "dqn.pt";
const std::string APPRENTICE_CHECKPOINT = "apprentice.pt";

// Model hyperparameters
const int INPUT_SIZE = 852;
const int HIDDEN_1_SIZE = 512;
const int HIDDEN_2_SIZE = 512;
const int HIDDEN_3_SIZE = 512;
const int OUTPUT_SIZE = 5;

// Eval
const int EVAL_FREQUENCY = 5;
const int EVAL_EPISODES = 3;

#endif //EQUILIBRIUM_TRAIN_CONFIG_H
