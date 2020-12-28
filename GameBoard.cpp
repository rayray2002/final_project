#include "GameBoard.h"

Color char_to_color(char in)
{
	Color c;
	switch (in)
	{
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

char color_to_char(Color in)
{
	char c;
	switch (in)
	{
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

GameBoard::GameBoard()
{
	for (int i = 1; i < BOARDHEIGHT + 1; i++)
	{
		for (int j = 1; j < BOARDWIDTH + 1; j++)
		{
			Color c = Empty;
			board[i][j] = c;
		}
	}
}

GameBoard::GameBoard(char board_i[][BOARDWIDTH])
{
	for (int i = 1; i < BOARDHEIGHT + 1; i++)
	{
		for (int j = 1; j < BOARDWIDTH + 1; j++)
		{
			board[i][j] = char_to_color(board_i[i - 1][j - 1]);
		}
	}
}

GameBoard::GameBoard(Color board_i[][BOARDWIDTH])
{
	for (int i = 1; i < BOARDHEIGHT + 1; i++)
	{
		for (int j = 1; j < BOARDWIDTH + 1; j++)
		{
			board[i][j] = board_i[i - 1][j - 1];
		}
	}
}

void GameBoard::printer()
{
	cout << "######\n";
	for (int i = 1; i < BOARDHEIGHT; i++)
	{
		for (int j = 1; j < BOARDWIDTH + 1; j++)
		{
			cout << color_to_char(board[i][j]);
		}
		cout << endl;
	}
	cout << "######\n\n";
}

vector<Block> GameBoard::check_chained(int x, int y)
{
	queue<Block> q;
	vector<Block> chain;
	q.push((Block){x, y});
	bool visited[BOARDWIDTH + 2][BOARDHEIGHT + 1] = {};

	while (!q.empty())
	{
		Block top = q.front();
		chain.push_back(top);
		visited[top.x][top.y] = true;
		q.pop();
		cout << top.x << " " << top.y << endl;
		if (top.x - 1 >= 1 && (board[top.y][top.x - 1] == board[y][x] || board[top.y][top.x - 1] == Rainbow) &&
			!visited[top.x - 1][top.y])
		{
			q.push((Block){top.x - 1, top.y});
			visited[top.x - 1][top.y] = true;
		}
		if (top.y - 1 >= 1 && (board[top.y - 1][top.x] == board[y][x] || board[top.y - 1][top.x] == Rainbow) &&
			!visited[top.x][top.y - 1])
		{
			q.push((Block){top.x, top.y - 1});
			visited[top.x - 1][top.y] = true;
		}
		if (top.x + 1 < BOARDWIDTH + 1 && (board[top.y][top.x + 1] == board[y][x] || board[top.y][top.x + 1] == Rainbow) &&
			!visited[top.x + 1][top.y])
		{
			q.push((Block){top.x + 1, top.y});
			visited[top.x + 1][top.y] = true;
		}
		if (top.y + 1 < BOARDHEIGHT + 1 && (board[top.y + 1][top.x] == board[y][x] || board[top.y + 1][top.x] == Rainbow) &&
			!visited[top.x][top.y + 1])
		{
			q.push((Block){top.x, top.y + 1});
			visited[top.x][top.y + 1] = true;
		}
	}
	return chain;
}

bool GameBoard::remove(Block block)
{
	bool success_removal = false;
	if (board[block.y][block.x] != Empty)
	{
		board[block.y][block.x] = Empty;
		success_removal = true;
	}
	if (block.x - 1 >= 1 && board[block.y][block.x - 1] == Trash)
		board[block.y][block.x - 1] = Empty;
	if (block.y - 1 >= 1 && board[block.y - 1][block.x] == Trash)
		board[block.y - 1][block.x] = Empty;
	if (block.x + 1 < BOARDWIDTH + 1 && board[block.y][block.x + 1] == Trash)
		board[block.y][block.x + 1] = Empty;
	if (block.y + 1 < BOARDHEIGHT + 1 && board[block.y + 1][block.x] == Trash)
		board[block.y + 1][block.x] = Empty;
	return success_removal;
}

void GameBoard::fill()
{
	bool quit;
	do
	{
		quit = true;
		for (int i = 1; i < BOARDHEIGHT; i++)
		{
			for (int j = 1; j < BOARDWIDTH + 1; j++)
			{
				if (board[i][j] != Empty && board[i + 1][j] == Empty)
				{
					quit = false;
					board[i + 1][j] = board[i][j];
					board[i][j] = Empty;
				}
			}
		}
	} while (!quit);
}

bool GameBoard::update()
{
	vector<Block> chain;
	isUpdated = false;
	printer();
	vector<vector<Block>> to_remove;
	for (int i = 1; i < BOARDHEIGHT + 1; i++)
	{
		for (int j = 1; j < BOARDWIDTH + 1; j++)
		{
			if (board[i][j] != Empty)
			{
				chain = check_chained(j, i);
				if (chain.size() >= 4)
				{
					if (find(color_bonus.begin(), color_bonus.end(), board[i][j]) == color_bonus.end())
						color_bonus.push_back(board[i][j]);
					switch (chain.size())
					{
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

	if (!to_remove.empty())
	{
		combo++;
		isUpdated = true;
		if (DEBUG)
			cout << "combo" << combo << endl;
		for (int i = 0; i < to_remove.size(); i++)
		{
			for (int j = 0; j < to_remove[i].size(); j++)
			{
				if (remove(to_remove[i][j]))
					count++;
			}
		}
	}

	if (DEBUG)
		printer();

	if (!isUpdated)
	{
		int score_add;
		if (color_bonus.size() != 1)
		{
			score_add = 10 * count * (group_bonus + 3 * pow(2, color_bonus.size()) + combo);
		}
		else
		{
			score_add = 10 * count * (group_bonus + combo);
		}
		trash_num = score_add / 70;
		score += score_add;
	}

	return isUpdated;
}

int GameBoard::get_combo() const
{
	return combo;
}

int GameBoard::get_score() const
{
	return score;
}

int GameBoard::get_count() const
{
	return count;
}

int GameBoard::get_trash_num() const
{
	return trash_num;
}

void GameBoard::reset()
{
	combo = 0;
	count = 0;
	group_bonus = 0;
	color_bonus.clear();
}