#include "test_initial_SDL.h"
#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "MenuComponent.h"
#define WIDTH 1280
#define HEIGHT 720
int P1 = -1, P2 = -1;
using namespace std;

Menu::Menu()
{
}
Menu::~Menu()
{
}
void Menu::startmenu(SDL_Window *window, SDL_Renderer *renderer)
{
	switch (firstmenu(window, renderer))
	{
	case 0: /*single player*/
		mode = 1;
		break;
	case 1:
		Charactermenu(window, renderer);
		mode = 2;
		break;
	}
}
void Menu::Charactermenu(SDL_Window *window, SDL_Renderer *renderer)
{
	switch (charactermenu(window, renderer))
	{
	case -1:
		startmenu(window, renderer);
		break;
	case 0: /*double player*/;
	}
}

int Menu::firstmenu(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Surface *screen = SDL_GetWindowSurface(window);
	SDL_Surface *img;

	//Uint32 time;
	int x = 0, y = 0;
	const int num = 2;

	bool selected[num] = {0, 0};
	SDL_Color color[2] = {{255, 223, 0}, {0, 255, 235}};
	SDL_Surface *menus[num];
	TTF_Font *font;
	font = TTF_OpenFont("fonts/SAOUITT-Regular.ttf", 100);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	char text1[] = "Single Player";
	char text2[] = "Double Player";
	menus[0] = TTF_RenderText_Solid(font, text1, color[0]);
	menus[1] = TTF_RenderText_Solid(font, text2, color[0]);
	SDL_Rect pos[num];
	pos[0].x = WIDTH / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = HEIGHT / 2 - menus[0]->clip_rect.h;
	pos[1].x = WIDTH / 2 - menus[1]->clip_rect.w / 2;
	pos[1].y = HEIGHT / 2 + menus[1]->clip_rect.h;

	SDL_Rect bgpos;
	bgpos.x = 0;
	bgpos.y = 0;
	bgpos.w = WIDTH;
	bgpos.h = HEIGHT;

	int z = 0;
	//initail renderer
	//SDL_SetRenderDrawColor(renderer,255,255,255,255);

	// SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
	// SDL_SetColorKey(screen, SDL_TRUE, SDL_MapRGB(screen->format, 0, 0, 0));

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	SDL_Event event;

	while (1)
	{

		// SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

		//string path="./img/miku/000"+to_string(z)+".bmp";
		string path;
		cout << "OK" << endl;

		if (z < 10)
			path = "./img/miku/000" + to_string(z) + ".bmp";
		else
			path = "./img/miku/00" + to_string(z) + ".bmp";
		img = SDL_LoadBMP(path.c_str());
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
		cout << "OK" << endl;

		for (int i = 0; i < num; i++)
		{
			SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
		}
		SDL_RenderClear(renderer);

		//background
		SDL_Texture *bgtexture = SDL_CreateTextureFromSurface(renderer, img);
		SDL_RenderCopy(renderer, bgtexture, NULL, &bgpos);
		SDL_DestroyTexture(bgtexture);

		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screen);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_DestroyTexture(texture);

		//SDL_UpdateWindowSurface(window);
		SDL_RenderPresent(renderer);

		SDL_Delay(70);
		SDL_FreeSurface(img);
		SDL_FreeSurface(screen);
		//		if (1000 / 30 > (SDL_GetTicks() - time)) {
		//			SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
		//		}
	}
}

int Menu::charactermenu(SDL_Window *window, SDL_Renderer *renderer)
{
	SDL_Surface *screen = SDL_GetWindowSurface(window);
	// SDL_SetColorKey(screen, SDL_FALSE, SDL_MapRGB(screen->format, 0, 0, 0));
	Uint32 time;
	int x = 0, y = 0;
	const int num = 5;

	bool selected[num] = {0, 0};
	SDL_Color color[2] = {{255, 223, 0}, {0, 255, 235}};
	SDL_Surface *menus[num];
	TTF_Font *font;
	font = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", 75);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);

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
	subtitlepos[1].x = WIDTH - 10 - subtitle[1]->clip_rect.w;
	subtitlepos[1].y = 100;
	subtitlepos[2].x = WIDTH / 2 - subtitle[2]->clip_rect.w / 2;
	subtitlepos[2].y = 100;

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

	// pos[0].x = WIDTH / 2 - menus[0]->clip_rect.w / 2;
	// pos[0].y = HEIGHT / 2 - menus[0]->clip_rect.h;
	// pos[1].x = WIDTH / 2 - menus[1]->clip_rect.w / 2;
	// pos[1].y = HEIGHT / 2 + menus[1]->clip_rect.h;

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

	// SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

	SDL_Event event;
	while (1)
	{
		time = SDL_GetTicks();

		//background free and color
		SDL_FreeSurface(screen);
		// SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));

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
							break;
						}
						else if (P2 == -1)
						{
							P2 = i;
							P2pos.x = (subtitlepos[2].x + subtitlepos[2].w + subtitlepos[1].x) / 2 - Psurface[P2]->clip_rect.w / 2;
						}
					}
				}
				break;
			}
		}

		//BlitSurface
		if (P1 == -1)
		{
			SDL_BlitSurface(title[0], NULL, screen, &titlepos);
		}
		else if (P2 == -1)
		{
			SDL_BlitSurface(title[1], NULL, screen, &titlepos);
		}

		for (int i = 0; i < 3; i++)
		{
			SDL_BlitSurface(subtitle[i], NULL, screen, &subtitlepos[i]);
		}

		if (P1 != -1)
		{
			SDL_BlitSurface(Psurface[P1], NULL, screen, &P1pos);
		}

		if (P2 != -1)
		{
			SDL_BlitSurface(Psurface[P2], NULL, screen, &P2pos);
		}

		for (int i = 0; i < num; i++)
		{
			SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
		}

		SDL_RenderClear(renderer);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, screen);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_DestroyTexture(texture);

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

int main(int argc, char *argv[])
{
	init();
	Menu menu;
	menu.startmenu(window, renderer);

	close();
	return 0;
}
