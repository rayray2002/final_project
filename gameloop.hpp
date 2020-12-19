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
#define NUMMENU 1
using namespace std;

class Game {

public:
    Game();
    ~Game();

    void handleEveants();
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void update();
    void render();
    void clean();
    void showmenu();
    void LinkStart(string text, int second, int h, int w);
    void MusicPlay(const char* Music);

    bool running() { return isRunning; };

private:
    int cnt = 64; //count
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    //Menu
    int X_MENU_MOUSE, Y_MENU_MOUSE;
    bool MenuisRunning;
    // const char* MenuLabel[NUMMENU] = {"Kirito"};
    stringstream MenuLabel[NUMMENU];
    SDL_Surface* MenuChoice[NUMMENU];
    SDL_Texture* MenuTex[NUMMENU];
    SDL_Color MenuColor[2] = {{255, 255, 255}, // unselected
                              {  0, 255, 235}}; //selected
    SDL_Rect MenuPos[NUMMENU];
    TTF_Font* MenuFont;
    
    //Menu

};

#endif /* Game_hpp */