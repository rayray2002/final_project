
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
    SDL_Surface* tmpSurface = SDL_LoadBMP("./sample.bmp");
    cout << "picture Loaded!" << endl;
    //SDL_Surface* tmpSurface = IMG_Load("./pictures/sample.png");
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
    // cnt++;
    SDL_Delay(10);
    destR.h = 64;
    destR.w = 64;
    // destR.x = cnt;
    // destR.y = cnt;
    SDL_Event e;
    if ( SDL_PollEvent( &e ) != 0 ) {
        switch ( e.key.keysym.sym ) {
            case SDLK_w:
                destR.y -= 50;
                printf("w\n");
                break;

            case SDLK_s:
                destR.y += 50;
                printf("s\n");
                break;

            case SDLK_a:
                destR.x -= 50;
                printf("a\n");
                break;

            case SDLK_d:
                destR.x += 50;
                printf("d\n");
                break;            
        }
    }
    
    //cout << cnt << endl;
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
    SDL_Quit();
    cout << "Game Cleaned!" << endl;
}