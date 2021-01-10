#ifndef _BACKGROUNDCOMPONENT_H
#define _BACKGROUNDCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "Components.h"
#include <map>
#include <string>
using namespace std;

class BackGroundComponent : public Component
{
private:
    int mode;

public:
    SDL_Texture *texture;
    SDL_Rect srcR, destR;

    BackGroundComponent()
    {
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 720;
        srcR.w = 1280;
        destR.x = 0;
        destR.y = 0;
        destR.h = 720;
        destR.w = 1280;
    }
    ~BackGroundComponent()
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

        static int num = 0;
        static int i = 1;
        static bool OK = true;
        num++;
        SDL_Surface *tmpSurface;
        if (num % 1 == 0)
            i++;
        switch (Game::event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if (Game::event.motion.x > WIDTH - 320 && Game::event.motion.x < WIDTH - 20 &&
                Game::event.motion.y > HEIGHT - 220 && Game::event.motion.y < HEIGHT - 20)
            {
                OK = !OK;
            }
        }
        if (1)
        {
            if (i > 3600)
                i = 0;
            string path = "./img/background/" + to_string(i) + ".bmp";
            tmpSurface = SDL_LoadBMP(path.c_str());
        }
        texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
        if (num == 2)
            num = 0;
        TextureManager::Draw(texture, srcR, destR);
    }
};

#endif