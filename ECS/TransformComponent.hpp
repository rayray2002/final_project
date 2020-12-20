#pragma once
#include "../Vector2D.h"

class TransformComponent : public Component {

public:
    Vector2D position;

    TransformComponent() {
        position.x = 0.0;
        position.y = 0.0;
    }

    TransformComponent(double x, double y) {
        position.x = x;
        position.y = y;
    }

    int x() {
        return position.x;
    }

    int y() {
        return position.y;
    }

    void init() override {
        position.x = 0;
        position.y = 0;
    }

    void update() override {
        position.x++;
        position.y++;
    }
};