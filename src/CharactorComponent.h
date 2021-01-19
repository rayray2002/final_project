#ifndef _CHARATORCOMPONET_H
#define _CHARATORCOMPONET_H

#include "Components.h"
class Charactor : protected Component
{
private:
    string Name;
    int Blood;
    int LastBlood;
    int KO_Number;
    int Score;
    int Combo;

public:
    virtual void Skill(){};
    virtual void Initialize(){};
};

#endif