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
        srcR.x = srcR.y = 0;
        srcR.h = srcR.w = 1000;
        file = f;
    }

    ButtomComponent(const ButtomComponent &b)
    {
        destR.x = b.destR.x;
        destR.y = b.destR.y;
        destR.h = b.destR.h;
        destR.w = b.destR.w;
        srcR.x = b.srcR.x;
        srcR.y = b.srcR.y;
        srcR.h = b.srcR.h;
        srcR.w = b.srcR.w;
        file = b.file;
    }

    ~ButtomComponent()
    {
        delete texture;
        texture = NULL;
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