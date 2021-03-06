#ifndef _MENUCOMPONENT_H
#define _MENUCOMPONENT_H
#include <SDL.h>
class Menu
{
public:
    Menu();
    ~Menu();
    void reset();
    void startmenu(SDL_Renderer *);
    int pausemenu(SDL_Renderer *);
    int GetMode();
    int GetP1();
    int GetP2();

private:
    int Mode;
    int P1;
    int P2;
    int firstmenu(SDL_Renderer *);
    void Firstmenu(SDL_Renderer *);
    int charactermenu(SDL_Renderer *);
    void Charactermenu(SDL_Renderer *);
    void startvideo(SDL_Renderer *);
};

#endif
