// #pragma once
#ifndef _TILECOMPONENT_H
#define _TILECOMPONENT_H

#include "ECS.h"
#include <SDL.h>

class TileComponent : public Component
{
public:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    // TransformComponent* transform;
    // SpriteComponent* sprite;

    // SDL_Rect tileRect;
    // int tileID;
    // char* path;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int xpos, int ypos, /*int tsize, int tscale, */const char* path) {

        texture = TextureManager::LoadTexture(path);

        position.x = xpos;
        position.y = ypos;

        srcRect.x = srcX;
        srcRect.y = srcY;
        // srcRect.h = srcRect.w = tsize;
        srcRect.h = srcRect.w = 100;

        destRect.x = xpos;
        destRect.y = ypos;
        // destRect.w = destRect.h = tsize * tscale;
        destRect.w = destRect.h = 100;
        // tileRect.x = x;
        // tileRect.y = y;
        // tileRect.h = h;
        // tileRect.w = w;
        // tileID = id;

        // switch (tileID) {
        // case 0:
        //     path = "./img/sample_red.bmp";
        //     break;
        // case 1:
        //     path = "./img/sample_green.bmp";
        //     break;
        // case 2:
        //     path = "./img/sample_yellow.bmp";
        //     break;
        // default:
        //     break;
    }

    void update() override
    {
        destRect.x = position.x;// - Game::camera.x;
        destRect.y = position.y;// - Game::camera.y;
    }

    void draw() override
    {
        cout << "draw" << endl;
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
        // SDL_RenderPresent(Game::renderer);

    }
};

    



#endif