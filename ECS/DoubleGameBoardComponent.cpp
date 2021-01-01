#include "DoubleGameBoardComponent.h"
#include "../Game.h"
#include <SDL.h>

void DoubleGameBoardComponent::init()
{
}

void DoubleGameBoardComponent::init1()
{
    InitializeRamdomUnitOnTop(2, 1);
    InitializeRamdomUnitOnTop(3, 1);
}

void DoubleGameBoardComponent::init2()
{
    InitializeRamdomUnitOnTop(2, 2);
    InitializeRamdomUnitOnTop(3, 2);
}

void DoubleGameBoardComponent::update()
{
    static int n = 0;
    if (n == 2)
    {

        n = 0;
    }
    n++;
    UpdateBoardMovingState(1);
    UpdateBoardMovingState(2);
    Move(1);
    Move(2);

    UpdateBoardMovingState(1);
    UpdateBoardMovingState(2);
    if (!AnyThingMoving(1))
    {
        init1();
    }
    else
    {
        MoveDown(1);
    }
    if (!AnyThingMoving(2))
    {
        init2();
    }
    else
    {
        MoveDown(2);
    }
}

void DoubleGameBoardComponent::draw()
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 6; j++)
        {
            if (UnitArray1[i][j].color != Empty)
                UnitArray1[i][j].isActive = true;
            if (UnitArray1[i][j].isMoving || UnitArray1[i][j].isActive)
            {
                SDL_Surface *tmpSurface;
                switch (UnitArray1[i][j].color)
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
                UnitArray1[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
                if (UnitArray1[i][j].color != Empty)
                    TextureManager::Draw(UnitArray1[i][j].texture, UnitArray1[i][j].srcR, UnitArray1[i][j].destR);
            }
        }
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 6; j++)
        {
            if (UnitArray2[i][j].color != Empty)
                UnitArray2[i][j].isActive = true;
            if (UnitArray2[i][j].isMoving || UnitArray2[i][j].isActive)
            {
                SDL_Surface *tmpSurface;
                switch (UnitArray2[i][j].color)
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
                UnitArray2[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
                if (UnitArray2[i][j].color != Empty)
                    TextureManager::Draw(UnitArray2[i][j].texture, UnitArray2[i][j].srcR, UnitArray2[i][j].destR);
            }
        }
}

unit *DoubleGameBoardComponent::getDataByMapPosition(int ypos, int xpos, int side)
{
    if (side == 1)
        return &UnitArray1[ypos][xpos];
    else if (side == 2)
        return &UnitArray2[ypos][xpos];
}

void DoubleGameBoardComponent::ReSetAllArrayZero(int side)
{
    if (side == 1)
    {
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 6; j++)
            {
                UnitArray1[i][j].destR.x = 100 + 50 * j;
                UnitArray1[i][j].destR.y = 35 + 50 * i;
                UnitArray1[i][j].destR.w = UnitArray1[i][j].destR.h = 50;
                UnitArray1[i][j].color = Empty;
                UnitArray1[i][j].isActive = false;
                UnitArray1[i][j].isMoving = false;
                UnitArray1[i][j].mapPosition.x = j;
                UnitArray1[i][j].mapPosition.y = i;
                UnitArray1[i][j].srcR.x = 0;
                UnitArray1[i][j].srcR.y = UnitArray1[i][j].srcR.x = 0;
                UnitArray1[i][j].srcR.w = UnitArray1[i][j].srcR.h = 1000;
                SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
                UnitArray1[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
            }
    }
    else if (side == 2)
    {
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 6; j++)
            {
                UnitArray2[i][j].destR.x = 880 + 50 * j;
                UnitArray2[i][j].destR.y = 35 + 50 * i;
                UnitArray2[i][j].destR.w = UnitArray2[i][j].destR.h = 50;
                UnitArray2[i][j].color = Empty;
                UnitArray2[i][j].isActive = false;
                UnitArray2[i][j].isMoving = false;
                UnitArray2[i][j].mapPosition.x = j;
                UnitArray2[i][j].mapPosition.y = i;
                UnitArray2[i][j].srcR.x = 0;
                UnitArray2[i][j].srcR.y = UnitArray2[i][j].srcR.x = 0;
                UnitArray2[i][j].srcR.w = UnitArray2[i][j].srcR.h = 1000;
                SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
                UnitArray2[i][j].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
                SDL_FreeSurface(tmpSurface);
            }
    }
}

void DoubleGameBoardComponent::ReSetZeroUnit(int &xpos, int &ypos, int side)
{
    if (side == 1)
    {
        UnitArray1[ypos][xpos].color = Empty;
        UnitArray1[ypos][xpos].isActive = false;
        UnitArray1[ypos][xpos].isMoving = false;
        SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
        UnitArray1[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
    }
    else if (side == 2)
    {
        UnitArray2[ypos][xpos].color = Empty;
        UnitArray2[ypos][xpos].isActive = false;
        UnitArray2[ypos][xpos].isMoving = false;
        SDL_Surface *tmpSurface = SDL_LoadBMP("./img/banana.bmp");
        UnitArray2[ypos][xpos].texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
    }
}

void DoubleGameBoardComponent::Swap(unit &a, unit &b)
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

void DoubleGameBoardComponent::SwapTwoUnit(int x1, int y1, int x2, int y2, int side)
{
    if (side == 1)
        Swap(UnitArray1[y1][x1], UnitArray1[y2][x2]);
    else if (side == 2)
        Swap(UnitArray2[y1][x1], UnitArray2[y2][x2]);
}

void DoubleGameBoardComponent::SwapTwoUnit(unit &u1, unit &u2, int side)
{
    SwapTwoUnit(u1.mapPosition.x, u1.mapPosition.y, u2.mapPosition.x, u2.mapPosition.y, side);
}

void DoubleGameBoardComponent::InitializeRamdomUnitOnTop(int topx, int side)
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
    if (side == 1)
    {
        UnitArray1[0][topx].color = tmpColor;
        UnitArray1[0][topx].isMoving = true;
        UnitArray1[0][topx].isActive = true;
    }
    else if (side == 2)
    {
        UnitArray2[0][topx].color = tmpColor;
        UnitArray2[0][topx].isMoving = true;
        UnitArray2[0][topx].isActive = true;
    }
}

bool DoubleGameBoardComponent::AnyThingMoving(int side)
{
    if (side == 1)
    {
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 6; j++)
            {
                if (UnitArray1[i][j].isMoving)
                    return true;
            }
        return false;
    }
    else if (side == 2)
    {
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 6; j++)
            {
                if (UnitArray2[i][j].isMoving)
                    return true;
            }
        return false;
    }
}

void DoubleGameBoardComponent::Move(int side)
{
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
                        if (UnitArray2[i][j].isMoving && UnitArray2[i + 1][j].color == Empty)
                            SwapTwoUnit(UnitArray2[i][j], UnitArray2[i + 1][j], 2);
                    }
                break;
            case SDLK_LEFT:
                for (int i = 0; i < 13; i++)
                    for (int j = 1; j < 6; j++) // start from 1
                    {
                        if (UnitArray2[i][j].isMoving && UnitArray2[i][j - 1].color == Empty)
                            SwapTwoUnit(UnitArray2[i][j], UnitArray2[i][j - 1], 2);
                    }
                break;
            case SDLK_RIGHT:
                for (int i = 0; i < 13; i++)
                    for (int j = 4; j >= 0; j--) // end at 0
                    {
                        if (UnitArray2[i][j].isMoving && UnitArray2[i][j + 1].color == Empty)
                            SwapTwoUnit(UnitArray2[i][j], UnitArray2[i][j + 1], 2);
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
    }
    else if (side == 1)
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_s:
                for (int i = 11; i >= 0; i--) // start from 11 to 0
                    for (int j = 0; j < 6; j++)
                    {
                        if (UnitArray1[i][j].isMoving && UnitArray1[i + 1][j].color == Empty)
                            SwapTwoUnit(UnitArray1[i][j], UnitArray1[i + 1][j], 1);
                    }
                break;
            case SDLK_a:
                for (int i = 0; i < 13; i++)
                    for (int j = 1; j < 6; j++) // start from 1
                    {
                        if (UnitArray1[i][j].isMoving && UnitArray1[i][j - 1].color == Empty)
                            SwapTwoUnit(UnitArray1[i][j], UnitArray1[i][j - 1], 1);
                    }
                break;
            case SDLK_d:
                for (int i = 0; i < 13; i++)
                    for (int j = 4; j >= 0; j--) // end at 0
                    {
                        if (UnitArray1[i][j].isMoving && UnitArray1[i][j + 1].color == Empty)
                            SwapTwoUnit(UnitArray1[i][j], UnitArray1[i][j + 1], 1);
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

void DoubleGameBoardComponent::MoveDown(int side)
{
    if (side == 1)
    {
        static int ii = 0;
        if (ii == 30)
        {
            for (int i = 11; i >= 0; i--)
                for (int j = 0; j < 6; j++)
                    if (UnitArray1[i][j].color != Empty && UnitArray1[i + 1][j].color == Empty)
                        SwapTwoUnit(UnitArray1[i][j], UnitArray1[i + 1][j], 1);
            ii = 0;
        }
        ii++;
    }
    else if (side == 2)
    {
        static int ii = 0;
        if (ii == 30)
        {
            for (int i = 11; i >= 0; i--)
                for (int j = 0; j < 6; j++)
                    if (UnitArray2[i][j].color != Empty && UnitArray2[i + 1][j].color == Empty)
                        SwapTwoUnit(UnitArray2[i][j], UnitArray2[i + 1][j], 2);
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
                if (UnitArray1[i][j].color == Empty)
                {
                    UnitArray1[i][j].isMoving = false;
                }
                else if (UnitArray1[i][j].mapPosition.y == 12)
                {
                    UnitArray1[i][j].isMoving = false;
                }
                else if (UnitArray1[i][j].mapPosition.y < 12)
                {
                    if (UnitArray1[i + 1][j].color != Empty && !UnitArray1[i + 1][j].isMoving)
                        UnitArray1[i][j].isMoving = false;
                }
                else
                    UnitArray1[i][j].isMoving = true;
            }
    }
    else if (side == 2)
    {
        for (int i = 12; i >= 0; i--)
            for (int j = 0; j < 6; j++)
            {
                if (UnitArray2[i][j].color == Empty)
                {
                    UnitArray2[i][j].isMoving = false;
                }
                else if (UnitArray2[i][j].mapPosition.y == 12)
                {
                    UnitArray2[i][j].isMoving = false;
                }
                else if (UnitArray2[i][j].mapPosition.y < 12)
                {
                    if (UnitArray2[i + 1][j].color != Empty && !UnitArray2[i + 1][j].isMoving)
                        UnitArray2[i][j].isMoving = false;
                }
                else
                    UnitArray2[i][j].isMoving = true;
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
                if (UnitArray1[i][j].isMoving)
                {
                    MovingPair1[n] = UnitArray1[i][j];
                    n++;
                }
            }
    }
    else if (side == 2)
    {
        int n = 0;
        for (int i = 0; i < 13; i++)
            for (int j = 0; j < 6; j++)
            {
                if (n == 2)
                    break;
                if (UnitArray2[i][j].isMoving)
                {
                    MovingPair2[n] = UnitArray2[i][j];
                    n++;
                }
            }
    }
}

void DoubleGameBoardComponent::UpdateMovingPairState(int side)
{
    if (side == 1)
    {
        if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y + 1 || MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y - 1)
        {
            if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x)
                MovingPairState1 = UP_AND_DOWN;
        }
        else if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x + 1 || MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x - 1)
        {
            if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y)
                MovingPairState1 = RIGHT_AND_LEFT;
        }
        else
            MovingPairState1 = SEPERATED;
    }
    else if (side == 2)
    {
        if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y + 1 || MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y - 1)
        {
            if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x)
                MovingPairState2 = UP_AND_DOWN;
        }
        else if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x + 1 || MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x - 1)
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
                    if (UnitArray1[i][j].mapPosition.x == MovingPair1[0].mapPosition.x && UnitArray1[i][j].color == Empty)
                        p1yd = UnitArray1[i][j].mapPosition.y;
                    if (UnitArray1[i][j].mapPosition.x == MovingPair1[1].mapPosition.x && UnitArray1[i][j].color == Empty)
                        p2yd = UnitArray1[i][j].mapPosition.y;
                }
        SwapTwoUnit(MovingPair1[0], UnitArray1[p1yd][(int)MovingPair1[0].mapPosition.x], 1);
        SwapTwoUnit(MovingPair1[1], UnitArray1[p2yd][(int)MovingPair1[1].mapPosition.x], 1);
    }
    else if (side == 2)
    {
        int p1yd;
        int p2yd;
        if (MovingPairState2 == RIGHT_AND_LEFT)
            for (int i = 0; i < 13; i++)
                for (int j = 0; j < 6; j++)
                {
                    if (UnitArray2[i][j].mapPosition.x == MovingPair2[0].mapPosition.x && UnitArray2[i][j].color == Empty)
                        p1yd = UnitArray1[i][j].mapPosition.y;
                    if (UnitArray2[i][j].mapPosition.x == MovingPair2[1].mapPosition.x && UnitArray2[i][j].color == Empty)
                        p2yd = UnitArray2[i][j].mapPosition.y;
                }
        SwapTwoUnit(MovingPair2[0], UnitArray2[p1yd][(int)MovingPair2[0].mapPosition.x], 2);
        SwapTwoUnit(MovingPair2[1], UnitArray2[p2yd][(int)MovingPair2[1].mapPosition.x], 2);
    }
}

void DoubleGameBoardComponent::Spin(int side)
{
    UpdateBoardMovingState(side);
    UpdateMovingPairLastestVersion(side);
    if (side == 1)
    {
        if (PairAdjacent(side))
        {
            switch (MovingPairState1)
            {
            case UP_AND_DOWN:
                if (MovingPair1[0].mapPosition.y < MovingPair1[1].mapPosition.y && MovingPair1[1].mapPosition.x < 5)
                {
                    if (UnitArray1[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1].color == Empty)
                    {
                        SwapTwoUnit(MovingPair1[0], UnitArray1[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
                    }
                }
                else if (MovingPair1[0].mapPosition.y < MovingPair1[1].mapPosition.y && MovingPair1[1].mapPosition.x == 5)
                {
                    SwapTwoUnit(MovingPair1[0], UnitArray1[(int)MovingPair1[0].mapPosition.y][(int)MovingPair1[0].mapPosition.x - 1], 1);
                    SwapTwoUnit(MovingPair1[1], UnitArray1[(int)MovingPair1[1].mapPosition.y][(int)MovingPair1[1].mapPosition.x - 1], 1);
                    if (UnitArray1[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1].color == Empty)
                        SwapTwoUnit(MovingPair1[0], UnitArray1[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
                }
                break;
            case RIGHT_AND_LEFT:
                if (MovingPair1[0].mapPosition.x < MovingPair1[1].mapPosition.x && MovingPair1[0].mapPosition.y > 0)
                {
                    SwapTwoUnit(MovingPair1[0], UnitArray1[(int)MovingPair1[0].mapPosition.y - 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
                }
                else if (MovingPair1[0].mapPosition.x < MovingPair1[1].mapPosition.x)
                {
                    SwapTwoUnit(MovingPair1[0], UnitArray1[(int)MovingPair1[0].mapPosition.y + 1][(int)MovingPair1[0].mapPosition.x], 1);
                    SwapTwoUnit(MovingPair1[1], UnitArray1[(int)MovingPair1[1].mapPosition.y + 1][(int)MovingPair1[1].mapPosition.x], 1);
                    SwapTwoUnit(MovingPair1[0], UnitArray1[(int)MovingPair1[0].mapPosition.y - 1][(int)MovingPair1[0].mapPosition.x + 1], 1);
                }
                break;
            case SEPERATED:
                break;
            }
        }
    }
    else if (side == 2)
    {
        if (PairAdjacent(side))
        {
            switch (MovingPairState2)
            {
            case UP_AND_DOWN:
                if (MovingPair2[0].mapPosition.y < MovingPair2[1].mapPosition.y && MovingPair2[1].mapPosition.x < 5)
                {
                    if (UnitArray2[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1].color == Empty)
                    {
                        SwapTwoUnit(MovingPair2[0], UnitArray2[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
                    }
                }
                else if (MovingPair2[0].mapPosition.y < MovingPair2[1].mapPosition.y && MovingPair2[1].mapPosition.x == 5)
                {
                    SwapTwoUnit(MovingPair2[0], UnitArray2[(int)MovingPair2[0].mapPosition.y][(int)MovingPair2[0].mapPosition.x - 1], 2);
                    SwapTwoUnit(MovingPair2[1], UnitArray2[(int)MovingPair2[1].mapPosition.y][(int)MovingPair2[1].mapPosition.x - 1], 2);
                    if (UnitArray2[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1].color == Empty)
                        SwapTwoUnit(MovingPair2[0], UnitArray2[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
                }
                break;
            case RIGHT_AND_LEFT:
                if (MovingPair2[0].mapPosition.x < MovingPair2[1].mapPosition.x && MovingPair2[0].mapPosition.y > 0)
                {
                    SwapTwoUnit(MovingPair2[0], UnitArray2[(int)MovingPair2[0].mapPosition.y - 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
                }
                else if (MovingPair2[0].mapPosition.x < MovingPair2[1].mapPosition.x)
                {
                    SwapTwoUnit(MovingPair2[0], UnitArray2[(int)MovingPair2[0].mapPosition.y + 1][(int)MovingPair2[0].mapPosition.x], 2);
                    SwapTwoUnit(MovingPair2[1], UnitArray2[(int)MovingPair2[1].mapPosition.y + 1][(int)MovingPair2[1].mapPosition.x], 2);
                    SwapTwoUnit(MovingPair2[0], UnitArray2[(int)MovingPair2[0].mapPosition.y - 1][(int)MovingPair2[0].mapPosition.x + 1], 2);
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
        if (MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x - 1 && MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y)
            return true;
        if (MovingPair1[0].mapPosition.y == MovingPair1[1].mapPosition.y - 1 && MovingPair1[0].mapPosition.x == MovingPair1[1].mapPosition.x)
            return true;
        else
            return false;
    }
    else if (side == 2)
    {
        if (MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x - 1 && MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y)
            return true;
        if (MovingPair2[0].mapPosition.y == MovingPair2[1].mapPosition.y - 1 && MovingPair2[0].mapPosition.x == MovingPair2[1].mapPosition.x)
            return true;
        else
            return false;
    }
}