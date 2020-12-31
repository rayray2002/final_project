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
};

class GameBoardComponent : public Component
{
    friend class CharactorComponent;

private:
    enum PairState
    {
        UP_AND_DOWN,
        RIGHT_AND_LEFT,
        SEPERATED
    };

public:
    unit UnitArray[13][6];
    void ReSetZeroUnit(int &xpos, int &ypos);         // set default unit
    void ReSetAllArrayZero();                         // reset gameboard
    void SwapTwoUnit(int x1, int y1, int x2, int y2); // pass position to swap
    void SwapTwoUnit(unit &u1, unit &u2);             // pass unit to swap
    void InitializeRamdomUnitOnTop(int topx);         // set new unit
    void UpdateBoardMovingState();                    // set moving state
    void GetMovingPair();
    bool AnyThingMoving();
    void UpdateMovingPairState();
    void Move();     // get keyboard event
    void MoveDown(); // drop
    void Spin();
    void Swap(unit &a, unit &b);
    void UpdateMovingPairLastestVersion();
    bool PairAdjacent();

    unit MovingPair[2];
    PairState MovingPairState;
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

    friend ostream &operator<<(ostream &stream, const unit **u)
    {
        stream << "********" << endl
               << endl;
        for (int i = 0; i < 13; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                stream << u[i][j].color << " ";
            }
            stream << endl;
        }
        stream << "********" << endl
               << endl;
    }
};

#endif