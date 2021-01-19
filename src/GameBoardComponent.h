1#ifndef _GAMEBOARDCOMPONENT_H
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
#include "GameBoardBase.h"
#include <vector>

using namespace std;

class GameBoardComponent : public Component, public GameBoardBase
{
private:
	int mode;

public:
	GameBoard gameboard;
	void showScore();

	void ReSetZeroUnit(int &xpos, int &ypos);				// set default unit
	void ReSetAllArrayZero(int gameBoardx, int gameBoardy); // reset gameboard
	void SwapTwoUnit(int x1, int y1, int x2, int y2);		// pass position to swap
	void SwapTwoUnit(unit &u1, unit &u2);					// pass unit to swap
	void InitializeRamdomUnitOnTop(int topx);				// set new unit
	void UpdateBoardMovingState();							// set moving state
	void GetMovingPair();

	bool AnyThingMoving();

	void UpdateMovingPairState();

	void Move();	 // get keyboard event
	void MoveDown(); // drop
	void Spin();

	void SpaceAction();

	void Swap(unit &a, unit &b);

	void UpdateMovingPairLastestVersion();

	bool PairAdjacent();

	unit MovingPair[2];
	PairState MovingPairState;
	

	GameBoardComponent(int x, int y, int m)
	{
		ReSetAllArrayZero(x, y);
		this->mode = m;
	}

	~GameBoardComponent()
	{
	}

	void init() override;

	void update() override;

	void draw() override;

	void chaining();

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
		return stream;
	}
};

#endif
