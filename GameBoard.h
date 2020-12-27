#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef BOARDHEIGHT
#define BOARDHEIGHT 13
#endif

#ifndef BOARDWIDTH
#define BOARDWIDTH 6
#endif

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

enum Color
{
	Empty,
	Trash,
	Rainbow,
	Red,
	Green,
	Blue,
	Yellow,
	Purple
};

struct Block
{
	int x, y;
};

Color char_to_color(char);

char color_to_char(Color);

class GameBoard
{
public:
	Color board[BOARDHEIGHT + 1][BOARDWIDTH + 2] = {};

	GameBoard();

	GameBoard(char[][BOARDWIDTH]);

	GameBoard(Color[][BOARDWIDTH]);

	void printer();

	bool update();

	bool isUpdated;

	bool isChanged;

	int get_combo() const;

	int get_count() const;

	int get_score() const;

	int get_trash_num() const;

	void reset();

private:
	vector<Block> check_chained(int, int);

	bool remove(Block);

	void fill();

	int combo = 0;
	int count = 0;
	int score = 0;
	int trash_num = 0;

	int group_bonus = 0;
	vector<Color> color_bonus;
};

#endif //GAMEBOARD_H
