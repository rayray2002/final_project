
#include "gameloop.hpp"
using namespace std;

SDL_Texture* playerTex;
SDL_Rect scrR, destR;

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsystem Initialised!..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
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
    printf("Music Loaded!\n");

    //LinkStart
    SDL_Texture *LinkStartTexture = NULL;
    SDL_Surface *LinkStartSurface = NULL;
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
    LinkStartText << "Link Start!";
    LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
    LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
    if (!LinkStartTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }
    SDL_FreeSurface(LinkStartSurface);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, LinkStartTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    TTF_CloseFont(font);
    font = NULL;
    printf("Link Start!\n");
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


void Game::showmenu(SDL_Surface* screen, TTF_Font* font) {
    Uint32 time;
    int x, y;
    const int NUMMENU = 2;
    const char* label[NUMMENU] = {"Kirito", "Hsieg"};
    SDL_Surface* menus[NUMMENU];
    bool selected[NUMMENU] = {0, 0};
    SDL_Color color[2] = {{255, 255, 255}, {255, 0, 0}};

    menus[0] = TTF_RenderText_Solid(font, label[0], color[0]);
    menus[1] = TTF_RenderText_Solid(font, label[1], color[0]);
    SDL_Rect pos[NUMMENU];
    pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
    pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
    pos[1].x = screen->clip_rect.w / 2 - menus[1]->clip_rect.w / 2;
    pos[1].y = screen->clip_rect.h / 2 - menus[1]->clip_rect.h;

    SDL_Event event;
    while (1) {
        time = SDL_GetTicks();
        while (SDL_PollEvent( &event )) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_FreeSurface(menus[0]);
                    SDL_FreeSurface(menus[1]);
                case 
            }
        }
    }
}