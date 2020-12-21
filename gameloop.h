#ifndef Game_hpp
#define Game_hpp

//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL_mixer.h>

//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
//#include "texturemanager.hpp"
#define NUMMENU 5
#define WIDTH 1600
#define HEIGHT 1000
using namespace std;

class ColliderComponent;

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
    void MusicPlay(const char* Music, int volume);
    int FirstMenu();
    //void SetCharacter(string s1, string s2);
    //int showmenu();

    bool running() { return isRunning; };

    // static void AddTile(int id, int x, int y);
    // static void AddTile(int srcX, int srcY, int xpos, int ypos);

    static SDL_Renderer* renderer;
    static SDL_Event event;
    static vector<ColliderComponent*> colliders;
    static bool isRunning;
    static SDL_Rect camera;

private:
    int cnt = 64; //count
    // bool isRunning;
    SDL_Window* window;
    
    
    //Character
    map<int, const char*> Character;
    
    

    //Menu
    int X_MENU_MOUSE, Y_MENU_MOUSE;
    bool MenuisRunning;
    // const char* MenuLabel[NUMMENU] = {"Kirito"};
    stringstream MenuLabel[NUMMENU];
    SDL_Surface* MenuChoice[NUMMENU];
    SDL_Surface* MenuCharacterSurface[NUMMENU];
    SDL_Texture* MenuTex[NUMMENU];
    SDL_Texture* MenuCharacterTex[NUMMENU];
    SDL_Color MenuColor[2] = {{255, 255, 255},
                              {255, 223, 0}  // unselected
                              /*,{  0, 255, 235}*/}; // selected
    SDL_Rect MenuPos[NUMMENU];
    SDL_Rect MenuCharacterPos[NUMMENU];
    TTF_Font* MenuFont;
    

    SDL_Texture *CharacterTextTexture[NUMMENU];
    SDL_Surface *CharacterTextSurface[NUMMENU];
    SDL_Rect CharacterTextRect[NUMMENU];
    TTF_Font *CharacterTextFont;
    //SDL_Color CharacterTextColor = {0, 255, 235};
    SDL_Color CharacterTextColor = {255, 223, 0};
    stringstream CharacterTextText[NUMMENU];


    //Menu

};

#endif /* Game_hpp */