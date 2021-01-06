#ifndef _MENUCOMPONENT_H
#define _MENUCOMPONENT_H
#include <SDL.h>
class Menu
{
public:
    Menu();
    ~Menu();
    int firstmenu(SDL_Window *, SDL_Renderer *);
    int charactermenu(SDL_Window *, SDL_Renderer *);
    void startmenu(SDL_Window *, SDL_Renderer *);
    void Charactermenu(SDL_Window *, SDL_Renderer *);
    int getMode() { return mode; };

private:
    int mode;
};

#endif