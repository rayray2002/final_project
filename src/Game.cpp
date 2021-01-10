#include "Game.h"
#include "ECS/Components.h"
#include "TextureManager.h"

using namespace std;

Manager manager;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

auto &back(manager.addEntity());

auto &buttom1(manager.addEntity());
auto &buttom2(manager.addEntity());
auto &buttom3(manager.addEntity());
auto &buttom4(manager.addEntity());
auto &buttom5(manager.addEntity());

auto &gameboard1(manager.addEntity());
auto &gameboard2(manager.addEntity());

vector<Entity *> gameblock;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(const char *title, int xMenuPos, int yMenuPos, int width, int height, bool fullscreen)
{

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystem Initialised!..." << endl;

		window = SDL_CreateWindow(title, xMenuPos, yMenuPos, width, height, flags);
		if (window)
		{
			cout << "Window Created!" << endl;
		}

		Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			cout << "Renderer Created!" << endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	buttom1.addComponent<ButtomComponent>(440, 35, 100, 100, "./img/kirito1.bmp");
	buttom2.addComponent<ButtomComponent>(740, 35, 100, 100, "./img/kirito1.bmp");
	buttom1.addGroup(groupButtoms);
	buttom2.addGroup(groupButtoms);

	buttom3.addComponent<ButtomComponent>(440, 150, 100, 100, "./img/kirito1.bmp");
	buttom4.addComponent<ButtomComponent>(740, 150, 100, 100, "./img/kirito1.bmp");
	buttom3.addGroup(groupButtoms);
	buttom4.addGroup(groupButtoms);

	buttom5.addComponent<ButtomComponent>(590, 75, 100, 100, "./img/vs.bmp");
	buttom5.addGroup(groupButtoms);

	back.addComponent<BackGroundComponent>();
	back.addGroup(groupBackGrounds);

	gameboard1.addComponent<GameBoardComponent>(0, 0, 0);
	gameboard1.addGroup(groupGameBoards);

	gameboard2.addComponent<DoubleGameBoardComponent>();
	gameboard2.addGroup(groupDoubleGameBoards);

	MusicPlay("./mp3/miku.wav", 64);

	LinkStart("Game Initailizing...", 1000, 100, 600);
	LinkStart("Game Initailized!", 1000, 100, 600);
	LinkStart("Link Start!", 2000, 200, 600);
}

auto &backs(manager.getGroup(Game::groupBackGrounds));
auto &buttoms(manager.getGroup(Game::groupButtoms));
auto &gameboards(manager.getGroup(Game::groupGameBoards));
auto &gameboards2(manager.getGroup(Game::groupDoubleGameBoards));

void Game::handleEveants()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	if (gameboard2.getComponent<DoubleGameBoardComponent>().gameboard1.score > 1000 ||
		gameboard2.getComponent<DoubleGameBoardComponent>().gameboard2.score > 1000)
	{
		stop = true;
	}

	if (stop)
	{
		SDL_RenderClear(Game::renderer);
		TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 100);
		TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
		string message;
		for (auto &b : gameboards2)
		{
			if (b->getComponent<DoubleGameBoardComponent>().gameboard1.score >
				b->getComponent<DoubleGameBoardComponent>().gameboard2.score)
			{
				if (P1 == 0)
				{
					message += "P1 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard1.score);
				}
				else if (P1 == 1)
				{
					message += "P1 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard1.score);
				}
				else if (P1 == 2)
				{
					message += "P1 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard1.score);
				}
				else if (P1 == 3)
				{
					message += "P1 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard1.score);
				}
				else if (P1 == 4)
				{
					message += "P1 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard1.score);
				}
			}
			else if (b->getComponent<DoubleGameBoardComponent>().gameboard1.score <
					 b->getComponent<DoubleGameBoardComponent>().gameboard2.score)
			{
				if (P2 == 0)
				{
					message += "P2 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard2.score);
				}
				else if (P2 == 1)
				{
					message += "P2 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard2.score);
				}
				else if (P2 == 2)
				{
					message += "P2 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard2.score);
				}
				else if (P2 == 3)
				{
					message += "P2 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard2.score);
				}
				else if (P2 == 4)
				{
					message += "P2 Win!!! Score: " + to_string(b->getComponent<DoubleGameBoardComponent>().gameboard2.score);
				}
			}
		}
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

		SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, message.c_str(), {255, 223, 0});
		SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
		SDL_Rect textrec1;
		textrec1.x = 640 - textsurface1->clip_rect.w / 2;
		textrec1.y = 360 - textsurface1->clip_rect.h / 2;
		textrec1.h = textsurface1->clip_rect.h;
		textrec1.w = textsurface1->clip_rect.w;
		SDL_FreeSurface(textsurface1);
		SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
		SDL_DestroyTexture(texttexture1);
		TTF_CloseFont(font1);

		TTF_Font *font2 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 120);
		TTF_SetFontStyle(font2, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
		SDL_Surface *textsurface2 = TTF_RenderText_Solid(font2, "Congratulations!!!", {255, 223, 0});
		SDL_Texture *texttexture2 = SDL_CreateTextureFromSurface(Game::renderer, textsurface2);
		SDL_Rect textrec2;
		textrec2.x = 640 - textsurface2->clip_rect.w / 2;
		textrec2.y = 55;
		textrec2.h = textsurface2->clip_rect.h;
		textrec2.w = textsurface2->clip_rect.w;
		SDL_FreeSurface(textsurface2);
		SDL_RenderCopy(Game::renderer, texttexture2, NULL, &textrec2);
		SDL_DestroyTexture(texttexture2);
		TTF_CloseFont(font2);

		SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

		SDL_RenderPresent(Game::renderer);
		SDL_RenderClear(Game::renderer);
		SDL_Delay(5000);
		// isRunning = false;
	}
	manager.refresh();
	for (auto &b : backs)
	{
		b->getComponent<BackGroundComponent>().update();
	}
	if (!stop)
	{
		if (playerNumber == 2)
		{
			for (auto &b : gameboards2)
			{
				b->getComponent<DoubleGameBoardComponent>().update();
			}
		}
		else if (playerNumber == 1)
		{
			for (auto &b : gameboards)
			{
				b->getComponent<GameBoardComponent>().update();
			}

			for (auto &b : buttoms)
			{
				b->getComponent<ButtomComponent>().update();
			}
		}
	}
}

void Game::render()
{

	for (auto &b : backs)
	{
		b->getComponent<BackGroundComponent>().draw();
	}

	if (!stop)
	{
		if (playerNumber == 2)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 64);
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
			SDL_Rect rec1, rec2;
			rec1.x = 100;
			rec1.y = 35;
			rec1.h = 650;
			rec1.w = 300;
			rec2.x = 880;
			rec2.y = 35;
			rec2.h = 650;
			rec2.w = 300;
			SDL_RenderDrawRect(Game::renderer, &rec1);
			SDL_RenderDrawRect(Game::renderer, &rec2);
			SDL_RenderFillRect(Game::renderer, &rec1);
			SDL_RenderFillRect(Game::renderer, &rec2);

			SDL_SetRenderDrawColor(Game::renderer, 255, 223, 0, 255);
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);
			for (int i = -2; i <= 2; ++i)
			{
				//1
				SDL_RenderDrawLine(Game::renderer, 100 + i, 35 + i, 400 + i, 35 + i);
				SDL_RenderDrawLine(Game::renderer, 100 + i, 685 + i, 400 + i, 685 + i);
				SDL_RenderDrawLine(Game::renderer, 100 + i, 35 + i, 100 + i, 685 + i);
				SDL_RenderDrawLine(Game::renderer, 400 + i, 35 + i, 400 + i, 685 + i);
				//2
				SDL_RenderDrawLine(Game::renderer, 1180 + i, 35 + i, 880 + i, 35 + i);
				SDL_RenderDrawLine(Game::renderer, 1180 + i, 685 + i, 880 + i, 685 + i);
				SDL_RenderDrawLine(Game::renderer, 1180 + i, 35 + i, 1180 + i, 685 + i);
				SDL_RenderDrawLine(Game::renderer, 880 + i, 35 + i, 880 + i, 685 + i);
			}

			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "score:", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 425;
			textrec1.y = 335;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);

			TTF_Font *font2 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font2, TTF_STYLE_ITALIC);
			SDL_Surface *textsurface2 = TTF_RenderText_Solid(font2, "score:", {255, 223, 0});
			SDL_Texture *texttexture2 = SDL_CreateTextureFromSurface(Game::renderer, textsurface2);
			SDL_Rect textrec2;
			textrec2.x = 1280 - 425 - textsurface2->clip_rect.w;
			textrec2.y = 335;
			textrec2.h = textsurface2->clip_rect.h;
			textrec2.w = textsurface2->clip_rect.w;
			SDL_FreeSurface(textsurface2);
			SDL_RenderCopy(Game::renderer, texttexture2, NULL, &textrec2);
			SDL_DestroyTexture(texttexture2);
			TTF_CloseFont(font2);
			for (auto &b : gameboards2)
			{
				b->getComponent<DoubleGameBoardComponent>().draw();
			}

			// for (auto &b : buttoms)
			// {
			// 	b->getComponent<ButtomComponent>().draw();
			// }
			SDL_SetRenderDrawColor(Game::renderer, 255, 223, 0, 255);
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);
			for (int i = -4; i <= 3; ++i)
			{
				//1
				SDL_RenderDrawLine(Game::renderer, 440 + i, 35 + i, 570 + i, 35 + i);
				SDL_RenderDrawLine(Game::renderer, 440 + i, 235 + i, 570 + i, 235 + i);
				SDL_RenderDrawLine(Game::renderer, 440 + i, 35 + i, 440 + i, 235 + i);
				SDL_RenderDrawLine(Game::renderer, 570 + i, 35 + i, 570 + i, 235 + i);
				//2
				SDL_RenderDrawLine(Game::renderer, 710 + i, 35 + i, 840 + i, 35 + i);
				SDL_RenderDrawLine(Game::renderer, 710 + i, 235 + i, 840 + i, 235 + i);
				SDL_RenderDrawLine(Game::renderer, 710 + i, 35 + i, 710 + i, 235 + i);
				SDL_RenderDrawLine(Game::renderer, 840 + i, 35 + i, 840 + i, 235 + i);
			}

			static int picturenum = 0;
			SDL_Surface *character1;
			SDL_Surface *character2;
			string path[5];
			if (picturenum < 10)
			{
				path[0] = "./img/Kiana/000" + to_string(picturenum) + ".bmp";
			}
			else if (picturenum < 100)
			{
				path[0] = "./img/Kiana/00" + to_string(picturenum) + ".bmp";
			}
			else
			{
				path[0] = "./img/Kiana/0" + to_string(picturenum) + ".bmp";
			}
			if (picturenum < 10)
			{
				path[1] = "./img/Rita/000" + to_string(picturenum) + ".bmp";
			}
			else if (picturenum < 100)
			{
				path[1] = "./img/Rita/00" + to_string(picturenum) + ".bmp";
			}
			else
			{
				path[1] = "./img/Rita/0" + to_string(picturenum) + ".bmp";
			}
			if (picturenum < 10)
			{
				path[2] = "./img/Fuhua/000" + to_string(picturenum) + ".bmp";
			}
			else if (picturenum < 100)
			{
				path[2] = "./img/Fuhua/00" + to_string(picturenum) + ".bmp";
			}
			else
			{
				path[2] = "./img/Fuhua/0" + to_string(picturenum) + ".bmp";
			}
			if (picturenum < 10)
			{
				path[3] = "./img/Mei/000" + to_string(picturenum) + ".bmp";
			}
			else if (picturenum < 100)
			{
				path[3] = "./img/Mei/00" + to_string(picturenum) + ".bmp";
			}
			else
			{
				path[3] = "./img/Mei/0" + to_string(picturenum) + ".bmp";
			}
			if (picturenum < 10)
			{
				path[4] = "./img/Terisa/000" + to_string(picturenum) + ".bmp";
			}
			else if (picturenum < 100)
			{
				path[4] = "./img/Terisa/00" + to_string(picturenum) + ".bmp";
			}
			else
			{
				path[4] = "./img/Terisa/0" + to_string(picturenum) + ".bmp";
			}
			character1 = SDL_LoadBMP(path[P1].c_str());
			character2 = SDL_LoadBMP(path[P2].c_str());
			picturenum++;
			if (picturenum > 326)
				picturenum = 1;
			SDL_Texture *character1t = SDL_CreateTextureFromSurface(Game::renderer, character1);
			SDL_Texture *character2t = SDL_CreateTextureFromSurface(Game::renderer, character2);
			SDL_FreeSurface(character1);
			SDL_FreeSurface(character2);
			SDL_Rect r1;
			r1.x = 440;
			r1.y = 35;
			r1.h = 200;
			r1.w = 130;
			SDL_Rect r2;
			r2.x = 710;
			r2.y = 35;
			r2.h = 200;
			r2.w = 130;
			SDL_Rect rr1;
			rr1.x = 260;
			rr1.y = 80;
			rr1.h = 300;
			rr1.w = 200;
			SDL_Rect rr2;
			rr2.x = 260;
			rr2.y = 80;
			rr2.h = 300;
			rr2.w = 200;
			SDL_RenderCopy(Game::renderer, character1t, &rr1, &r1);
			SDL_RenderCopy(Game::renderer, character2t, &rr2, &r2);
			SDL_DestroyTexture(character1t);
			SDL_DestroyTexture(character2t);
		}
		else if (playerNumber == 1)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 64);
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_BLEND);
			SDL_Rect rec1;
			rec1.x = 640 - 150;
			rec1.y = 35;
			rec1.h = 650;
			rec1.w = 300;
			SDL_RenderDrawRect(Game::renderer, &rec1);
			SDL_RenderFillRect(Game::renderer, &rec1);

			SDL_SetRenderDrawColor(Game::renderer, 255, 223, 0, 255);
			SDL_SetRenderDrawBlendMode(Game::renderer, SDL_BLENDMODE_NONE);
			for (int i = -2; i <= 2; ++i)
			{
				SDL_RenderDrawLine(Game::renderer, 490 + i, 35 + i, 490 + 300 + i, 35 + i);
				SDL_RenderDrawLine(Game::renderer, 490 + i, 685 + i, 490 + 300 + i, 685 + i);
				SDL_RenderDrawLine(Game::renderer, 490 + i, 35 + i, 490 + i, 685 + i);
				SDL_RenderDrawLine(Game::renderer, 490 + 300 + i, 35 + i, 490 + 300 + i, 685 + i);
			}

			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "score:", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 100;
			textrec1.y = 335;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
			for (auto &b : gameboards)
			{
				b->getComponent<GameBoardComponent>().draw();
			}
		}
	}

	if (playerNumber == 2)
	{
		if (P1 == 0)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Kiana", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 425;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P1 == 1)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Rita", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 425;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P1 == 2)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Fuhua", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 425;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P1 == 3)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Mei", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 425;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P1 == 1)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Terisa", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 425;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}

		if (P2 == 0)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Kiana", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 1280 - 425 - textsurface1->clip_rect.w;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P2 == 1)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Rita", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 1280 - 425 - textsurface1->clip_rect.w;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P2 == 2)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Fuhua", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 1280 - 425 - textsurface1->clip_rect.w;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P2 == 3)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Mei", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 1280 - 425 - textsurface1->clip_rect.w;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
		else if (P2 == 1)
		{
			TTF_Font *font1 = TTF_OpenFont("./fonts/GenJyuuGothic-Medium.ttf", 40);
			TTF_SetFontStyle(font1, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
			SDL_Surface *textsurface1 = TTF_RenderText_Solid(font1, "Terisa", {255, 223, 0});
			SDL_Texture *texttexture1 = SDL_CreateTextureFromSurface(Game::renderer, textsurface1);
			SDL_Rect textrec1;
			textrec1.x = 1280 - 425 - textsurface1->clip_rect.w;
			textrec1.y = 285;
			textrec1.h = textsurface1->clip_rect.h;
			textrec1.w = textsurface1->clip_rect.w;
			SDL_FreeSurface(textsurface1);
			SDL_RenderCopy(Game::renderer, texttexture1, NULL, &textrec1);
			SDL_DestroyTexture(texttexture1);
			TTF_CloseFont(font1);
		}
	}

	SDL_RenderPresent(Game::renderer);
	SDL_RenderClear(Game::renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_CloseAudio();
	SDL_Quit();
	Mix_Quit();
	IMG_Quit();
	cout << "Game Cleaned!" << endl;
}

void Game::LinkStart(string text, int second, int h, int w)
{
	SDL_Texture *LinkStartTexture = NULL;
	SDL_Surface *LinkStartSurface = NULL;
	SDL_Rect dst;
	if (TTF_Init() == -1)
	{
		cout << "TTF_Init: " << TTF_GetError() << endl;
	}
	TTF_Font *font;
	font = TTF_OpenFont("./fonts/GenJyuuGothic-Regular.ttf", 120);
	if (!font)
	{
		cout << "TTF_OpenFont: " << TTF_GetError() << endl;
	}
	TTF_SetFontStyle(font, TTF_STYLE_BOLD | TTF_STYLE_ITALIC);
	SDL_Color color = {255, 223, 0};
	stringstream LinkStartText;
	LinkStartText.str("");
	LinkStartText << text;
	LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
	LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
	dst.h = LinkStartSurface->clip_rect.h;
	dst.w = LinkStartSurface->clip_rect.w;
	dst.x = WIDTH / 2 - dst.w / 2;
	dst.y = HEIGHT / 2 - dst.h / 2;
	if (!LinkStartTexture)
	{
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

void Game::MusicPlay(const char *Music, int volume)
{
	int mflags = MIX_INIT_MP3;

	if ((Mix_Init(mflags) & mflags) != mflags)
	{
		cout << "Mix_Init: Failed to init required ogg and mod support!\n";
		cout << "Mix_Init: %s\n"
			 << Mix_GetError() << endl;
	}

	if (Mix_OpenAudio(128000, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		cout << "Mix_OpenAudio: %s\n"
			 << Mix_GetError() << endl;
	}

	Mix_Music *music = Mix_LoadMUS(Music);

	if (!music)
	{
		cout << "Mix_LoadMUS(\"miku.mp3\"): %s\n"
			 << Mix_GetError();
	}

	Mix_VolumeMusic(volume);
	Mix_PlayMusic(music, -1);

	cout << "Music Loaded!\n";
}

void Game::getP1(int p)
{
	P1 = p;
}
void Game::getP2(int p)
{
	P2 = p;
}
