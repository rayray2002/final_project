#pragma once
// #include "gameloop.h"
#include "texturemanager.h"

class Map {
public:
    Map();
    ~Map();

    static void LoadMap(std::string, int sizeX, int sizeY);
    // void DrawMap();

private:
    // SDL_Rect src, dest;
    // SDL_Texture* dirt;
    // SDL_Texture* grass;
    // SDL_Texture* water;


    // int map[6][13];
};