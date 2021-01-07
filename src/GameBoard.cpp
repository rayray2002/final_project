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
	for (int i = 0; i < BOARDHEIGHT; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			Color c = Empty;
			UnitArray[i][j].color = c;
		}
	}
}

GameBoard::GameBoard(char board_i[][BOARDWIDTH])
{
	for (int i = 0; i < BOARDHEIGHT; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			UnitArray[i][j].color = char_to_color(board_i[i][j]);
		}
	}
}

GameBoard::GameBoard(Color board_i[][BOARDWIDTH])
{
	for (int i = 0; i < BOARDHEIGHT; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			UnitArray[i][j].color = board_i[i][j];
		}
	}
}

void GameBoard::printer()
{
	cout << "######\n";
	for (int i = 0; i < BOARDHEIGHT; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			cout << color_to_char(UnitArray[i][j].color);
		}
		cout << endl;
	}
	cout << "######\n\n";
}

vector<Block> GameBoard::check_chained(const int &x, const int &y)
{
	queue<Block> q;
	vector<Block> chain;
	q.push((Block){x, y});
	bool visited[BOARDWIDTH][BOARDHEIGHT] = {};

	while (!q.empty())
	{
		Block top = q.front();
		chain.push_back(top);
		visited[top.x][top.y] = true;
		q.pop();
		//		cout << top.x << " " << top.y << endl;
		if (top.x - 1 >= 0 && (UnitArray[top.y][top.x - 1].color == UnitArray[y][x].color || UnitArray[top.y][top.x - 1].color == Rainbow) && !visited[top.x - 1][top.y])
		{
			q.push((Block){top.x - 1, top.y});
			visited[top.x - 1][top.y] = true;
		}
		if (top.y - 1 >= 0 && (UnitArray[top.y - 1][top.x].color == UnitArray[y][x].color || UnitArray[top.y - 1][top.x].color == Rainbow) && !visited[top.x][top.y - 1])
		{
			q.push((Block){top.x, top.y - 1});
			visited[top.x - 1][top.y] = true;
		}
		if (top.x + 1 < BOARDWIDTH && (UnitArray[top.y][top.x + 1].color == UnitArray[y][x].color || UnitArray[top.y][top.x + 1].color == Rainbow) && !visited[top.x + 1][top.y])
		{
			q.push((Block){top.x + 1, top.y});
			visited[top.x + 1][top.y] = true;
		}
		if (top.y + 1 < BOARDHEIGHT && (UnitArray[top.y + 1][top.x].color == UnitArray[y][x].color || UnitArray[top.y + 1][top.x].color == Rainbow) && !visited[top.x][top.y + 1])
		{
			q.push((Block){top.x, top.y + 1});
			visited[top.x][top.y + 1] = true;
		}
	}
	return chain;
}

bool GameBoard::remove(const Block &block)
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

void GameBoard::fill()
{
	bool quit;
	do
	{
		quit = true;
		for (int i = 0; i < BOARDHEIGHT; i++)
		{
			for (int j = 0; j < BOARDWIDTH; j++)
			{
				if (UnitArray[i][j].color != Empty && UnitArray[i + 1][j].color == Empty)
				{
					quit = false;
					UnitArray[i + 1][j].color = UnitArray[i][j].color;
					UnitArray[i][j].color = Empty;
				}
			}
		}
	} while (!quit);
}

bool GameBoard::update()
{
	vector<Block> chain;
	isUpdated = false;
	vector<vector<Block>> to_remove;
	cout << 1 << endl;
	for (int i = 0; i < BOARDHEIGHT; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			if (UnitArray[i][j].color != Empty)
			{
				chain = check_chained(j, i);
				if (chain.size() >= 4)
				{
					if (find(color_bonus.begin(), color_bonus.end(), UnitArray[i][j].color) == color_bonus.end())
						color_bonus.push_back(UnitArray[i][j].color);
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
	cout << 2 << endl;

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
			//			to_remove[i].clear();
			//			to_remove[i].shrink_to_fit();
		}
	}
	cout << 3 << endl;

	if (DEBUG)
		printer();
	cout << 4 << endl;

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
	cout << 5 << endl;

	chain.clear();
	chain.shrink_to_fit();
	cout << 6 << endl;

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

ostream &operator<<(ostream &output, const GameBoard &g)
{
	output << "######\n";
	for (int i = 0; i < BOARDHEIGHT; i++)
	{
		for (int j = 0; j < BOARDWIDTH; j++)
		{
			output << color_to_char(g.UnitArray[i][j].color);
		}
		output << '\n';
	}
	output << "######\n";
	output << "Score:" << g.score << "\nCombo:" << g.combo << "\nTrash:" << g.trash_num << '\n';
	return output;
}
