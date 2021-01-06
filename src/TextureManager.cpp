
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

// SDL_Texture *TextureManager::LoadTextTexture(const char *text, SDL_Color color, SDL_Rect dst)
// {
//         TTF_Font *font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
//         // TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
//         SDL_Color Color = color;
//         stringstream text_in;
//         text_in.str("");
//         text_in << text;
//         SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, text_in.str().c_str(), Color);
//         SDL_Texture *tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
//         SDL_RenderCopy(Game::renderer, tex, NULL, &dst);
//         SDL_FreeSurface(tmpSurface);
//         TTF_CloseFont(font);
//         return tex;
// }

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest)
{
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
        SDL_DestroyTexture(tex);
}
