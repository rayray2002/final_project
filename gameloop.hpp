#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

class Game {

public:
    Game();
    ~Game();

    void handleEveants();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void update();
    void render();
    void clean();
    void showmenu(SDL_Surface* screen, TTF_Font* font);
    //void linkstart();

    bool running() { return isRunning; };

private:
    int cnt = 64; //count
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
};

#endif /* Game_hpp */