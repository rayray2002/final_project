#include "Board.h"

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

char color_to_char(Color in) {
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

vector<Block> Board::check_chained(const int &x, const int &y) const {
	queue<Block> q;
	vector<Block> chain;
	q.push((Block) {x, y});
	bool visited[BOARDWIDTH][BOARDHEIGHT] = {};

	while (!q.empty()) {
		Block top = q.front();
		chain.push_back(top);
		visited[top.x][top.y] = true;
		q.pop();
		if (top.x - 1 >= 0 && (UnitArray[top.y][top.x - 1].color == UnitArray[y][x].color ||
		                       UnitArray[top.y][top.x - 1].color == Rainbow) && !visited[top.x - 1][top.y]) {
			q.push((Block) {top.x - 1, top.y});
			visited[top.x - 1][top.y] = true;
		}
		if (top.y - 1 >= 0 && (UnitArray[top.y - 1][top.x].color == UnitArray[y][x].color ||
		                       UnitArray[top.y - 1][top.x].color == Rainbow) && !visited[top.x][top.y - 1]) {
			q.push((Block) {top.x, top.y - 1});
			visited[top.x - 1][top.y] = true;
		}
		if (top.x + 1 < BOARDWIDTH && (UnitArray[top.y][top.x + 1].color == UnitArray[y][x].color ||
		                               UnitArray[top.y][top.x + 1].color == Rainbow) && !visited[top.x + 1][top.y]) {
			q.push((Block) {top.x + 1, top.y});
			visited[top.x + 1][top.y] = true;
		}
		if (top.y + 1 < BOARDHEIGHT && (UnitArray[top.y + 1][top.x].color == UnitArray[y][x].color ||
		                                UnitArray[top.y + 1][top.x].color == Rainbow) && !visited[top.x][top.y + 1]) {
			q.push((Block) {top.x, top.y + 1});
			visited[top.x][top.y + 1] = true;
		}
	}
	return chain;
}

void Board::fill() const {
	bool quit;
	do {
		quit = true;
		for (int i = 0; i < BOARDHEIGHT - 1; i++) {
			for (int j = 0; j < BOARDWIDTH; j++) {
				if (UnitArray[i][j].color != Empty && UnitArray[i + 1][j].color == Empty) {
					quit = false;
					UnitArray[i + 1][j].color = UnitArray[i][j].color;
					UnitArray[i][j].color = Empty;
				}
			}
		}
	} while (!quit);
}

int Board::get_combo() const {
	return combo;
}

int Board::get_score() const {
	return score;
}

bool Board::update() {
	return false;
}

void Board::operator~() {
	combo = 0;
}

bool Board::remove(const Block &block)
{
	bool success_removal = false;
	if (UnitArray[block.y][block.x].color != Empty)
	{
		UnitArray[block.y][block.x].color = Empty;
		UnitArray[block.y][block.x].isActive = false;
		success_removal = true;
	}
	if (block.x - 1 >= 0 && UnitArray[block.y][block.x - 1].color == Trash)
	{
		UnitArray[block.y][block.x - 1].color = Empty;
		UnitArray[block.y][block.x - 1].isActive = false;
	}
	if (block.y - 1 >= 0 && UnitArray[block.y - 1][block.x].color == Trash)
	{
		UnitArray[block.y - 1][block.x].color = Empty;
		UnitArray[block.y - 1][block.x].isActive = false;
	}
	if (block.x + 1 < BOARDWIDTH && UnitArray[block.y][block.x + 1].color == Trash)
	{
		UnitArray[block.y][block.x + 1].color = Empty;
		UnitArray[block.y][block.x + 1].isActive = false;
	}
	if (block.y + 1 < BOARDHEIGHT && UnitArray[block.y + 1][block.x].color == Trash)
	{
		UnitArray[block.y + 1][block.x].color = Empty;
		UnitArray[block.y + 1][block.x].isActive = false;
	}
	return success_removal;
}

ostream &operator<<(ostream &output, const Board &g) {
	output << "######\n";
	for (int i = 0; i < BOARDHEIGHT; i++) {
		for (int j = 0; j < BOARDWIDTH; j++) {
			output << color_to_char(g.UnitArray[i][j].color);
		}
		output << '\n';
	}
	output << "######\n";
	output << "Score:" << g.score << "\nCombo:" << g.combo << '\n';
	return output;
}