//
// Created by Lukas Schmidt on 2/28/21.
//

#include "game.h"

game::game(std::string pCwdString) : mResourceManager(std::move(pCwdString)), mDraw(&mResourceManager),
                                     mExpManager(&mMap, &mLeftPlayer, &mRightPlayer, &mFrameCount),
                                     mInputManager(&mLeftPlayer, &mRightPlayer, &mExpManager)
{
    if (!mResourceManager.init())
    {
        std::cout << "Failed to initialize resource manager!\n";
    }
    else
    {
        if (!mResourceManager.load_media())
        {
            std::cout << "Failed to load media\n";
        }
        else
        {
            // SDL utils
            mRen = mResourceManager.get_ren();
            mFont = mResourceManager.get_font();

            // Init objects
            mMap.populate_map(&mResourceManager);

            mLeftPlayer.init(&mResourceManager, "leftPlayer", 2, PLANE_WIDTH, PLANE_HEIGHT,
                             0, LEFT_PLAYER_START_X, LEFT_PLAYER_START_Y);
            mLeftPlayer.init_self(&mResourceManager, true,
                                  PLAYER_HEALTH_BEGINNING, PLAYER_MAX_HEALTH, LEFT_PLAYER_INDICATOR);

            mRightPlayer.init(&mResourceManager, "rightPlayer", 2, PLANE_WIDTH, PLANE_HEIGHT,
                             1, RIGHT_PLAYER_START_X, RIGHT_PLAYER_START_Y);
            mRightPlayer.init_self(&mResourceManager, false,
                                   PLAYER_HEALTH_BEGINNING, PLAYER_MAX_HEALTH, RIGHT_PLAYER_INDICATOR);

            // After everything has been initialized, free the surfaces
            mResourceManager.free_media();

            mFrameCount = 0;
        }
    }
}

game::~game() = default;

void game::game_loop()
{
    bool quit = false;
    bool started = false;
    bool gameOver = false;
    int winner;

    if (TRAIN) started = true;

    if (SINGLE_PLAYER)
    {
        mInputManager.init_ai("None", CHECKPOINT, 0.0);
    }

    while(!quit)
    {
        if (TRAIN || !TRAIN && SINGLE_PLAYER)
        {
            // Creates experience (including observations) for both or only enemy player
            mExpManager.new_experience();
        }
        else if (!TRAIN)
        {
            mFpsManager.start_cap_timer();
        }

        process_input(&quit, &gameOver, &started);

        if (RENDER) render(&started, &gameOver, &winner);

        if (!gameOver)
        {
            update();
            is_done(&gameOver, &winner);
        }

        if (!TRAIN)
        {
            mFpsManager.check_and_cap_fps();
            if (SINGLE_PLAYER) mExpManager.add_experience(&gameOver);
        }
        else
        {
            mExpManager.add_experience(&gameOver);
            if (gameOver) quit = true;
        }

        if (!gameOver) mFrameCount++;
    }

    // Quit and free
    mResourceManager.close();
}

std::vector<experience> game::game_loop_train(double pEpsilon)
{
    mInputManager.init_ai(CHECKPOINT, CHECKPOINT, pEpsilon);
    game_loop();
    return mExpManager.get_experiences();
}

int game::game_loop_eval()
{
    mInputManager.init_ai(APPRENTICE_CHECKPOINT, CHECKPOINT, 0.0);
    game_loop();
    // Left player is apprentice and therefore used in our metric for avg points over current best player
    return mLeftPlayer.get_health();
}

void game::is_done(bool *pGameOver, int *pWinner)
{
    if (mLeftPlayer.get_health() < 1 || mRightPlayer.get_health() < 1)
    {
        *pGameOver = true;
        *pWinner = int (mLeftPlayer.get_health() < 1); // Get indicator 0 - left, 1 - right
        mMap.set_winner_tiles(*pWinner);
        mTimer.stop();
    }
    else if (mTimer.get_seconds() >= 60 || mFrameCount == TRAIN_FRAME_CAP)
    {
        *pGameOver = true;
        *pWinner = int (mRightPlayer.get_health() > mLeftPlayer.get_health());
        mMap.set_winner_tiles(*pWinner);
        mTimer.stop();
    }
}

void game::process_input(bool *pQuit, bool *pGameOver, bool *pStarted)
{
    if (!TRAIN)
    {
        mInputManager.input_human(pQuit, pStarted, &mTimer);
    }
    if (*pStarted && !*pGameOver && (TRAIN || SINGLE_PLAYER))
    {
        mInputManager.input_ai();
    }
}

void game::render(bool *pStarted, bool *pGameOver, int *pWinner) {
    SDL_RenderClear(mRen);

    // Objects
    mDraw.draw_map(mMap);

    bullet *leftBullet = mLeftPlayer.get_bullet();
    if (leftBullet->get_is_active()) mDraw.draw_object(leftBullet);
    bullet *rightBullet = mRightPlayer.get_bullet();
    if (rightBullet->get_is_active()) mDraw.draw_object(rightBullet);

    mDraw.draw_object(mLeftPlayer.get_shadow());
    mDraw.draw_object(&mLeftPlayer);
    mDraw.draw_object(mRightPlayer.get_shadow());
    mDraw.draw_object(&mRightPlayer);

    // Text
    if (*pStarted == false) {
        mDraw.draw_font("Equilibrium", HEADING_X, HEADING_Y, 255, 255, 255);
        mDraw.draw_font("Move To Start The Game", SUB_HEADING_X, SUB_HEADING_Y, 255, 255, 255);
    } else {
        int leftHealthInt = mLeftPlayer.get_health();
        std::string leftHealth = std::to_string(leftHealthInt);
        int rightHealthInt = mRightPlayer.get_health();
        std::string rightHealth = std::to_string(rightHealthInt);
        mDraw.draw_font(leftHealth.c_str(), COUNTER_LEFT_X, COUNTER_LEFT_Y, 255, 255, 255);
        mDraw.draw_font(rightHealth.c_str(), COUNTER_RIGHT_X, COUNTER_RIGHT_Y, 255, 255, 255);

        int time;
        if (TRAIN || SINGLE_PLAYER)
        {
            time = mFrameCount / 60;
        }
        else
        {
            time = mTimer.get_seconds();
        }
        int timeX = TIME_X_TWO;
        if (time < 10) timeX = TIME_X_ONE;
        mDraw.draw_font(std::to_string(time).c_str(), timeX, TIME_Y, 255,255, 255);
    }

    if (*pGameOver)
    {
        mDraw.draw_font("Game Over", GAME_OVER_X, GAME_OVER_Y, 255, 255, 255);
        std::string winnerString = "Player " + std::to_string(*pWinner + 1) + " wins!";
        mDraw.draw_font(winnerString.c_str(), SUB_GAME_OVER_X, SUB_GAME_OVER_Y, 255, 255, 255);
    }

    // Send the buffer that's in the renderer to the screen to draw it out
    SDL_RenderPresent(mRen);
}

void game::update()
{
    mLeftPlayer.update();
    mRightPlayer.update();
    mCollisionDetection.check_for_collision(&mMap, &mLeftPlayer, &mRightPlayer);
}