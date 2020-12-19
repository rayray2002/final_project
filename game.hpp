
#include "gameloop.hpp"
using namespace std;
#define WIDTH 800
#define HEIGHT 600

SDL_Texture* playerTex;
SDL_Rect scrR, destR;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xMenuPos, int yMenuPos, int width, int height, bool fullscreen) {

    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystem Initialised!..." << endl;

        window = SDL_CreateWindow(title, xMenuPos, yMenuPos, width, height, flags);
        if (window) {
            cout << "Window Created!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "renderer Created!" << endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }
    //SDL_LoadBMP
    //IMG_Load
    //SDL_Surface* tmpSurface = SDL_LoadBMP("./sample.bmp");
    SDL_Surface* tmpSurface = SDL_LoadBMP("./img/kirito1.bmp");
    cout << "picture Loaded!" << endl;
    //SDL_Surface* tmpSurface = IMG_Load("pictures/sample.png");

    //Music
    // load support for the MP3 sample/music formats
    int mflags = MIX_INIT_MP3;
    if( (Mix_Init(mflags) & mflags) != mflags ) {
        cout << "Mix_Init: Failed to init required ogg and mod support!\n";
        cout << "Mix_Init: %s\n" << Mix_GetError() << endl;
    }

    if(Mix_OpenAudio(128000, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        cout << "Mix_OpenAudio: %s\n" << Mix_GetError() << endl;
    }


    // load the MP3 file "music.mp3" to play as music
    Mix_Music *music;
    music = Mix_LoadMUS("mp3/miku.mp3");
    if(!music) {
        cout << "Mix_LoadMUS(\"miku.mp3\"): %s\n" << Mix_GetError();
    }
    Mix_PlayMusic( music, -1 );
    cout << "Music Loaded!\n";

    //LinkStart
    LinkStart("Game Initailizing...", 1000, 100, 600);
    LinkStart("Game Initailized!", 1000, 100, 600);
    LinkStart("Link Start!", 2000, 200, 600);
    //LinkStart

    

    playerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
}

void Game::handleEveants() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        
    }
}

void Game::update() {
    SDL_Delay(10);
    destR.h = cnt;
    destR.w = cnt;
    SDL_Event e;
    if ( SDL_PollEvent( &e ) != 0 ) {
        switch ( e.key.keysym.sym ) {
            case SDLK_w:
                destR.y -= 50;
                break;

            case SDLK_s:
                destR.y += 50;
                break;

            case SDLK_a:
                destR.x -= 50;
                break;

            case SDLK_d:
                destR.x += 50;
                break;

            case SDLK_j:
                cnt *= 2;
                break;

            case SDLK_k:
                if (cnt / 2 > 0) cnt /= 2;
                break;
            
            case SDLK_i:
                cnt *= 1.2;
                break;
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTex, NULL, &destR);
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


void Game::showmenu() {
    
    MenuisRunning = true;
    Uint32 time;
    if (TTF_Init() == -1) {

    }
    MenuFont = TTF_OpenFont("./fonts/GenJyuuGothic-Regular.ttf", 500);

    bool selected[NUMMENU] = {0};

    for (int i = 0; i < NUMMENU; i++) {
        MenuPos[i].h = 50;
        MenuPos[i].w = 120;
    }

    MenuLabel[0] << "Kirito";

    MenuChoice[0] = TTF_RenderText_Solid(MenuFont, MenuLabel[0].str().c_str(), MenuColor[0]);
    //MenuChoice[1] = TTF_RenderText_Solid(MenuFont, MenuLabel[1], MenuColor[0]);

    MenuPos[0].x = WIDTH  / 2 - MenuPos[0].w / 2;
    MenuPos[0].y = HEIGHT / 2 - MenuPos[0].h;
    //MenuPos[1].x = WIDTH  / 2 - MenuPos[1].w / 2;
    //MenuPos[1].y = HEIGHT / 2 - MenuPos[1].h;

    SDL_Event event;
    while (1) {
        SDL_Delay(2);
        // time = SDL_GetTicks();
        for (int i = 0; i < NUMMENU; i++) {
            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
        }
        if (SDL_PollEvent( &event ) != 0) {
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
                        if (X_MENU_MOUSE >= MenuPos[i].x && X_MENU_MOUSE <= MenuPos[i].x + MenuPos[i].w && Y_MENU_MOUSE >= MenuPos[i].y && Y_MENU_MOUSE <= MenuPos[i].y + MenuPos[i].h) {
                            selected[i] = 1;
                            SDL_FreeSurface(MenuChoice[i]);
                            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
                            // if (!selected[i]) {
                            //     selected[i] = 1;
                            //     SDL_FreeSurface(MenuChoice[i]);
                            //     MenuChoice[i] = TTF_RenderText_Solid(font, MenuLabel[i], color[1]);
                            // }
                            // else {
                            //     if (selected[i]) {
                            //         selected[i] = 0;
                            //         SDL_FreeSurface(MenuChoice[i]);
                            //         MenuChoice[i] = TTF_RenderText_Solid(font, MenuLabel[i], color[0]);
                            //     }
                            // }
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
                                //SDL_FreeSurface(MenuChoice[j]); 
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
                MenuTex[i] = SDL_CreateTextureFromSurface(renderer, MenuChoice[i]);
                SDL_FreeSurface(MenuChoice[i]);
                SDL_RenderCopy(renderer, MenuTex[i], NULL, &MenuPos[i]);
                SDL_DestroyTexture(MenuTex[i]);
            }
            break;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        for (int i = 0; i < NUMMENU; i++) {
            MenuTex[i] = SDL_CreateTextureFromSurface(renderer, MenuChoice[i]);
            SDL_FreeSurface(MenuChoice[i]);
            SDL_RenderCopy(renderer, MenuTex[i], NULL, &MenuPos[i]);
            SDL_DestroyTexture(MenuTex[i]);
        }
        SDL_RenderPresent(renderer);
        // if (!isRunning) {
        //     clean();
        // }
        // cout << "OK" << endl;
        
    }
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
    font = TTF_OpenFont("./fonts/GenJyuuGothic-Regular.ttf", 500);
    if(!font) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
    }
    TTF_SetFontStyle(font, TTF_STYLE_BOLD|TTF_STYLE_ITALIC);
    SDL_Color color = {0, 255, 235};
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