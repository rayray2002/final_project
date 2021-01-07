#ifndef _DOUBLEGAMEBOARDCOMPONENT_H
#define _DOUBLEGAMEBOARDCOMPONENT_H

/*SDL*/
#include <SDL.h>

/*STL*/
#include <deque>
#include <ctime>
#include <map>
#include <vector>

/*SOURCE CODE*/
#include "../Game.h"
#include "../GameBoard.h"
#include "../TextureManager.h"
#include "Components.h"
#include "ECS.h"

using namespace std;

class DoubleGameBoardComponent : public Component
{
private:
	enum PairState
	{
		UP_AND_DOWN,
		RIGHT_AND_LEFT,
		SEPERATED
	};

	int ch1 = 1;
	int ch2 = 1;

	bool ch1skilled = true;
	bool ch2skilled = true;

	bool chKO1;
	bool chKO2;

	bool stop;

public:
	void showCharacter();
	void showScore();

	void MikuSkill(int side);
	void MeiSkill(int side);
	void SakuraSkill(int side);
	void FuhuaSkill(int side);
	void PSkill(int side);

	GameBoard gameboard1;
	GameBoard gameboard2;

	void ReSetZeroUnit(int &xpos, int &ypos, int side);			// set default unit
	void ReSetAllArrayZero(int side);							// reset gameboard
	void SwapTwoUnit(int x1, int y1, int x2, int y2, int side); // pass position to swap
	void SwapTwoUnit(unit &u1, unit &u2, int side);				// pass unit to swap
	void InitializeRandomUnitOnTop(int topx, int side);			// set new unit
	void InitializeRainbowUnitOnTop(int topx, int side);		// set new unit
	void UpdateBoardMovingState(int side);						// set moving state
	void GetMovingPair(int side);

	bool AnyThingMoving(int side);

	void UpdateMovingPairState(int side);

	void Move(int side);	 // get keyboard event
	void MoveDown(int side); // drop
	void Spin(int side);

	void SpaceAction(int side);

	void Swap(unit &a, unit &b);

	void UpdateMovingPairLastestVersion(int side);

	bool PairAdjacent(int side);

	void stopAll();

	unit MovingPair1[2];
	unit MovingPair2[2];

	PairState MovingPairState1;
	PairState MovingPairState2;

	bool isChanged1;
	bool isChanged2;

	DoubleGameBoardComponent();

	~DoubleGameBoardComponent() = default;

	unit *getDataByMapPosition(int ypos, int xpos, int side);

	void init() override;
	void update() override;
	void draw() override;

	void init1();
	void init2();

	void chaining(int side);
};

#endif