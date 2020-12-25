// #pragma once

#ifndef _BACKGROUNDCOMPONENT_H
#define _BACKGROUNDCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "Components.h"
#include <map>
using namespace std;

class BackGroundComponent : public Component
{
public:
    SDL_Texture* texture;
    SDL_Rect srcR, destR;
    map<int, const char*> MIKUGIF;
 
    // static int num;
    // static int order;

    BackGroundComponent()
    {
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 720;
        srcR.w = 1280;
        destR.x = 0;
        destR.y = 0;
        destR.h = 720;
        destR.w = 1280;
        // num = 0;
        // order = 0;
        MIKUGIF[1]  = "../img/miku/0001.bmp";
        MIKUGIF[2]  = "../img/miku/0002.bmp";
        MIKUGIF[3]  = "../img/miku/0003.bmp";
        MIKUGIF[4]  = "../img/miku/0004.bmp";
        MIKUGIF[5]  = "../img/miku/0005.bmp";
        MIKUGIF[6]  = "../img/miku/0006.bmp";
        MIKUGIF[7]  = "../img/miku/0007.bmp";
        MIKUGIF[8]  = "../img/miku/0008.bmp";
        MIKUGIF[9]  = "../img/miku/0009.bmp";
        MIKUGIF[10] = "../img/miku/0010.bmp";
        MIKUGIF[11] = "../img/miku/0011.bmp";
        MIKUGIF[12] = "../img/miku/0012.bmp";
        MIKUGIF[13] = "../img/miku/0013.bmp";
        MIKUGIF[14] = "../img/miku/0014.bmp";
        MIKUGIF[15] = "../img/miku/0015.bmp";
        MIKUGIF[16] = "../img/miku/0016.bmp";
        MIKUGIF[17] = "../img/miku/0017.bmp";
        MIKUGIF[18] = "../img/miku/0018.bmp";
        MIKUGIF[19] = "../img/miku/0019.bmp";
        MIKUGIF[20] = "../img/miku/0020.bmp";
        MIKUGIF[21] = "../img/miku/0021.bmp";
        MIKUGIF[22] = "../img/miku/0022.bmp";
        MIKUGIF[23] = "../img/miku/0023.bmp";
        MIKUGIF[24] = "../img/miku/0024.bmp";
        MIKUGIF[25] = "../img/miku/0025.bmp";
        MIKUGIF[26] = "../img/miku/0026.bmp";
        MIKUGIF[27] = "../img/miku/0027.bmp";
        MIKUGIF[28] = "../img/miku/0028.bmp";
        MIKUGIF[29] = "../img/miku/0029.bmp";
        MIKUGIF[30] = "../img/miku/0030.bmp";
        MIKUGIF[31] = "../img/miku/0031.bmp";
        MIKUGIF[32] = "../img/miku/0032.bmp";
        MIKUGIF[33] = "../img/miku/0033.bmp";
        MIKUGIF[34] = "../img/miku/0034.bmp";
        MIKUGIF[35] = "../img/miku/0035.bmp";
        MIKUGIF[36] = "../img/miku/0036.bmp";
        MIKUGIF[37] = "../img/miku/0037.bmp";
        MIKUGIF[38] = "../img/miku/0038.bmp";
        MIKUGIF[39] = "../img/miku/0039.bmp";
        MIKUGIF[40] = "../img/miku/0040.bmp";
        MIKUGIF[41] = "../img/miku/0041.bmp";
        MIKUGIF[42] = "../img/miku/0042.bmp";
        MIKUGIF[43] = "../img/miku/0043.bmp";
        MIKUGIF[44] = "../img/miku/0044.bmp";
        MIKUGIF[45] = "../img/miku/0045.bmp";
        MIKUGIF[46] = "../img/miku/0046.bmp";
        MIKUGIF[47] = "../img/miku/0047.bmp";
        MIKUGIF[48] = "../img/miku/0048.bmp";
        MIKUGIF[49] = "../img/miku/0049.bmp";
        MIKUGIF[50] = "../img/miku/0050.bmp";
        MIKUGIF[51] = "../img/miku/0051.bmp";
        MIKUGIF[52] = "../img/miku/0052.bmp";
        MIKUGIF[53] = "../img/miku/0053.bmp";
        MIKUGIF[54] = "../img/miku/0054.bmp";
    }
    ~BackGroundComponent()
    {

    }

    void init() override
    {
        // num = 0;
        texture = TextureManager::LoadTexture(MIKUGIF[1]);
    }

    void update() override
    {
        // static int num = 0;
        // static int i = 1;
        // num++;
        // if (num % 3 == 0) 
        // {
        //     texture = TextureManager::LoadTexture(MIKUGIF[i]);
        // }
        // if (num > 200) num = 0;
        // if (i >= 54) i = 1;
    }

    void draw() override
    {
        // SDL_RenderCopyEx(Game::renderer, texture, &srcR, &destR, NULL, NULL, SDL_FLIP_NONE);
        // SDL_RenderPresent(Game::renderer);
        // SDL_DestroyTexture(texture);
        static int num = 0;
        static int i = 1;
        num++;
        i++;
        //texture = TextureManager::LoadTexture(MIKUGIF[i]);
        //texture = TextureManager::LoadTexture(MIKUGIF[1]);
        // SDL_Surface* tmpSurface = SDL_LoadBMP(MIKUGIF[i]);
        // SDL_Surface* 
        // texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        // SDL_FreeSurface(tmpSurface);
        // cout << i << endl;
        // if (num % 1 == 0) 
        // {
            
        // }
        SDL_Surface* tmpSurface;
    // static int i = 1;
    SDL_RenderClear(Game::renderer);
    cout << "i = " << i<<endl;
if (i == 1)
        tmpSurface = SDL_LoadBMP("./img/miku/0001.bmp");
if (i == 2)
        tmpSurface = SDL_LoadBMP("./img/miku/0002.bmp");
if (i == 3)
        tmpSurface = SDL_LoadBMP("./img/miku/0003.bmp");
if (i == 4)
         tmpSurface = SDL_LoadBMP("./img/miku/0004.bmp");
if (i == 5)
         tmpSurface = SDL_LoadBMP("./img/miku/0005.bmp");
if (i == 6)
         tmpSurface = SDL_LoadBMP("./img/miku/0006.bmp");
if (i == 7)
         tmpSurface = SDL_LoadBMP("./img/miku/0007.bmp");
if (i == 8)
         tmpSurface = SDL_LoadBMP("./img/miku/0008.bmp");
if (i == 9)
         tmpSurface = SDL_LoadBMP("./img/miku/0009.bmp");
if (i == 10)
         tmpSurface = SDL_LoadBMP("./img/miku/0010.bmp");
if (i == 11)
         tmpSurface = SDL_LoadBMP("./img/miku/0011.bmp");
if (i == 12)
         tmpSurface = SDL_LoadBMP("./img/miku/0012.bmp");
if (i == 13)
         tmpSurface = SDL_LoadBMP("./img/miku/0013.bmp");
if (i == 14)
         tmpSurface = SDL_LoadBMP("./img/miku/0014.bmp");
if (i == 15)
         tmpSurface = SDL_LoadBMP("./img/miku/0015.bmp");
if (i == 16)
         tmpSurface = SDL_LoadBMP("./img/miku/0016.bmp");
if (i == 17)
         tmpSurface = SDL_LoadBMP("./img/miku/0017.bmp");
if (i == 18)
         tmpSurface = SDL_LoadBMP("./img/miku/0018.bmp");
if (i == 19)
         tmpSurface = SDL_LoadBMP("./img/miku/0019.bmp");
if (i == 20)
         tmpSurface = SDL_LoadBMP("./img/miku/0020.bmp");
if (i == 21)
         tmpSurface = SDL_LoadBMP("./img/miku/0021.bmp");
if (i == 22)
         tmpSurface = SDL_LoadBMP("./img/miku/0022.bmp");
if (i == 23)
         tmpSurface = SDL_LoadBMP("./img/miku/0023.bmp");
if (i == 24)
         tmpSurface = SDL_LoadBMP("./img/miku/0024.bmp");
if (i == 25)
         tmpSurface = SDL_LoadBMP("./img/miku/0025.bmp");
if (i == 26)
         tmpSurface = SDL_LoadBMP("./img/miku/0026.bmp");
if (i == 27)
         tmpSurface = SDL_LoadBMP("./img/miku/0027.bmp");
if (i == 28)
         tmpSurface = SDL_LoadBMP("./img/miku/0028.bmp");
if (i == 29)
         tmpSurface = SDL_LoadBMP("./img/miku/0029.bmp");
if (i == 30)
         tmpSurface = SDL_LoadBMP("./img/miku/0030.bmp");
if (i == 31)
         tmpSurface = SDL_LoadBMP("./img/miku/0031.bmp");
if (i == 32)
         tmpSurface = SDL_LoadBMP("./img/miku/0032.bmp");
if (i == 33)
         tmpSurface = SDL_LoadBMP("./img/miku/0033.bmp");
if (i == 34)
         tmpSurface = SDL_LoadBMP("./img/miku/0034.bmp");
if (i == 35)
         tmpSurface = SDL_LoadBMP("./img/miku/0035.bmp");
if (i == 36)
         tmpSurface = SDL_LoadBMP("./img/miku/0036.bmp");
if (i == 37)
         tmpSurface = SDL_LoadBMP("./img/miku/0037.bmp");
if (i == 38)
         tmpSurface = SDL_LoadBMP("./img/miku/0038.bmp");
if (i == 39)
         tmpSurface = SDL_LoadBMP("./img/miku/0039.bmp");
if (i == 40)
         tmpSurface = SDL_LoadBMP("./img/miku/0040.bmp");
if (i == 41)
         tmpSurface = SDL_LoadBMP("./img/miku/0041.bmp");
if (i == 42)
         tmpSurface = SDL_LoadBMP("./img/miku/0042.bmp");
if (i == 43)
         tmpSurface = SDL_LoadBMP("./img/miku/0043.bmp");
if (i == 44)
         tmpSurface = SDL_LoadBMP("./img/miku/0044.bmp");
if (i == 45)
         tmpSurface = SDL_LoadBMP("./img/miku/0045.bmp");
if (i == 46)
         tmpSurface = SDL_LoadBMP("./img/miku/0046.bmp");
if (i == 47)
         tmpSurface = SDL_LoadBMP("./img/miku/0047.bmp");
if (i == 48)
         tmpSurface = SDL_LoadBMP("./img/miku/0048.bmp");
if (i == 49)
         tmpSurface = SDL_LoadBMP("./img/miku/0049.bmp");
if (i == 50)
         tmpSurface = SDL_LoadBMP("./img/miku/0050.bmp");
if (i == 51)
         tmpSurface = SDL_LoadBMP("./img/miku/0051.bmp");
if (i == 52)
         tmpSurface = SDL_LoadBMP("./img/miku/0052.bmp");
if (i == 53)
         tmpSurface = SDL_LoadBMP("./img/miku/0053.bmp");
if (i == 54)
         tmpSurface = SDL_LoadBMP("./img/miku/0054.bmp");
    i++;
    texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
         SDL_FreeSurface(tmpSurface);
             SDL_Delay(120);

        //  SDL_Delay(30);
    if (i > 54) i = 1;
        if (num > 200) num = 0;
        cout << "draw - back" << endl;
        //TextureManager::Draw(texture, srcR, destR, SDL_FLIP_NONE);
        SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);
        SDL_RenderPresent(Game::renderer);
        SDL_DestroyTexture(texture);
    }
};

#endif