#ifndef _MIKU_H
#define _MIKU_H

#include "../CharactorComponent.h"

class Miku : public CharactorComponent
{
public:
    bool Skill() override;
    void Initialize() override;
};
#endif