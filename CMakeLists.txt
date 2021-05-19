cmake_minimum_required(VERSION 3.17)
project(equilibrium)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH /usr/local/lib/libtorch)

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${equilibrium_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR})

add_executable(equilibrium main.cpp src/game/game.cpp src/game/game.h src/game/resource_manager.cpp
        src/game/resource_manager.h src/game/timer.cpp src/game/timer.h src/game/game_config.h src/game/fps_manager.cpp
        src/game/fps_manager.h src/game/input_manager.cpp src/game/input_manager.h src/game/draw.cpp src/game/draw.h
        src/game/object.cpp src/game/object.h src/game/player.cpp src/game/player.h src/game/shadow.h
        src/game/bullet.cpp src/game/bullet.h src/game/collision_detection.cpp src/game/collision_detection.h
        src/game/map.cpp src/game/map.h src/game/animation_manager.cpp src/game/animation_manager.h
        src/train/train.cpp src/train/train.h src/train/dqn_manager.cpp src/train/dqn_manager.h src/train/train_utils.cpp
        src/train/train_utils.h src/game/tile.cpp src/game/tile.h src/game/shadow.cpp src/game/shadow.h
        src/train/experience_manager.cpp src/train/experience_manager.h src/train/train_config.h src/train/experience.h src/train/dqn.h)

target_link_libraries(equilibrium
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${TORCH_LIBRARIES})