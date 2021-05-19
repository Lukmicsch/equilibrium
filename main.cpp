#include <iostream>

#include "src/game/game_config.h"
#include "src/game/game.h"
#include "src/train/train.h"

int main(int argc, char* argv[])
{
    if (TRAIN)
    {
        train trainer = train(argv[0]);
        trainer.training_loop();
    } else
    {
        game equilibrium = game(argv[0]);
        equilibrium.game_loop();
    }
}