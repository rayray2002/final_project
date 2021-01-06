#ifndef _BUTTOMCOMPONENT_H
#define _BUTTOMCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "Components.h"
#include "../TextureManager.h"
#include "ECS.h"
#include <map>
using namespace std;

class ButtomComponent : public Component
{
private:
    const char *file;

public:
    SDL_Texture *texture;
    SDL_Rect destR, srcR;
    SDL_Color color = {255, 223, 0};

    ButtomComponent(int xpos, int ypos, int h, int w, const char *f)
    {
        destR.x = xpos;
        destR.y = ypos;
        destR.h = h;
        destR.w = w;
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 1000;
        srcR.w = 1000;
        file = f;
    }
    ~ButtomComponent()
    {
    }

    void init() override
    {
    }

    void update() override
    {
    }

    void draw() override
    {
        SDL_Surface *tmpSurface = SDL_LoadBMP(file);
        texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_FreeSurface(tmpSurface);
        TextureManager::Draw(texture, srcR, destR);
    }
};

#endif