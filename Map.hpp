#include "Mapclass.hpp"
#include "gameloop.h"
#include <fstream>
using namespace std;

extern Manager manager;
//#include "texturemanager.hpp"

// int Lv1[13][6] = {
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0},
// };

<<<<<<< HEAD
Map::Map(const char* mfp, int ms, int ts) : mapFilePath(mfp), mapScale(ms), tileSize(ts) 
=======
Map::Map(string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) 
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
{
    scaledSize = ms * ts;
    // dirt = TextureManager::LoadTexture("./img/miku.bmp");
    // grass = TextureManager::LoadTexture("./img/miku.bmp");
    // water = TextureManager::LoadTexture("./img/miku.bmp");

    // LoadMap(Lv1);

    // src.x = src.y = 0;
    // src.h = dest.h = 80;
    // src.w = dest.w = 80;

    // dest.x = dest.y = 0;
}

Map::~Map() {
    // SDL_DestroyTexture(grass);
    // SDL_DestroyTexture(dirt);
    // SDL_DestroyTexture(water);
}

<<<<<<< HEAD
void Map::LoadMap(std::string path, int sizeX, int sizeY) {
=======
void Map::LoadMap(std::string path, int sizeX, int sizeY) 
{
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    char c;
    fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

<<<<<<< HEAD
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
=======
    for (int y = 0; y < sizeY; y++) 
    {
        for (int x = 0; x < sizeX; x++) 
        {
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
            mapFile.get(c);
            srcY = atoi(&c) * tileSize;
            mapFile.get(c);
            srcX = atoi(&c) * tileSize;
            AddTile(srcX, srcY, x * scaledSize, y * scaledSize);
            mapFile.ignore();
        }
    }

    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            mapFile.get(c);
            if (c == '1')
            {
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("miku", x * scaledSize, y * scaledSize, scaledSize);
<<<<<<< HEAD
                mapFile.ignore();
=======
                tcol.addGroup(Game::groupColliders);
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
            }
            mapFile.ignore();
        }
    }

    mapFile.close();
    // for (int row = 0; row < 6; row++) {
    //     for (int colume = 0; colume < 13; colume++) {
    //         map[row][colume] = arr[row][colume];
    //     }
    // }
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos) {

    auto& tile(manager.addEntity());
<<<<<<< HEAD
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, mapFilePath);
=======
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
>>>>>>> b8c33cbae185a8097c244cebea181943c6ecc4cb
    tile.addGroup(Game::groupMap);

}


// void Map::DrawMap() {
//     int type = 0;
//     for (int row = 0; row < 6; row++) {
//         for (int colume = 0; colume < 13; colume++) {
//             type = map[row][colume];

//             dest.x = colume * 32;
//             dest.y = row * 32;

//             switch (type) {
//             case 0:
//                 TextureManager::Draw(water, src, dest);
//                 break;
//             case 1:
//                 TextureManager::Draw(dirt, src, dest);
//                 break;
//             case 2:
//                 TextureManager::Draw(grass, src, dest);
//                 break;
//             default:
//                 break;
//             }
//         }
//     }
// }