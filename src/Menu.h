#include "MenuElement.h"
class Menu
{
public:
    Menu();
    ~Menu();
    void startmenu(SDL_Renderer *);
    int GetMode();
    int GetP1();
    int GetP2();

private:
    void Firstmenu(SDL_Renderer *);
    void Charactermenu(SDL_Renderer *);
    MenuElement *menuelement;
};



