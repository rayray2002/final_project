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

    GameBoardComponent(int xpos, int ypos, int h, int w)
    {
        destR.x = xpos;
        destR.y = ypos;
        destR.h = h;
        destR.w = w;
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 1000;
        srcR.w = 1000;
    }
    ~GameBoardComponent()
    {
    }

    void init() override
    {
    }

    void update() override
    {
        static int x;
        static int y;
        x = Game::event.motion.x;
        y = Game::event.motion.y;
    }

    void draw() override
    {

        // cout << "here" << endl;
        // texture = TextureManager::LoadTexture("../img/kirito1.bmp");

        SDL_Surface *tmpSurface = SDL_LoadBMP("./img/kirito1.bmp");
        texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_FreeSurface(tmpSurface);
        TextureManager::Draw(texture, srcR, destR);
        // SDL_RenderCopy(Game::renderer, texture, NULL, &destR);
        // SDL_DestroyTexture(texture);
        // Game::LinkStart("Game Initailizing...", 1000, 100, 600);
        // cout << "ha ha" << endl;
    }
};

#endif