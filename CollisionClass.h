#pragma once
#include "ECS/Components.hpp"

class Collision {

public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};