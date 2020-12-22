#pragma once

#include "Components.hpp"
#include <SDL.h>
#include "Animation.h"
#include "../AssetManager.h"
#include <map>

class SpriteComponent : public Component 
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int animIndex = 0;

    map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    SpriteComponent(const char* path) 
    {
        setTex(path);
    }

    SpriteComponent(string id, bool isAnimated) 
    {
        animated = isAnimated;

        Animation idle = Animation(0, 3, 100); //0 index 3 picture number 100 frame size
        Animation walk = Animation(1, 8, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        Play("Idle");

        // speed = mSpeed;
        // frames = nFrames;
        setTex(id);
    }

    ~SpriteComponent()
    {
        // SDL_DestroyTexture(texture);
    }

    void setTex(string id)
    {
        texture = Game::assets->GetTexture(id);
    }

    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.h = transform->width;
        srcRect.w = transform->height;
    }

    void update() override
    {
        if (animated)
        {
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames); // put actions in a picture
            //Then if we need animation, we only need to move the camera.
        }

        srcRect.y = animIndex * transform->height;

        destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
        destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
        destRect.h = transform->width * transform->scale;
        destRect.w = transform->height * transform->scale;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }

    void Play(const char* animName)
    {
        frames    = animations[animName].frames;
        animIndex =  animations[animName].index;
        speed     =  animations[animName].speed;
    }
};
