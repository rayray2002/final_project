#include <string>
#include "MenuComponent.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>

using namespace std;
class MenuElement
{
	friend class Menu;
public:
	MenuElement();
	~MenuElement();
private:
	int Mode;
    int P1;
    int P2;
    void reset();
    void startvideo(SDL_Renderer *);
    int firstmenu(SDL_Renderer *);
    int charactermenu(SDL_Renderer *);
	int pausemenu(SDL_Renderer *);	
};


