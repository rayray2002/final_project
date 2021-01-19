#include <SDL2/SDL.h>
#include "Menu.h"
#include <string>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#define WIDTH 1280
#define HEIGHT 720

using namespace std;

Menu::Menu()
{
    menuelement=new MenuElement;
    menuelement->reset();
}

Menu::~Menu()
{
    delete menuelement;
}

void Menu::startmenu(SDL_Renderer *renderer)
{
    menuelement->startvideo(renderer);
    Firstmenu(renderer);
}

void Menu::Firstmenu(SDL_Renderer *renderer)
{
    switch (menuelement->firstmenu(renderer))
    {
    case 0: /*single player*/
        menuelement->Mode = 1;
        break;
    case 1: /*double player*/
        menuelement->Mode = 2;
        Charactermenu(renderer);
        break;
    }
}

void Menu::Charactermenu(SDL_Renderer *renderer)
{
    switch (menuelement->charactermenu(renderer))
    {
    case -1:
        Firstmenu(renderer);
        menuelement->reset();
        break;
    case 0:;
    }
}

int Menu::GetMode()
{
    return menuelement->Mode;
}

int Menu::GetP1()
{
    return menuelement->P1;
}

int Menu::GetP2()
{
    return menuelement->P2;
}



