cmake_minimum_required(VERSION 3.17)
project(final_project)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

message(${CMAKE_SOURCE_DIR})

add_executable(final_project main.cpp SDL_bgi.cpp)
add_executable(Puyo_test Puyo_test.cpp Puyo.cpp)
add_executable(show_board show_board.cpp)

#set(SDL2_LIBRARY "/Library/frameworks/SDL2.framework")
#set(SDL2_IMAGE_LIBRARY "/Library/frameworks/SDL2_image.framework")
#set(SDL2_TTF_LIBRARY "/Library/frameworks/SDL2_ttf.framework")
#set(SDL2_MIXER_LIBRARY "/Library/frameworks/SDL2_mixer.framework")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${SDL2_TTF_INCLUDE_DIR})
include_directories(${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(final_project ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})
target_link_libraries(show_board ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${SDL2_MIXER_LIBRARY})

