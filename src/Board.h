#ifndef BOARDHEIGHT
#define BOARDHEIGHT 13
#endif

#ifndef BOARDWIDTH
#define BOARDWIDTH 6
#endif

#include <iostream>
#include <vector>
#include <queue>
//#include <SDL.h>
//#include "Vector2D.h"

#ifndef BOARD_H
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
//	SDL_Texture *texture;
//	SDL_Rect srcR, destR;
//	Vector2D mapPosition;
//	SDL_Surface *surface;
	Color color;
	bool isMoving;
	bool isActive;
	bool KO;
};

Color char_to_color(char);

char color_to_char(Color);

class Board {
	friend ostream &operator<<(ostream &, const Board &);
protected:

	int width = BOARDWIDTH, height = BOARDHEIGHT;
	int combo = 0;
public:

	unit **UnitArray = nullptr;

	vector<Block> check_chained(const int &, const int &) const;

	void fill() const;

	bool remove(const Block &block);

	virtual bool update();

	virtual void operator~();

	int get_combo() const;

	int get_score() const;

	bool isUpdated = false;

	bool falling = true;

	int score = 0;
};

#define BOARD_H

#endif //INC_1_BOARD_H
