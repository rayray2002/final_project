#include "GameBoardComponent.h"
#include "Game.h"
#include <SDL.h>

void GameBoardComponent::ReSetAllArrayZero()
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 6; j++)
        {
            UnitArray[i][j].destR.x = 35 + 50 * i;
            UnitArray[i][j].destR.y = 100 + 50 * j;
            UnitArray[i][j].destR.w = UnitArray[i][j].destR.h = 50;
            UnitArray[i][j].color = Empty;
            UnitArray[i][j].isActive = false;
            UnitArray[i][j].isMoving = false;
            UnitArray[i][j].ispaired = false;
            UnitArray[i][j].mapPosition.x = j;
            UnitArray[i][j].mapPosition.y = i;
            UnitArray[i][j].srcR.x = 0;
            UnitArray[i][j].srcR.y = UnitArray[i][j].srcR.x = 0;
            UnitArray[i][j].srcR.w = UnitArray[i][j].srcR.h = 1000;
            SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
            UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);
        }
}

void GameBoardComponent::ReSetZeroUnit(int &xpos, int &ypos)
{
    UnitArray[ypos][xpos].color = Empty;
    UnitArray[ypos][xpos].isActive = false;
    UnitArray[ypos][xpos].isMoving = false;
    UnitArray[ypos][xpos].ispaired = false;
    SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
    UnitArray[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void GameBoardComponent::SwapTwoUnit(int x1, int y1, int x2, int y2)
{
    unit tmpUnit;
    tmpUnit = UnitArray[y1][x1];
    UnitArray[y1][x1] = UnitArray[y2][x2];
    UnitArray[y2][x2] = tmpUnit;
}

void GameBoardComponent::SwapTwoUnit(unit &u1, unit &u2)
{
    SwapTwoUnit(u1.mapPosition.x, u1.mapPosition.y, u2.mapPosition.x, u2.mapPosition.y);
}

void GameBoardComponent::UpdateUnitArray()
{
    for (int i = 12; i >= 0; i--)
        for (int j = 0; j < 6; j++)
        {
            if (UnitArray[i][j].mapPosition.y <= 12)
                if (UnitArray[i][j + 1].color == Empty)
                {
                    SwapTwoUnit(UnitArray[i][j], UnitArray[i][j + 1]);
                }
        }
}

void GameBoardComponent::InitializeRamdomUnitOnTop(int topx)
{
    Color tmpColor;
    switch (rand() % 5)
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
    UnitArray[0][topx].color = tmpColor;
    UnitArray[0][topx].isMoving = true;
    UnitArray[0][topx].isActive = true;
    UnitArray[0][topx].ispaired = true;
}

bool GameBoardComponent::AnyThingMoving()
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 6; j++)
        {
            if (UnitArray[i][j].isMoving)
                return true;
        }
    return false;
}

void GameBoardComponent::AddMovingPair(unit u1, unit u2)
{
    MovingPair.push_back(u1);
    MovingPair.push_back(u2);
}

void GameBoardComponent::DeleteUsedMovingPair(unit u1, unit u2)
{
    MovingPair.pop_front();
    MovingPair.pop_front();
}

void GameBoardComponent::Move()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_DOWN:
        }
    }
}

void GameBoardComponent::MoveDown()
{
    for (int i = 12; i >= 0; i--)
        for (int j = 0; j < 8; j++)
            if (UnitArray[i][j].color != Empty && UnitArray[i + 1][j].color == Empty)
                SwapTwoUnit(UnitArray[i][j], UnitArray[i + 1][j]);
}