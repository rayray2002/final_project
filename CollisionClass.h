#pragma once
#include "ECS/Components.hpp"

class ColliderComponent;

class Collision {

public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, ColliderComponent& colB);
};