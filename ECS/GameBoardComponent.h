// #pragma once

#ifndef _GAMEBOARDCOMPONENT_H
#define _GAMEBOARDCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "Components.h"
#include "../TextureManager.h"
#include "ECS.h"
#include <deque>
#include <ctime>
#include <map>
using namespace std;

class GameBoardComponent : public Component
{
private:
    char map[13][6];

public:
    struct unit
    {
        SDL_Texture *texture;
        SDL_Rect srcR, destR;
        Vector2D speed;
        Vector2D bspeed;
        int color;
        bool isMoving = true;
        bool isActive = true;
    };
    deque<unit> blocks;

    GameBoardComponent(int xpos, int ypos, int color)
    {
    }
    ~GameBoardComponent()
    {
    }
    void setInitialMap()
    {
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                map[i][j] = '0';
            }
        }
    }

    void init() override
    {
        unit a;
        static int w = 50;

        a.destR.x = 100;
        a.destR.y = 50;
        a.destR.h = w;
        a.destR.w = w;

        a.srcR.x = 0;
        a.srcR.y = 0;
        a.srcR.h = 1000;
        a.srcR.w = 1000;

        srand(time(0));
        a.color = rand() % 4 + 1;

        a.isActive = true;
        a.isMoving = true;

        a.speed.x = w;
        a.speed.y = w;

        a.bspeed.x = w;
        a.bspeed.y = w;

        blocks.push_back(a);
    }

    void update() override
    {
        static int num = 0;
        for (auto &a : blocks)
        {
            map[(a.destR.y - 50) / 50][(a.destR.x - 50) / 50] = a.color + '0';
            if (a.speed.y == 0)
            {
                a.isMoving = false;
            }
            if (num % 10 == 0 && a.isMoving)
            {
                if (Game::event.type == SDL_KEYDOWN)
                    switch (Game::event.key.keysym.sym)
                    {
                    case SDLK_LEFT:
                        if (a.destR.x >= 100 && map[(a.destR.y - 50) / 50][(a.destR.x - 50) / 50 - 1] == '0')
                            a.destR.x -= a.bspeed.y;
                        break;
                    case SDLK_RIGHT:
                        if (a.destR.x <= 250 && map[(a.destR.y - 50) / 50][(a.destR.x - 50) / 50 + 1] == '0')
                            a.destR.x += a.bspeed.x;
                        break;
                    case SDLK_DOWN:
                        a.destR.y += a.speed.y;
                        break;
                    case SDLK_SPACE:
                        break;
                    default:
                        break;
                    }
                else if (num == 60)
                    a.destR.y += a.speed.y;
            }
        }
        if (num == 60)
            num = 0;
        num++;
    }

    void draw() override
    {
        for (auto &a : blocks)
        {
            if (a.isActive)
            {
                SDL_Surface *tmpSurface;
                if (a.color == 1)
                    tmpSurface = SDL_LoadBMP("./img/sample_red.bmp");
                else if (a.color == 2)
                    tmpSurface = SDL_LoadBMP("./img/sample_green.bmp");
                else if (a.color == 3)
                    tmpSurface = SDL_LoadBMP("./img/sample_yellow.bmp");
                else
                    tmpSurface = SDL_LoadBMP("./img/banana.bmp");
                a.texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
                TextureManager::Draw(a.texture, a.srcR, a.destR);
            }
        }
    }
};

#endif