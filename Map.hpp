#include "Mapclass.hpp"
#include "texturemanager.hpp"

int Lv1[6][13] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
}

Map::Map() {
    dirt = TextureManager::LoadTexture("./img/miku.bmp");
    grass = TextureManager::LoadTexture("./img/miku.bmp");
    water = TextureManager::LoadTexture("./img/miku.bmp");

    LoadMap(Lv1);

    src.x = src.y = 0;
}


void Map::LoadMap(int arr[6][13]) {
    for (int row = 0; row < 6; row++) {
        for (int colume = 0; colume < 13; colume++) {
            map[row][colume] = arr[row][colume];
        }
    }
}

void Map::DrawMap() {
    int type = 0;
    for (int row = 0; row < 6; row++) {
        for (int colume = 0; colume < 13; colume++) {
            type = map[row][colume];

            switch (type) {
            case 0:
                TextureManager::Draw(water, src, dest);
            case 1:

            case 2:

            default:

            }
        }
    }
}