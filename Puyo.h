#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const bool DEBUG = true;

const int HEIGHT = 13;
const int WIDTH = 6;

enum Color {
	Empty, Trash, Rainbow, Red, Green, Blue, Yellow, Purple
};

struct Block {
	int x, y;
};

Color char_to_color(char);

char color_to_char(char in);

class Puyo {
public:
	Color board[HEIGHT][WIDTH] = {};

	Puyo();

	Puyo(char [][WIDTH]);

	Puyo(Color [][WIDTH]);

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
