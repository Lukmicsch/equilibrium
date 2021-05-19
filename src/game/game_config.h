//
// Created by Lukas Schmidt on 3/1/21.
//

#ifndef EQUILIBRIUM_GAME_CONFIG_H
#define EQUILIBRIUM_GAME_CONFIG_H

// Screen
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;

// Map
const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;
const int LEFT_PLAYER_INDICATOR = 0;
const int RIGHT_PLAYER_INDICATOR = 1;

// FPS
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
const int TRAIN_FRAME_CAP = SCREEN_FPS * 60;

// Sprites
const int TILE_SIZE = 50;
const int PLANE_WIDTH = 42;
const int PLANE_HEIGHT = 51;
const int BULLET_WIDTH = 90;
const int BULLET_HEIGHT = 3;

// Animations
const int IDOL_SPEED = 1;
const int IDOL_AMPLITUDE = 50;

// Player
const int PLAYER_MAX_HEALTH = 200;
const int PLAYER_HEALTH_BEGINNING = 100;
const int LEFT_PLAYER_START_X = 100;
const int LEFT_PLAYER_START_Y = (SCREEN_HEIGHT/2) - (PLANE_HEIGHT);
const int RIGHT_PLAYER_START_X = SCREEN_WIDTH - (LEFT_PLAYER_START_X + PLANE_WIDTH);
const int RIGHT_PLAYER_START_Y = (SCREEN_HEIGHT/2) - (PLANE_HEIGHT);
const int PLAYER_SPEED = 9;
const int SHADOW_OFFSET = 29;

// AI
const int AI_SUBSEQUENT_FRAMES = 4;

// Bullet
const int BULLET_SPEED = 40;
const int DMG = 10;

// Text
const int HEADING_X = SCREEN_WIDTH/2 - 100;
const int HEADING_Y = 50;
const int SUB_HEADING_X = SCREEN_WIDTH/2 - 185;
const int SUB_HEADING_Y =  100;
const int GAME_OVER_X = SCREEN_WIDTH/2 - 75;
const int GAME_OVER_Y = 70;
const int SUB_GAME_OVER_X = SCREEN_WIDTH/2 - 115;
const int SUB_GAME_OVER_Y = 100;
const int COUNTER_LEFT_X = 50;
const int COUNTER_LEFT_Y = 50;
const int COUNTER_RIGHT_X = SCREEN_WIDTH - 100;
const int COUNTER_RIGHT_Y = 50;
const int TIME_X_ONE = SCREEN_WIDTH/2 - 7;
const int TIME_X_TWO = SCREEN_WIDTH/2 - 17;
const int TIME_Y = 20;

// Game state variables
const bool TRAIN = false;
const bool SINGLE_PLAYER = false;
const bool RENDER = true;

#endif //EQUILIBRIUM_GAME_CONFIG_H