#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <cmath>
#include "menu1.hpp"
const int HEIGHT = 13;
const int WIDTH = 6;

bool init();

void close();

void show_board(const char[][6]);

SDL_Window* Window = NULL;

SDL_Renderer* Renderer = NULL;

SDL_Texture* texture = NULL;

SDL_Surface* surface = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (TTF_Init() == -1) {
            std::cout << "TTF_Init: " << TTF_GetError() << std::endl;
            return 3;
        }
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        Window = SDL_CreateWindow("board test", 100, 100, 1300, 1000, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);
        if (Window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
            if (Renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void close()
{
    //Destroy window
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Window = NULL;
    Renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

void show_board(const char board[][WIDTH]) {
    // SDL_SetTextureColorMod(texture, 0, 0, 0);
    // SDL_RenderCopy(Renderer, texture, NULL, NULL);
    texture = NULL;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (board[i][j]) {
            case 'R':
                if (rand() % 10 == 1) {
                    surface = SDL_LoadBMP("./img/banana.bmp"); break;
                }
                else surface = SDL_LoadBMP("./img/sample_red.bmp"); break;
            case 'G':
                surface = SDL_LoadBMP("./img/sample_green.bmp"); break;
            case 'Y':
                surface = SDL_LoadBMP("./img/sample_yellow.bmp"); break;

            }
            int size = 80;
            SDL_Rect a;
            a.x = 500 + size * j;
            a.y = size * i;
            a.w = size;
            a.h = size;

            texture = SDL_CreateTextureFromSurface(Renderer, surface);

            SDL_FreeSurface(surface);
            surface = NULL;
            SDL_RenderCopy(Renderer, texture, NULL, &a);
        }
    }
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderPresent(Renderer);
    }
}

int main(int argc, char* argv[]) {
    init();
    char test_board[13][6] = { {'R', 'R', 'G', 'Y', 'R', 'R'},
                              {'R', 'Y', 'Y', 'G', 'Y', 'G'},
                              {'G', 'Y', 'G', 'Y', 'R', 'R'},
                              {'R', 'Y', 'G', 'Y', 'R', 'G'},
                              {'Y', 'G', 'Y', 'R', 'Y', 'G'},
                              {'G', 'Y', 'R', 'Y', 'R', 'G'},
                              {'Y', 'G', 'Y', 'R', 'Y', 'R'},
                              {'Y', 'G', 'Y', 'R', 'Y', 'R'},
                              {'Y', 'R', 'R', 'G', 'R', 'G'},
                              {'R', 'Y', 'G', 'Y', 'G', 'G'},
                              {'G', 'R', 'Y', 'G', 'Y', 'R'},
                              {'G', 'R', 'Y', 'G', 'Y', 'R'},
                              {'G', 'R', 'R', 'R', 'Y', 'R'} };
    show_board(test_board);

    close();


    return 0;
}