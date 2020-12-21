#pragma once
#include "gameloop.h"
// #include "game.hpp"



class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* filename);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

// SDL_Texture* TextureManager::LoadTexture(const char* texture)
// {
//     SDL_Surface* tmpSurface = SDL_LoadBMP(texture);
//     SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
//     SDL_FreeSurface(tmpSurface);
//     return tex;
// }


// void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
// {
//     SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
// }