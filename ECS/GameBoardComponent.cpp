#include "GameBoardComponent.h"
#include "../Game.h"
#include <SDL.h>

void GameBoardComponent::init()
{
    InitializeRamdomUnitOnTop(2);
    InitializeRamdomUnitOnTop(3);
}

void GameBoardComponent::draw()
{
    // cout << UnitArray << endl;
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 6; j++)
        {
            if (UnitArray[i][j].isMoving)
            {
                SDL_Surface *tmpSurface;
                switch (UnitArray[i][j].color)
                {
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
                UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
                if (UnitArray[i][j].color != Empty)
                    TextureManager::Draw(UnitArray[i][j].texture, UnitArray[i][j].srcR, UnitArray[i][j].destR);
            }
        }
}

unit *GameBoardComponent::getDataByMapPosition(int ypos, int xpos)
{
    return &UnitArray[ypos][xpos];
}

void GameBoardComponent::ReSetAllArrayZero()
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 6; j++)
        {
            UnitArray[i][j].destR.x = 100 + 50 * j;
            UnitArray[i][j].destR.y = 35 + 50 * i;
            UnitArray[i][j].destR.w = UnitArray[i][j].destR.h = 50;
            UnitArray[i][j].color = Empty;
            UnitArray[i][j].isActive = false;
            UnitArray[i][j].isMoving = false;
            UnitArray[i][j].mapPosition.x = j;
            UnitArray[i][j].mapPosition.y = i;
            UnitArray[i][j].srcR.x = 0;
            UnitArray[i][j].srcR.y = UnitArray[i][j].srcR.x = 0;
            UnitArray[i][j].srcR.w = UnitArray[i][j].srcR.h = 1000;
            SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
            UnitArray[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
            SDL_FreeSurface(tmpSurface);
        }
    // cout << " reset 2 " << endl;
}

void GameBoardComponent::ReSetZeroUnit(int &xpos, int &ypos)
{
    UnitArray[ypos][xpos].color = Empty;
    UnitArray[ypos][xpos].isActive = false;
    UnitArray[ypos][xpos].isMoving = false;
    SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
    UnitArray[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void GameBoardComponent::Swap(unit &a, unit &b)
{
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

void GameBoardComponent::SwapTwoUnit(int x1, int y1, int x2, int y2)
{
    Swap(UnitArray[y1][x1], UnitArray[y2][x2]);
}

void GameBoardComponent::SwapTwoUnit(unit &u1, unit &u2)
{
    cout << " SWAP B " << u1.isMoving << endl;
    SwapTwoUnit(u1.mapPosition.x, u1.mapPosition.y, u2.mapPosition.x, u2.mapPosition.y);
    cout << " SWAP E " << u1.isMoving << endl;
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

void GameBoardComponent::ClearMovingPair()
{
    if (MovingPair.size() == 2)
    {
        MovingPair.pop_back();
        MovingPair.pop_back();
    }
}

void GameBoardComponent::Move()
{
    // cout << "MOVE" << endl;
    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_DOWN:
            cout << "DOWN" << endl;
            for (int i = 11; i >= 0; i--) // start from 11 to 0
                for (int j = 0; j < 6; j++)
                {
                    if (UnitArray[i][j].mapPosition.y < 13)
                        if (UnitArray[i][j].isMoving && UnitArray[i + 1][j].color == Empty)
                            SwapTwoUnit(UnitArray[i][j], UnitArray[i + 1][j]);
                }
            break;
        case SDLK_LEFT:
            cout << "LEFT" << endl;
            for (int i = 0; i < 13; i++)
                for (int j = 1; j < 6; j++) // start from 1
                {
                    if (UnitArray[i][j].isMoving && UnitArray[i][j - 1].color == Empty)
                        SwapTwoUnit(UnitArray[i][j], UnitArray[i][j - 1]);
                }
            break;
        case SDLK_RIGHT:
            cout << "RIGHT" << endl;
            for (int i = 0; i < 13; i++)
                for (int j = 4; j >= 0; j--) // end at 0
                {
                    if (UnitArray[i][j].isMoving && UnitArray[i][j + 1].color == Empty)
                        SwapTwoUnit(UnitArray[i][j], UnitArray[i][j + 1]);
                }
            break;
        case SDLK_UP:
            Spin();
            break;
        case SDLK_ESCAPE:
            Game::isRunning = false;
            break;
        default:
            break;
        }
    }
    // cout << "Game Board Moved!" << endl;
}

void GameBoardComponent::MoveDown()
{
    static int ii = 0;
    if (ii == 30)
    {
        for (int i = 12; i >= 0; i--)
            for (int j = 0; j < 6; j++)
                if (UnitArray[i][j].color != Empty && UnitArray[i + 1][j].color == Empty)
                    SwapTwoUnit(UnitArray[i][j], UnitArray[i + 1][j]);
        ii = 0;
    }
    ii++;
}

void GameBoardComponent::UpdateBoardMovingState()
{
    for (int i = 12; i >= 0; i--)
        for (int j = 0; j < 6; j++)
        {
            if (UnitArray[i][j].color == Empty)
            {
                UnitArray[i][j].isMoving = false;
                UnitArray[i][j].isActive = false;
            }
            else if (UnitArray[i][j].mapPosition.y == 12)
            {
                UnitArray[i][j].isMoving = false;
                UnitArray[i][j].isActive = false;
            }
            else if (UnitArray[i][j].mapPosition.y < 12 && (UnitArray[i + 1][j].color != Empty && !UnitArray[i][j].isMoving))
            {
                UnitArray[i][j].isMoving = false;
                UnitArray[i][j].isActive = false;
            }
            else
                UnitArray[i][j].isMoving = true;
        }
}

void GameBoardComponent::update()
{
    // cout << "UPDATE" << endl;
    static int n = 0;
    if (n == 10)
    {
        UpdateBoardMovingState();
        Move();
        n = 0;
    }
    n++;
}

void GameBoardComponent::GetMovingPair()
{
    static int n = 0;
    for (int i = 0; i < 14; i++)
        for (int j = 0; j < 8; j++)
        {
            if (n == 2)
                break;
            if (UnitArray[i][j].isMoving)
            {
                MovingPair.push_back(UnitArray[i][j]);
                n++;
            }
        }
}

void GameBoardComponent::UpdateMovingPairState()
{
    GetMovingPair();
    if (!MovingPair.empty())
    {
        if (MovingPair[0].mapPosition.y == MovingPair[1].mapPosition.y + 1 || MovingPair[0].mapPosition.y == MovingPair[1].mapPosition.y - 1)
            MovingPairState = UP_AND_DOWN;
        else if (MovingPair[0].mapPosition.x == MovingPair[1].mapPosition.x + 1 || MovingPair[0].mapPosition.x == MovingPair[1].mapPosition.x - 1)
            MovingPairState = RIGHT_AND_LEFT;
        else
            MovingPairState = SEPERATED;
    }
    ClearMovingPair();
}

void GameBoardComponent::Spin()
{
    UpdateBoardMovingState();
    GetMovingPair();
    UpdateMovingPairState();
    switch (MovingPairState)
    {
    case UP_AND_DOWN:
        if (MovingPair[0].mapPosition.y > MovingPair[1].mapPosition.y)
        {
            SwapTwoUnit(MovingPair[1], UnitArray[(int)MovingPair[1].mapPosition.y - 1][(int)MovingPair[1].mapPosition.x - 1]);
        }
        else if (MovingPair[0].mapPosition.y < MovingPair[1].mapPosition.y)
        {
            SwapTwoUnit(MovingPair[0], UnitArray[(int)MovingPair[0].mapPosition.y - 1][(int)MovingPair[0].mapPosition.x - 1]);
        }
        break;
    case RIGHT_AND_LEFT:
        if (MovingPair[0].mapPosition.x > MovingPair[1].mapPosition.x && MovingPair[0].mapPosition.y > 0)
        {
            SwapTwoUnit(MovingPair[1], UnitArray[(int)MovingPair[1].mapPosition.y - 1][(int)MovingPair[1].mapPosition.x + 1]);
        }
        else if (MovingPair[0].mapPosition.x < MovingPair[1].mapPosition.x && MovingPair[0].mapPosition.y > 0)
        {
            SwapTwoUnit(MovingPair[0], UnitArray[(int)MovingPair[0].mapPosition.y - 1][(int)MovingPair[0].mapPosition.x - 1]);
        }
        else if (MovingPair[0].mapPosition.x > MovingPair[1].mapPosition.x)
        {
            MovingPair[0].mapPosition.y++;
            MovingPair[1].mapPosition.y++;
            SwapTwoUnit(MovingPair[1], UnitArray[(int)MovingPair[1].mapPosition.y - 1][(int)MovingPair[1].mapPosition.x + 1]);
        }
        else if (MovingPair[0].mapPosition.x < MovingPair[1].mapPosition.x)
        {
            MovingPair[0].mapPosition.y++;
            MovingPair[1].mapPosition.y++;
            SwapTwoUnit(MovingPair[0], UnitArray[(int)MovingPair[0].mapPosition.y - 1][(int)MovingPair[0].mapPosition.x + 1]);
        }
        break;
    case SEPERATED:
        break;
    }
}