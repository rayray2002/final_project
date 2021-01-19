#include "GameBoard.h"

int GameBoard::total_process = 0;

GameBoard::GameBoard() {
	UnitArray = new unit *[BOARDHEIGHT];
	for (int i = 0; i < BOARDHEIGHT; i++) {
		UnitArray[i] = new unit[BOARDWIDTH];
		for (int j = 0; j < BOARDWIDTH; j++) {
			Color c = Empty;
			UnitArray[i][j].color = c;
		}
	}
}

GameBoard::GameBoard(char board_i[][BOARDWIDTH]) {
	UnitArray = new unit *[BOARDHEIGHT];
	for (int i = 0; i < BOARDHEIGHT; i++) {
		UnitArray[i] = new unit[BOARDWIDTH];
		for (int j = 0; j < BOARDWIDTH; j++) {
			UnitArray[i][j].color = char_to_color(board_i[i][j]);
		}
	}
}

GameBoard::GameBoard(Color board_i[][BOARDWIDTH]) {
	UnitArray = new unit *[BOARDHEIGHT];
	for (int i = 0; i < BOARDHEIGHT; i++) {
		UnitArray[i] = new unit[BOARDWIDTH];
		for (int j = 0; j < BOARDWIDTH; j++) {
			UnitArray[i][j].color = board_i[i][j];
		}
	}
}

GameBoard::GameBoard(const GameBoard &board) :
		count(board.count), trash_num(board.trash_num) {
	UnitArray = new unit *[BOARDHEIGHT];
	score = board.score;
	combo = board.combo;
	for (int i = 0; i < BOARDHEIGHT; i++) {
		UnitArray[i] = new unit[BOARDWIDTH];
		for (int j = 0; j < BOARDWIDTH; j++) {
			UnitArray[i][j] = board.UnitArray[i][j];
		}
	}
}

GameBoard::~GameBoard() {
	for (int i = 0; i < BOARDHEIGHT; i++) {
		delete[] UnitArray[i];
	}
	delete[] UnitArray;
}

GameBoard GameBoard::operator-(const Block &block) {
	GameBoard board(*this);
	remove(block);
	if (board.UnitArray[block.y][block.x].color != Empty) {
		board.UnitArray[block.y][block.x].color = Empty;
		board.UnitArray[block.y][block.x].isActive = false;
	}
	if (block.x - 1 >= 0 && board.UnitArray[block.y][block.x - 1].color == Trash) {
		board.UnitArray[block.y][block.x - 1].color = Empty;
		board.UnitArray[block.y][block.x - 1].isActive = false;
	}
	if (block.y - 1 >= 0 && board.UnitArray[block.y - 1][block.x].color == Trash) {
		board.UnitArray[block.y - 1][block.x].color = Empty;
		board.UnitArray[block.y - 1][block.x].isActive = false;
	}
	if (block.x + 1 < BOARDWIDTH && board.UnitArray[block.y][block.x + 1].color == Trash) {
		board.UnitArray[block.y][block.x + 1].color = Empty;
		board.UnitArray[block.y][block.x + 1].isActive = false;
	}
	if (block.y + 1 < BOARDHEIGHT && board.UnitArray[block.y + 1][block.x].color == Trash) {
		board.UnitArray[block.y + 1][block.x].color = Empty;
		board.UnitArray[block.y + 1][block.x].isActive = false;
	}
	return board;
}

bool GameBoard::update() {
	vector<Block> chain;
	isUpdated = false;
	vector<vector<Block>> to_remove;
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {
			if (UnitArray[i][j].color != Empty) {
				chain = check_chained(j, i);
				if (chain.size() >= 4) {
					if (find(color_bonus.begin(), color_bonus.end(), UnitArray[i][j].color) == color_bonus.end())
						color_bonus.push_back(UnitArray[i][j].color);
					switch (chain.size()) {
						case 4:
							break;
						case 5:
							group_bonus += 2;
							break;
						case 6:
							group_bonus += 3;
							break;
						case 7:
							group_bonus += 4;
							break;
						case 8:
							group_bonus += 5;
							break;
						case 9:
							group_bonus += 6;
							break;
						case 10:
							group_bonus += 7;
							break;
						default:
							group_bonus += 10;
							break;
					}
					to_remove.push_back(chain);
				}
			}
		}
	}

	if (!to_remove.empty()) {
		combo++;
		isUpdated = true;

		if (DEBUG)
			cout << "combo" << combo << endl;

		for (int i = 0; i < to_remove.size(); i++) {
			for (int j = 0; j < to_remove[i].size(); j++) {
				*this - to_remove[i][j];
				count++;
			}
		}
	}

	if (DEBUG)
		cout << *this;
	fill();

	if (!isUpdated) {
		int score_add;
		if (color_bonus.size() != 1) {
			score_add = 10 * count * (group_bonus + 3 * pow(2, color_bonus.size()) + combo) * (1 + total_process / 50);
		} else {
			score_add = 10 * count * (group_bonus + combo) * (1 + total_process / 50);
		}
		trash_num = score_add / 70;
		score += score_add;
		total_process++;
	}

	chain.clear();
	chain.shrink_to_fit();

	return isUpdated;
}


int GameBoard::get_count() const {
	return count;
}

int GameBoard::get_trash_num() const {
	return trash_num;
}

void GameBoard::operator~() {
	combo = 0;
	count = 0;
	group_bonus = 0;
	color_bonus.clear();
}

ostream &operator<<(ostream &output, const GameBoard &g) {
	output << "######\n";
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {
			output << color_to_char(g.UnitArray[i][j].color);
		}
		output << '\n';
	}
	output << "######\n";
	output << "Score:" << g.score << "\nCombo:" << g.combo << "\nTrash:" << g.trash_num << '\n';
	return output;
}