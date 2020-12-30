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
    bool isMoving;
    bool isActive;
    bool ispaired;
};

class GameBoardComponent : public Component
{
private:
public:
    unit UnitArray[13][6];
    void ReSetZeroUnit(int &xpos, int &ypos);
    void ReSetAllArrayZero();
    void SwapTwoUnit(int x1, int y1, int x2, int y2);
    void SwapTwoUnit(unit &u1, unit &u2);
    void UpdateUnitArray();
    void InitializeRamdomUnitOnTop(int topx);
    void AddMovingPair(unit u1, unit u2);
    void DeleteUsedMovingPair(unit u1, unit u2);
    void UpdateBoardMovingState();
    bool AnyThingMoving();
    void Move();
    deque<unit> MovingPair;
    bool isChanged;

    GameBoardComponent()
    {
        ReSetAllArrayZero();
    }

    ~GameBoardComponent()
    {
    }
    unit *getDataByMapPosition(int ypos, int xpos);
    void init() override;
    void update() override;
    void draw() override;

    void chaining()
    {
        // isChanged = gameboard.update();
        // if (isChanged)
        //     for (int i = 0; i < blocks.size(); i++)
        //     {
        //         cout << "1" << endl;
        //         auto a = blocks[i];
        //         if (gameboard.board[(a.destR.y - 35) / 50 + 1][(a.destR.x - 100) / 50 + 1] == Empty)
        //         {
        //             blocks.erase(blocks.begin() + i);
        //             i--;
        //         }
        //         cout << "2" << endl;
        //     }
        // cout << "OK" << endl;
    }

    void MoveDown();

    friend ostream &operator<<(ostream &stream, const unit *u)
    {
        stream << "********" << endl
               << endl;
        for (int i = 0; i < 14; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                stream << u->color << " ";
            }
            stream << endl;
        }
        stream << "********" << endl
               << endl;
    }
};

#endif