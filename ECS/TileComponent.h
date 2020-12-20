#pragma once

#include "ECS.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include <SDL.h>


class TileComponent : public Component {
public:
    TransformComponent* transform;
    SpriteComponent* sprite;

    SDL_Rect tileRect;
    int tileID;
    char* path;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id) {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.h = h;
        tileRect.w = w;
        tileID = id;

        switch (tileID) {
        case 0:
            path = "./img/sample_red.bmp";
            break;
        case 1:
            path = "./img/sample_green.bmp";
            break;
        case 2:
            path = "./img/sample_yellow.bmp";
            break;
        default:
            break;
        }
    }

    void init() override {
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};

