//
// Created by Lukas Schmidt on 3/2/21.
//

#include "input_manager.h"

input_manager::input_manager(player *pLeftPlayer, player *pRightPlayer,
                             experience_manager *pExpManager)
{
    mLeftPlayer = pLeftPlayer;
    mRightPlayer = pRightPlayer;
    mExpManager = pExpManager;
}

input_manager::~input_manager() = default;

void input_manager::init_ai(std::string pLeftPlayerCheckpoint, std::string pRightPlayerCheckpoint, double pEpsilon)
{
    if (pLeftPlayerCheckpoint != "None")
    {
       mLeftDqnManager.load_model(pLeftPlayerCheckpoint);
    }
    if (pRightPlayerCheckpoint != "None")
    {
        mRightDqnManager.load_model(pRightPlayerCheckpoint);
    }
    mEpsilon = pEpsilon;
}

void input_manager::input_ai()
{
    if(TRAIN) {
        SDL_Event e;
        if(!SDL_PollEvent(&e))
            ;
    }

    // Remeber only every 4 frames new action else repeat
    int framesWaited = mExpManager->get_frames_waited();
    if (framesWaited == AI_SUBSEQUENT_FRAMES)
    {
        torch::Tensor rightState = mExpManager->get_cur_state(true);
        int rightPlayerAction = mRightDqnManager.get_action_from_state(rightState, mEpsilon);
        if (rightPlayerAction == 4)
        {
            mRightPlayer->shoot();
        }
        else
        {
            std::string translation = translate_action(rightPlayerAction);
            mRightPlayer->move(translation, "d");
        }

        if (!SINGLE_PLAYER)
        {
            torch::Tensor leftState = mExpManager->get_cur_state(false);
            int leftPlayerAction = mLeftDqnManager.get_action_from_state(leftState, mEpsilon);
            if (leftPlayerAction == 4)
            {
                mLeftPlayer->shoot();
            }
            else
            {
                std::string translation = translate_action(leftPlayerAction);
                mLeftPlayer->move(translation, "d");
            }
        }
    }
}

void input_manager::input_human(bool *pQuit, bool *pStarted, timer *pTimer)
{
    // Event handler
    SDL_Event e;

    // Handle Events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit and start game
        if ((e.type == SDL_KEYDOWN) && !*pStarted)
        {
            *pStarted = true;
            pTimer->start();
        }
        if (e.type == SDL_QUIT) *pQuit = true;

        // Handle human input
        input_human_left(&e);
        if (!SINGLE_PLAYER) input_human_right(&e);
    }
}

void input_manager::input_human_left(SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN)
    {
        if (e->key.keysym.sym == SDLK_a) mLeftPlayer->move("l","d");
        if (e->key.keysym.sym == SDLK_d) mLeftPlayer->move("r", "d");
        if (e->key.keysym.sym == SDLK_w) mLeftPlayer->move("u", "d");
        if (e->key.keysym.sym == SDLK_s) mLeftPlayer->move("d", "d");
    }
    if(e->type == SDL_KEYUP)
    {
        if (e->key.keysym.sym == SDLK_a) mLeftPlayer->move("l","u");
        if (e->key.keysym.sym == SDLK_d) mLeftPlayer->move("r", "u");
        if (e->key.keysym.sym == SDLK_w) mLeftPlayer->move("u", "u");
        if (e->key.keysym.sym == SDLK_s) mLeftPlayer->move("d", "u");
    }
    if (e->type == SDL_MOUSEBUTTONDOWN) mLeftPlayer->shoot();
}

void input_manager::input_human_right(SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN)
    {
        if (e->key.keysym.sym == SDLK_LEFT) mRightPlayer->move("l", "d");
        if (e->key.keysym.sym == SDLK_RIGHT) mRightPlayer->move("r", "d");
        if (e->key.keysym.sym == SDLK_UP) mRightPlayer->move("u", "d");
        if (e->key.keysym.sym == SDLK_DOWN) mRightPlayer->move("d", "d");
        if (e->key.keysym.sym == SDLK_SPACE) mRightPlayer->shoot();
    }
    if (e->type == SDL_KEYUP)
    {
        if (e->key.keysym.sym == SDLK_LEFT) mRightPlayer->move("l", "u");
        if (e->key.keysym.sym == SDLK_RIGHT) mRightPlayer->move("r", "u");
        if (e->key.keysym.sym == SDLK_UP) mRightPlayer->move("u", "u");
        if (e->key.keysym.sym == SDLK_DOWN) mRightPlayer->move("d", "u");
    }
}

std::string input_manager::translate_action(int pAction)
{
    std::string translation;

    switch (pAction) {
        case 0:
            translation = "l";
            break;
        case 1:
            translation = "r";
            break;
        case 2:
            translation = "u";
            break;
        case 3:
            translation = "d";
            break;
    }

    return translation;
}