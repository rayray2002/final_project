#pragma once

class TransformComponent : public Component {

private:
    int xpos;
    int ypos;

public:

    TransformComponent() {
        xpos = 0;
        ypos = 0;
    }

    TransformComponent(int x, int y) {
        xpos = x;
        ypos = y;
    }

    int x() {
        return xpos;
    }

    int y() {
        return ypos;
    }

    void init() override {
        xpos = 0;
        ypos = 0;
    }

    void update() override {
        xpos++;
        ypos++;
    }

    void setPos(int x, int y) {
        xpos = x;
        ypos = y;
    }

    void x(int x) {
        xpos = x;
    }

    void y(int y) {
        ypos = y;
    }
};