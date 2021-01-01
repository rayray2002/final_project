// #pragma once

#ifndef _DOUBLEGAMEBOARDCOMPONENT_H
#define _DOUBLEGAMEBOARDCOMPONENT_H

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

class DoubleGameBoardComponent : public Component
{
    friend class CharactorComponent;

private:
    int mode;

    enum PairState
    {
        UP_AND_DOWN,
        RIGHT_AND_LEFT,
        SEPERATED
    };

public:
    unit UnitArray1[13][6];
    unit UnitArray2[13][6];

    void ReSetZeroUnit(int &xpos, int &ypos, int side);         // set default unit
    void ReSetAllArrayZero(int side);                           // reset gameboard
    void SwapTwoUnit(int x1, int y1, int x2, int y2, int side); // pass position to swap
    void SwapTwoUnit(unit &u1, unit &u2, int side);             // pass unit to swap
    void InitializeRamdomUnitOnTop(int topx, int side);         // set new unit
    void UpdateBoardMovingState(int side);                      // set moving state
    void GetMovingPair(int side);
    bool AnyThingMoving(int side);
    void UpdateMovingPairState(int side);
    void Move(int side);     // get keyboard event
    void MoveDown(int side); // drop
    void Spin(int side);
    void SpaceAction(int side);
    void Swap(unit &a, unit &b);
    void UpdateMovingPairLastestVersion(int side);
    bool PairAdjacent(int side);

    unit MovingPair1[2];
    unit MovingPair2[2];

    PairState MovingPairState1;
    PairState MovingPairState2;

    bool isChanged1;
    bool isChanged2;

    DoubleGameBoardComponent()
    {
        ReSetAllArrayZero(1);
        ReSetAllArrayZero(2);
    }

    ~DoubleGameBoardComponent()
    {
    }
    unit *getDataByMapPosition(int ypos, int xpos, int side);
    void init() override;
    void update() override;
    void draw() override;

    void init1();
    void init2();

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
};

#endif