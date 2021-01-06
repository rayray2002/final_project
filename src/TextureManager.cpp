
#include "TextureManager.h"
using namespace std;
// #include "ECS/BackGroundComponent.hpp"
#include <map>

SDL_Texture *TextureManager::LoadTexture(const char *texture)
{
        SDL_Surface *tmpSurface = SDL_LoadBMP(texture);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
        return tex;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
        SDL_DestroyTexture(tex);
}
