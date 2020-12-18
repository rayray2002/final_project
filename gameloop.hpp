#ifndef Game_hpp
#define Game_hpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <iostream>

class Game {

public:
    Game();
    ~Game();

    void handleEveants();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void update();
    void render();
    void clean();

    bool running() { return isRunning; };

private:
    int cnt = 0; //count
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
};

#endif /* Game_hpp */