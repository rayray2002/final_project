#pragma once
#include "gameloop.h"
#include "firstmenu.hpp"
// #include "gameobject.hpp"
#include "Map.hpp"
// #include "ECS/ECS.hpp"
// #include "ECS/Components.hpp"
#include "ECS/Components.hpp"
#include "texturemanager.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "ECS/ECSaddGroup.hpp"
#include "AssetManager.h"
using namespace std;

// GameObject* player;
// GameObject* player2;
SDL_Renderer* Game::renderer = nullptr;
Map* mmap;
// SDL_Texture* playerTex;
// SDL_Rect scrR, destR;
Manager manager;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0, 0, 800, 600 };

AssetManager* Game::assets = new AssetManager(&manager);

// vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
// auto& wall(manager.addEntity());
// const char* mapfile = "./img/miku.bmp";

// enum groupLabels : std::size_t {
//     groupMap,
//     groupPlayers,
//     groupEnemies,
//     groupColliders
// };

// auto& tile0(manager.addEntity());
// auto& tile1(manager.addEntity());
// auto& tile2(manager.addEntity());
// auto& tiles(manager.getGroup(groupMap));
// auto& players(manager.getGroup(groupPlayers));
// auto& enemies(manager.getGroup(groupEnemies));

Game::Game() 
{
    Character[0] = "Miku";
    Character[1] = "Kirito";
    Character[2] = "Asuna";
    Character[3] = "Hung";
    Character[4] = "Heish";
}

Game::~Game() 
{

}

void Game::init(const char* title, int xMenuPos, int yMenuPos, int width, int height, bool fullscreen) {

    int flags = 0;

    if (fullscreen) 
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
    {
        cout << "Subsystem Initialised!..." << endl;

        window = SDL_CreateWindow(title, xMenuPos, yMenuPos, width, height, flags);
        if (window) 
        {
            cout << "Window Created!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer Created!" << endl;
        }

        isRunning = true;
    } 
    else 
    {
        isRunning = false;
    }
    //SDL_LoadBMP
    //IMG_Load
    //SDL_Surface* tmpSurface = SDL_LoadBMP("./sample.bmp");
    // SDL_Surface* tmpSurface = SDL_LoadBMP("./img/kirito1.bmp");
    // cout << "picture Loaded!" << endl;
    // playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    // playerTex = TextureManager::LoadTexture("./img/kirito1.bmp", renderer);
    // player = new GameObject("./img/kirito1.bmp", 0, 0);
    // player2 = new GameObject("./img/kirito1.bmp", 500, 500);
    assets->AddTexture("miku", "./img/miku.bmp");
    assets->AddTexture("player", "./img/sample_green.bmp");

    mmap = new Map("miku", 3, 32);
    // newPlayer.addComponent<PositionComponent>();
    // newPlayer.getComponent<PositionComponent>().setPos(500, 500);
    // tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
    // tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
    // tile1.addComponent<ColliderComponent>("dirt");
    // tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
    // tile2.addComponent<ColliderComponent>("water");

    mmap->LoadMap("img/p16x16.map", 16, 16);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<KeyBoardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);

    // wall.addComponent<TransformComponent>(300, 300, 300, 20, 1);
    // wall.addComponent<SpriteComponent>("./img/kirito1.bmp");
    // wall.addComponent<ColliderComponent>("wall");
    // wall.addGroup(groupMap);
    //SDL_Surface* tmpSurface = IMG_Load("pictures/sample.png");

    //Music
    MusicPlay("./mp3/miku.wav", 32);

    //LinkStart
    LinkStart("Game Initailizing...", 1000, 100, 600);
    LinkStart("Game Initailized!", 1000, 100, 600);
    LinkStart("Link Start!", 2000, 200, 600);
    //LinkStart

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));


void Game::handleEveants() 
{
    // SDL_Event event;

    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        
    }
}

void Game::update() 
{
    SDL_Rect playerCol = player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = player.getComponent<TransformComponent>().position;
    // player->Update();
    // player2->Update();
    manager.refresh();
    manager.update();

    for (auto& c : colliders)
    {
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        // c->getComponent<TransformComponent>().position.x - 400;
        if (Collision::AABB(cCol, playerCol))
        {
            player.getComponent<TransformComponent>().position = playerPos;
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if (camera.x < 0) {
        camera.x = 0;
    }

    if (camera.y < 0) {
        camera.y = 0;
    }

    if (camera.x > camera.w) {
        camera.x = camera.w;
    }

    if (camera.y > camera.h) {
        camera.y = camera.h;
    }

    // Vector2D pVel = player.getComponent<TransformComponent>().velocity;
    // int pSpeed = player.getComponent<TransformComponent>().speed;

    // for (auto t : tiles) {
    //     t ->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
    //     t ->getComponent<TileComponent>().destRect.y += -(pVel.x * pSpeed);
    // }

    // for (auto cc : colliders) {
    //     Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    //     // if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc)) {
    //     //     player.getComponent<TransformComponent>().velocity * -1;
    //     //     cout << "Wall Hit!" << endl;
    //     // }
    // }
    
    // player.getComponent<TransformComponent>().position.Add(Vector2D(5, 0));
    // if (player.getComponent<TransformComponent>().position.x > 100) {
    //     player.getComponent<SpriteComponent>().setTex("./img/miku.bmp");
    // }
    // cout << newPlayer.getComponent<PositionComponent>().x << ", " << newPlayer.getComponent<PositionComponent>().y << endl;
    // map->LoadMap();
    // destR.h = cnt;
    // destR.w = cnt;
    // SDL_Event e;
    // if ( SDL_PollEvent( &e ) != 0 ) {
    //     switch ( e.key.keysym.sym ) {
    //         case SDLK_w:
    //             destR.y -= 50;
    //             break;

    //         case SDLK_s:
    //             destR.y += 50;
    //             break;

    //         case SDLK_a:
    //             destR.x -= 50;
    //             break;

    //         case SDLK_d:
    //             destR.x += 50;
    //             break;

    //         case SDLK_j:
    //             cnt *= 2;
    //             break;

    //         case SDLK_k:
    //             if (cnt / 2 > 0) cnt /= 2;
    //             break;
            
    //     }
    // }
}


void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& t : tiles) {
        t->draw();
    }

    // for (auto& c : colliders)
    // {
    //     c->draw();
    // }

    for (auto& p : players) {
        p->draw();
    }

    // for (auto& e : enemies) {
    //     e->draw();
    // }
    //mmap->DrawMap();
    // manager.draw();
    // player->Render();
    // player2->Render();
    //SDL_RenderCopy(renderer, playerTex, NULL, &destR);
    //this is where we add stuff to render
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_CloseAudio();
    SDL_Quit();
    Mix_Quit();
    IMG_Quit();
    cout << "Game Cleaned!" << endl;
}

// void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
//     // auto& tile(manager.addEntity());
//     // tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
//     // tile.addGroup(groupMap);
// }

void Game::showmenu() {
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime; //int

    MenuisRunning = true;
    if (TTF_Init() == -1) {

    }
    

    //Set Character Position Here (Start)
    int CharacterHeight = 160;
    for (int i = 0; i < NUMMENU; i++) {
        MenuCharacterPos[i].y = HEIGHT - 80 - CharacterHeight;
        MenuCharacterPos[i].h = CharacterHeight;
        MenuCharacterPos[i].w = 100;
    }

    MenuCharacterPos[0].x =  30;
    for (int i = 1; i < NUMMENU; i++) {
        MenuCharacterPos[i].x = MenuCharacterPos[i - 1].x + 130;
    }
    //Set Character Position Here (End)


    //Set Menu Font (Start)
    MenuFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
    TTF_SetFontStyle(MenuFont, /*TTF_STYLE_BOLD|*/TTF_STYLE_ITALIC);
    //Set Menu Font (End)

    bool selected[NUMMENU] = {0};

    //Set Menu Position Here (Start)
    for (int i = 0; i < NUMMENU; i++) {
        MenuPos[i].h = 50;
        MenuPos[i].w = 100;
    }

    int UP    = HEIGHT - 130;
    int DOWN  = HEIGHT -  30;
    int LEFT[NUMMENU]  = {  30, 160, 290, 420, 550 };
    int RIGHT[NUMMENU] = { 130, 260, 390, 520, 650 };
    for (int i = 0; i < NUMMENU; i++) {
        MenuLabel[i] << Character[i];
    }
    
    for (int i = 0; i < NUMMENU; i++) {
        MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
        MenuPos[i].y = HEIGHT - 60;
    }

    MenuPos[0].x =  30;
    for (int i = 1; i < NUMMENU; i++) {
        MenuPos[i].x = MenuPos[i - 1].x + 130;
    }
    //Set Menu Position Here (End)

    //Title (Character) Basic Setting (Start)
    for (int i = 0; i < NUMMENU; i++) {
        CharacterTextRect[i].h = 70;
        CharacterTextRect[i].w = 600;
        CharacterTextRect[i].x = 50;
        CharacterTextRect[i].y = 200 + 80 * i;
    }
        
    CharacterTextFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
    TTF_SetFontStyle(CharacterTextFont, TTF_STYLE_ITALIC);
    for (int i = 0; i < NUMMENU; i++) {
        CharacterTextText[i].str( "" );
    }
    CharacterTextText[0] << "Miku: Miku Yu Yu!!!";
    CharacterTextText[1] << "Kirito: Star Burst Stream!!!";
    CharacterTextText[2] << "Shark: AAAAA!!!";
    CharacterTextText[3] << "Hung: Miku 39 Is Answer!!!";
    CharacterTextText[4] << "Heish: I'm Your Muji!!!";
    // for (int i = 0; i < NUMMENU; i++) {
    //     CharacterTextSurface[i] = TTF_RenderText_Solid(CharacterTextFont, CharacterTextText[i].str().c_str(), CharacterTextColor);
    // }
    //Title (Character) Basic Setting (End)

    //Main Loop (Start)
    SDL_Event event;
    while (1) {
        SDL_Delay(1000);
        //Title Basic Setting (Start)
        SDL_Texture *LinkStartTexture = NULL;
        SDL_Surface *LinkStartSurface = NULL;
        SDL_Rect dst;
        dst.h = 150;
        dst.w = 600;
        dst.x = 30;
        dst.y = 30;
        if(TTF_Init() == -1) {
            cout << "TTF_Init: " << TTF_GetError() << endl;
        }
        TTF_Font *font;
        font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
        if(!font) {
            cout << "TTF_OpenFont: " << TTF_GetError() << endl;
        }
        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
        //SDL_Color color = { 0, 255, 235 };
        SDL_Color color = { 255, 223,   0 };
        stringstream LinkStartText;
        LinkStartText.str( "" );
        LinkStartText << "Choose Character";
        LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
        LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
        if (!LinkStartTexture) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        }
        SDL_FreeSurface(LinkStartSurface);
        TTF_CloseFont(font);
        font = NULL;
        //Title Basic Setting (End)

        
        //Title (Character) Basic Setting (Start)
        for (int i = 0; i < NUMMENU; i++) {
            SDL_FreeSurface(CharacterTextSurface[i]);
        }
        for (int i = 0; i < NUMMENU; i++) {
            CharacterTextSurface[i] = TTF_RenderText_Solid(CharacterTextFont, CharacterTextText[i].str().c_str(), CharacterTextColor);
        }
        
        //Title (Character) Basic Setting (End)

        //Character Setting (Start)
        frameStart = SDL_GetTicks();

        for (int i = 0; i < NUMMENU; i++) {
            SDL_FreeSurface(MenuCharacterSurface[i]);
        }
        MenuCharacterSurface[0] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[1] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[2] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[3] = SDL_LoadBMP("./img/miku.bmp");
        MenuCharacterSurface[4] = SDL_LoadBMP("./img/miku.bmp");       
        //Character Setting (End)
        for (int i = 0; i < NUMMENU; i++) {
            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
        }
        

        //Event Loop (Start)
        while (SDL_PollEvent( &event ) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    for (int i = 0; i < NUMMENU; i++) {
                        SDL_FreeSurface(MenuChoice[i]);
                        MenuisRunning = false;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    X_MENU_MOUSE = event.motion.x;
                    Y_MENU_MOUSE = event.motion.y;
                    
                    
                    for (int i = 0; i < NUMMENU; i++) {
                        if (X_MENU_MOUSE >= LEFT[i] && X_MENU_MOUSE <= RIGHT[i] && Y_MENU_MOUSE >= UP && Y_MENU_MOUSE <= DOWN) {
                            if (!selected[i]) {
                                selected[i] = 1;
                                SDL_FreeSurface(MenuChoice[i]);
                                MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
                            }
                            else {
                                if (selected[i]) {
                                    selected[i] = 0;
                                    SDL_FreeSurface(MenuChoice[i]);
                                    MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
                                }
                            }
                        }
                        else {
                            selected[i] = 0;
                            SDL_FreeSurface(MenuChoice[i]);
                            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    X_MENU_MOUSE = event.motion.x;
                    Y_MENU_MOUSE = event.motion.y;
                    for (int i = 0; i < NUMMENU; i++) {
                        if (X_MENU_MOUSE >= MenuPos[i].x && X_MENU_MOUSE <= MenuPos[i].x + MenuPos[i].w && Y_MENU_MOUSE >= MenuPos[i].y && Y_MENU_MOUSE <= MenuPos[i].y + MenuPos[i].h) {
                            for (int j = 0; j < NUMMENU; j++) {
                                SDL_FreeSurface(MenuChoice[j]); 
                            }
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        for (int i = 0; i < NUMMENU; i++) {
                            SDL_FreeSurface(MenuChoice[i]);
                        }
                        MenuisRunning = false;
                    }
                    break;
            }
        }
        if (!MenuisRunning) {
            for (int i = 0; i < NUMMENU; i++) {
                SDL_DestroyTexture(MenuTex[i]);
                SDL_DestroyTexture(MenuCharacterTex[i]);
                SDL_DestroyTexture(CharacterTextTexture[i]);
            }
            break;
        }
        //Event Loop (End)

        //Render (Start)
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        for (int i = 0; i < NUMMENU; i++) {

            MenuCharacterTex[i] = SDL_CreateTextureFromSurface(renderer, MenuCharacterSurface[i]);
            CharacterTextTexture[i] = SDL_CreateTextureFromSurface(renderer, CharacterTextSurface[i]);
            MenuTex[i] = SDL_CreateTextureFromSurface(renderer, MenuChoice[i]);
            // SDL_FreeSurface(MenuCharacterSurface[i]);
            SDL_FreeSurface(MenuChoice[i]);
            // SDL_FreeSurface(CharacterTextSurface[i]);
            SDL_RenderCopy(renderer, MenuTex[i], NULL, &MenuPos[i]);
            SDL_RenderCopy(renderer, CharacterTextTexture[i], NULL, &CharacterTextRect[i]);
            SDL_RenderCopy(renderer, MenuCharacterTex[i], NULL, &MenuCharacterPos[i]);
            SDL_DestroyTexture(MenuTex[i]);
            SDL_DestroyTexture(CharacterTextTexture[i]);
            SDL_DestroyTexture(MenuCharacterTex[i]);

        }
        SDL_RenderCopy(renderer, LinkStartTexture, NULL, &dst);
        SDL_DestroyTexture(LinkStartTexture);
        SDL_RenderPresent(renderer);
        //Render (End)

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) { //make the screen more smooth
            SDL_Delay(frameDelay - frameTime);
        }
    }
    //Main Loop (End)
}

void Game::LinkStart(string text, int second, int h, int w) {
    SDL_Texture *LinkStartTexture = NULL;
    SDL_Surface *LinkStartSurface = NULL;
    SDL_Rect dst;
    dst.h = h;
    dst.w = w;
    dst.x = WIDTH / 2 - dst.w / 2;
    dst.y = HEIGHT / 2 - dst.h / 2;
    if(TTF_Init() == -1) {
        cout << "TTF_Init: " << TTF_GetError() << endl;
    }
    TTF_Font *font;
    font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
    if(!font) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
    }
    TTF_SetFontStyle(font, 0/*TTF_STYLE_BOLD|TTF_STYLE_ITALIC*/);
    //SDL_Color color = { 0, 255, 235 };
    SDL_Color color = { 255, 223,   0 };
    stringstream LinkStartText;
    LinkStartText.str( "" );
    LinkStartText << text;
    LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
    LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
    if (!LinkStartTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }
    SDL_FreeSurface(LinkStartSurface);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, LinkStartTexture, NULL, &dst);
    SDL_DestroyTexture(LinkStartTexture);
    SDL_RenderPresent(renderer);
    SDL_Delay(second);
    TTF_CloseFont(font);
    font = NULL;
    cout << text << endl;
}

void Game::MusicPlay(const char* Music, int volume) {
    // load support for the MP3 sample/music formats
    int mflags = MIX_INIT_MP3;
    if( (Mix_Init(mflags) & mflags) != mflags ) {
        // cout << "Mix_Init: Failed to init required ogg and mod support!\n";
        // cout << "Mix_Init: %s\n" << Mix_GetError() << endl;
    }

    if(Mix_OpenAudio(128000, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        // cout << "Mix_OpenAudio: %s\n" << Mix_GetError() << endl;
    }


    // load the MP3 file to play as music
    Mix_Music *music;
    music = Mix_LoadMUS(Music);
    //Mix_LoadMUS
    if(!music) {
        cout << "Mix_LoadMUS(\"miku.mp3\"): %s\n" << Mix_GetError();
    }
    Mix_VolumeMusic(volume);
    Mix_PlayMusic( music, -1 );
    cout << "Music Loaded!\n";
}