// #pragma once
#ifndef _ANIMATION_H
#define _ANIMATION_H

struct Animation 
{

    int index;
    int frames;
    int speed;

    Animation() {}
    Animation(int i, int f, int s) 
    {
        index = i;
        frames = f;
        speed = s;
    }
};

#endif