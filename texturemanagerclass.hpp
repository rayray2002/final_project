#pragma once
#include "gameloop.hpp"



class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* filename);
};