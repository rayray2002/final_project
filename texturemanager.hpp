#pragma once

#include "texturemanagerclass.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{
    SDL_Surface* tmpSurface = SDL_LoadBMP("./img/miku.bmp");
    // SDL_Surface* tmpSurface = SDL_LoadBMP(texture);

    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}


void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, /*&src,*/NULL, &dest, NULL, NULL, flip);
    cout << "copy" << endl;
    // SDL_Surface* tmpSurface = SDL_LoadBMP("./img/miku.bmp");
    // SDL_Texture* texx = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    // SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    // cout << "(" << dest.w << "," << dest.h << ")" << endl;
}