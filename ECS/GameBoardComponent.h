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
#include "../GameBoard.h"
#include <vector>

using namespace std;

struct unit
{
    SDL_Texture *texture;
    SDL_Rect srcR, destR;
    Vector2D speed;
    Vector2D bspeed;
    Vector2D mapPosition;
    Color color;
    bool isMoving = true;
    bool isActive = true;
};

class GameBoardComponent : public Component
{
private:
    //	char map[14][8];

public:
    GameBoard gameboard;
    // char map[14][8];
    unit UnitArray[13][6];
    void ReSetZeroUnit(int xpos, int ypos);
    void ReSetAllArrayZero();
    void SwapTwoUnit(int x1, int y1, int x2, int y2);
    void SwapTwoUnit(unit u1, unit u2);
    void UpdateUnitArray();
    void InitializeRamdomUnitOnTop(int topx);

    deque<unit> blocks;

    bool isChanged;

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
                gameboard.board[i][j] = Empty;
            }
        }
    }

    void resetSize()
    {
        while (blocks.size() > 0)
        {
            blocks.pop_back();
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

        switch (randNumber % 5)
        {
        case 0:
            a.color = Red;
            break;
        case 1:
            a.color = Green;
            break;
        case 2:
            a.color = Yellow;
            break;
        case 3:
            a.color = Purple;
            break;
        case 4:
            a.color = Blue;
            break;
        }

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
            gameboard.board[(a.destR.y - 35) / 50][(a.destR.x - 100) / 50 + 1] = a.color;

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
                        if (a.destR.x >= 150 &&
                            (gameboard.board[(a.destR.y - 35) / 50][(a.destR.x - 100) / 50] == Empty ||
                             (getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50)->isMoving &&
                              getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50)->mapPosition.x >= 2)))
                            a.destR.x -= a.bspeed.y;
                        break;
                    case SDLK_RIGHT:
                        if (a.destR.x <= 300 &&
                            (gameboard.board[(a.destR.y - 35) / 50][(a.destR.x - 100) / 50 + 2] == Empty ||
                             (getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50 + 2)->isMoving &&
                              getDataByMapPosition((a.destR.y - 35) / 50, (a.destR.x - 100) / 50 + 2)->mapPosition.x <= 5)))
                            a.destR.x += a.bspeed.x;
                        break;
                    case SDLK_DOWN:
                        if (gameboard.board[(a.destR.y - 35) / 50 + 1][(a.destR.x - 100) / 50 + 1] == Empty)
                            a.destR.y += a.speed.y;
                        break;
                    case SDLK_SPACE:
                        break;
                    default:
                        break;
                    }
                else if (num % 60 == 0)
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
            if (a.isActive && a.color != Empty)
            {
                SDL_Surface *tmpSurface;
                if (a.color == Red)
                    tmpSurface = SDL_LoadBMP("./img/sample_red.bmp");
                else if (a.color == Green)
                    tmpSurface = SDL_LoadBMP("./img/sample_green.bmp");
                else if (a.color == Yellow)
                    tmpSurface = SDL_LoadBMP("./img/sample_yellow.bmp");
                else if (a.color == Purple)
                    tmpSurface = SDL_LoadBMP("./img/sample_purple.bmp");
                else if (a.color == Blue)
                    tmpSurface = SDL_LoadBMP("./img/sample_blue.bmp");
                else
                    tmpSurface = SDL_LoadBMP("./img/banana.bmp");
                a.texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
                TextureManager::Draw(a.texture, a.srcR, a.destR);
            }
        }

        // gameboard.printer();

        //        for (int i = 0; i < 13; i++) {
        //            for (int j = 0; j < 8; j++) {
        //                cout << color_to_char(gameboard.board[i][j]) << " ";
        //            }
        //            cout << '\n';
        //        }
        //
        //        cout << "\n************************\n\n";
    }

    void chaining()
    {
        gameboard.isUpdated = gameboard.update();
        if (gameboard.isUpdated)
            gameboard.isChanged = true;
        else
            gameboard.isChanged = false;

        if (gameboard.isChanged)
            for (int i = 0; i < blocks.size(); i++)
            {
                auto a = blocks[i];
                if (gameboard.board[(a.destR.y - 35) / 50 + 1][(a.destR.x - 100) / 50 + 1] == Empty)
                {
                    blocks.erase(blocks.begin() + i);
                    i--;
                }
            }
    }

    void MoveDown()
    {
        for (int i = 12; i >= 0; i++)
        {
            for (int j = 1; j <= 7; j++)
            {
                int ypos = getDataByMapPosition(j, i)->mapPosition.y;
                int xpos = getDataByMapPosition(j, i)->mapPosition.x;
                if (gameboard.board[ypos + 1][xpos] == Empty && ypos <= 12)
                {
                    printf("Position (%d, %d) move down\n", i, j);
                    if (ypos <= 12)
                    {
                        getDataByMapPosition(j, i)->destR.y += 50;
                        printf("Position (%d, %d) move down\n", i, j);
                    }
                }
            }
        }
    }

    bool isAnyBlocksCanMove()
    {
        for (auto &a : blocks)
        {
            int ypos = a.mapPosition.y;
            int xpos = a.mapPosition.x;
            if (gameboard.board[ypos + 1][xpos] == Empty && ypos <= 12)
                return true;
        }
        printf("No block can move\n");
        return false;
    }
};

#endif