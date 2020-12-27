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
    char map[14][8];

public: //
    struct unit
    {
        SDL_Texture *texture;
        SDL_Rect srcR, destR;
        Vector2D speed;
        Vector2D bspeed;
        Vector2D mapPosition;
        int color;
        bool isMoving = true;
        bool isActive = true;
    };
    deque<unit> blocks;

    GameBoardComponent(int xpos, int ypos, int color)
    {
        setInitialMap();
    }
    ~GameBoardComponent()
    {
    }
    void setInitialMap()
    {
        for (int i = 0; i < 14; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                map[i][j] = '0';
            }
        }
    }

    void initBlock(int randNumber, int xpos)
    {
        unit a;

        a.destR.x = xpos;
        a.destR.y = 35;
        a.destR.h = 50;
        a.destR.w = 50;

        a.srcR.x = 0;
        a.srcR.y = 0;
        a.srcR.h = 1000;
        a.srcR.w = 1000;

        a.color = randNumber % 4 + 1;

        a.isActive = true;
        a.isMoving = true;

        a.speed.x = 50;
        a.speed.y = 50;

        a.bspeed.x = 50;
        a.bspeed.y = 50;

        a.mapPosition.x = (a.destR.x - 100) / 50 + 1;
        a.mapPosition.y = 0;

        blocks.push_back(a);
    }

    unit *getDataByMapPosition(int ypos, int xpos)
    {
        for (auto &b : blocks)
        {
            if (b.mapPosition.x == xpos && b.mapPosition.y == ypos)
            {
                return &b;
            }
        }
    }

    void init() override
    {
        initBlock(rand(), 150);
        srand(time(0));
        initBlock(rand(), 200);
    }

    void update() override
    {
        setInitialMap();
        for (auto &a : blocks)
            map[(a.destR.y - 35) / 50][(a.destR.x - 100) / 50 + 1] = a.color + '0';
        for (auto &a : blocks)
        {
            a.mapPosition.x = (a.destR.x - 100) / 50 + 1;
            a.mapPosition.y = (a.destR.y - 35) / 50;
        }
        static int num = 0;
        for (auto &a : blocks)
        {
            if (a.speed.y == 0)
                a.isMoving = false;
            if (num % 10 == 0 && a.isMoving)
            {
                if (Game::event.type == SDL_KEYDOWN)
                    switch (Game::event.key.keysym.sym)
                    {
                    case SDLK_LEFT:
                        if (a.destR.x >= 150 && (map[(a.destR.y - 35) / 50][(a.destR.x - 100) / 50] == '0' || (getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50)->isMoving && getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50)->mapPosition.x >= 2)))
                            a.destR.x -= a.bspeed.y;
                        break;
                    case SDLK_RIGHT:
                        if (a.destR.x <= 300 && (map[(a.destR.y - 35) / 50][(a.destR.x - 100) / 50 + 2] == '0' || (getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50 + 2)->isMoving && getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50 + 2)->mapPosition.x <= 5)))
                            a.destR.x += a.bspeed.x;
                        break;
                    case SDLK_DOWN:
                        if (map[(a.destR.y - 35) / 50 + 1][(a.destR.x - 100) / 50 + 1] == '0')
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
                    tmpSurface = SDL_LoadBMP("./img/padoru1.bmp");
                else if (a.color == 2)
                    tmpSurface = SDL_LoadBMP("./img/padoru2.bmp");
                else if (a.color == 3)
                    tmpSurface = SDL_LoadBMP("./img/padoru3.bmp");
                else
                    tmpSurface = SDL_LoadBMP("./img/padoru4.bmp");
                a.texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
                TextureManager::Draw(a.texture, a.srcR, a.destR);
            }
        }

        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cout << map[i][j] << " ";
            }
            cout << endl;
        }

        cout << "\n************************\n\n";
    }
};

#endif