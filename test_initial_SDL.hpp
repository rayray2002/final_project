#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <string>
#include <cmath>
bool init();
void close();
SDL_Window* Window = NULL;

SDL_Renderer* Renderer = NULL;

//SDL_Texture* texture = NULL;

//SDL_Surface* surface = NULL;
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
