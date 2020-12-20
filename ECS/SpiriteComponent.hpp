#pragma once

#include "Components.hpp"
#include <SDL2/SDL.h>

class SpiriteComponent : public Component {


private:
    PositionComponent *position;
    SDL_Texture *texture;
    SDL_Rect srcRecr, destRect;



public:
    SpiriteComponent() = default;
    SpiriteComponent(const char* path) {

    }

    void init() override {

    }

    void update() override {

    }

    void draw() override {
        
    }

};
