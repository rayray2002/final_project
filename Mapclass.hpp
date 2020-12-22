#pragma once
// #include "gameloop.h"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
<<<<<<< HEAD
#include "texturemanager.h"
=======
#include "texturemanager.hpp"
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
#include <string>

class Map {
public:
<<<<<<< HEAD
    Map(const char* mfp, int ms, int ts);
=======
    Map(string tID, int ms, int ts);
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    ~Map();

    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY, int xpos, int ypos);

    // void DrawMap();

private:
<<<<<<< HEAD
    const char* mapFilePath;
=======
    // const char* mapFilePath;
    string texID;
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    int mapScale;
    int tileSize;
    int scaledSize;
    // SDL_Rect src, dest;
    // SDL_Texture* dirt;
    // SDL_Texture* grass;
    // SDL_Texture* water;


    // int map[6][13];
};