#pragma once
// #include "gameloop.h"
#include "texturemanager.h"
#include <string>

class Map {
public:
    Map();
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    // void DrawMap();

private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
    // SDL_Rect src, dest;
    // SDL_Texture* dirt;
    // SDL_Texture* grass;
    // SDL_Texture* water;


    // int map[6][13];
};