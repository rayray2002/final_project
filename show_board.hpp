#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <string>
#include <cmath>

extern enum Color {
	Empty, Red, Green, Blue, Yellow
};
SDL_Surface* surface_ba = SDL_LoadBMP("./img/banana.bmp");
SDL_Surface* surface_r = SDL_LoadBMP("./img/sample_red.bmp");
SDL_Surface* surface_g = SDL_LoadBMP("./img/sample_green.bmp");
SDL_Surface* surface_y = SDL_LoadBMP("./img/sample_yellow.bmp");

void show_board(Color board[][6]) {
    // SDL_SetTextureColorMod(texture, 0, 0, 0);
    // SDL_RenderCopy(Renderer, texture, NULL, NULL);
    /*SDL_Surface* surface_ba = SDL_LoadBMP("./img/banana.bmp");
    SDL_Surface* surface_r = SDL_LoadBMP("./img/sample_red.bmp");
	SDL_Surface* surface_g = SDL_LoadBMP("./img/sample_green.bmp");
	SDL_Surface* surface_y = SDL_LoadBMP("./img/sample_yellow.bmp");*/
    SDL_SetRenderDrawColor(Renderer,0,0,0,0);
    srand(time(0));
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 6; j++) {
        	SDL_Texture*  texture=NULL;
            switch (board[i][j]) {
            case 1:
                if (rand() % 10 == 1) {
                    texture = SDL_CreateTextureFromSurface(Renderer, surface_ba); break;
                }
                else texture = SDL_CreateTextureFromSurface(Renderer, surface_r); break;
            case 2:
                texture = SDL_CreateTextureFromSurface(Renderer, surface_g); break;
            case 4:
                texture = SDL_CreateTextureFromSurface(Renderer, surface_y); break;

            }
            //SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
            int size = 80;
            SDL_Rect a;
            a.x = 500 + size * j;
            a.y = size * i;
            a.w = size;
            a.h = size;

            SDL_RenderCopy(Renderer, texture, NULL, &a);
            SDL_DestroyTexture(texture);
        }
    }
    /*SDL_Event e;
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
    }*/
	SDL_RenderPresent(Renderer);
    SDL_Delay(300);
    SDL_RenderClear(Renderer);
    
}
