// #pragma once

#ifndef _MAP_H
#define _MAP_H
#include <SDL.h>
#include <string>
using namespace std;
// #include "Game.h"

class Map {
public:
    Map(const char* mfp, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    // void DrawMap();

private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;

    const char* mapFilePath;
    // int mapScale;
    // int tileSize;
    // int scaledSize;

    // // SDL_Rect src, dest;
    // // SDL_Texture* dirt;
    // // SDL_Texture* grass;
    // // SDL_Texture* water;


    // // int map[6][13];
};

#endif