// #pragma once
#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 32;
    int width = 32;
    int scale = 1;
    int speed = 3;

    TransformComponent()
    {
        // position.Zero();
        position.x = 0;
        position.y = 0;
        height = 100;
        width = 100;
    }

    TransformComponent(int sc)
    {
        // position.x = 400;
        // position.y = 320;
        position.x = 0;
        position.y = 0;

        scale = sc;
    }

    TransformComponent(double x, double y, int h, int w, int sc)
    {
        // position.x = x;
        // position.y = y;
        // height = h;
        // width = h;
        position.x = 0;
        position.y = 0;
        height = 100;
        width = 100;
        scale = sc;
    }

    int x() { return position.x; }
    int y() { return position.y; }

    void init() override
    {
        velocity.Zero();
    }

    void update() override
    {
        // position.x += velocity.x * speed;
        // position.y += velocity.y * speed;
    }
};

#endif