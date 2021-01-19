#ifndef DEBUG
#define DEBUG 0
#endif

#include <algorithm>
#include <cmath>
#include "Board.h"

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

using namespace std;

class GameBoard : public Board {
	friend ostream &operator<<(ostream &, const GameBoard &);

public:

	GameBoard();

	GameBoard(char[][BOARDWIDTH]);

	GameBoard(Color[][BOARDWIDTH]);

	GameBoard(const GameBoard &);

	~GameBoard();

	bool update() override;

	void operator~() override;

	int get_count() const;

	int get_trash_num() const;

	GameBoard operator-(const Block &);

private:
	int count = 0;
	int trash_num = 0;

	int group_bonus = 0;
	vector<Color> color_bonus;

	static int total_process;
};

#endif //GAMEBOARD_H