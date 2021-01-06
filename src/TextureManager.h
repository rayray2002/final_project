// #pragma once
#ifndef _TEXTUREMANAER_H
#define _TEXTUREMANAER_H
#include "Game.h"
#include <map>
using namespace std;

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const char *filename);
    // static SDL_Texture *LoadTextTexture(const char *text, SDL_Color color);
    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);
    map<int, const char *> MIKUGIF;
};

#endif