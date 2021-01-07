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

auto &tiles(manager.getGroup(Game::groupMap));
auto &colliders(manager.getGroup(Game::groupColliders));
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
	case SDLK_SPACE:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

	manager.refresh();
	// manager.update();
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
			for (auto &b : gameboards2)
			{
				b->getComponent<DoubleGameBoardComponent>().draw();
			}

			for (auto &b : buttoms)
			{
				b->getComponent<ButtomComponent>().draw();
			}
		}
		else if (playerNumber == 1)
		{
			for (auto &b : gameboards)
			{
				b->getComponent<GameBoardComponent>().draw();
			}
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
	dst.h = h;
	dst.w = w;
	dst.x = WIDTH / 2 - dst.w / 2;
	dst.y = HEIGHT / 2 - dst.h / 2;
	if (TTF_Init() == -1)
	{
		cout << "TTF_Init: " << TTF_GetError() << endl;
	}
	TTF_Font *font;
	font = TTF_OpenFont("./fonts/SAOUITT-Regular.ttf", 1000);
	if (!font)
	{
		cout << "TTF_OpenFont: " << TTF_GetError() << endl;
	}
	TTF_SetFontStyle(font, 0 /*TTF_STYLE_BOLD|TTF_STYLE_ITALIC*/);
	SDL_Color color = {255, 223, 0};
	stringstream LinkStartText;
	LinkStartText.str("");
	LinkStartText << text;
	LinkStartSurface = TTF_RenderText_Solid(font, LinkStartText.str().c_str(), color);
	LinkStartTexture = SDL_CreateTextureFromSurface(renderer, LinkStartSurface);
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
