#ifndef _Game_H
#define _Game_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "GameBoard.h"
#include "Vector2D.h"

#define WIDTH 1280
#define HEIGHT 720
using namespace std;
class Game
{
public:
    Game();
    ~Game();

    void handleEveants();
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void update();
    void render();
    void clean();
    void showmenu();
    static void LinkStart(string text, int second, int h, int w);
    void MusicPlay(const char *Music, int volume);
    int FirstMenu();
    bool running() { return isRunning; };

    static bool isRunning;

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static SDL_Rect camera;

    enum groupLabels : std::size_t
    {
        groupMap,
        groupPlayers,
        groupColliders,
        groupBackGrounds,
        groupTextButtoms,
        groupButtoms,
        groupGameBoards,
        groupDoubleGameBoards
    };

private:
    SDL_Window *window;
};

#endif /* Game_hpp */