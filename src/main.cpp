#include "Game.h"
#include <ctime>

Game *game = nullptr;

int main(int argc, char *argv[])
{
    srand(time(0));
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();

    game->init("The Seed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
menu:
    game->menu.startmenu(Game::renderer);
    game->playerNumber = game->menu.GetMode();

    while (game->running())
    {
        frameStart = SDL_GetTicks();
        if (!game->isRunning)
            goto menu;
        game->handleEveants();
        game->update();
        // int a = SDL_GetTicks();
        game->render();
        // cout << SDL_GetTicks() - a << endl;
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}
