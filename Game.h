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
#include <map>
#include <vector>
#include "GameBoard.h"
#include "Vector2D.h"
#include "Menu.h"
#define NUMMENU 5
#define WIDTH 1280
#define HEIGHT 720
using namespace std;

class ColliderComponent;

//struct unit
//{
//    SDL_Texture *texture;
//    SDL_Rect srcR, destR;
//    Vector2D speed;
//    Vector2D bspeed;
//    Vector2D mapPosition;
//    Color color;
//    bool isMoving;
//    bool isActive;
//    SDL_Surface *surface;
//    int Combo;
//    int Score;
//    bool KO;
//};
class Game
{
public:
    Game();
    ~Game();
    Menu menu;

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

    static SDL_Renderer *renderer;
    static SDL_Event event;
    // static vector<ColliderComponent*> colliders;
    static bool isRunning;
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
    int cnt = 64; //count
    // bool isRunning;
    SDL_Window *window;

    //Character
    map<int, const char *> Character;

    //Menu
    int X_MENU_MOUSE, Y_MENU_MOUSE;
    bool MenuisRunning;
    // const char* MenuLabel[NUMMENU] = {"Kirito"};
    stringstream MenuLabel[NUMMENU];
    SDL_Surface *MenuChoice[NUMMENU];
    SDL_Surface *MenuCharacterSurface[NUMMENU];
    SDL_Texture *MenuTex[NUMMENU];
    SDL_Texture *MenuCharacterTex[NUMMENU];
    SDL_Color MenuColor[2] = {{255, 255, 255},
                              {255, 223, 0}          // unselected
                              /*,{  0, 255, 235}*/}; // selected
    SDL_Rect MenuPos[NUMMENU];
    SDL_Rect MenuCharacterPos[NUMMENU];
    TTF_Font *MenuFont;

    SDL_Texture *CharacterTextTexture[NUMMENU];
    SDL_Surface *CharacterTextSurface[NUMMENU];
    SDL_Rect CharacterTextRect[NUMMENU];
    TTF_Font *CharacterTextFont;
    //SDL_Color CharacterTextColor = {0, 255, 235};
    SDL_Color CharacterTextColor = {255, 223, 0};
    stringstream CharacterTextText[NUMMENU];
};

#endif /* Game_hpp */