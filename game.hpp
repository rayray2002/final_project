
#include "gameloop.hpp"
using namespace std;
#define WIDTH 800
#define HEIGHT 600

SDL_Texture* playerTex;
SDL_Rect scrR, destR;

Game::Game() {
    Character["Miku"] = "./img/miku.bmp";
    Character["Kirito"] = "./img/kirito1.bmp";
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
            cout << "Renderer Created!" << endl;
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
    MusicPlay("./mp3/miku.wav", 96);

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

// int Game::showmenu() {
// 	SDL_Surface* screen = SDL_GetWindowSurface(window);
// 	Uint32 time;
// 	int x = 0, y = 0;
// 	// const int NUMMENU = 2;
// 	MenuLabel[0] = "Miku";
// 	bool selected[NUMMENU] = {0};
// 	MenuFont = TTF_OpenFont("fonts/SAOUITT-Regular.ttf", 100);
// 	TTF_SetFontStyle(MenuFont, TTF_STYLE_ITALIC);

// 	MenuChoice[0] = TTF_RenderText_Solid(MenuFont, MenuLabel[0], MenuColor[0]);
// 	//MenuChoice[1] = TTF_Render_Solid(MenuFont, text2, color[0]);

// 	MenuPos[0].x = screen->clip_rect.w / 2 - MenuChoice[0]->clip_rect.w / 2;
// 	MenuPos[0].y = screen->clip_rect.h / 2 - MenuChoice[0]->clip_rect.h;
// 	//MenuPos[1].x = screen->clip_rect.w / 2 - MenuChoice[1]->clip_rect.w / 2;
// 	//MenuPos[1].y = screen->clip_rect.h / 2 + MenuChoice[1]->clip_rect.h;

// 	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
	
// 	SDL_Event event;
// 	while (1) {
// 		time = SDL_GetTicks();
// 			while (SDL_PollEvent(&event)) {
// 				switch (event.type) {
// 				case SDL_QUIT:
// 					for (int i = 0; i < NUMMENU; i++)
// 						SDL_FreeSurface(MenuChoice[i]);
// 					return 1;
// 				case SDL_MOUSEMOTION:
// 					x = event.motion.x;
// 					y = event.motion.y;
// 					for (int i = 0; i < NUMMENU; i++) {
// 						if (x >= MenuPos[i].x && x <= MenuPos[i].x + MenuPos[i].w && y >= MenuPos[i].y && y <= MenuPos[i].y + MenuPos[i].h) {
// 							if (!selected[i]) {
// 								selected[i] = true;
// 								if (i == 0) {
// 									SDL_FreeSurface(MenuChoice[0]);
// 									MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[0], MenuColor[1]);
// 								}
// 								// else if (i == 1) {
// 								// 	SDL_FreeSurface(MenuChoice[1]);
// 								// 	MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[1], MenuColor[1]);
// 								// }
// 							}
// 						}
//                         else {
// 							if (selected[i]){
// 								selected[i] = false;
// 								if (i == 0) {
// 									SDL_FreeSurface(MenuChoice[0]);
// 									MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[0], MenuColor[0]);
// 								}
// 								// else if (i == 1) {
// 								// 	SDL_FreeSurface(MenuChoice[1]);
// 								// 	MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[1], MenuColor[0]);
// 								// }
// 							}
// 						}
// 					}
// 					break;
// 				case SDL_MOUSEBUTTONDOWN:
// 					x = event.button.x;
// 					y = event.button.y;
// 					for (int i = 0; i < NUMMENU; i++) {
// 						if (x >= MenuPos[i].x && x <= MenuPos[i].x + MenuPos[i].w && y >= MenuPos[i].y && y <= MenuPos[i].y + MenuPos[i].h) {
// 							for (int j = 0; j < NUMMENU; j++) {
// 								SDL_FreeSurface(MenuChoice[i]);
// 							}
// 							return i;
// 						}
// 					}
// 					break;
// 				case SDL_KEYDOWN:
// 					if (event.key.keysym.sym == SDLK_ESCAPE)
// 						for (int i = 0; i < NUMMENU; i++) {
// 							SDL_FreeSurface(MenuChoice[i]);
// 						}
// 						return 0;
// 				}
// 			}
// 			for (int i = 0; i < NUMMENU; i++) {
// 				SDL_BlitSurface(MenuChoice[i], NULL, screen, &MenuPos[i]);
// 			}
// 			SDL_UpdateWindowSurface(window);
			
// 			if (1000 / 30 > (SDL_GetTicks() - time)) {
// 				SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
// 			}
// 	}
// }

void Game::showmenu() {
    
    // SDL_Surface* screen = SDL_GetWindowSurface(window);
    // SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime; //int

    MenuisRunning = true;
    if (TTF_Init() == -1) {

    }


    MenuCharacterSurface[0] = SDL_LoadBMP("./img/miku.bmp");
    MenuCharacterSurface[1] = SDL_LoadBMP("./img/miku.bmp");
    MenuCharacterSurface[2] = SDL_LoadBMP("./img/miku.bmp");
    
    int CharacterHeight = 260;
    for (int i = 0; i < NUMMENU; i++) {
        MenuCharacterPos[i].x = HEIGHT - 160 - CharacterHeight;
        MenuCharacterPos[i].h = CharacterHeight;
        MenuCharacterPos[i].w = 100;
    }
    MenuCharacterPos[0].y =  30;
    MenuCharacterPos[1].y = 160;
    MenuCharacterPos[2].y = 290;

    for (int i = 0; i < NUMMENU; i++) {
        MenuCharacterTex[i] = SDL_CreateTextureFromSurface(renderer, MenuCharacterSurface[i]);
        SDL_FreeSurface(MenuCharacterSurface[i]);
    }
    

    MenuFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 500);
    TTF_SetFontStyle(MenuFont, /*TTF_STYLE_BOLD|*/TTF_STYLE_ITALIC);

    bool selected[NUMMENU] = {0};

    for (int i = 0; i < NUMMENU; i++) {
        MenuPos[i].h = 50;
        MenuPos[i].w = 100;
    }

    // MenuPos[0].h = 50;
    // MenuPos[0].w = 120;

    int UP    = HEIGHT - 130;
    int DOWN  = HEIGHT -  30;
    int LEFT[NUMMENU]  = {  30, 160, 290};
    int RIGHT[NUMMENU] = { 130, 260, 390};
    MenuLabel[0] << "Miku";
    MenuLabel[1] << "Kirito";
    MenuLabel[2] << "Asuna";
    
    for (int i = 0; i < NUMMENU; i++) {
        MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[i]);
        MenuPos[i].y = HEIGHT - 60;
    }

    MenuPos[0].x =  30;
    MenuPos[1].x = 160;
    MenuPos[2].x = 290;

    SDL_Event event;
    while (1) {
        frameStart = SDL_GetTicks();
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
            SDL_RenderCopy(renderer, MenuCharacterTex[i], NULL, &MenuCharacterPos[i]);
            SDL_DestroyTexture(MenuTex[i]);
            SDL_DestroyTexture(MenuCharacterTex[i]);
        }
        SDL_RenderPresent(renderer);
        // for (int i = 0; i < NUMMENU; i++) {
		// 	SDL_BlitSurface(MenuChoice[i], NULL, screen, &MenuPos[i]);
		// }
		// SDL_UpdateWindowSurface(window);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) { //make the screen more smooth
            SDL_Delay(frameDelay - frameTime);
        }
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
    font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 500);
    if(!font) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
    }
    TTF_SetFontStyle(font, 0/*TTF_STYLE_BOLD|TTF_STYLE_ITALIC*/);
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