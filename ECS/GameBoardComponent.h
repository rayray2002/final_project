// #pragma once

#ifndef _GAMEBOARDCOMPONENT_H
#define _GAMEBOARDCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "Components.h"
#include "../TextureManager.h"
#include "ECS.h"
#include <map>
using namespace std;

class GameBoardComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect destR, srcR;
    Vector2D speed;

    GameBoardComponent(int xpos, int ypos)
    {
        destR.x = xpos;
        destR.y = ypos;
        destR.h = 30;
        destR.w = 30;

        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 1000;
        srcR.w = 1000;

        speed.x = 0;
        speed.y = 50;
    }
    ~GameBoardComponent()
    {
    }

    void init() override
    {
    }

    void update() override
    {
        static int num = 0;
        if (num == 60)
        {
            destR.y += 30;
        }
        if (num == 60)
            num = 0;
        num++;
    }

    void draw() override
    {
        SDL_Surface *tmpSurface = SDL_LoadBMP("./img/sample_red.bmp");
        texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_FreeSurface(tmpSurface);
        TextureManager::Draw(texture, srcR, destR);
    }
};

#endif