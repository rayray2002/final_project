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
#include "GameBoardBase.h"
#include "ECS.h"

using namespace std;

class DoubleGameBoardComponent : public Component, public GameBoardBase
{
private:
	bool ch1skilled = false;
	bool ch2skilled = false;

	bool chKO1;
	bool chKO2;

	bool stop;

public:
	int ch1 = 1;
	int ch2 = 1;
	void showCharacter();
	void showScore();

	void RitaSkill(int side);
	void MeiSkill(int side);
	void TerisaSkill(int side);
	void FuhuaSkill(int side);
	void KianaSkill(int side);

	GameBoard gameboard1;
	GameBoard gameboard2;

	void ReSetZeroUnit(int &xpos, int &ypos, int side);			// set default unit
	void ReSetAllArrayZero(int side);							// reset gameboard
	void SwapTwoUnit(int x1, int y1, int x2, int y2, int side); // pass position to swap
	void SwapTwoUnit(unit u1, unit u2, int side);				// pass unit to swap
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


	DoubleGameBoardComponent();

	~DoubleGameBoardComponent() = default;

	unit *getDataByMapPosition(int ypos, int xpos, int side);

	void init() override;
	void update() override;
	void draw() override;

	void init1();
	void init2();

	void chaining(int side);

	void getstop();
};

#endif