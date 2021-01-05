//#ifndef _MENUCOMPONENT_H
//#define _MENUCOMPONENT_H
#include "test_initial_SDL.h"
#include <SDL2/SDL.h>
//#include "Components.h"
//#include "../Game.h"
#include <string>
//#include <sstream>
//#include <map>
#include <SDL2/SDL_ttf.h>
#define WIDTH 1280
#define HEIGHT 720
int P1 = -1, P2 = -1;
using namespace std;

class Menu
//: public Component
{
public:
	Menu();
	~Menu();
	int firstmenu(SDL_Renderer *);
	int charactermenu(SDL_Renderer *);
	void startmenu(SDL_Renderer *);
	void Charactermenu(SDL_Renderer *);

private:
};
Menu::Menu()
{
}
Menu::~Menu()
{
	;
}
void Menu::startmenu(SDL_Renderer *renderer)
{
	switch (firstmenu(renderer))
	{
	case 0: /*single player*/;
	case 1:
		Charactermenu(renderer);
		break;
	}
}
void Menu::Charactermenu(SDL_Renderer *renderer)
{
	switch (charactermenu(renderer))
	{
	case -1:
		startmenu(renderer);
		break;
	case 0: /*double player*/;
	}
}

int Menu::firstmenu(SDL_Renderer *renderer)
{
	//SDL_Surface *screen = SDL_GetWindowSurface(window);
	SDL_Surface *img;

	//Uint32 time;
	int x = 0, y = 0;
	const int num = 2;

	bool selected[num] = {0, 0};
	SDL_Color color[2] = {{255, 223, 0}, {0, 255, 235}};
	SDL_Surface *menus[num];
	TTF_Font *font;
	font = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", 100);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
	char text1[] = "Single Player";
	char text2[] = "Double Player";
	menus[0] = TTF_RenderText_Solid(font, text1, color[0]);
	menus[1] = TTF_RenderText_Solid(font, text2, color[0]);

	SDL_Rect pos[num];
	pos[0].x = WIDTH / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = HEIGHT / 2 - menus[0]->clip_rect.h;
	pos[0].w = menus[0]->clip_rect.w;
	pos[0].h = menus[0]->clip_rect.h;
	pos[1].x = WIDTH / 2 - menus[1]->clip_rect.w / 2;
	pos[1].y = HEIGHT / 2 + menus[1]->clip_rect.h;
	pos[1].w = menus[0]->clip_rect.w;
	pos[1].h = menus[0]->clip_rect.h;

	SDL_Rect bgpos;
	bgpos.x = 0;
	bgpos.y = 0;
	bgpos.w = WIDTH;
	bgpos.h = HEIGHT;

	int z = 0;
	//initail renderer
	//SDL_SetRenderDrawColor(renderer,255,255,255,255);

	//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
	// SDL_SetColorKey(screen, SDL_TRUE, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Event event;
	while (1)
	{
		//string path="./img/miku/000"+to_string(z)+".bmp";
		string path;
		if (z < 10)
			path = "./img/miku/000" + to_string(z) + ".bmp";
		else
			path = "./img/miku/00" + to_string(z) + ".bmp";
		img = SDL_LoadBMP(path.c_str());

		SDL_RenderClear(renderer);

		//background
		SDL_Texture *bgtexture = SDL_CreateTextureFromSurface(renderer, img);
		SDL_RenderCopy(renderer, bgtexture, NULL, &bgpos);
		SDL_DestroyTexture(bgtexture);
		//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		//SDL_BlitSurface(img,NULL,screen,&bgpos);
		z++;
		if (z > 54)
			z = 0;
		//time = SDL_GetTicks();
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < num; i++)
					SDL_FreeSurface(menus[i]);
				return 1;
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < num; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						if (!selected[i])
						{
							selected[i] = true;
							if (i == 0)
							{
								SDL_FreeSurface(menus[0]);
								menus[i] = TTF_RenderText_Solid(font, text1, color[1]);
							}
							else if (i == 1)
							{
								SDL_FreeSurface(menus[1]);
								menus[i] = TTF_RenderText_Solid(font, text2, color[1]);
							}
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = false;
							if (i == 0)
							{
								SDL_FreeSurface(menus[0]);
								menus[i] = TTF_RenderText_Solid(font, text1, color[0]);
							}
							else if (i == 1)
							{
								SDL_FreeSurface(menus[1]);
								menus[i] = TTF_RenderText_Solid(font, text2, color[0]);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < num; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h)
					{
						for (int j = 0; j < num; j++)
						{
							SDL_FreeSurface(menus[j]);
						}
						return i;
					}
				}
				break;
			}
		}
		for (int i = 0; i < num; i++)
		{
			SDL_Texture *menutexture[num];
			menutexture[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
			SDL_RenderCopy(renderer, menutexture[i], NULL, &pos[i]);
			//SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
			//SDL_DestroyTexture(menutexture[i]);
		}

		//menu
		// SDL_Texture *menutexture[num];
		// for(int i=0;i<num;i++){
		// 	menutexture[i]=SDL_CreateTextureFromSurface(renderer,menus[i]);
		// 	SDL_RenderCopy(renderer,menutexture[i],NULL,&pos[i]);
		// 	SDL_DestroyTexture(menutexture[i]);
		// }

		//SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screen);
		// SDL_RenderCopy(renderer, texture, NULL, NULL);
		// SDL_DestroyTexture(texture);

		//SDL_UpdateWindowSurface(window);
		SDL_RenderPresent(renderer);

		SDL_Delay(70);
		SDL_FreeSurface(img);
		//SDL_FreeSurface(screen);
		//		if (1000 / 30 > (SDL_GetTicks() - time)) {
		//			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
		//		}
	}
}

int Menu::charactermenu(SDL_Renderer *renderer)
{
	//SDL_Surface *screen = SDL_GetWindowSurface(window);
	//SDL_SetColorKey(screen, SDL_FALSE, SDL_MapRGB(screen->format, 0X00, 0X00, 0X00));
	Uint32 time;
	int x = 0, y = 0;
	const int num = 5;

	bool selected[num] = {0, 0};
	SDL_Color color[2] = {{255, 223, 0}, {0, 255, 235}};
	SDL_Surface *menus[num];
	TTF_Font *font;
	font = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", 75);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);

	char text1[] = "Miku";
	char text2[] = "Kirito";
	char text3[] = "Shark";
	char text4[] = "Hung";
	char text5[] = "Hsieh";

	menus[0] = TTF_RenderText_Solid(font, text1, color[0]);
	menus[1] = TTF_RenderText_Solid(font, text2, color[0]);
	menus[2] = TTF_RenderText_Solid(font, text3, color[0]);
	menus[3] = TTF_RenderText_Solid(font, text4, color[0]);
	menus[4] = TTF_RenderText_Solid(font, text5, color[0]);

	SDL_Rect pos[num];
	for (int i = 0; i < num; i++)
	{
		pos[i].x = WIDTH * (2 * i + 1) / 10 - menus[i]->clip_rect.w / 2;
		pos[i].y = HEIGHT * 28 / 50 - menus[i]->clip_rect.h / 2;
		pos[i].w = menus[i]->clip_rect.w;
		pos[i].h = menus[i]->clip_rect.h;
	}

	//title
	char Title1[] = "Choose P1";
	char Title2[] = "Choose P2";
	SDL_Surface *title[2];
	title[0] = TTF_RenderText_Solid(font, Title1, color[0]);
	title[1] = TTF_RenderText_Solid(font, Title2, color[0]);

	SDL_Rect titlepos;
	titlepos.x = WIDTH / 2 - title[0]->clip_rect.w / 2;
	titlepos.y = 10;
	titlepos.w = title[0]->clip_rect.w;
	titlepos.h = title[0]->clip_rect.h;

	//subtitle
	char Subtitle1[] = "1P";
	char Subtitle2[] = "2P";
	char Subtitle3[] = ":";
	SDL_Surface *subtitle[3];
	subtitle[0] = TTF_RenderText_Solid(font, Subtitle1, color[0]);
	subtitle[1] = TTF_RenderText_Solid(font, Subtitle2, color[0]);
	subtitle[2] = TTF_RenderText_Solid(font, Subtitle3, color[0]);
	SDL_Rect subtitlepos[3];
	subtitlepos[0].x = 10;
	subtitlepos[0].y = 100;
	subtitlepos[0].w = subtitle[0]->clip_rect.w;
	subtitlepos[0].h = subtitle[0]->clip_rect.h;
	subtitlepos[1].x = WIDTH - 10 - subtitle[1]->clip_rect.w;
	subtitlepos[1].y = 100;
	subtitlepos[1].w = subtitle[1]->clip_rect.w;
	subtitlepos[1].h = subtitle[1]->clip_rect.h;
	subtitlepos[2].x = WIDTH / 2 - subtitle[2]->clip_rect.w / 2;
	subtitlepos[2].y = 100;
	subtitlepos[2].w = subtitle[2]->clip_rect.w;
	subtitlepos[2].h = subtitle[2]->clip_rect.h;

	//P1 : P2
	SDL_Surface *Psurface[num];
	Psurface[0] = TTF_RenderText_Solid(font, text1, color[0]);
	Psurface[1] = TTF_RenderText_Solid(font, text2, color[0]);
	Psurface[2] = TTF_RenderText_Solid(font, text3, color[0]);
	Psurface[3] = TTF_RenderText_Solid(font, text4, color[0]);
	Psurface[4] = TTF_RenderText_Solid(font, text5, color[0]);
	SDL_Rect P1pos, P2pos;
	P1pos.y = 100;
	P2pos.y = 100;

	//	pos[0].x = WIDTH / 2 - menus[0]->clip_rect.w / 2;
	//	pos[0].y = HEIGHT / 2 - menus[0]->clip_rect.h;
	//	pos[1].x = WIDTH / 2 - menus[1]->clip_rect.w / 2;
	//	pos[1].y = HEIGHT / 2 + menus[1]->clip_rect.h;

	SDL_Surface *character[num];
	character[0] = SDL_LoadBMP("./img/miku.bmp");
	character[1] = SDL_LoadBMP("./img/miku.bmp");
	character[2] = SDL_LoadBMP("./img/miku.bmp");
	character[3] = SDL_LoadBMP("./img/miku.bmp");
	character[4] = SDL_LoadBMP("./img/miku.bmp");

	int charactersize = 200;
	SDL_Rect characterpos[num];
	for (int i = 0; i < num; i++)
	{
		characterpos[i].x = WIDTH * i / 5 + 22;
		characterpos[i].y = HEIGHT - 230;
		characterpos[i].w = charactersize;
		characterpos[i].h = charactersize;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();

		//background free and color
		//SDL_FreeSurface(screen);
		//SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					if (P1 == -1)
						return -1;
					else if (P2 == -1)
					{
						P1 = -1;
					}
					else
					{
						P2 = -1;
					}
					break;
				}
			}
			switch (event.type)
			{
			case SDL_QUIT:
				for (int i = 0; i < num; i++)
					SDL_FreeSurface(menus[i]);
				return 1;

			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;
				for (int i = 0; i < num; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y /*&& y <= pos[i].y + pos[i].h*/)
					{
						if (!selected[i])
						{
							selected[i] = true;
							if (i == 0)
							{
								SDL_FreeSurface(menus[0]);
								menus[i] = TTF_RenderText_Solid(font, text1, color[1]);
							}
							else if (i == 1)
							{
								SDL_FreeSurface(menus[1]);
								menus[i] = TTF_RenderText_Solid(font, text2, color[1]);
							}
							else if (i == 2)
							{
								SDL_FreeSurface(menus[2]);
								menus[i] = TTF_RenderText_Solid(font, text3, color[1]);
							}
							else if (i == 3)
							{
								SDL_FreeSurface(menus[3]);
								menus[i] = TTF_RenderText_Solid(font, text4, color[1]);
							}
							else if (i == 4)
							{
								SDL_FreeSurface(menus[4]);
								menus[i] = TTF_RenderText_Solid(font, text5, color[1]);
							}
						}
					}
					else
					{
						if (selected[i])
						{
							selected[i] = false;
							if (i == 0)
							{
								SDL_FreeSurface(menus[0]);
								menus[i] = TTF_RenderText_Solid(font, text1, color[0]);
							}
							else if (i == 1)
							{
								SDL_FreeSurface(menus[1]);
								menus[i] = TTF_RenderText_Solid(font, text2, color[0]);
							}
							else if (i == 2)
							{
								SDL_FreeSurface(menus[2]);
								menus[i] = TTF_RenderText_Solid(font, text3, color[0]);
							}
							else if (i == 3)
							{
								SDL_FreeSurface(menus[3]);
								menus[i] = TTF_RenderText_Solid(font, text4, color[0]);
							}
							else if (i == 4)
							{
								SDL_FreeSurface(menus[4]);
								menus[i] = TTF_RenderText_Solid(font, text5, color[0]);
							}
						}
					}
				}
				break;

			case SDL_MOUSEBUTTONDOWN:
				x = event.button.x;
				y = event.button.y;
				for (int i = 0; i < num; i++)
				{
					if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y /*&& y <= pos[i].y + pos[i].h*/)
					{
						if (P1 == -1)
						{
							P1 = i;
							P1pos.x = (subtitlepos[0].x + subtitlepos[0].w + subtitlepos[2].x) / 2 - Psurface[P1]->clip_rect.w / 2;
							P1pos.w = Psurface[P1]->clip_rect.w;
							P1pos.h = Psurface[P1]->clip_rect.h;
							break;
						}
						else if (P2 == -1)
						{
							P2 = i;
							P2pos.x = (subtitlepos[2].x + subtitlepos[2].w + subtitlepos[1].x) / 2 - Psurface[P2]->clip_rect.w / 2;
							P2pos.w = Psurface[P2]->clip_rect.w;
							P2pos.h = Psurface[P2]->clip_rect.h;
						}

						//						// FreeSurface
						//						for(int i=0;i<2;i++){
						//							SDL_FreeSurface(title[i]);
						//						}
						//						for(int i=0;i<3;i++){
						//							SDL_FreeSurface(subtitle[i]);
						//						}
						//						for (int j = 0; j < num; j++) {
						//							SDL_FreeSurface(menus[j]);
						//							SDL_FreeSurface(character[j]);
						//						}
						//						return 0;
					}
				}
				break;
			}
		}

		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		//RenderCopy
		if (P1 == -1)
		{
			SDL_Texture *titletexture = SDL_CreateTextureFromSurface(renderer, title[0]);
			SDL_RenderCopy(renderer, titletexture, NULL, &titlepos);
			SDL_DestroyTexture(titletexture);
		}
		else if (P2 == -1)
		{
			SDL_Texture *titletexture = SDL_CreateTextureFromSurface(renderer, title[1]);
			SDL_RenderCopy(renderer, titletexture, NULL, &titlepos);
			SDL_DestroyTexture(titletexture);
		}

		SDL_Texture *subtitletexture[3];
		for (int i = 0; i < 3; i++)
		{
			subtitletexture[i] = SDL_CreateTextureFromSurface(renderer, subtitle[i]);
			SDL_RenderCopy(renderer, subtitletexture[i], NULL, &subtitlepos[i]);
			SDL_DestroyTexture(subtitletexture[i]);
		}

		if (P1 != -1)
		{
			SDL_Texture *P1texture = SDL_CreateTextureFromSurface(renderer, Psurface[P1]);
			SDL_RenderCopy(renderer, P1texture, NULL, &P1pos);
			SDL_DestroyTexture(P1texture);
		}

		if (P2 != -1)
		{
			SDL_Texture *P2texture = SDL_CreateTextureFromSurface(renderer, Psurface[P2]);
			SDL_RenderCopy(renderer, P2texture, NULL, &P2pos);
			SDL_DestroyTexture(P2texture);
		}

		//		for(int i=0;i<num;i++){
		//			SDL_BlitSurface(character[i],NULL,screen,&characterpos[i]);
		//		}
		SDL_Texture *menutexture[5];
		for (int i = 0; i < num; i++)
		{
			menutexture[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
			SDL_RenderCopy(renderer, menutexture[i], NULL, &pos[i]);
			SDL_DestroyTexture(menutexture[i]);
		}

		// SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screen);
		// SDL_RenderCopy(renderer, texture, NULL, NULL);
		// SDL_DestroyTexture(texture);

		SDL_Texture *charactertexture[num];
		for (int i = 0; i < num; i++)
		{
			charactertexture[i] = SDL_CreateTextureFromSurface(renderer, character[i]);
			SDL_RenderCopy(renderer, charactertexture[i], NULL, &characterpos[i]);
			SDL_DestroyTexture(charactertexture[i]);
		}
		SDL_RenderPresent(renderer);

		//SDL_UpdateWindowSurface(window);

		// make more smooth
		if (1000 / 30 > (SDL_GetTicks() - time))
		{
			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
		}
	}
}
//int MenuComponent::charactermenu()
//{
//	const int NUMMENU=5;
//	bool MenuisRunning=true;
//    std::stringstream MenuLabel[NUMMENU];
//    SDL_Surface *MenuChoice[NUMMENU];
//    SDL_Surface *MenuCharacterSurface[NUMMENU];
//    SDL_Texture *MenuTex[NUMMENU];
//    SDL_Texture *MenuCharacterTex[NUMMENU];
//    SDL_Color MenuColor[2] = {{255, 255, 255},
//                              {255, 223, 0}          // unselected
//                              /*,{  0, 255, 235}*/}; // selected
//    SDL_Rect MenuPos[NUMMENU];
//    SDL_Rect MenuCharacterPos[NUMMENU];
//    TTF_Font *MenuFont;
//
//    SDL_Texture *CharacterTextTexture[NUMMENU];
//    SDL_Surface *CharacterTextSurface[NUMMENU];
//    SDL_Rect CharacterTextRect[NUMMENU];
//    TTF_Font *CharacterTextFont;
//    //SDL_Color CharacterTextColor = {0, 255, 235};
//    SDL_Color CharacterTextColor = {255, 223, 0};
//    stringstream CharacterTextText[NUMMENU];
//    map<int, const char *> Character;
//    int X_MENU_MOUSE=0, Y_MENU_MOUSE=0;
//    int output = -1;
//    const int FPS = 60;
//    const int frameDelay = 1000 / FPS;
//
//    Uint32 frameStart;
//    int frameTime; //int
//
//    //MenuisRunning = true;
//    if (TTF_Init() == -1)
//    {
//    	cout<<"NO TTF";
//    }
//
//    //Set Character Position Here (Start)
//    int Characterscreen->clip_rect.h = 160;
//    for (int i = 0; i < NUMMENU; i++)
//    {
//        MenuCharacterPos[i].y = HEIGHT - 80 - CharacterHeight;
//        MenuCharacterPos[i].h = CharacterHeight;
//        MenuCharacterPos[i].w = 100;
//    }
//
//    MenuCharacterPos[0].x = 30;
//    for (int i = 1; i < NUMMENU; i++)
//    {
//        MenuCharacterPos[i].x = MenuCharacterPos[i - 1].x + 130;
//    }
//    //Set Character Position Here (End)
//
//    //Set Menu Font (Start)
//    MenuFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
//    TTF_SetFontStyle(MenuFont, /*TTF_STYLE_BOLD|*/ TTF_STYLE_ITALIC);
//    //Set Menu Font (End)
//
//    bool selected[NUMMENU] = {0};
//
//    //Set Menu Position Here (Start)
//    for (int i = 0; i < NUMMENU; i++)
//    {
//        MenuPos[i].h = 50;
//        MenuPos[i].w = 100;
//    }
//
//    int UP = HEIGHT - 130;
//    int DOWN = HEIGHT - 30;
//    int LEFT[NUMMENU] = {30, 160, 290, 420, 550};
//    int RIGHT[NUMMENU] = {130, 260, 390, 520, 650};
//    for (int i = 0; i < NUMMENU; i++)
//    {
//        MenuLabel[i] << Character[i];
//    }
//
//    for (int i = 0; i < NUMMENU; i++)
//    {
//        MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
//        MenuPos[i].y = HEIGHT - 60;
//    }
//
//    MenuPos[0].x = 30;
//    for (int i = 1; i < NUMMENU; i++)
//    {
//        MenuPos[i].x = MenuPos[i - 1].x + 130;
//    }
//    //Set Menu Position Here (End)
//
//    //Title (Character) Basic Setting (Start)
//    for (int i = 0; i < NUMMENU; i++)
//    {
//        CharacterTextRect[i].x = 1280/2 - MenuChoice[i]->clip_rect.h/2;
//        CharacterTextRect[i].y = 720/2 - MenuChoice[i]->clip_rect.h/2;
////        CharacterTextRect[i].x = 50;
////        CharacterTextRect[i].y = 200 + 80 * i;
//    }
//
//    CharacterTextFont = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
//    TTF_SetFontStyle(CharacterTextFont, TTF_STYLE_ITALIC);
//    for (int i = 0; i < NUMMENU; i++)
//    {
//        CharacterTextText[i].str("");
//    }
//    CharacterTextText[0] << "Miku: Miku Yu Yu!!!";
//    CharacterTextText[1] << "Kirito: Star Burst Stream!!!";
//    CharacterTextText[2] << "Shark: AAAAA!!!";
//    CharacterTextText[3] << "Hung: Miku 39 Is Answer!!!";
//    CharacterTextText[4] << "Heish: I'm Your Muji!!!";
//     for (int i = 0; i < NUMMENU; i++) {
//         CharacterTextSurface[i] = TTF_RenderText_Solid(CharacterTextFont, CharacterTextText[i].str().c_str(), CharacterTextColor);
//     }
//    //Title (Character) Basic Setting (End)
//
//    //Main Loop (Start)
//    SDL_Event event;
//    while (1)
//    {
//        SDL_Delay(1000);
//        //Title Basic Setting (Start)
//        SDL_Texture *LinkStartTexture = NULL;
//        SDL_Surface *LinkStartSurface = NULL;
//        SDL_Rect dst;
//        dst.h = 150;
//        dst.w = 600;
//        dst.x = 30;
//        dst.y = 30;
//        if (TTF_Init() == -1)
//        {
//            cout << "TTF_Init: " << TTF_GetError() << endl;
//        }
//        TTF_Font *font;
//        font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
//        if (!font)
//        {
//            cout << "TTF_OpenFont: " << TTF_GetError() << endl;
//        }
//        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
//        //SDL_Color color = { 0, 255, 235 };
//        SDL_Color color = {255, 223, 0};
//        stringstream LinkStartText;
//        LinkStartText.str("");
//        LinkStartText << "Choose Character";
//        LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
//        LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
//        if (!LinkStartTexture)
//        {
//            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
//        }
//        SDL_FreeSurface(LinkStartSurface);
//        TTF_CloseFont(font);
//        font = NULL;
//        //Title Basic Setting (End)
//
//        //Title (Character) Basic Setting (Start)
//        for (int i = 0; i < NUMMENU; i++)
//        {
//            SDL_FreeSurface(CharacterTextSurface[i]);
//        }
//        for (int i = 0; i < NUMMENU; i++)
//        {
//            CharacterTextSurface[i] = TTF_RenderText_Solid(CharacterTextFont, CharacterTextText[i].str().c_str(), CharacterTextColor);
//        }
//
//        //Title (Character) Basic Setting (End)
//
//        //Character Setting (Start)
//        frameStart = SDL_GetTicks();
//cout<<"dcr";
//        for (int i = 0; i < NUMMENU; i++)
//        {
//        	//ensure freesurface
//        	MenuCharacterSurface[i] = SDL_LoadBMP("./img/miku.bmp");
//            SDL_FreeSurface(MenuCharacterSurface[i]);
//        }
//        MenuCharacterSurface[0] = SDL_LoadBMP("./img/miku.bmp");
//        MenuCharacterSurface[1] = SDL_LoadBMP("./img/miku.bmp");
//        MenuCharacterSurface[2] = SDL_LoadBMP("./img/miku.bmp");
//        MenuCharacterSurface[3] = SDL_LoadBMP("./img/miku.bmp");
//        MenuCharacterSurface[4] = SDL_LoadBMP("./img/miku.bmp");
//        //Character Setting (End)
//        cout<<"dcr";
//        for (int i = 0; i < NUMMENU; i++)
//        {
//            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
//        }
//
//        //Event Loop (Start)
//        while (SDL_PollEvent(&event) != 0)
//        {
//            switch (event.type)
//            {
//            case SDL_QUIT:
//                for (int i = 0; i < NUMMENU; i++)
//                {
//                    SDL_FreeSurface(MenuChoice[i]);
//                    MenuisRunning = false;
//                }
//                break;
//            case SDL_MOUSEMOTION:
//                X_MENU_MOUSE = event.motion.x;
//                Y_MENU_MOUSE = event.motion.y;
//
//                for (int i = 0; i < NUMMENU; i++)
//                {
//                    if (X_MENU_MOUSE >= LEFT[i] && X_MENU_MOUSE <= RIGHT[i] && Y_MENU_MOUSE >= UP && Y_MENU_MOUSE <= DOWN)
//                    {
//                        if (!selected[i])
//                        {
//                            selected[i] = 1;
//                            SDL_FreeSurface(MenuChoice[i]);
//                            MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[1]);
//                        }
//                        else
//                        {
//                            if (selected[i])
//                            {
//                                selected[i] = 0;
//                                SDL_FreeSurface(MenuChoice[i]);
//                                MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
//                            }
//                        }
//                    }
//                    else
//                    {
//                        selected[i] = 0;
//                        SDL_FreeSurface(MenuChoice[i]);
//                        MenuChoice[i] = TTF_RenderText_Solid(MenuFont, MenuLabel[i].str().c_str(), MenuColor[0]);
//                    }
//                }
//                break;
//            case SDL_MOUSEBUTTONDOWN:
//                X_MENU_MOUSE = event.motion.x;
//                Y_MENU_MOUSE = event.motion.y;
//                for (int i = 0; i < NUMMENU; i++)
//                {
//                    if (X_MENU_MOUSE >= MenuPos[i].x && X_MENU_MOUSE <= MenuPos[i].x + MenuPos[i].w && Y_MENU_MOUSE >= MenuPos[i].y && Y_MENU_MOUSE <= MenuPos[i].y + MenuPos[i].h)
//                    {
//                        output = i;
//                        for (int j = 0; j < NUMMENU; j++)
//                        {
//                            SDL_FreeSurface(MenuChoice[j]);
//                        }
//                    }
//                }
//                break;
//            case SDL_KEYDOWN:
//                if (event.key.keysym.sym == SDLK_ESCAPE)
//                {
//                    output = 5;
//                    for (int i = 0; i < NUMMENU; i++)
//                    {
//
//                        SDL_FreeSurface(MenuChoice[i]);
//                    }
//                    MenuisRunning = false;
//                }
//                break;
//            }
//        }
//        if (!MenuisRunning)
//        {
//            for (int i = 0; i < NUMMENU; i++)
//            {
//                SDL_DestroyTexture(MenuTex[i]);
//                SDL_DestroyTexture(MenuCharacterTex[i]);
//                SDL_DestroyTexture(CharacterTextTexture[i]);
//            }
//            break;
//        }
//        //Event Loop (End)
//
//        //Render (Start)
//        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
//        SDL_RenderClear(renderer);
//        for (int i = 0; i < NUMMENU; i++)
//        {
//
//            MenuCharacterTex[i] = SDL_CreateTextureFromSurface(renderer, MenuCharacterSurface[i]);
//            CharacterTextTexture[i] = SDL_CreateTextureFromSurface(renderer, CharacterTextSurface[i]);
//            MenuTex[i] = SDL_CreateTextureFromSurface(renderer, MenuChoice[i]);
//            // SDL_FreeSurface(MenuCharacterSurface[i]);
//            SDL_FreeSurface(MenuChoice[i]);
//            // SDL_FreeSurface(CharacterTextSurface[i]);
//            SDL_RenderCopy(renderer, MenuTex[i], NULL, &MenuPos[i]);
//            SDL_RenderCopy(renderer, CharacterTextTexture[i], NULL, &CharacterTextRect[i]);
//            SDL_RenderCopy(renderer, MenuCharacterTex[i], NULL, &MenuCharacterPos[i]);
//            SDL_DestroyTexture(MenuTex[i]);
//            SDL_DestroyTexture(CharacterTextTexture[i]);
//            SDL_DestroyTexture(MenuCharacterTex[i]);
//        }
//        SDL_RenderCopy(renderer, LinkStartTexture, NULL, &dst);
//        SDL_DestroyTexture(LinkStartTexture);
//        SDL_RenderPresent(renderer);
//        //Render (End)
//
//        frameTime = SDL_GetTicks() - frameStart;
//        if (frameDelay > frameTime)
//        { //make the screen more smooth
//            SDL_Delay(frameDelay - frameTime);
//        }
//        if (output != -1)
//            return output;
//    }
//    //Main Loop (End)
//}

int main(int argc, char *argv[])
{
	init();
	Menu menu;
	menu.startmenu(renderer);

	close();
	return 0;
}
