#ifndef DEBUG
#define DEBUG 1
#endif

#ifndef HEIGHT
#define HEIGHT 13
#endif

#ifndef WIDTH
#define WIDTH 6
#endif

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

enum Color {
	Empty, Trash, Rainbow, Red, Green, Blue, Yellow, Purple
};

struct Block {
	int x, y;
};

Color char_to_color(char);

char color_to_char(char in);

class GameBoard {
public:
	Color board[HEIGHT][WIDTH] = {};

	GameBoard();

	GameBoard(char [][WIDTH]);

	GameBoard(Color [][WIDTH]);

	void printer();

	bool update();

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
