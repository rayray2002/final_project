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

Color char_to_color(char in) {
	Color c;
	switch (in) {
		case 'R':
			c = Red;
			break;
		case 'G':
			c = Green;
			break;
		case 'B':
			c = Blue;
			break;
		case 'Y':
			c = Yellow;
			break;
		case 'T':
			c = Trash;
			break;
		case '*':
			c = Rainbow;
			break;
		case 'P':
			c = Purple;
			break;
		default:
			c = Empty;
			break;
	}
	return c;
}

char color_to_char(char in) {
	char c;
	switch (in) {
		case Red:
			c = 'R';
			break;
		case Green:
			c = 'G';
			break;
		case Blue:
			c = 'B';
			break;
		case Yellow:
			c = 'Y';
			break;
		case Trash:
			c = 'T';
			break;
		case Rainbow:
			c = '*';
			break;
		case Purple:
			c = 'P';
			break;
		default:
			c = ' ';
			break;
	}
	return c;
}

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

	void reset();

private:
	vector<Block> check_chained(int, int);

	bool remove(Block);

	void fill();

	int combo = 0;
	int count = 0;

};

Puyo::Puyo() {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			Color c = Empty;
			board[i][j] = c;
		}
	}
}

Puyo::Puyo(char board_i[][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = char_to_color(board_i[i][j]);
		}
	}
}

Puyo::Puyo(Color board_i[][WIDTH]) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = board_i[i][j];
		}
	}
}

void Puyo::printer() {
	cout << "######\n";
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cout << color_to_char(board[i][j]);
		}
		cout << endl;
	}
	cout << "######\n\n";
}

vector<Block> Puyo::check_chained(int x, int y) {
	queue<Block> q;
	vector<Block> chain;
	q.push((Block) {x, y});
	bool visited[WIDTH][HEIGHT] = {};

	while (!q.empty()) {
		Block top = q.front();
		chain.push_back(top);
		visited[top.x][top.y] = true;
		q.pop();
//		cout << top.x << " " << top.y << endl;
		if (top.x - 1 >= 0 && (board[top.y][top.x - 1] == board[y][x] || board[top.y][top.x - 1] == Rainbow) &&
		    !visited[top.x - 1][top.y]) {
			q.push((Block) {top.x - 1, top.y});
			visited[top.x - 1][top.y] = true;
		}
		if (top.y - 1 >= 0 && (board[top.y - 1][top.x] == board[y][x] || board[top.y - 1][top.x] == Rainbow) &&
		    !visited[top.x][top.y - 1]) {
			q.push((Block) {top.x, top.y - 1});
			visited[top.x - 1][top.y] = true;
		}
		if (top.x + 1 < WIDTH && (board[top.y][top.x + 1] == board[y][x] || board[top.y][top.x + 1] == Rainbow) &&
		    !visited[top.x + 1][top.y]) {
			q.push((Block) {top.x + 1, top.y});
			visited[top.x + 1][top.y] = true;
		}
		if (top.y + 1 < HEIGHT && (board[top.y + 1][top.x] == board[y][x] || board[top.y + 1][top.x] == Rainbow) &&
		    !visited[top.x][top.y + 1]) {
			q.push((Block) {top.x, top.y + 1});
			visited[top.x][top.y + 1] = true;
		}
	}
	return chain;
}

bool Puyo::remove(Block block) {
	bool success_removal = false;
	if (board[block.y][block.x] != Empty) {
		board[block.y][block.x] = Empty;
		success_removal = true;
	}
	if (block.x - 1 >= 0 && board[block.y][block.x - 1] == Trash) board[block.y][block.x - 1] = Empty;
	if (block.y - 1 >= 0 && board[block.y - 1][block.x] == Trash) board[block.y - 1][block.x] = Empty;
	if (block.x + 1 < WIDTH && board[block.y][block.x + 1] == Trash) board[block.y][block.x + 1] = Empty;
	if (block.y + 1 < HEIGHT && board[block.y + 1][block.x] == Trash) board[block.y + 1][block.x] = Empty;
	return success_removal;
}

void Puyo::fill() {
	bool quit;
	do {
		quit = true;
		for (int i = 0; i < HEIGHT - 1; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (board[i][j] != Empty && board[i + 1][j] == Empty) {
					quit = false;
					board[i + 1][j] = board[i][j];
					board[i][j] = Empty;
				}
			}
		}
	} while (!quit);
}

bool Puyo::update() {
	vector<Block> chain;
	bool is_updated = false;
	if (DEBUG) fill();
	vector<vector<Block>> to_remove;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (board[i][j] != Empty) {
				chain = check_chained(j, i);
				if (chain.size() >= 4) {
					to_remove.push_back(chain);
				}
			}
		}
	}

	if (!to_remove.empty()) {
		combo++;
		is_updated = true;
		if (DEBUG) cout << "combo" << combo << endl;
		for (int i = 0; i < to_remove.size(); i++) {
			for (int j = 0; j < to_remove[i].size(); j++) {
				if (remove(to_remove[i][j])) count++;
			}
		}
	}

	if (DEBUG) printer();

	return is_updated;
}

int Puyo::get_combo() const {
	return combo;
}

int Puyo::get_count() const {
	return count;
}

void Puyo::reset() {
	combo = 0;
	count = 0;
}

int main() {
	char test_board[13][6] = {{'T', ' ', 'G', 'Y', 'R', 'R'},
	                          {'R', 'Y', 'Y', 'G', 'Y', 'G'},
	                          {'G', 'Y', 'G', 'Y', 'R', 'R'},
	                          {'R', 'Y', 'G', 'Y', 'R', 'G'},
	                          {'Y', 'G', 'Y', 'R', 'Y', 'G'},
	                          {'G', 'Y', 'R', 'Y', 'R', 'G'},
	                          {'Y', 'G', 'Y', 'R', 'Y', 'R'},
	                          {'Y', 'G', 'Y', 'R', 'Y', 'R'},
	                          {'Y', 'R', 'R', 'G', 'R', 'G'},
	                          {'R', 'Y', 'G', 'Y', 'G', 'G'},
	                          {'G', 'R', 'Y', 'G', 'Y', 'R'},
	                          {'G', 'R', 'Y', 'G', 'Y', 'R'},
	                          {'G', 'R', 'Y', 'G', 'Y', 'R'}};
	Puyo puyo(test_board);
	puyo.reset();

	while (puyo.update()) {
		puyo.printer();
	}

	puyo.printer();
	cout << "combo:" << puyo.get_combo() << ", count:" << puyo.get_count();
}