#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const bool DEBUG = true;
const int HEIGHT = 13;
const int WIDTH = 6;

enum Color {
	Empty, Red, Green, Blue, Yellow
};
struct Block {
	int x, y;
//	Color color;
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

	vector<Block> check_chained(int, int);

	void remove(Block);

	void fill();

	vector<int> update();

private:

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
	cout << "######\n";
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
		if (top.x - 1 >= 0 && board[top.y][top.x - 1] == board[y][x] && !visited[top.x - 1][top.y]) {
			q.push((Block) {top.x - 1, top.y});
			visited[top.x - 1][top.y] = true;
		}
		if (top.y - 1 >= 0 && board[top.y - 1][top.x] == board[y][x] && !visited[top.x][top.y - 1]) {
			q.push((Block) {top.x, top.y - 1});
			visited[top.x - 1][top.y] = true;
		}
		if (top.x + 1 < WIDTH && board[top.y][top.x + 1] == board[y][x] && !visited[top.x + 1][top.y]) {
			q.push((Block) {top.x + 1, top.y});
			visited[top.x + 1][top.y] = true;
		}
		if (top.y + 1 < HEIGHT && board[top.y + 1][top.x] == board[y][x] && !visited[top.x][top.y + 1]) {
			q.push((Block) {top.x, top.y + 1});
			visited[top.x][top.y + 1] = true;
		}
	}
	return chain;
}

void Puyo::remove(Block block) {
	board[block.y][block.x] = Empty;
}

void Puyo::fill() {
	bool quit;
	do {
		quit = true;
		for (int i = 0; i < HEIGHT; i++) {
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

vector<int> Puyo::update() {
	bool quit;
	int combo = 0, count = 0;
	do {
		quit = true;
		vector<Block> chain;
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (board[i][j] != Empty) {
					chain = check_chained(j, i);
					if (chain.size() >= 4) {
						quit = false;
						combo++;
						count += chain.size();
						for (int k = 0; k < chain.size(); k++) {
							remove(chain[k]);
						}
						if (DEBUG) printer();
						fill();
						if (DEBUG) printer();
						break;
					}
				}
			}
		}
	} while (!quit);
	vector<int> out;
	out.push_back(combo);
	out.push_back(count);
	return out;
}

int main() {
	char test_board[13][6] = {{' ', ' ', 'G', 'Y', 'R', 'R'},
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
	puyo.update();
	puyo.printer();
}