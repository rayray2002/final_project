#ifndef DEBUG
#define DEBUG 0
#endif

#ifndef BOARDHEIGHT
#define BOARDHEIGHT 13
#endif

#ifndef BOARDWIDTH
#define BOARDWIDTH 6
#endif

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <SDL.h>
#include "Vector2D.h"
//#include "Game.h"

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

using namespace std;

struct Block {
	int x, y;
};

enum Color {
	Empty,
	Trash,
	Rainbow,
	Red,
	Green,
	Blue,
	Yellow,
	Purple
};

struct unit {
	SDL_Texture *texture;
	SDL_Rect srcR, destR;
	Vector2D mapPosition;
	Color color;
	bool isMoving;
	bool isActive;
	SDL_Surface *surface;
	int Combo;
	int Score;
	bool KO;
};

Color char_to_color(char);

char color_to_char(Color);

class GameBoard {
	friend ostream &operator<<(ostream &, const GameBoard &);

public:
	unit UnitArray[BOARDHEIGHT][BOARDWIDTH];

	//	Color board[BOARDHEIGHT][BOARDWIDTH] = {};

	GameBoard();

	GameBoard(char[][BOARDWIDTH]);

	GameBoard(Color[][BOARDWIDTH]);

	void printer();

	bool update();

	bool isUpdated = false;

	bool falling = true;

	int get_combo() const;

	int get_count() const;

	int get_score() const;

	int get_trash_num() const;

	void reset();

private:
	vector<Block> check_chained(const int &, const int &);

	bool remove(const Block &block);

	void fill();

	int combo = 0;
	int count = 0;
	int score = 0;
	int trash_num = 0;

	int group_bonus = 0;
	vector<Color> color_bonus;
};

#endif //GAMEBOARD_H
