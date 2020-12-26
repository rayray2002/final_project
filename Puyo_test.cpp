#include "GameBoard.h"

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
	GameBoard puyo(test_board);

	int x;
	char c;
	while (true) {
		puyo.reset();
		while (puyo.update()) {
			puyo.printer();
		}
		puyo.printer();
		cout << "combo:" << puyo.get_combo() << ", trash:" << puyo.get_trash_num() << ", score:" << puyo.get_score()
		     << endl;

		cin >> c >> x;
		puyo.board[0][x] = char_to_color(c);
	}
}