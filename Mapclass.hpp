#pragma once
#include "gameloop.hpp"

class Map {
public:
    Map(int arr[6][13]);
    ~Map();

    void LoadMap();
    void DrawMap();

private:
    SDL_Rect src, dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;


    int map[6][13];
};