#include "DoubleGameBoardComponent.h"
#include "../Game.h"
#include <SDL.h>

void DoubleGameBoardComponent::init()
{
}

DoubleGameBoardComponent::DoubleGameBoardComponent()
{
	ReSetAllArrayZero(1);
	ReSetAllArrayZero(2);
}

void DoubleGameBoardComponent::init1()
{
	InitializeRandomUnitOnTop(2, 1);
	InitializeRandomUnitOnTop(3, 1);
}

void DoubleGameBoardComponent::init2()
{
	InitializeRandomUnitOnTop(2, 2);
	InitializeRandomUnitOnTop(3, 2);
}

void DoubleGameBoardComponent::update()
{
	// for (int i = 0; i < 13; i++)
	// {
	// 	for (int j = 0; j < 6; j++)
	// 	{
	// 		cout << gameboard1.UnitArray[i][j].color << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	// for (int i = 0; i < 13; i++)
	// {
	// 	for (int j = 0; j < 6; j++)
	// 	{
	// 		cout << gameboard1.UnitArray[i][j].isMoving << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	// for (int i = 0; i < 13; i++)
	// {
	// 	for (int j = 0; j < 6; j++)
	// 	{
	// 		cout << gameboard1.UnitArray[i][j].isActive << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;
	static int time = SDL_GetTicks();
	if (SDL_GetTicks() - time >= 5000)
	{
		if (gameboard1.score > gameboard2.score)
		{
			chKO2 = true;
		}
		else
		{
			chKO1 = true;
		}
		stopAll();
	}
	UpdateBoardMovingState(1);
	UpdateBoardMovingState(2);
	static int ii = 0;
	if (ii == 3)
	{
		if (!gameboard2.falling)
			Move(2);

		ii = 0;
	}
	ii++;

	if (!gameboard1.falling)
		Move(1);

	UpdateBoardMovingState(1);
	UpdateBoardMovingState(2);
	// int iiii = SDL_GetTicks();

	if (!AnyThingMoving(1))
	{
		// cout << "Side1:\n"
		// 	 << gameboard1 << endl;
		if (!gameboard1.falling)
		{
			chaining(1);
			if (isChanged1)
			{
				gameboard1.falling = true;
			}
			else
			{
				init1();
				gameboard1.reset();
			}
		}
		else
		{
			MoveDown(1);
			gameboard1.falling = false;
		}
	}
	else
	{
		MoveDown(1);
	}

	if (!AnyThingMoving(2))
	{
		// cout << "Side2:\n"
		// 	 << gameboard2 << endl;
		if (!gameboard2.falling)
		{
			chaining(2);
			if (isChanged2)
			{
				gameboard2.falling = true;
			}
			else
			{
				init2();
				gameboard2.reset();
			}
		}
		else
		{
			MoveDown(2);
			gameboard2.falling = false;
		}
	}
	else
	{
		MoveDown(2);
	}

	// cout << SDL_GetTicks() - iiii << endl;

	if (ch1skilled)
		switch (ch1)
		{
		case 1:
			MikuSkill(1);
			break;
		case 3:
			SakuraSkill(1);
			break;
		case 4:
			FuhuaSkill(1);
			break;
		case 5:
			PSkill(1);
			break;
		}
	if (gameboard1.score % 2000 == 0 && gameboard1.score > 0)
	{
		ch1skilled = true;
	}
	if (gameboard2.score % 2000 == 0 && gameboard2.score > 0)
	{
		ch2skilled = true;
	}
	if (ch2skilled)
		switch (ch2)
		{
		case 1:
			MikuSkill(2);
			break;
		case 3:
			SakuraSkill(2);
			break;
		case 4:
			FuhuaSkill(2);
			break;
		case 5:
			PSkill(2);
			break;
		}
	ch1skilled = false;
	ch2skilled = false;
	getstop();
}

void DoubleGameBoardComponent::chaining(int side)
{
	if (side == 1)
	{
		isChanged1 = gameboard1.update();
	}
	else
	{
		isChanged2 = gameboard2.update();
	}
}

void DoubleGameBoardComponent::draw()
{
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 6; j++)
		{
			if (gameboard1.UnitArray[i][j].color != Empty)
				gameboard1.UnitArray[i][j].isActive = true;
			else
				gameboard1.UnitArray[i][j].isActive = false;

			if (gameboard1.UnitArray[i][j].isMoving || gameboard1.UnitArray[i][j].isActive)
			{
				SDL_Surface *tmpSurface;
				switch (gameboard1.UnitArray[i][j].color)
				{
				case Empty:
					tmpSurface = SDL_LoadBMP("./img/padoru1.bmp");
					break;
				case Red:
					tmpSurface = IMG_Load("./img/sample_red.png");
					break;
				case Green:
					tmpSurface = IMG_Load("./img/sample_green.png");
					break;
				case Yellow:
					tmpSurface = IMG_Load("./img/sample_yellow.png");
					break;
				case Purple:
					tmpSurface = SDL_LoadBMP("./img/PP.bmp");
					break;
				case Blue:
					tmpSurface = IMG_Load("./img/sample_blue.bmp");
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
		for (int j = 0; j < 6; j++)
		{
			if (gameboard2.UnitArray[i][j].color != Empty)
				gameboard2.UnitArray[i][j].isActive = true;
			else
				gameboard2.UnitArray[i][j].isActive = false;

			if (gameboard2.UnitArray[i][j].isMoving || gameboard2.UnitArray[i][j].isActive)
			{
				SDL_Surface *tmpSurface;
				switch (gameboard2.UnitArray[i][j].color)
				{
				case Empty:
					tmpSurface = SDL_LoadBMP("./img/padoru1.bmp");
					break;
				case Red:
					tmpSurface = IMG_Load("./img/sample_red.png");
					break;
				case Green:
					tmpSurface = IMG_Load("./img/sample_green.png");
					break;
				case Yellow:
					tmpSurface = IMG_Load("./img/sample_yellow.png");
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
	showScore();
}

unit *DoubleGameBoardComponent::getDataByMapPosition(int ypos, int xpos, int side)
{
	if (side == 1)
		return &gameboard1.UnitArray[ypos][xpos];
	else
		return &gameboard2.UnitArray[ypos][xpos];
}

void DoubleGameBoardComponent::ReSetAllArrayZero(int side)
{
	if (side == 1)
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++)
			{
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
	}
	if (side == 2)
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++)
			{
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

void DoubleGameBoardComponent::ReSetZeroUnit(int &xpos, int &ypos, int side)
{
	if (side == 1)
	{
		gameboard1.UnitArray[ypos][xpos].color = Empty;
		gameboard1.UnitArray[ypos][xpos].isActive = false;
		gameboard1.UnitArray[ypos][xpos].isMoving = false;
		SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
		gameboard1.UnitArray[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
	if (side == 2)
	{
		gameboard2.UnitArray[ypos][xpos].color = Empty;
		gameboard2.UnitArray[ypos][xpos].isActive = false;
		gameboard2.UnitArray[ypos][xpos].isMoving = false;
		SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
		gameboard2.UnitArray[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
}

void DoubleGameBoardComponent::Swap(unit &a, unit &b)
{
	static unit *t;
	t = new unit;
	t->isActive = a.isActive;
	t->isMoving = a.isMoving;
	t->texture = a.texture;
	t->color = a.color;
	cout << "SWAP2" << endl;

	a.isMoving = b.isMoving;
	a.isActive = b.isActive;
	a.texture = b.texture;
	a.color = b.color;
	cout << "SWAP3" << endl;

	b.isMoving = t->isMoving;
	b.isActive = t->isActive;
	b.texture = t->texture;
	b.color = t->color;
	cout << "SWAP4" << endl;
	delete t;
	t = NULL;
	SDL_Delay(1);
	cout << "SWAP5" << endl;
}

void DoubleGameBoardComponent::SwapTwoUnit(int x1, int y1, int x2, int y2, int side)
{
	// cout << "1111111111111111111111111" << endl;

	cout << x1 << "," << y1 << endl;
	cout << x2 << "," << y2 << endl;
	if (side == 1)
		Swap(gameboard1.UnitArray[y1][x1], gameboard1.UnitArray[y2][x2]);
	if (side == 2)
		Swap(gameboard2.UnitArray[y1][x1], gameboard2.UnitArray[y2][x2]);
	// cout << "1111111111111111111111111" << endl;
}

void DoubleGameBoardComponent::SwapTwoUnit(unit u1, unit u2, int side)
{
	// cout << "222222222222222222222222" << endl;

	// if (side == 1)
	// 	Swap(gameboard1.UnitArray[(int)u1.mapPosition.y][(int)u1.mapPosition.x], gameboard1.UnitArray[(int)u2.mapPosition.y][(int)u2.mapPosition.x]);
	// if (side == 2)
	// 	Swap(gameboard2.UnitArray[(int)u1.mapPosition.y][(int)u1.mapPosition.x], gameboard2.UnitArray[(int)u2.mapPosition.y][(int)u2.mapPosition.x]);

	SwapTwoUnit(u1.mapPosition.x, u1.mapPosition.y, u2.mapPosition.x, u2.mapPosition.y, side);
	cout << u1.mapPosition.x << "," << u1.mapPosition.y << "," << u2.mapPosition.x << "," << u2.mapPosition.y << "p" << endl;
	// cout << "222222222222222222222222" << endl;
}

void DoubleGameBoardComponent::InitializeRandomUnitOnTop(int topx, int side)
{
	cout << "INIT" << endl;
	Color tmpColor;
	switch (rand() % 3)
	{
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
	if (side == 1)
	{
		if (gameboard1.UnitArray[0][topx].color != Empty)
		{
			chKO1 = true;
			return;
		}
		if (1)
		{
			gameboard1.UnitArray[0][topx].color = tmpColor;
			gameboard1.UnitArray[0][topx].isMoving = true;
			gameboard1.UnitArray[0][topx].isActive = true;
		}
		else
		{
			InitializeRainbowUnitOnTop(2, 1);
			InitializeRainbowUnitOnTop(3, 1);
		}
	}
	if (side == 2)
	{
		if (gameboard2.UnitArray[0][topx].color != Empty)
		{
			chKO2 = true;
			return;
		}
		if (1)
		{
			gameboard2.UnitArray[0][topx].color = tmpColor;
			gameboard2.UnitArray[0][topx].isMoving = true;
			gameboard2.UnitArray[0][topx].isActive = true;
		}
		else
		{
			InitializeRainbowUnitOnTop(2, 2);
			InitializeRainbowUnitOnTop(3, 2);
		}
	}
	cout << "INIT END" << endl;
}

void DoubleGameBoardComponent::InitializeRainbowUnitOnTop(int topx, int side)
{
	if (side == 1)
	{
		gameboard1.UnitArray[0][topx].color = Rainbow;
		gameboard1.UnitArray[0][topx].isMoving = true;
		gameboard1.UnitArray[0][topx].isActive = true;
	}
	if (side == 2)
	{
		gameboard2.UnitArray[0][topx].color = Rainbow;
		gameboard2.UnitArray[0][topx].isMoving = true;
		gameboard2.UnitArray[0][topx].isActive = true;
	}
}

bool DoubleGameBoardComponent::AnyThingMoving(int side)
{
	if (side == 1)
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++)
			{
				if (gameboard1.UnitArray[i][j].isMoving)
					return true;
			}
		return false;
	}
	if (side == 2)
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++)
			{
				if (gameboard2.UnitArray[i][j].isMoving)
					return true;
			}
		return false;
	}
	return false;
}

void DoubleGameBoardComponent::Move(int side)
{
	cout << "move";
	if (side == 2)
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_DOWN:
				for (int i = 11; i >= 0; i--) // start from 11 to 0
					for (int j = 0; j < 6; j++)
					{
						cout << "e" << endl;
						if (gameboard2.UnitArray[i][j].isMoving && gameboard2.UnitArray[i + 1][j].color == Empty)
							SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i + 1][j], 2);
					}
				break;
			case SDLK_LEFT:
				for (int i = 0; i < 13; i++)
					for (int j = 1; j < 6; j++) // start from 1
					{
						cout << "f" << endl;
						if (gameboard2.UnitArray[i][j].isMoving && gameboard2.UnitArray[i][j - 1].color == Empty)
							SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i][j - 1], 2);
					}
				break;
			case SDLK_RIGHT:
				for (int i = 0; i < 13; i++)
					for (int j = 4; j >= 0; j--) // end at 0
					{
						cout << "g" << endl;
						if (gameboard2.UnitArray[i][j].isMoving && gameboard2.UnitArray[i][j + 1].color == Empty)
							SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i][j + 1], 2);
					}
				break;
			case SDLK_UP:
				Spin(2);
				break;
			case SDLK_RSHIFT:
				SpaceAction(2);
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:
				break;
			}
		}
	}
	if (side == 1)
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_s:
				for (int i = 11; i >= 0; i--) // start from 11 to 0
					for (int j = 0; j < 6; j++)
					{
						cout << "h" << endl;
						if (gameboard1.UnitArray[i][j].isMoving && gameboard1.UnitArray[i + 1][j].color == Empty)
							SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i + 1][j], 1);
					}
				break;
			case SDLK_a:
				for (int i = 0; i < 13; i++)
					for (int j = 1; j < 6; j++) // start from 1
					{
						cout << "i" << endl;
						if (gameboard1.UnitArray[i][j].isMoving && gameboard1.UnitArray[i][j - 1].color == Empty)
							SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i][j - 1], 1);
					}
				break;
			case SDLK_d:
				for (int i = 0; i < 13; i++)
					for (int j = 4; j >= 0; j--) // end at 0
					{
						cout << "j" << endl;
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
	SDL_Delay(1);
}

void DoubleGameBoardComponent::MoveDown(int side)
{
	cout << "movedown";
	if (side == 1)
	{
		static int ii = 0;
		if (ii == 30)
		{
			//cout << "z\n";
			// SDL_Delay(500);
			for (int i = 11; i >= 0; i--)
				for (int j = 0; j < 6; j++)

					if (gameboard1.UnitArray[i][j].color != Empty && gameboard1.UnitArray[i + 1][j].color == Empty)
						SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i + 1][j], 1);
			ii = 0;
		}
		ii++;
	}
	if (side == 2)
	{
		static int ii = 0;
		if (ii == 30)
		{
			cout << "z\n";
			// SDL_Delay(500);
			for (int i = 11; i >= 0; i--)
				for (int j = 0; j < 6; j++)

					if (gameboard2.UnitArray[i][j].color != Empty && gameboard2.UnitArray[i + 1][j].color == Empty)
						SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i + 1][j], 2);
			ii = 0;
		}
		ii++;
	}
}

void DoubleGameBoardComponent::UpdateBoardMovingState(int side)
{
	if (side == 1)
	{
		for (int i = 12; i >= 0; i--)
			for (int j = 0; j < 6; j++)
			{
				if (gameboard1.UnitArray[i][j].color == Empty)
				{
					gameboard1.UnitArray[i][j].isMoving = false;
				}
				else if (gameboard1.UnitArray[i][j].mapPosition.y == 12)
				{
					gameboard1.UnitArray[i][j].isMoving = false;
				}
				else if (gameboard1.UnitArray[i][j].mapPosition.y < 12)
				{
					if (gameboard1.UnitArray[i + 1][j].color != Empty && !gameboard1.UnitArray[i + 1][j].isMoving)
						gameboard1.UnitArray[i][j].isMoving = false;
					else
					{
						gameboard1.UnitArray[i][j].isMoving = true;
					}
				}
				else
					gameboard1.UnitArray[i][j].isMoving = true;
			}
	}
	if (side == 2)
	{
		for (int i = 12; i >= 0; i--)
			for (int j = 0; j < 6; j++)
			{
				if (gameboard2.UnitArray[i][j].color == Empty)
				{
					gameboard2.UnitArray[i][j].isMoving = false;
				}
				else if (gameboard2.UnitArray[i][j].mapPosition.y == 12)
				{
					gameboard2.UnitArray[i][j].isMoving = false;
				}
				else if (gameboard2.UnitArray[i][j].mapPosition.y < 12)
				{
					if (gameboard2.UnitArray[i + 1][j].color != Empty && !gameboard2.UnitArray[i + 1][j].isMoving)
						gameboard2.UnitArray[i][j].isMoving = false;
					else
					{
						gameboard2.UnitArray[i][j].isMoving = true;
					}
				}
				else
					gameboard2.UnitArray[i][j].isMoving = true;
			}
	}
}

void DoubleGameBoardComponent::GetMovingPair(int side)
{
	if (side == 1)
	{
		int n = 0;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++)
			{
				if (n == 2)
					break;
				if (gameboard1.UnitArray[i][j].isMoving)
				{
					MovingPair1[n] = gameboard1.UnitArray[i][j];
					++n;
				}
			}
	}
	if (side == 2)
	{
		int n = 0;
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 6; j++)
			{
				if (n == 2)
					break;
				if (gameboard2.UnitArray[i][j].isMoving)
				{
					MovingPair2[n] = gameboard2.UnitArray[i][j];
					++n;
				}
			}
	}
}

void DoubleGameBoardComponent::UpdateMovingPairState(int side)
{
	if (side == 1)
	{
		if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y + 1 ||
			MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y - 1)
		{
			if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x)
				MovingPairState1 = UP_AND_DOWN;
		}
		else if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x + 1 ||
				 MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x - 1)
		{
			if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y)
				MovingPairState1 = RIGHT_AND_LEFT;
		}
		else
			MovingPairState1 = SEPERATED;
	}
	if (side == 2)
	{
		if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y + 1 ||
			MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y - 1)
		{
			if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x)
				MovingPairState2 = UP_AND_DOWN;
		}
		else if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x + 1 ||
				 MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x - 1)
		{
			if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y)
				MovingPairState2 = RIGHT_AND_LEFT;
		}
		else
			MovingPairState2 = SEPERATED;
	}
}

void DoubleGameBoardComponent::UpdateMovingPairLastestVersion(int side)
{
	GetMovingPair(side);
	UpdateMovingPairState(side);
}

void DoubleGameBoardComponent::SpaceAction(int side)
{
	cout << "space";
	UpdateBoardMovingState(side);
	UpdateMovingPairLastestVersion(side);
	if (side == 1)
	{
		int p1yd;
		int p2yd;
		if (MovingPairState1 == RIGHT_AND_LEFT)
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 6; j++)
				{
					if (gameboard1.UnitArray[i][j].mapPosition.x == MovingPair1[0].mapPosition.x &&
						gameboard1.UnitArray[i][j].color == Empty)
						p1yd = gameboard1.UnitArray[i][j].mapPosition.y;
					if (gameboard1.UnitArray[i][j].mapPosition.x == MovingPair1[1].mapPosition.x &&
						gameboard1.UnitArray[i][j].color == Empty)
						p2yd = gameboard1.UnitArray[i][j].mapPosition.y;
				}
		else if (MovingPairState1 == UP_AND_DOWN)
		{
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 6; j++)
				{
					if (gameboard1.UnitArray[i][j].mapPosition.x == MovingPair1[1].mapPosition.x &&
						gameboard1.UnitArray[i][j].color == Empty)
						p2yd = gameboard1.UnitArray[i][j].mapPosition.y;
					p1yd = p2yd - 1;
				}
		}
		SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[p1yd][(int)MovingPair1[0].mapPosition.x], 1);
		SwapTwoUnit(MovingPair1[1], gameboard1.UnitArray[p2yd][(int)MovingPair1[1].mapPosition.x], 1);
	}
	if (side == 2)
	{
		int p1yd;
		int p2yd;
		cout << "z\n";
		if (MovingPairState2 == RIGHT_AND_LEFT)
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 6; j++)
				{
					if (gameboard2.UnitArray[i][j].mapPosition.x == MovingPair2[0].mapPosition.x &&
						gameboard2.UnitArray[i][j].color == Empty)
						p1yd = gameboard2.UnitArray[i][j].mapPosition.y;
					if (gameboard2.UnitArray[i][j].mapPosition.x == MovingPair2[1].mapPosition.x &&
						gameboard2.UnitArray[i][j].color == Empty)
						p2yd = gameboard2.UnitArray[i][j].mapPosition.y;
				}
		else if (MovingPairState2 == UP_AND_DOWN)
		{
			for (int i = 0; i < 13; i++)
				for (int j = 0; j < 6; j++)
				{
					if (gameboard2.UnitArray[i][j].mapPosition.x == MovingPair2[1].mapPosition.x &&
						gameboard2.UnitArray[i][j].color == Empty)
						p2yd = gameboard2.UnitArray[i][j].mapPosition.y;
					p1yd = p2yd - 1;
				}
		}
		SwapTwoUnit(MovingPair2[1], gameboard2.UnitArray[p2yd][(int)MovingPair2[1].mapPosition.x], 2);
		SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[p1yd][(int)MovingPair2[0].mapPosition.x], 2);
	}
	SDL_Delay(1);
}

void DoubleGameBoardComponent::Spin(int side)
{
	cout << "spin";
	UpdateBoardMovingState(side);
	UpdateMovingPairLastestVersion(side);
	if (side == 1)
	{
		if (PairAdjacent(side))
		{
			switch (MovingPairState1)
			{
			case UP_AND_DOWN:
				if (MovingPair1[0].mapPosition.y < MovingPair1[1].mapPosition.y &&
					MovingPair1[1].mapPosition.x < 5)
				{
					if (gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1].color == Empty)
					{
						SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
					}
				}
				else if (MovingPair1[0].mapPosition.y < MovingPair1[1].mapPosition.y &&
						 MovingPair1[1].mapPosition.x == 5)
				{
					SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y][(int)MovingPair1[0].mapPosition.x - 1], 1);
					SwapTwoUnit(MovingPair1[1], gameboard1.UnitArray[(int)MovingPair1[1].mapPosition.y][(int)MovingPair1[1].mapPosition.x - 1], 1);
					if (gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1].color == Empty)
						SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
				}
				break;
			case RIGHT_AND_LEFT:
				if (MovingPair1[0].mapPosition.x < MovingPair1[1].mapPosition.x &&
					MovingPair1[0].mapPosition.y > 0)
				{
					SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y - 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
				}
				else if (MovingPair1[0].mapPosition.x < MovingPair1[1].mapPosition.x)
				{
					SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x], 1);
					SwapTwoUnit(MovingPair1[1], gameboard1.UnitArray[(int)MovingPair1[1].mapPosition.y + 1][(int)MovingPair1[1].mapPosition.x], 1);
					SwapTwoUnit(MovingPair1[0], gameboard1.UnitArray[(int)MovingPair1[0].mapPosition.y - 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
				}
				break;
			case SEPERATED:
				break;
			}
		}
	}
	if (side == 2)
	{
		if (PairAdjacent(side))
		{
			switch (MovingPairState2)
			{
			case UP_AND_DOWN:
				if (MovingPair2[0].mapPosition.y < MovingPair2[1].mapPosition.y &&
					MovingPair2[1].mapPosition.x < 5)
				{
					if (gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1].color == Empty)
					{
						SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
					}
				}
				else if (MovingPair2[0].mapPosition.y < MovingPair2[1].mapPosition.y &&
						 MovingPair2[1].mapPosition.x == 5)
				{
					SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y][(int)MovingPair2[0].mapPosition.x - 1], 2);
					SwapTwoUnit(MovingPair2[1], gameboard2.UnitArray[(int)MovingPair2[1].mapPosition.y][(int)MovingPair2[1].mapPosition.x - 1], 2);
					if (gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1].color == Empty)
						SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
				}
				break;
			case RIGHT_AND_LEFT:
				if (MovingPair2[0].mapPosition.x < MovingPair2[1].mapPosition.x &&
					MovingPair2[0].mapPosition.y > 0)
				{
					SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y - 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
				}
				else if (MovingPair2[0].mapPosition.x < MovingPair2[1].mapPosition.x)
				{
					SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x], 2);
					SwapTwoUnit(MovingPair2[1], gameboard2.UnitArray[(int)MovingPair2[1].mapPosition.y + 1][(int)MovingPair2[1].mapPosition.x], 2);
					SwapTwoUnit(MovingPair2[0], gameboard2.UnitArray[(int)MovingPair2[0].mapPosition.y - 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
				}
				break;
			case SEPERATED:
				break;
			}
		}
	}
}

bool DoubleGameBoardComponent::PairAdjacent(int side)
{
	if (side == 1)
	{
		if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x - 1 &&
			MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y)
			return true;
		if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y - 1 &&
			MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x)
			return true;
		else
			return false;
	}
	if (side == 2)
	{
		if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x - 1 &&
			MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y)
			return true;
		if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y - 1 &&
			MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x)
			return true;
		else
			return false;
	}
	return false;
}

void DoubleGameBoardComponent::SakuraSkill(int side)
{
	if (side == 1)
	{
		for (int i = 1; i < 13; i++) // start from 1
		{
			for (int j = 0; j < 6; j++)
			{
				SwapTwoUnit(gameboard1.UnitArray[i][j], gameboard1.UnitArray[i - 1][j], 1);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			gameboard1.UnitArray[12][i].color = Trash;
		}
	}
	if (side == 2)
	{
		for (int i = 1; i < 13; i++) // start from 1
		{
			for (int j = 0; j < 6; j++)
			{
				SwapTwoUnit(gameboard2.UnitArray[i][j], gameboard2.UnitArray[i - 1][j], 1);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			gameboard2.UnitArray[12][i].color = Trash;
		}
	}
}

void DoubleGameBoardComponent::PSkill(int side)
{
	if (side == 1)
	{
		gameboard1.score = gameboard1.score * 4 / 5;
	}
	if (side == 2)
	{
		gameboard2.score = gameboard2.score * 4 / 5;
	}
}

void DoubleGameBoardComponent::MikuSkill(int side)
{
	if (side == 1)
	{
		for (int j = 0; j < 6; j++)
		{
			gameboard1.UnitArray[12][j].color = Empty;
			gameboard1.UnitArray[12][j].isActive = false;
			gameboard1.UnitArray[12][j].isMoving = false;
		}
		gameboard1.score += 1000;
	}
	if (side == 2)
	{
		for (int j = 0; j < 6; j++)
		{
			gameboard2.UnitArray[12][j].color = Empty;
			gameboard2.UnitArray[12][j].isActive = false;
			gameboard2.UnitArray[12][j].isMoving = false;
		}
		gameboard2.score += 1000;
	}
}

void DoubleGameBoardComponent::MeiSkill(int side)
{
	switch (side)
	{
	case 1:
		InitializeRainbowUnitOnTop(2, 1);
		InitializeRainbowUnitOnTop(3, 1);
		break;
	case 2:
		InitializeRainbowUnitOnTop(2, 2);
		InitializeRainbowUnitOnTop(3, 2);
		break;
	}
}

void DoubleGameBoardComponent::FuhuaSkill(int side)
{
	switch (side)
	{
	case 1:
		gameboard1.score *= 1.1;
		break;
	case 2:
		gameboard2.score *= 1.1;
		break;
	}
}

void DoubleGameBoardComponent::stopAll()
{
	if (chKO1 || chKO2)
	{
		SDL_Rect dest, src;
		src.x = 0;
		src.y = 0;
		src.h = 100;
		src.w = 100;
		dest.y = 0;
		dest.h = 100;
		dest.w = 100;
		SDL_Texture *tex;
		if (chKO1)
		{
			dest.x = 0;
			tex = TextureManager::LoadTexture("./img/kirito1.bmp");
			TextureManager::Draw(tex, src, dest);
		}
		if (chKO2)
		{
			dest.x = 1180;
			tex = TextureManager::LoadTexture("./img/kirito1.bmp");
			TextureManager::Draw(tex, src, dest);
		}
		stop = true;
	}
}

void DoubleGameBoardComponent::showCharacter()
{
}
void DoubleGameBoardComponent::showScore()
{
	TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
	TTF_SetFontStyle(font1, TTF_STYLE_ITALIC);
	SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, to_string(gameboard1.score).c_str(), {255, 223, 0});
	SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
	SDL_Rect textrec1;
	textrec1.x = 425;
	textrec1.y = 335 + 50;
	textrec1.h = textsurface1->clip_rect.h;
	textrec1.w = textsurface1->clip_rect.w;
	SDL_FreeSurface(textsurface1);
	SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
	SDL_DestroyTexture(texttexture1);
	TTF_CloseFont(font1);

	TTF_Font *font2 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
	TTF_SetFontStyle(font2, TTF_STYLE_ITALIC);
	SDL_Surface *textsurface2 = TTF_RenderText_Solid(font2, to_string(gameboard2.score).c_str(), {255, 223, 0});
	SDL_Texture *texttexture2 = SDL_CreateTextureFromSurface(Game::renderer, textsurface2);
	SDL_Rect textrec2;
	textrec2.x = 1280 - 425 - textsurface2->clip_rect.w;
	textrec2.y = 335 + 50;
	textrec2.h = textsurface2->clip_rect.h;
	textrec2.w = textsurface2->clip_rect.w;
	SDL_FreeSurface(textsurface2);
	SDL_RenderCopy(Game::renderer, texttexture2, NULL, &textrec2);
	SDL_DestroyTexture(texttexture2);
	TTF_CloseFont(font2);
}

void DoubleGameBoardComponent::getstop()
{
	SDL_Event e;
	if (e.type == SDL_MOUSEMOTION)
	{
		if (e.motion.x > 640 - 100 && e.motion.x < 640 + 100 &&
			e.motion.y > 35 && e.motion.y < 135)
		{
			cout << "Mouse Motion" << endl;
		}
	}
}