#pragma once

#include "Components.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {


private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;



public:
    SpriteComponent() = default;
    SpriteComponent(const char* path) {
        setTex(path);
    }

    ~SpriteComponent() {
        SDL_DestroyTexture(texture);
    }

    void setTex(const char* path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {

        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.h = transform->width;
        srcRect.w = transform->height;
    }

    void update() override {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        destRect.h = transform->width * transform->scale;
        destRect.w = transform->height * transform->scale;
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

};
