//
// Created by Lukas Schmidt on 4/8/21.
//

#ifndef EQUILIBRIUM_EXPERIENCE_H
#define EQUILIBRIUM_EXPERIENCE_H

struct experience {
    int belongsTo; // 0 - left, 1 - right
    torch::Tensor state;
    torch::Tensor action;
    torch::Tensor reward;
    torch::Tensor nextState;
    torch::Tensor done;
};

#endif //EQUILIBRIUM_EXPERIENCE_H
