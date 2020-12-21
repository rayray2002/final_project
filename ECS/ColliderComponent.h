#pragma once

#include <string>
#include <SDL.h>
#include "Components.hpp"
using namespace std;

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, destR;

    TransformComponent* transform;

    ColliderComponent(string t) {
        tag = t;
    }

    void init() override {
        if (entity->hasComponent<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        tex = TextureManager::LoadTexture("./img/miku.bmp");
        srcR = { 0, 0, 32, 32 };
        destR = { collider.x , collider.y, collider.w, collider.h };

        // Game::colliders.push_back(this);
    }

    void update() override {

        if (tag != "miku") {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;

        destR.x = collider.x - Game::camera.x;
        destR.y = collider.y - Game::camera.y;
    }

    void draw() override {
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};
