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
        if (num % 2 == 0)
            i++;
        switch (Game::event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            if (Game::event.motion.x > WIDTH - 320 && Game::event.motion.x < WIDTH - 20 &&
                Game::event.motion.y > HEIGHT - 220 && Game::event.motion.y < HEIGHT - 20)
            {
                OK = !OK;
                cout << "OK" << endl;
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
        SDL_PumpEvents();

        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 64);
        SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
        SDL_Rect rec1, rec2;
        rec1.x = 100;
        rec1.y = 35;
        rec1.h = 650;
        rec1.w = 300;
        rec2.x = 880;
        rec2.y = 35;
        rec2.h = 650;
        rec2.w = 300;
        SDL_RenderDrawRect(Game::renderer, &rec1);
        SDL_RenderDrawRect(Game::renderer, &rec2);
        SDL_RenderFillRect(Game::renderer, &rec1);
        SDL_RenderFillRect(Game::renderer, &rec2);

        SDL_SetRenderDrawColor(Game::renderer, 255, 223, 0, 255);
        SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);
        for (int i = -2; i <= 2; ++i)
        {
            //1
            SDL_RenderDrawLine(Game::renderer, 100 + i, 35 + i, 400 + i, 35 + i);
            SDL_RenderDrawLine(Game::renderer, 100 + i, 685 + i, 400 + i, 685 + i);
            SDL_RenderDrawLine(Game::renderer, 100 + i, 35 + i, 100 + i, 685 + i);
            SDL_RenderDrawLine(Game::renderer, 400 + i, 35 + i, 400 + i, 685 + i);
            //2
            SDL_RenderDrawLine(Game::renderer, 1180 + i, 35 + i, 880 + i, 35 + i);
            SDL_RenderDrawLine(Game::renderer, 1180 + i, 685 + i, 880 + i, 685 + i);
            SDL_RenderDrawLine(Game::renderer, 1180 + i, 35 + i, 1180 + i, 685 + i);
            SDL_RenderDrawLine(Game::renderer, 880 + i, 35 + i, 880 + i, 685 + i);
        }

        TTF_Font *font = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
        SDL_Surface *textsurface = TTF_RenderText_Solid(font, "score:", {255, 223, 0});
        SDL_Texture *texttexture = SDL_CreateTextureFromSurface(Game::renderer, textsurface);
        SDL_Rect textrec;
        textrec.x = 425;
        textrec.y = 335;
        textrec.h = textsurface->clip_rect.h;
        textrec.w = textsurface->clip_rect.w;
        SDL_FreeSurface(textsurface);
        SDL_RenderCopy(Game::renderer, texttexture, NULL, &textrec);
        SDL_DestroyTexture(texttexture);
        TTF_CloseFont(font);
    }
};

#endif