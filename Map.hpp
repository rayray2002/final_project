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

Map::Map(string tID, int ms, int ts) : texID(tID), mapScale(ms), tileSize(ts) 
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

void Map::LoadMap(std::string path, int sizeX, int sizeY) 
{
    char c;
    fstream mapFile;
    mapFile.open(path);

    int srcX, srcY;

    for (int y = 0; y < sizeY; y++) 
    {
        for (int x = 0; x < sizeX; x++) 
        {
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
                tcol.addGroup(Game::groupColliders);
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
    tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, tileSize, mapScale, texID);
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