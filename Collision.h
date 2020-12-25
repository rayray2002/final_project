// #pragma once
#ifndef _COLLISION_H
#define _COLLISION_H
#include "ECS/Components.h"

class ColliderComponent;

class Collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, ColliderComponent& colB);
};

#endif