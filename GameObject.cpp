#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
    xpos = x;
    ypos = y;
    objTexture = TextureManager::LoadTexture(texturesheet);
}

void GameObject::Update()
{
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = xpos;
    destRect.w = ypos;
    destRect.x = srcRect.x * 2;
    destRect.y = srcRect.y * 2;
}


void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}