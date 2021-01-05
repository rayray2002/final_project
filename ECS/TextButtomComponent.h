// #pragma once

#ifndef _TEXTBUTTOMCOMPONENT_H
#define _TEXTBUTTOMCOMPONENT_H

#include <SDL.h>
#include "../Game.h"
#include "Components.h"
#include "../TextureManager.h"
#include "ECS.h"
#include <map>
using namespace std;

class TextButtomComponent : public Component
{
private:
    const char *file;
    // const char *text;
    TTF_Font *font;
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Rect destR, srcR;
    SDL_Color color;
    string text;
    stringstream Text;

public:
    TextButtomComponent(int xpos, int ypos, int h, int w, const char *f)
    {
        destR.x = xpos;
        destR.y = ypos;
        destR.h = h;
        destR.w = w;
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = ypos;
        srcR.w = xpos;
        text = "f";
    }
    ~TextButtomComponent()
    {
    }

    void init() override
    {
    }

    void update() override
    {
        // static int x;
        // static int y;
        // x = Game::event.motion.x;
        // y = Game::event.motion.y;
        // if (Game::event.type == SDL_MOUSEMOTION)
        // {
        //     if (x > destR.x && y > destR.y && x < destR.x + destR.w && y < destR.y + destR.h)
        //     {
        //         color = {255, 223, 0};
        //     }
        //     else
        //     {
        //         color = {0, 255, 255};
        //     }
        // }
    }

    void draw() override
    {
        font = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 1000);
        TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
        color = {255, 223, 0};
        Text.str("");
        Text << text;
        surface = TTF_RenderText_Solid(font, "haha" /*Text.str().c_str()*/, color);
        if (!surface)
        {
            cout << "NO SURFACE" << endl;
        }
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        if (!texture)
        {
            cout << "NO TEXTURE" << endl;
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        }
        SDL_FreeSurface(surface);
        SDL_RenderCopy(Game::renderer, texture, NULL, &destR);
        SDL_DestroyTexture(texture);
        // TextureManager::Draw(texture, srcR, destR);
        cout << "DRAW " << file << endl;
        TTF_CloseFont(font);
        font = NULL;
    }
};

#endif