
#include "texturemanagerclass.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
    SDL_Surface* tmpSurface = SDL_LoadBMP(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}