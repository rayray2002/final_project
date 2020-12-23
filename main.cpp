#include "game.hpp"

Game* game = nullptr;



int main(int argc, const char* argv[]) {

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime; //int


    game = new Game();

    game->init("The Seed", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, false);
    //game->FirstMenu();
    //game->showmenu();
    
    while (game->running()) {
        cout << "OK" << endl;
        SDL_Delay(1000);
        frameStart = SDL_GetTicks();


        game->handleEveants();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) { //make the screen more smooth
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();

    return 0;
}

