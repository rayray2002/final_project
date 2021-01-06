//#ifndef _MENUCOMPONENT_H
//#define _MENUCOMPONENT_H
//#include "test_initial_SDL.h"
#include <SDL2/SDL.h>
#include "MenuComponent.h"

//#include "Components.h"
//#include "../Game.h"
#include <string>
//#include <sstream>
//#include <map>
#include <SDL_ttf.h>
#define WIDTH 1280
#define HEIGHT 720

using namespace std;

Menu::Menu() : P1(-1), P2(-1), Mode(-1)
{
	;
}

Menu::~Menu()
{
	;
}

void Menu::startmenu(SDL_Renderer *renderer)
{
	switch (firstmenu(renderer))
	{
	case 0: /*single player*/
		Mode = 1;
		break;
	case 1: /*double player*/
		Mode = 2;
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
		Mode = -1;
		P1 = -1;
		P2 = -1;
		break;
	case 0: /*double player*/;
	}
}

int Menu::GetMode()
{
	return Mode;
}

int Menu::GetP1()
{
	return P1;
}

int Menu::GetP2()
{
	return P2;
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
	const char text1[] = "Single Player";
	const char text2[] = "Double Player";
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
		}

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
	int picturenum = 0;
	int x = 0, y = 0;
	const int num = 5;

	bool selected[num] = {0, 0, 0, 0, 0};
	SDL_Color color[2] = {{255, 223, 0}, {0, 255, 235}};
	SDL_Surface *menus[num];
	TTF_Font *font;
	font = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", 60);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);

	const char text1[] = "Ho";
	const char text2[] = "Shan";
	const char text3[] = "Shouw";
	const char text4[] = "S";
	const char text5[] = "Shung";

	menus[0] = TTF_RenderText_Solid(font, text1, color[0]);
	menus[1] = TTF_RenderText_Solid(font, text2, color[0]);
	menus[2] = TTF_RenderText_Solid(font, text3, color[0]);
	menus[3] = TTF_RenderText_Solid(font, text4, color[0]);
	menus[4] = TTF_RenderText_Solid(font, text5, color[0]);

	SDL_Rect pos[num];
	for (int i = 0; i < num; i++)
	{
		pos[i].x = WIDTH * (2 * i + 1) / 10 - menus[i]->clip_rect.w / 2;
		pos[i].y = HEIGHT * 45 / 50 - menus[i]->clip_rect.h / 2;
		pos[i].w = menus[i]->clip_rect.w;
		pos[i].h = menus[i]->clip_rect.h;
	}

	//title
	const char Title1[] = "Choose P1";
	const char Title2[] = "Choose P2";
	SDL_Surface *title[2];
	title[0] = TTF_RenderText_Solid(font, Title1, color[0]);
	title[1] = TTF_RenderText_Solid(font, Title2, color[0]);

	SDL_Rect titlepos;
	titlepos.x = WIDTH / 2 - title[0]->clip_rect.w / 2;
	titlepos.y = 10;
	titlepos.w = title[0]->clip_rect.w;
	titlepos.h = title[0]->clip_rect.h;

	//subtitle
	TTF_Font *bigfont = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", 85);
	TTF_SetFontStyle(bigfont, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
	const char Subtitle1[] = "P1";
	const char Subtitle2[] = "P2";
	const char Subtitle3[] = ":";
	SDL_Surface *subtitle[3];
	subtitle[0] = TTF_RenderText_Solid(bigfont, Subtitle1, color[0]);
	subtitle[1] = TTF_RenderText_Solid(bigfont, Subtitle2, color[0]);
	subtitle[2] = TTF_RenderText_Solid(bigfont, Subtitle3, color[0]);
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
	Psurface[0] = TTF_RenderText_Solid(bigfont, text1, color[0]);
	Psurface[1] = TTF_RenderText_Solid(bigfont, text2, color[0]);
	Psurface[2] = TTF_RenderText_Solid(bigfont, text3, color[0]);
	Psurface[3] = TTF_RenderText_Solid(bigfont, text4, color[0]);
	Psurface[4] = TTF_RenderText_Solid(bigfont, text5, color[0]);
	SDL_Rect P1pos, P2pos;
	P1pos.y = 100;
	P2pos.y = 100;

	//character picture
	int charactersize = 200;
	SDL_Rect characterpos[num];
	for (int i = 0; i < num; i++)
	{
		characterpos[i].x = WIDTH * i / 5 + 22;
		characterpos[i].y = HEIGHT - 400;
		characterpos[i].w = charactersize;
		characterpos[i].h = charactersize * 4 / 3;
	}

	SDL_Rect CutCharactrerpos[num];
	for (int i = 0; i < num; i++)
	{
		CutCharactrerpos[i].x = 500;
		CutCharactrerpos[i].y = 50;
		CutCharactrerpos[i].w = 300;
		CutCharactrerpos[i].h = 400;
	}

	//adjustment
	CutCharactrerpos[0].x -= 25;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	//column
	SDL_Rect columnpos[num];
	for (int i = 0; i < num; i++)
	{
		columnpos[i] = {characterpos[i].x - 10,
						characterpos[i].y - 10,
						characterpos[i].w + 20,
						characterpos[i].h + 20};
	}

	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();

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
					if (x >= columnpos[i].x && x <= columnpos[i].x + columnpos[i].w && y >= columnpos[i].y && y <= pos[i].y + pos[i].h /*&& y <= pos[i].y + pos[i].h*/)
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
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					for (int i = 0; i < num; i++)
					{
						if (x >= columnpos[i].x && x <= columnpos[i].x + columnpos[i].w && y >= columnpos[i].y && y <= pos[i].y + pos[i].h /*&& y <= pos[i].y + pos[i].h*/)
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
						}
					}
				}

				break;
			}
		}

		SDL_Surface *character[num];
		string path[num];
		if (picturenum < 10)
		{
			path[0] = "./img/sakura/000" + to_string(picturenum) + ".bmp";
		}
		else
		{
			path[0] = "./img/sakura/00" + to_string(picturenum) + ".bmp";
		}
		if (picturenum < 10)
		{
			path[1] = "./img/fuhua/000" + to_string(picturenum) + ".bmp";
		}
		else
		{
			path[1] = "./img/fuhua/00" + to_string(picturenum) + ".bmp";
		}
		if (picturenum < 10)
		{
			path[2] = "./img/mei/000" + to_string(picturenum) + ".bmp";
		}
		else
		{
			path[2] = "./img/mei/00" + to_string(picturenum) + ".bmp";
		}

		for (int i = 0; i < 3; i++)
		{
			character[i] = SDL_LoadBMP(path[i].c_str());
		}
		character[3] = SDL_LoadBMP("./img/miku.bmp");
		character[4] = SDL_LoadBMP("./img/miku.bmp");

		picturenum++;
		if (picturenum > 99)
			picturenum = 1;

		//clear renderer
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

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

		for (int i = 0; i < num; i++)
		{
			if (selected[i])
			{
				SDL_SetRenderDrawColor(renderer, 0, 255, 235, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 223, 0, 255);
			}

			SDL_RenderFillRect(renderer, &columnpos[i]);
		}
		// SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screen);
		// SDL_RenderCopy(renderer, texture, NULL, NULL);
		// SDL_DestroyTexture(texture);

		SDL_Texture *charactertexture[num];
		for (int i = 0; i < num; i++)
		{
			charactertexture[i] = SDL_CreateTextureFromSurface(renderer, character[i]);
			SDL_RenderCopy(renderer, charactertexture[i], &CutCharactrerpos[i], &characterpos[i]);
			SDL_DestroyTexture(charactertexture[i]);
		}
		SDL_RenderPresent(renderer);

		//SDL_UpdateWindowSurface(window);

		// make more smooth
		// if (1000 / 30 > (SDL_GetTicks() - time))
		// {
		// 	SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
		// }

		SDL_Delay(20);

		for (int i = 0; i < num; i++)
		{
			SDL_FreeSurface(character[i]);
		}
	}
}

// int main(int argc, char *argv[])
// {
// 	init();
// 	Menu menu;
// 	menu.startmenu(renderer);
// 	cout << menu.GetMode() << endl;
// 	cout << menu.GetP1() << endl;
// 	cout << menu.GetP2() << endl;
// 	close();
// 	return 0;
// }
