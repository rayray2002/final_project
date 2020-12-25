// #pragma once
#ifndef _COLLIDERCOMPONENT_H
#define _COLLIDERCOMPONENT_H

#include <string>
#include <SDL.h>
#include "Components.h"
using namespace std;

class ColliderComponent : public Component 
{
public:
    SDL_Rect collider;
    string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    TransformComponent* transform;

    ColliderComponent(string t) 
    {
        tag = t;
    }

    ColliderComponent(string t, int xpos, int ypos, int size)
    {
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override 
    {
        if (entity->hasComponent<TransformComponent>()) 
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::LoadTexture("./img/miku.bmp");
        srcR.x = 0;
        srcR.y = 0;
        srcR.h = 32;
        srcR.w = 32;
        // destR = { collider.x , collider.y, collider.w, collider.h };
        destR.x = 0;
        destR.y = 0;
        destR.w = 100;
        destR.h = 100;
        // Game::colliders.push_back(this);
    }

    void update() override 
    {

        // if (tag != "miku") 
        // {
        //     collider.x = static_cast<int>(transform->position.x);
        //     collider.y = static_cast<int>(transform->position.y);
        //     collider.w = transform->width * transform->scale;
        //     collider.h = transform->height * transform->scale;
        // }
        // collider.x = static_cast<int>(transform->position.x);
        // collider.y = static_cast<int>(transform->position.y);
        // collider.w = transform->width * transform->scale;
        // collider.h = transform->height * transform->scale;
        collider.x = 0;
        collider.y = 0;
        collider.w = 100;
        collider.h = 100;


        destR.x = collider.x;// - Game::camera.x;
        destR.y = collider.y;// - Game::camera.y;
    }

    void draw() override 
    {
        cout << "draw - collider" << endl;
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
        // SDL_RenderPresent(Game::renderer);

    }
};

#endif