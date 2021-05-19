//
// Created by Lukas Schmidt on 3/24/21.
//

#include "experience_manager.h"

// TODO: MAKE THIS LOOK NICER

experience_manager::experience_manager(map *pMap, player *pLeftPlayer, player *pRightPlayer, int *pFrameCount) {
    mMap = pMap;
    mLeftPlayer = pLeftPlayer;
    mLeftPlayerLastHealth = PLAYER_HEALTH_BEGINNING;
    mRightPlayer = pRightPlayer;
    mRightPlayerLastHealth = PLAYER_HEALTH_BEGINNING;
    mFrameCount = pFrameCount;

    mFramesWaited = 0;
}

experience_manager::~experience_manager() = default;

void experience_manager::add_experience(bool *pGameOver)
{
    // Get rewards
    if (mFramesWaited == 1)
    {
        mExperienceRight.reward = torch::tensor(get_player_reward(true));
        if (!SINGLE_PLAYER) mExperienceLeft.reward = torch::tensor(get_player_reward(false));
    }
    else
    {
        mExperienceRight.reward = torch::tensor(get_player_reward(true)) + mExperienceRight.reward;
        if (!SINGLE_PLAYER) mExperienceLeft.reward = torch::tensor(get_player_reward(false)) + mExperienceLeft.reward;
    }

    // Get new action
    if (mFramesWaited == 1)
    {
        mExperienceRight.action = torch::tensor(mRightPlayer->get_last_action());
        if (!SINGLE_PLAYER)
        {
            mExperienceLeft.action = torch::tensor(mLeftPlayer->get_last_action());
        }
    }

    // Set done
    mExperienceRight.done = torch::tensor(*pGameOver);
    if (!SINGLE_PLAYER) mExperienceLeft.done = torch::tensor(*pGameOver);

    // repeat last state if done
    if (*pGameOver && mFramesWaited != AI_SUBSEQUENT_FRAMES) repeat_state_and_done();

    // Add the Observation to last experience's nextState if we have 4 subsequent observations,
    // add experience to experiences and reset mFramesWaited
    if (mFramesWaited == AI_SUBSEQUENT_FRAMES)
    {
        if (mExperiences.size() > 1)
        {
            int tmpLastPlayer = mExperiences.back().belongsTo;
            if (tmpLastPlayer == 0)
            {
                mExperiences.back().nextState = mExperienceLeft.state;
            }
            else
            {
                mExperiences.back().nextState = mExperienceRight.state;
            }

            if (!SINGLE_PLAYER)
            {
                int tmpSecondLastPlayer = mExperiences.end()[-2].belongsTo;
                if (tmpSecondLastPlayer == 0)
                {
                    mExperiences.end()[-2].nextState = mExperienceLeft.state;
                }
                else
                {
                    mExperiences.end()[-2].nextState = mExperienceRight.state;
                }
            }
        }

        mExperiences.push_back(mExperienceRight);
        if (!SINGLE_PLAYER) mExperiences.push_back(mExperienceLeft);

        mFramesWaited = 0;
    }
}

void experience_manager::add_state_to_experience(torch::Tensor *pState, bool pPlayer)
{
    experience *tmpExperience;
    tmpExperience = (!pPlayer) ? &mExperienceLeft : &mExperienceRight;

    if (mFramesWaited > 3)
    {
        std::cout << "More than " + std::to_string(AI_SUBSEQUENT_FRAMES)
                        + " frames waited while adding state to experience.";
    }
    else if (mFramesWaited == 0)
    {
        tmpExperience->state = *pState;
    }
    else
    {
        // Concatenate s.t. we have four subsequent observations
        tmpExperience->state = torch::cat({tmpExperience->state, *pState});
    }
}

torch::Tensor experience_manager::create_cur_obs(bool pPlayer)
{
    std::vector<float> tmpState;

    // Player dependent (12)
    player *myPlayer;
    bullet *myPlayerBullet;
    player *enemyPlayer;
    bullet *enemyPlayerBullet;

    if (!pPlayer)
    {
        myPlayer =  mLeftPlayer;
        myPlayerBullet = mLeftPlayer->get_bullet();
        enemyPlayer = mRightPlayer;
        enemyPlayerBullet = mRightPlayer->get_bullet();
    }
    else
    {
        myPlayer = mRightPlayer;
        myPlayerBullet = mRightPlayer->get_bullet();
        enemyPlayer = mLeftPlayer;
        enemyPlayerBullet = mLeftPlayer->get_bullet();
    }

    tmpState.push_back((float)myPlayer->get_dx() / (float)SCREEN_WIDTH);
    tmpState.push_back((float)myPlayer->get_dy() / (float)SCREEN_HEIGHT);
    tmpState.push_back((float)myPlayer->get_cur_direction());
    tmpState.push_back((float)enemyPlayer->get_dx() / (float)SCREEN_WIDTH);
    tmpState.push_back((float)enemyPlayer->get_dy() / (float)SCREEN_HEIGHT);
    tmpState.push_back((float)enemyPlayer->get_cur_direction());

    if (myPlayerBullet->get_is_active())
    {
        tmpState.push_back((float)myPlayerBullet->get_dx() / (float)SCREEN_WIDTH);
        tmpState.push_back((float)myPlayerBullet->get_dy() / (float)SCREEN_HEIGHT);
        tmpState.push_back((float)myPlayerBullet->get_cur_direction());
    }
    else
    {
        tmpState.push_back(0.0);
        tmpState.push_back(0.0);
        tmpState.push_back(0.5);
    }

    if (enemyPlayerBullet->get_is_active())
    {
        tmpState.push_back((float)enemyPlayerBullet->get_dx() / (float)SCREEN_WIDTH);
        tmpState.push_back((float)enemyPlayerBullet->get_dy() / (float)SCREEN_HEIGHT);
        tmpState.push_back((float)enemyPlayerBullet->get_cur_direction());
    }
    else
    {
        tmpState.push_back(0.0);
        tmpState.push_back(0.0);
        tmpState.push_back(0.5);
    }

    // Player independent (201)
    std::vector<tile> *map = mMap->get_map();

    for(auto & i : *map) {
        tile *tmpTile = &i;
        int tmpIndicator = tmpTile->get_indicator();
        float isMyTile = (tmpIndicator == myPlayer->get_player_indicator()) ? 1.0 : 0.0;
        tmpState.push_back(isMyTile);
    }

    tmpState.push_back((float)(*mFrameCount/60)/60.0);

    return torch::tensor(tmpState);
}

torch::Tensor experience_manager::get_cur_state(bool pPlayer)
{
    // Just for safety reason
    if (mFramesWaited == AI_SUBSEQUENT_FRAMES)
    {
        torch::Tensor tmpState;
        tmpState = (!pPlayer) ? mExperienceLeft.state : mExperienceRight.state;
        return tmpState;
    }
    else
    {
        std::cout << "State does not encapsulate all " + std::to_string(AI_SUBSEQUENT_FRAMES) +
            " frames yet";
        exit(1);
    }
}

std::vector<experience> experience_manager::get_experiences()
{
    return mExperiences;
}

int experience_manager::get_frames_waited()
{
    return mFramesWaited;
}

int experience_manager::get_player_reward(bool pPlayer)
{
    int leftPlayerHealth = mLeftPlayer->get_health();
    int rightPlayerHealth = mRightPlayer->get_health();

    int leftPlayerReward = leftPlayerHealth - mLeftPlayerLastHealth;
    int rightPlayerReward = rightPlayerHealth - mRightPlayerLastHealth;

    mLeftPlayerLastHealth = leftPlayerHealth;
    mRightPlayerLastHealth = rightPlayerHealth;

    return (!pPlayer) ? leftPlayerReward : rightPlayerReward;
}

void experience_manager::new_experience()
{
    torch::Tensor stateRightTmp = create_cur_obs(true);
    add_state_to_experience(&stateRightTmp, true);
    mExperienceRight.belongsTo = 1;

    if (!SINGLE_PLAYER)
    {
        torch::Tensor stateLeftTmp = create_cur_obs(false);
        add_state_to_experience(&stateLeftTmp, false);
        mExperienceLeft.belongsTo = 0;
    }

    // Add zeros tensor for last experience (s.t. its always defined)
    torch::Tensor tmpNextStates = torch::zeros({INPUT_SIZE});
    mExperienceRight.nextState = tmpNextStates;
    if (!SINGLE_PLAYER) mExperienceLeft.nextState = tmpNextStates;

    // Increment frames s.t. we take new action every 4 frames
    // and concatenate 4 subsequent observations to one input observation
    mFramesWaited++;
}

void experience_manager::repeat_state_and_done()
{
    int repeats = AI_SUBSEQUENT_FRAMES - mFramesWaited;
    int stateSize = INPUT_SIZE/AI_SUBSEQUENT_FRAMES;
    int startIndexLastState = (mFramesWaited * stateSize) - stateSize;

    torch::Tensor lastStateRight = mExperienceRight.state.index({ torch::indexing::Slice(startIndexLastState, torch::indexing::None) });
    torch::Tensor lastStateLeft;
    if (!SINGLE_PLAYER)
    {
        lastStateLeft = mExperienceLeft.state.index({ torch::indexing::Slice(startIndexLastState, torch::indexing::None) });
    }

    for (int i = 0; i < repeats; i++)
    {
        add_state_to_experience(&lastStateRight, true);

        if (!SINGLE_PLAYER)
        {
            add_state_to_experience(&lastStateLeft, false);
        }
    }
}