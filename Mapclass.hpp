#pragma once
// #include "gameloop.h"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include "texturemanager.hpp"
#include <string>

class Map {
public:
    Map(string tID, int ms, int ts);
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    // void DrawMap();

private:
    // const char* mapFilePath;
    string texID;
    int mapScale;
    int tileSize;
    int scaledSize;
    // SDL_Rect src, dest;
    // SDL_Texture* dirt;
    // SDL_Texture* grass;
    // SDL_Texture* water;


    // int map[6][13];
};