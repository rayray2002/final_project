#include "Mapclass.hpp"
#include "gameloop.h"
#include <fstream>
using namespace std;
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

Map::Map() {
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

void Map::LoadMap(std::string, int sizeX, int sizeY) {
    char tile;
    fstream mapFile;
    mapFile.open(path);

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            mapFile.get(tile);
            Game::AddTile(atoi(&tile), x * 32, y * 32);
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