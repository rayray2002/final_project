cmake_minimum_required(VERSION 3.16.3)
project(1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

message(${CMAKE_SOURCE_DIR})

add_executable(main main.cpp ECS/ECS.cpp Game.cpp TextureManager.cpp Vector2D.cpp GameBoard.cpp ECS/GameBoardComponent.cpp ECS/DoubleGameBoardComponent.cpp ECS/MenuComponent.cpp)
#  add_executable(menu ECS/MenuComponent.cpp)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(main ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
#  target_link_libraries(menu ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
