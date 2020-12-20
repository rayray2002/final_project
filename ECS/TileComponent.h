#pragma once

#include "ECS.hpp"
// #include "TransformComponent.hpp"
// #include "SpriteComponent.hpp"
#include <SDL.h>


class TileComponent : public Component {
public:


    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    // TransformComponent* transform;
    // SpriteComponent* sprite;

    // SDL_Rect tileRect;
    // int tileID;
    // char* path;

    TileComponent() = default;

    ~TileComponent() {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path) {

        texture = TextureManager::LoadTexture(path);

        srcRect.x = srcX;
        srcRect.y = srcY;
        srcRect.h = srcRect.w = 32;

        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = 32;
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

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

    // void init() override {
    //     entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
    //     transform = &entity->getComponent<TransformComponent>();

    //     entity->addComponent<SpriteComponent>(path);
    //     sprite = &entity->getComponent<SpriteComponent>();
    // }
};

    



