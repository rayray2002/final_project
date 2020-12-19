#include <SDL.h>
#include <SDL_image.h>
#include<SDL_ttf.h>
#include <stdio.h>
#include <iostream>

int showmenu1(SDL_Window* window) {
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	Uint32 time;
	int x = 0, y = 0;
	const int num = 2;
	Uint16 text[2][100000];
	
	bool selected[num] = { 0,0 };
	SDL_Color color[2] = { {255,255,255},{255,0,0} };
	SDL_Surface* menus[num];
	TTF_Font* font;
	font = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", 100);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
	Uint16 text1[] = { 0x55ae, 0x4eba, 0x904a, 0x6232 ,0x0000};
	Uint16 text2[] = { 0x96d9, 0x4eba, 0x904a, 0x6232 ,0x0000};

	menus[0] = TTF_RenderUNICODE_Solid(font, text1, color[0]);
	menus[1] = TTF_RenderUNICODE_Solid(font, text2, color[0]);
	SDL_Rect pos[num];
	pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
	pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
	pos[1].x = screen->clip_rect.w / 2 - menus[1]->clip_rect.w / 2;
	pos[1].y = screen->clip_rect.h / 2 + menus[1]->clip_rect.h;

	SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0, 0, 0));
	
	SDL_Event event;
	while (1) {
		time = SDL_GetTicks();
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					for (int i = 0; i < num; i++)
						SDL_FreeSurface(menus[i]);
					return 1;
				case SDL_MOUSEMOTION:
					x = event.motion.x;
					y = event.motion.y;
					for (int i = 0; i < num; i++) {
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
							if (!selected[i]) {
								selected[i] = true;
								if (i == 0) {
									SDL_FreeSurface(menus[0]);
									menus[i] = TTF_RenderUNICODE_Solid(font, text1, color[1]);
								}
								else if (i == 1) {
									SDL_FreeSurface(menus[1]);
									menus[i] = TTF_RenderUNICODE_Solid(font, text2, color[1]);
								}
							}
						}else{
							if (selected[i]){
								selected[i] = false;
								if (i == 0) {
									SDL_FreeSurface(menus[0]);
									menus[i] = TTF_RenderUNICODE_Solid(font, text1, color[0]);
								}
								else if (i == 1) {
									SDL_FreeSurface(menus[1]);
									menus[i] = TTF_RenderUNICODE_Solid(font, text2, color[0]);
								}
							}
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					x = event.button.x;
					y = event.button.y;
					for (int i = 0; i < num; i++) {
						if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
							for (int j = 0; j < num; j++) {
								SDL_FreeSurface(menus[i]);
							}
							return i;
						}
					}
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						for (int i = 0; i < num; i++) {
							SDL_FreeSurface(menus[i]);
						}
						return 0;
				}
			}
			for (int i = 0; i < num; i++) {
				SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
			}
			SDL_UpdateWindowSurface(window);
			
			if (1000 / 30 > (SDL_GetTicks() - time)) {
				SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
			}
	}

}
