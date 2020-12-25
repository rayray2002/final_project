// #pragma once
#ifndef _TEXTUREMANAER_H
#define _TEXTUREMANAER_H
#include "Game.h"
#include <map>
using namespace std;



class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
    map<int, const char*> MIKUGIF;
};

#endif