#include <iostream>
#include <vector>
#include <string>

using namespace std;

void drawGame(vector<vector<char>> oriVector, int colNum)
{
	for (int i = 1; i <= colNum; ++i) {
		cout << i << " ";
	}

	cout << '\n';

	for (int row = 0; row < oriVector.size(); row++)
	{
		for (int col = 0; col < oriVector[row].size(); col++)
		{
			cout << oriVector[row][col] << " ";
		}
		cout << "\n";
	}
}

bool checkHorizontal(vector<vector<char>> grid, bool isFirstPlayer, int setRow, int setCol, int checkmate)
{
	if (checkmate > setCol)
		return false;

	char token = isFirstPlayer ? 'O' : 'X';
	int row, col;

	for (row = 0; row < setRow; row++)
	{
		for (col = 0; col <= setCol - checkmate; col++)
		{
			int flag = checkmate;
			while (flag)
			{
				flag--;
				if (grid[row][col + flag] != token)
				{
					break;
				}
				if (flag == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool checkVertical(vector<vector<char>> grid, bool isFirstPlayer, int setRow, int setCol, int checkmate)
{
	if (checkmate > setRow)
		return false;

	char token = isFirstPlayer ? 'O' : 'X';
	int row, col;

	for (col = 0; col < setCol; col++)
	{
		for (row = 0; row <= setRow - checkmate; row++)
		{
			int flag = checkmate;
			while (flag)
			{
				flag--;
				if (grid[row + flag][col] != token)
				{
					break;
				}
				if (flag == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// from left to right
bool checkLeftDiagonal(vector<vector<char>> grid, bool isFirstPlayer, int setRow, int setCol, int checkmate)
{
	if (checkmate > setRow || checkmate > setCol)
		return false;

	char token = isFirstPlayer ? 'O' : 'X';
	int row, col;

	for (row = 0; row <= setRow - checkmate; row++)
	{
		for (col = 0; col <= setCol - checkmate; col++)
		{
			int flag = checkmate;
			while (flag)
			{
				flag--;
				if (grid[row + flag][col + flag] != token)
				{
					break;
				}
				if (flag == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool checkRightDiagonal(vector<vector<char>> grid, bool isFirstPlayer, int setRow, int setCol, int checkmate)
{
	if (checkmate > setRow || checkmate > setCol)
		return false;

	char token = isFirstPlayer ? 'O' : 'X';
	int row, col;

	for (row = 0; row <= setRow - checkmate; row++)
	{
		for (col = checkmate - 1; col <= setCol; col++)
		{
			int flag = checkmate;
			while (flag)
			{
				flag--;
				if (grid[row + flag][col - flag] != token)
				{
					break;
				}
				if (flag == 0)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool hasWon(vector<vector<char>> grid, bool isFirstPlayer, int row, int col, int checkmate)
{
	return checkHorizontal(grid, isFirstPlayer, row, col, checkmate) || checkVertical(grid, isFirstPlayer, row, col, checkmate) ||
		checkLeftDiagonal(grid, isFirstPlayer, row, col, checkmate) || checkRightDiagonal(grid, isFirstPlayer, row, col, checkmate);
}

vector<vector<char>> insertPiece(vector<vector<char>> grid, int selectedNum, int player)
{
	int aaa = static_cast<int>(grid.size());

	while (aaa)
	{
		if (grid[aaa - 1][selectedNum - 1] == '#')
		{
			player == 1 ? grid[aaa - 1][selectedNum - 1] = 'O' : grid[aaa - 1][selectedNum - 1] = 'X';
			break;
		}
		aaa--;
	}

	return grid;
}

vector<vector<char>> subtractPiece(vector<vector<char>> grid, int selectedNum)
{
	for (int row = grid.size() - 1; row > 0; row--)
	{
		grid[row][selectedNum - 1] = grid[row - 1][selectedNum - 1];
	}

	grid[0][selectedNum - 1] = '#';

	return grid;
}

bool isTokenRemovable(vector<vector<char>> grid, bool isFirstPlayer)
{
	for (int col = 0; col < grid[0].size(); ++col)
	{
		if (grid[grid.size() - 1][col] == (isFirstPlayer ? 'O' : 'X'))
		{
			return true;
		}
	}
	return false;
}

bool isTied(vector<vector<char>> grid)
{
	int flag = 0;

	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[row].size(); col++)
		{
			if (grid[row][col] != '#')
			{
				flag++;
			}
		}
	}

	return flag == grid.size() * grid[0].size();
}

int main()
{
	bool isFirstPlayer = true;

	string removeMode;

	int selectedPiece;

	cout << "Welcome, let's play\n";

	int cusRow = 0, cusColumn = 0, winCondition = 0;

	while (!cin.fail() && (cusRow < 4 || cusRow > 20))
	{
		cout << "How many rows do you want to have?(4-20)\n";
		cin >> cusRow;
	};

	while (!cin.fail() && (cusColumn < 4 || cusColumn > 20))
	{
		cout << "How many column do you want to have?(4-20)\n";
		cin >> cusColumn;
	};


	while (!cin.fail() && (winCondition < 3 || winCondition >((cusRow > cusColumn) ? cusRow : cusColumn)))
	{
		cout << "How many to win?(3-" << ((cusRow > cusColumn) ? cusRow : cusColumn) << ')' << endl;
		cin >> winCondition;
	};

	while (!cin.fail() && removeMode != "y" && removeMode != "n")
	{
		cout << "Do you want to play remove mode?(y?n)\n";
		cin >> removeMode;
	};


	vector <vector<char>> theGrid(static_cast<unsigned long>(cusRow), vector<char>(static_cast<unsigned long>(cusColumn), '#'));


	drawGame(theGrid, cusColumn);

	while (true)
	{
		string selectMode = "";
		// insert number
		cout << "Player " << to_string(isFirstPlayer ? 1 : 2) << " is playing\n";

		if (removeMode == "y" && isTokenRemovable(theGrid, isFirstPlayer))
		{
			while (!cin.fail() && selectMode != "i" && selectMode != "r")
				//                while (cin.fail() || selectMode != "i" || selectMode != "r")
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "You want to insert or remove?(i/r)\n";
				cin >> selectMode;
			}
		}

		cout << (removeMode == "y" && selectMode == "r" ? "Remove" : "Insert") << " a piece: \n";

		cin >> selectedPiece;

		if (selectMode == "r")
		{
			while (cin.fail() || selectedPiece > cusColumn || selectedPiece < 1 || theGrid[cusRow - 1][selectedPiece - 1] == '#' || theGrid[cusRow - 1][selectedPiece - 1] != (isFirstPlayer ? 'O' : 'X'))
			{
				// this is not yours, && this is empty
				cin.clear();
				cin.ignore(1000, '\n');

				if (selectedPiece > cusColumn || selectedPiece < 1)
				{
					cout << "Please select number from 1-" << cusColumn << '.' << endl;
				}
				else if (theGrid[cusRow - 1][selectedPiece - 1] == '#')
				{
					cout << "This column is empty, you cannot remove. \n";
				}
				else if (theGrid[cusRow - 1][selectedPiece - 1] != (isFirstPlayer ? 'O' : 'X'))
				{
					cout << "This column is not yours, you cannot remove. \n";
				}
				cin >> selectedPiece;
			}
		}
		else
		{
			while (cin.fail() || selectedPiece > cusColumn || selectedPiece < 1 || theGrid[0][selectedPiece - 1] != '#')
			{
				cin.clear();
				cin.ignore(1000, '\n');

				if (selectedPiece > cusColumn || selectedPiece < 1)
				{
					cout << "Please select number from 1-" << theGrid[0].size() << '.' << endl;
				}
				else if (theGrid[0][selectedPiece - 1] != '#')
				{
					cout << "This column is full, please select another column\n";
				}
				cin >> selectedPiece;
			}
		}

		if (selectMode == "r")
		{
			theGrid = subtractPiece(theGrid, selectedPiece);
		}
		else
		{
			theGrid = insertPiece(theGrid, selectedPiece, isFirstPlayer);
		}

		cout << "New Graph is:\n";

		drawGame(theGrid, cusColumn);

		if (hasWon(theGrid, isFirstPlayer, cusRow, cusColumn, winCondition))
		{
			cout << "Player " << to_string(isFirstPlayer ? 1 : 2) << " won!!!\n";

			string playAgain;

			while (!cin.fail() && playAgain != "y" && playAgain != "n")
			{
				cout << "Do you want to play again?(y?n)\n";
				cin >> playAgain;
			};

			cin.clear();
			cin.ignore(1000, '\n');

			if (playAgain == "y")
			{
				isFirstPlayer = false;
				cout << "Game restarted.\n";
				for (int row = 0; row < theGrid.size(); row++)
				{
					for (int col = 0; col<theGrid[row].size(); col++)
					{
						theGrid[row][col] = '#';
					}
				}
				drawGame(theGrid, cusColumn);
			}
			if (playAgain == "n")
			{
				break;
			}
		}

		if (isTied(theGrid))
		{
			string playAgain;

			while (!cin.fail() && playAgain != "y" && playAgain != "n")
			{
				cout << "Draw! Do you want to play again?(y?n)\n";
				cin >> playAgain;
			};

			cin.clear();
			cin.ignore(1000, '\n');

			if (playAgain == "y")
			{
				isFirstPlayer = false;
				cout << "Game restarted.\n";
				for (int row = 0; row < theGrid.size(); row++)
				{
					for (int col = 0; col<theGrid[row].size(); col++)
					{
						theGrid[row][col] = '#';
					}
				}
				drawGame(theGrid, cusColumn);
			}
			if (playAgain == "n")
			{
				break;
			}
		}

		isFirstPlayer = !isFirstPlayer;
	}

	cout << "Bye bye \n";
	return 0;
}
