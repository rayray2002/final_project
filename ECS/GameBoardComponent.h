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
    bool isMoving = true;
    bool isActive = true;

public:
    struct unit
    {
        SDL_Texture *texture;
        SDL_Rect srcR, destR;
        Vector2D speed;
        int color;
        bool isMoving = true;
        bool isActive = true;
    };
    deque<unit> blocks;
    int color;

    SDL_Texture *texture;
    SDL_Rect destR, srcR;
    Vector2D speed;
    bool move() { return isMoving; };
    bool active() { return isActive; };

    GameBoardComponent(int xpos, int ypos, int color)
    {

        destR.x = xpos;
        destR.y = ypos;
        destR.h = 30;
        destR.w = 30;

        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 1000;
        srcR.w = 1000;

        speed.x = 30;
        speed.y = 30;

        this->color = color;

        // init();
        cout << "init" << endl;
    }
    ~GameBoardComponent()
    {
    }

    void init() override
    {
	    unit a;

	    a.destR.x = 100;
	    a.destR.y = 35;
	    a.destR.h = 50;
	    a.destR.w = 50;

	    a.srcR.x = 0;
	    a.srcR.y = 0;
	    a.srcR.h = 1000;
	    a.srcR.w = 1000;

	    srand(time(0));
	    a.color = rand() % 4;

	    a.isActive = true;
	    a.isMoving = true;

	    a.speed.x = 50;
	    a.speed.y = 50;

	    blocks.push_back(a);
	    cout << "Push Back" << endl;
    }

    void update() override
    {
        static int num = 0;
        for (auto &a : blocks)
        {
            cout << a.destR.x << " " << a.destR.y << endl;
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
                        if (a.destR.x >= 100)
                            a.destR.x -= a.speed.x;
                        break;
                    case SDLK_RIGHT:
	                    if (a.destR.x <= 300)
		                    a.destR.x += a.speed.x;
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
        // SDL_Surface *tmpSurface;
        // if (isActive)
        // {
        //     if (color == 1)
        //         tmpSurface = SDL_LoadBMP("./img/sample_red.bmp");
        //     else if (color == 2)
        //         tmpSurface = SDL_LoadBMP("./img/sample_green.bmp");
        //     else if (color == 3)
        //         tmpSurface = SDL_LoadBMP("./img/sample_yellow.bmp");
        //     else
        //         tmpSurface = SDL_LoadBMP("./img/banana.bmp");

        //     texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        //     SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        //     SDL_FreeSurface(tmpSurface);
        //     TextureManager::Draw(texture, srcR, destR);
        // }
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
                // cout << "a.destR.x = " << a.destR.x << " a.destR.y = " << a.destR.y << endl;
                TextureManager::Draw(a.texture, a.srcR, a.destR);
            }
        }
    }
};

#endif