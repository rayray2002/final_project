#include "DoubleGameBoardComponent.h"
#include "../Game.h"
#include <SDL.h>

void DoubleGameBoardComponent::init() {
}

DoubleGameBoardComponent::DoubleGameBoardComponent() {
	ReSetAllArrayZero(1);
	ReSetAllArrayZero(2);
}

void DoubleGameBoardComponent::init1() {
	InitializeRamdomUnitOnTop(2, 1);
	InitializeRamdomUnitOnTop(3, 1);
}

void DoubleGameBoardComponent::init2() {
	InitializeRamdomUnitOnTop(2, 2);
	InitializeRamdomUnitOnTop(3, 2);
}

void DoubleGameBoardComponent::update() {
	UpdateBoardMovingState(1);
	UpdateBoardMovingState(2);
	Move(1);
	Move(2);

	UpdateBoardMovingState(1);
	UpdateBoardMovingState(2);
	if (!AnyThingMoving(1)) {
		chaining(1);
		if (!isChanged1) init1();
	} else {
		MoveDown(1);
	}
	if (!AnyThingMoving(2)) {
		chaining(2);
		if (!isChanged2) init2();
	} else {
		MoveDown(2);
	}
}

void DoubleGameBoardComponent::chaining(int side) {
	if (side == 1) {
		isChanged1 = gameboard1.update();
	} else {
		isChanged2 = gameboard2.update();
	}
}

void DoubleGameBoardComponent::draw() {
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 6; j++) {
			if (gameboard1.UnitArray[i][j].color != Empty)
				gameboard1.UnitArray[i][j].isActive = true;
			if (gameboard1.UnitArray[i][j].isMoving || gameboard1.UnitArray[i][j].isActive) {
				SDL_Surface *tmpSurface;
				switch (gameboard1.UnitArray[i][j].color) {
					case Empty:
						tmpSurface = SDL_LoadBMP("./img/padoru1.bmp");
						break;
					case Red:
						tmpSurface = SDL_LoadBMP("./img/sample_red.bmp");
						break;
					case Green:
						tmpSurface = SDL_LoadBMP("./img/sample_green.bmp");
						break;
					case Yellow:
						tmpSurface = SDL_LoadBMP("./img/sample_yellow.bmp");
						break;
					case Purple:
						tmpSurface = SDL_LoadBMP("./img/PP.bmp");
						break;
					case Blue:
						tmpSurface = SDL_LoadBMP("./img/sample_blue.bmp");
						break;
					default:
						tmpSurface = SDL_LoadBMP("./img/banana.bmp");
				}
				gameboard1.UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
				SDL_FreeSurface(tmpSurface);
				if (gameboard1.UnitArray[i][j].color != Empty)
					TextureManager::Draw(gameboard1.UnitArray[i][j].texture, gameboard1.UnitArray[i][j].srcR,
					                     gameboard1.UnitArray[i][j].destR);
			}
		}
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 6; j++) {
			if (gameboard2.UnitArray[i][j].color != Empty)
				gameboard2.UnitArray[i][j].isActive = true;
			if (gameboard2.UnitArray[i][j].isMoving || gameboard2.UnitArray[i][j].isActive) {
				SDL_Surface *tmpSurface;
				switch (gameboard2.UnitArray[i][j].color) {
					case Empty:
						tmpSurface = SDL_LoadBMP("./img/padoru1.bmp");
						break;
					case Red:
						tmpSurface = SDL_LoadBMP("./img/sample_red.bmp");
						break;
					case Green:
						tmpSurface = SDL_LoadBMP("./img/sample_green.bmp");
						break;
					case Yellow:
						tmpSurface = SDL_LoadBMP("./img/sample_yellow.bmp");
						break;
					case Purple:
						tmpSurface = SDL_LoadBMP("./img/PP.bmp");
						break;
					case Blue:
						tmpSurface = SDL_LoadBMP("./img/sample_blue.bmp");
						break;
					default:
						tmpSurface = SDL_LoadBMP("./img/banana.bmp");
				}
				gameboard2.UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
				SDL_FreeSurface(tmpSurface);
				if (gameboard2.UnitArray[i][j].color != Empty)
					TextureManager::Draw(gameboard2.UnitArray[i][j].texture, gameboard2.UnitArray[i][j].srcR,
					                     gameboard2.UnitArray[i][j].destR);
			}
		}
}

unit *DoubleGameBoardComponent::getDataByMapPosition(int ypos, int xpos, int side) {
	if (side == 1)
		return &gameboard1.UnitArray[ypos][xpos];
	else if (side == 2)
		return &gameboard2.UnitArray[ypos][xpos];
}

void DoubleGameBoardComponent::ReSetAllArrayZero(int side) {
	if (side == 1) {
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++) {
				gameboard1.UnitArray[i][j].destR.x = 100 + 50 * j;
				gameboard1.UnitArray[i][j].destR.y = 35 + 50 * i;
				gameboard1.UnitArray[i][j].destR.w = gameboard1.UnitArray[i][j].destR.h = 50;
				gameboard1.UnitArray[i][j].color = Empty;
				gameboard1.UnitArray[i][j].isActive = false;
				gameboard1.UnitArray[i][j].isMoving = false;
				gameboard1.UnitArray[i][j].mapPosition.x = j;
				gameboard1.UnitArray[i][j].mapPosition.y = i;
				gameboard1.UnitArray[i][j].srcR.x = 0;
				gameboard1.UnitArray[i][j].srcR.y = gameboard1.UnitArray[i][j].srcR.x = 0;
				gameboard1.UnitArray[i][j].srcR.w = gameboard1.UnitArray[i][j].srcR.h = 1000;
				gameboard1.UnitArray[i][j].surface = SDL_LoadBMP("./img/banana.bmp");
				gameboard1.UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer,
				                                                                  gameboard1.UnitArray[i][j].surface);
				SDL_FreeSurface(gameboard1.UnitArray[i][j].surface);
			}
	} else if (side == 2) {
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++) {
				gameboard2.UnitArray[i][j].destR.x = 880 + 50 * j;
				gameboard2.UnitArray[i][j].destR.y = 35 + 50 * i;
				gameboard2.UnitArray[i][j].destR.w = gameboard2.UnitArray[i][j].destR.h = 50;
				gameboard2.UnitArray[i][j].color = Empty;
				gameboard2.UnitArray[i][j].isActive = false;
				gameboard2.UnitArray[i][j].isMoving = false;
				gameboard2.UnitArray[i][j].mapPosition.x = j;
				gameboard2.UnitArray[i][j].mapPosition.y = i;
				gameboard2.UnitArray[i][j].srcR.x = 0;
				gameboard2.UnitArray[i][j].srcR.y = gameboard2.UnitArray[i][j].srcR.x = 0;
				gameboard2.UnitArray[i][j].srcR.w = gameboard2.UnitArray[i][j].srcR.h = 1000;
				gameboard2.UnitArray[i][j].surface = SDL_LoadBMP("./img/banana.bmp");
				gameboard2.UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer,
				                                                                  gameboard2.UnitArray[i][j].surface);
				SDL_FreeSurface(gameboard2.UnitArray[i][j].surface);
			}
	}
}

void DoubleGameBoardComponent::ReSetZeroUnit(int &xpos, int &ypos, int side) {
	if (side == 1) {
		gameboard1.UnitArray[ypos][xpos].color = Empty;
		gameboard1.UnitArray[ypos][xpos].isActive = false;
		gameboard1.UnitArray[ypos][xpos].isMoving = false;
		SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
		gameboard1.UnitArray[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	} else if (side == 2) {
		gameboard2.UnitArray[ypos][xpos].color = Empty;
		gameboard2.UnitArray[ypos][xpos].isActive = false;
		gameboard2.UnitArray[ypos][xpos].isMoving = false;
		SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
		gameboard2.UnitArray[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
}

void DoubleGameBoardComponent::Swap(unit &a, unit &b) {
	unit t = a;
	a.isMoving = b.isMoving;
	a.isActive = b.isActive;
	a.texture = b.texture;
	a.color = b.color;

	b.isMoving = t.isMoving;
	b.isActive = t.isActive;
	b.texture = t.texture;
	b.color = t.color;
}

void DoubleGameBoardComponent::SwapTwoUnit(int x1, int y1, int x2, int y2, int side) {
	if (side == 1)
		Swap(gameboard1.UnitArray[y1][x1], gameboard1.UnitArray[y2][x2]);
	else if (side == 2)
		Swap(gameboard2.UnitArray[y1][x1], gameboard2.UnitArray[y2][x2]);
}

void DoubleGameBoardComponent::SwapTwoUnit(unit &u1, unit &u2, int side) {
	SwapTwoUnit(u1.mapPosition.x, u1.mapPosition.y, u2.mapPosition.x, u2.mapPosition.y, side);
}

void DoubleGameBoardComponent::InitializeRamdomUnitOnTop(int topx, int side) {
	Color tmpColor;
	switch (rand() % 5) {
		case 0:
			tmpColor = Red;
			break;
		case 1:
			tmpColor = Green;
			break;
		case 2:
			tmpColor = Yellow;
			break;
		case 3:
			tmpColor = Purple;
			break;
		case 4:
			tmpColor = Blue;
			break;
	}
	if (side == 1) {
		gameboard1.UnitArray[0][topx].color = tmpColor;
		gameboard1.UnitArray[0][topx].isMoving = true;
		gameboard1.UnitArray[0][topx].isActive = true;
	} else if (side == 2) {
		gameboard2.UnitArray[0][topx].color = tmpColor;
		gameboard2.UnitArray[0][topx].isMoving = true;
		gameboard2.UnitArray[0][topx].isActive = true;
	}
}

bool DoubleGameBoardComponent::AnyThingMoving(int side) {
	if (side == 1) {
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++) {
				if (gameboard1.UnitArray[i][j].isMoving)
					return true;
			}
		return false;
	} else if (side == 2) {
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++) {
				if (gameboard2.UnitArray[i][j].isMoving)
					return true;
			}
		return false;
	}
}

void DoubleGameBoardComponent::Move(int side) {
	if (side == 2) {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
				case SDLK_DOWN:
					for (int i = 11; i >= 0; i--) // start from 11 to 0
						for (int j = 0; j < 6; j++) {
							if (gameboard2.UnitArray[i][j].isMoving && gameboard2.UnitArray[i + 1][j].color == Empty)
								SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i + 1][j], 2);
						}
					break;
				case SDLK_LEFT:
					for (int i = 0; i < 13; i++)
						for (int j = 1; j < 6; j++) // start from 1
						{
							if (gameboard2.UnitArray[i][j].isMoving && gameboard2.UnitArray[i][j - 1].color == Empty)
								SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i][j - 1], 2);
						}
					break;
				case SDLK_RIGHT:
					for (int i = 0; i < 13; i++)
						for (int j = 4; j >= 0; j--) // end at 0
						{
							if (gameboard2.UnitArray[i][j].isMoving && gameboard2.UnitArray[i][j + 1].color == Empty)
								SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i][j + 1], 2);
						}
					break;
				case SDLK_UP:
					Spin(2);
					break;
				case SDLK_SPACE:
					SpaceAction(2);
					break;
				case SDLK_ESCAPE:
					Game::isRunning = false;
					break;
				default:
					break;
			}
		}
	} else if (side == 1) {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
				case SDLK_s:
					for (int i = 11; i >= 0; i--) // start from 11 to 0
						for (int j = 0; j < 6; j++) {
							if (gameboard1.UnitArray[i][j].isMoving && gameboard1.UnitArray[i + 1][j].color == Empty)
								SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i + 1][j], 1);
						}
					break;
				case SDLK_a:
					for (int i = 0; i < 13; i++)
						for (int j = 1; j < 6; j++) // start from 1
						{
							if (gameboard1.UnitArray[i][j].isMoving && gameboard1.UnitArray[i][j - 1].color == Empty)
								SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i][j - 1], 1);
						}
					break;
				case SDLK_d:
					for (int i = 0; i < 13; i++)
						for (int j = 4; j >= 0; j--) // end at 0
						{
							if (gameboard1.UnitArray[i][j].isMoving && gameboard1.UnitArray[i][j + 1].color == Empty)
								SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i][j + 1], 1);
						}
					break;
				case SDLK_w:
					Spin(1);
					break;
				case SDLK_SPACE:
					SpaceAction(1);
					break;
				case SDLK_ESCAPE:
					Game::isRunning = false;
					break;
				default:
					break;
			}
		}
	}
}

void DoubleGameBoardComponent::MoveDown(int side) {
	if (side == 1) {
		static int ii = 0;
		if (ii == 30) {
			for (int i = 11; i >= 0; i--)
				for (int j = 0; j < 6; j++)
					if (gameboard1.UnitArray[i][j].color != Empty && gameboard1.UnitArray[i + 1][j].color == Empty)
						SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i + 1][j], 1);
			ii = 0;
		}
		ii++;
	} else if (side == 2) {
		static int ii = 0;
		if (ii == 30) {
			for (int i = 11; i >= 0; i--)
				for (int j = 0; j < 6; j++)
					if (gameboard2.UnitArray[i][j].color != Empty && gameboard2.UnitArray[i + 1][j].color == Empty)
						SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i + 1][j], 2);
			ii = 0;
		}
		ii++;
	}
}

void DoubleGameBoardComponent::UpdateBoardMovingState(int side) {
	if (side == 1) {
		for (int i = 12; i >= 0; i--)
			for (int j = 0; j < 6; j++) {
				if (gameboard1.UnitArray[i][j].color == Empty) {
					gameboard1.UnitArray[i][j].isMoving = false;
				} else if (gameboard1.UnitArray[i][j].mapPosition.y == 12) {
					gameboard1.UnitArray[i][j].isMoving = false;
				} else if (gameboard1.UnitArray[i][j].mapPosition.y < 12) {
					if (gameboard1.UnitArray[i + 1][j].color != Empty && !gameboard1.UnitArray[i + 1][j].isMoving)
						gameboard1.UnitArray[i][j].isMoving = false;
				} else
					gameboard1.UnitArray[i][j].isMoving = true;
			}
	} else if (side == 2) {
		for (int i = 12; i >= 0; i--)
			for (int j = 0; j < 6; j++) {
				if (gameboard2.UnitArray[i][j].color == Empty) {
					gameboard2.UnitArray[i][j].isMoving = false;
				} else if (gameboard2.UnitArray[i][j].mapPosition.y == 12) {
					gameboard2.UnitArray[i][j].isMoving = false;
				} else if (gameboard2.UnitArray[i][j].mapPosition.y < 12) {
					if (gameboard2.UnitArray[i + 1][j].color != Empty && !gameboard2.UnitArray[i + 1][j].isMoving)
						gameboard2.UnitArray[i][j].isMoving = false;
				} else
					gameboard2.UnitArray[i][j].isMoving = true;
			}
	}
}

void DoubleGameBoardComponent::GetMovingPair(int side) {
	if (side == 1) {
		int n = 0;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++) {
				if (n == 2)
					break;
				if (gameboard1.UnitArray[i][j].isMoving) {
					MovingPair1[n] = gameboard1.UnitArray[i][j];
					n++;
				}
			}
	} else if (side == 2) {
		int n = 0;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++) {
				if (n == 2)
					break;
				if (gameboard2.UnitArray[i][j].isMoving) {
					MovingPair2[n] = gameboard2.UnitArray[i][j];
					n++;
				}
			}
	}
}

void DoubleGameBoardComponent::UpdateMovingPairState(int side) {
	if (side == 1) {
		if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y + 1 ||
		    MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y - 1) {
			if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x)
				MovingPairState1 = UP_AND_DOWN;
		} else if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x + 1 ||
		           MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x - 1) {
			if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y)
				MovingPairState1 = RIGHT_AND_LEFT;
		} else
			MovingPairState1 = SEPERATED;
	} else if (side == 2) {
		if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y + 1 ||
		    MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y - 1) {
			if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x)
				MovingPairState2 = UP_AND_DOWN;
		} else if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x + 1 ||
		           MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x - 1) {
			if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y)
				MovingPairState2 = RIGHT_AND_LEFT;
		} else
			MovingPairState2 = SEPERATED;
	}
}

void DoubleGameBoardComponent::UpdateMovingPairLastestVersion(int side) {
	GetMovingPair(side);
	UpdateMovingPairState(side);
}

void DoubleGameBoardComponent::SpaceAction(int side) {
	UpdateBoardMovingState(side);
	UpdateMovingPairLastestVersion(side);
	if (side == 1) {
		int p1yd;
		int p2yd;
		if (MovingPairState1 == RIGHT_AND_LEFT)
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 6; j++) {
					if (gameboard1.UnitArray[i][j].mapPosition.x == MovingPair1[0].mapPosition.x &&
					    gameboard1.UnitArray[i][j].color == Empty)
						p1yd = gameboard1.UnitArray[i][j].mapPosition.y;
					if (gameboard1.UnitArray[i][j].mapPosition.x == MovingPair1[1].mapPosition.x &&
					    gameboard1.UnitArray[i][j].color == Empty)
						p2yd = gameboard1.UnitArray[i][j].mapPosition.y;
				}
		SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[p1yd][(int) MovingPair1[0].mapPosition.x], 1);
		SwapTwoUnit(MovingPair1[1], gameboard1.UnitArray[p2yd][(int) MovingPair1[1].mapPosition.x], 1);
	} else if (side == 2) {
		int p1yd;
		int p2yd;
		if (MovingPairState2 == RIGHT_AND_LEFT)
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 6; j++) {
					if (gameboard2.UnitArray[i][j].mapPosition.x == MovingPair2[0].mapPosition.x &&
					    gameboard2.UnitArray[i][j].color == Empty)
						p1yd = gameboard1.UnitArray[i][j].mapPosition.y;
					if (gameboard2.UnitArray[i][j].mapPosition.x == MovingPair2[1].mapPosition.x &&
					    gameboard2.UnitArray[i][j].color == Empty)
						p2yd = gameboard2.UnitArray[i][j].mapPosition.y;
				}
		SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[p1yd][(int) MovingPair2[0].mapPosition.x], 2);
		SwapTwoUnit(MovingPair2[1], gameboard2.UnitArray[p2yd][(int) MovingPair2[1].mapPosition.x], 2);
	}
}

void DoubleGameBoardComponent::Spin(int side) {
	UpdateBoardMovingState(side);
	UpdateMovingPairLastestVersion(side);
	if (side == 1) {
		if (PairAdjacent(side)) {
			switch (MovingPairState1) {
				case UP_AND_DOWN:
					if (MovingPair1[0].mapPosition.y < MovingPair1[1].mapPosition.y &&
					    MovingPair1[1].mapPosition.x < 5) {
						if (gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y + 1][
								    (int) MovingPair1[0].mapPosition.x + 1].color == Empty) {
							SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y + 1][
									(int) MovingPair1[0].mapPosition.x + 1], 1);
						}
					} else if (MovingPair1[0].mapPosition.y < MovingPair1[1].mapPosition.y &&
					           MovingPair1[1].mapPosition.x == 5) {
						SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y][
								(int) MovingPair1[0].mapPosition.x - 1], 1);
						SwapTwoUnit(MovingPair1[1], gameboard1.UnitArray[(int) MovingPair1[1].mapPosition.y][
								(int) MovingPair1[1].mapPosition.x - 1], 1);
						if (gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y + 1][
								    (int) MovingPair1[0].mapPosition.x + 1].color == Empty)
							SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y + 1][
									(int) MovingPair1[0].mapPosition.x + 1], 1);
					}
					break;
				case RIGHT_AND_LEFT:
					if (MovingPair1[0].mapPosition.x < MovingPair1[1].mapPosition.x &&
					    MovingPair1[0].mapPosition.y > 0) {
						SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y - 1][
								(int) MovingPair1[0].mapPosition.x + 1], 1);
					} else if (MovingPair1[0].mapPosition.x < MovingPair1[1].mapPosition.x) {
						SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y +
						                                                 1][(int) MovingPair1[0].mapPosition.x], 1);
						SwapTwoUnit(MovingPair1[1], gameboard1.UnitArray[(int) MovingPair1[1].mapPosition.y +
						                                                 1][(int) MovingPair1[1].mapPosition.x], 1);
						SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int) MovingPair1[0].mapPosition.y - 1][
								(int) MovingPair1[0].mapPosition.x + 1], 1);
					}
					break;
				case SEPERATED:
					break;
			}
		}
	} else if (side == 2) {
		if (PairAdjacent(side)) {
			switch (MovingPairState2) {
				case UP_AND_DOWN:
					if (MovingPair2[0].mapPosition.y < MovingPair2[1].mapPosition.y &&
					    MovingPair2[1].mapPosition.x < 5) {
						if (gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y + 1][
								    (int) MovingPair2[0].mapPosition.x + 1].color == Empty) {
							SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y + 1][
									(int) MovingPair2[0].mapPosition.x + 1], 2);
						}
					} else if (MovingPair2[0].mapPosition.y < MovingPair2[1].mapPosition.y &&
					           MovingPair2[1].mapPosition.x == 5) {
						SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y][
								(int) MovingPair2[0].mapPosition.x - 1], 2);
						SwapTwoUnit(MovingPair2[1], gameboard2.UnitArray[(int) MovingPair2[1].mapPosition.y][
								(int) MovingPair2[1].mapPosition.x - 1], 2);
						if (gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y + 1][
								    (int) MovingPair2[0].mapPosition.x + 1].color == Empty)
							SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y + 1][
									(int) MovingPair2[0].mapPosition.x + 1], 2);
					}
					break;
				case RIGHT_AND_LEFT:
					if (MovingPair2[0].mapPosition.x < MovingPair2[1].mapPosition.x &&
					    MovingPair2[0].mapPosition.y > 0) {
						SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y - 1][
								(int) MovingPair2[0].mapPosition.x + 1], 2);
					} else if (MovingPair2[0].mapPosition.x < MovingPair2[1].mapPosition.x) {
						SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y +
						                                                 1][(int) MovingPair2[0].mapPosition.x], 2);
						SwapTwoUnit(MovingPair2[1], gameboard2.UnitArray[(int) MovingPair2[1].mapPosition.y +
						                                                 1][(int) MovingPair2[1].mapPosition.x], 2);
						SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int) MovingPair2[0].mapPosition.y - 1][
								(int) MovingPair2[0].mapPosition.x + 1], 2);
					}
					break;
				case SEPERATED:
					break;
			}
		}
	}
}

bool DoubleGameBoardComponent::PairAdjacent(int side) {
	if (side == 1) {
		if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x - 1 &&
		    MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y)
			return true;
		if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y - 1 &&
		    MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x)
			return true;
		else
			return false;
	} else if (side == 2) {
		if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x - 1 &&
		    MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y)
			return true;
		if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y - 1 &&
		    MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x)
			return true;
		else
			return false;
	}
}