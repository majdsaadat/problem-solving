#include<iostream>
#include <iomanip> 

using namespace std;

const int Player_X = 'X';
const int Player_O = 'O';
const int EMPTY_CHAR=' ';
const int LOSE = -1;
const int UNFINISHED =2;
const int FALSE = 0;
const int WIN = 1;
const int DRAW = 0;
const int Size = 3;
const int TRUE = 1;

#define VALID_SQUARE(square) (square >= 1 && square <= 9 ? TRUE : FALSE)
#define OTHER(player) (player == Player_X ? Player_O : Player_X)
#define VALID_COORD(x,y) ((x < 0 || x > Size-1 || y < 0 || y > Size-1) ? FALSE : TRUE)
#define IS_EMPTY(square) (square == ' ' ? TRUE : FALSE)


void init_board(char board[Size][Size]);
void print_Title();
int player_move(char board[Size][Size], char player);
int comp_move(char board[Size][Size], char player);
int enter_grid(char board[Size][Size], char player, int grid_num);
int enter_coord(char board[Size][Size], char player, int x, int y);
void print_board(char board[Size][Size]);
int check_winner(char board[Size][Size], char player);
int my_max(char board[Size][Size], char player);
int my_min(char board[Size][Size], char player);
void minimax(char board[Size][Size], char player);


int main()
{
	char board[Size][Size];
	char choice;   
	print_Title();
	while (TRUE)
	{
		cout << "Do you want to play in X ? (y/n): " << endl;;
		cin >> choice;
		choice = tolower(choice);
		if (choice == 'y' || choice == 'n')
		{
			if (choice == 'y')
				choice = Player_X;
			else if(choice == 'n')
				choice = Player_O;
			break;
		}
		cout << "Incorrect choice, Please Try Again" << endl;
	}

	init_board(board);

	print_board(board);

	while (TRUE)
	{
		if (choice == Player_X)
		{
			if (player_move(board, Player_X) == TRUE)
				break;
			if (comp_move(board, Player_O) == TRUE)
				break;
		}
		else {
			if (comp_move(board, Player_X) == TRUE)
				break;
			if (player_move(board, Player_O) == TRUE)
				break;
		}
	}

	return 0;
}

void print_Title()
{
	cout << "\n****************************************************" << endl;
	cout << "**\t\t X and O Game \t\t          **" << endl;
	cout << "****************************************************" << endl;
	cout << endl;
	cout << endl;
}

void init_board(char board[Size][Size])
{
	int i, j;
	for (i = 0; i < Size; ++i)
	{
		for (j = 0; j < Size; ++j) {
			board[i][j] = EMPTY_CHAR;
		}
	}
}
int player_move(char board[Size][Size], char player)
{
	int grid_num;
	while (TRUE)
	{
		cout<<"\nEnter the box number you want : ";
		 cin>>grid_num;
		cout<<"\n\tYOUR TURN\n"<<endl;
		if (enter_grid(board, player, grid_num) == 0)
			break;

		cout << "Incorrect choice, Try Again Please\n" << endl;
	}

	print_board(board);

	int play = check_winner(board, player);
	if (play == WIN) {
		cout << "\n\n\nCongratulations, you are the winner" << endl;
		return TRUE;
	}
	else if (play == DRAW) {
		cout << "\n\n\nIt's a Draw" << endl;
		return TRUE;
	}
	return FALSE;
}

int comp_move(char board[Size][Size], char player)
{
	cout << "\n\tCOMPUTER'S TURN\n" << endl;

	minimax(board, player);
	print_board(board);

	int play = check_winner(board, player);
	if (play == WIN)
	{
		cout << "\n\n\nUnlucky, the computer wins *_*" << endl;
		return TRUE;
	}
	else if (play == DRAW) {
		cout<<"\n\n\nIt's a Draw"<<endl;
		return TRUE;
	}
	return FALSE;
}

int enter_grid(char board[Size][Size], char player, int grid_num)
{
	if (VALID_SQUARE(grid_num) == FALSE)
		return TRUE;
	int i, j;
	if (grid_num < 4) {
		j = 0;
	}
	else if (grid_num < 7) {
		j = 1;
	}
	else {
		j = 2;
	}
	i = grid_num - 1 - (j * Size);
	if (IS_EMPTY(board[i][j]) == FALSE)
		return TRUE; 

	board[i][j] = player;
	return FALSE;
}
int enter_coord(char board[Size][Size], char player, int x, int y)
{
	if (VALID_COORD(x, y) == FALSE)
		return TRUE;
	if (IS_EMPTY(board[x][y]) == FALSE)
		return TRUE;
	board[x][y] = player;

	return FALSE;
}

int check_winner(char board[Size][Size], char player)
{
	for (int i = 0; i < Size; ++i)
	{
		if (board[i][0] != EMPTY_CHAR && board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			if (board[i][0] == player)
				return WIN;
		}
	}

	for (int i = 0; i < Size; ++i)
	{
		if (board[0][i] != EMPTY_CHAR && board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			if (board[0][i] == player)
				return WIN;
		}
	}

	if (board[0][0] != EMPTY_CHAR && board[0][0] == board[1][1] && board[1][1] == board[2][2])
	{
		if (board[0][0] == player)
			return WIN;
	}

	if (board[2][0] != EMPTY_CHAR && board[2][0] == board[1][1] && board[1][1] == board[0][2])
	{
		if (board[2][0] == player)
			return WIN;
	}

	bool is_draw = true;
	for (int i = 0; i < Size; ++i)
	{
		for (int j = 0; j < Size; ++j)
		{
			if (board[i][j] == EMPTY_CHAR)
			{
				is_draw = false;
				break;
			}
		}
		if (!is_draw)
			break;
	}
	if (is_draw)
		return DRAW;

	return UNFINISHED;
}

int my_max(char board[Size][Size], char player)
{
	int result = check_winner(board, player);
	if (result != UNFINISHED)
		return result;

	int i, j, max;
	max = -10; 
	for (i = 0; i < Size; ++i)
	{
		for (j = 0; j < Size; ++j)
		{
			if (board[i][j] != ' ')
				continue;
			char new_board[Size][Size];
			int x, y;
			for (x = 0; x < Size; ++x)
			{
				for (y = 0; y < Size; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			if (new_board[i][j] != ' ') {
				cout<<"MY_MAX overlap"<<endl;
				exit(0);
			}
			new_board[i][j] = player;
			int temp = my_min(new_board, OTHER(player));
			if (temp > max)
				max = temp;
		}
	}
	return max;
}

int my_min(char board[Size][Size], char player)
{
	int result = check_winner(board, OTHER(player));
	if (result != UNFINISHED)
		return result;

	int i, j, min;
	min = 10; 
	for (i = 0; i < Size; ++i)
	{
		for (j = 0; j < Size; ++j)
		{
			if (board[i][j] != ' ')
				continue;
			char new_board[Size][Size];
			int x, y;
			for (x = 0; x < Size; ++x)
			{
				for (y = 0; y < Size; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			if (new_board[i][j] != ' ') {
				cout<<"MY_MIN overlap"<<endl; 
				exit(0);
			}
			new_board[i][j] = player;
			int temp = my_max(new_board, OTHER(player));
			if (temp < min)
				min = temp;
		}
	}
	return min;
}
void minimax(char board[Size][Size], char player)
{
	int i, j, max, max_i, max_j;
	max = -10;
	for (i = 0; i < Size; ++i)
	{
		for (j = 0; j < Size; ++j)
		{
			if (board[i][j] != ' ')
				continue;
			char new_board[Size][Size];
			int x, y;
			for (x = 0; x < Size; ++x)
			{
				for (y = 0; y < Size; ++y)
				{
					new_board[x][y] = board[x][y];
				}
			}
			new_board[i][j] = player;
			int temp = my_min(new_board, OTHER(player));
			
			if (temp > max)
			{
				max = temp;
				max_i = i;
				max_j = j;
			}
		}
	}
	if (enter_coord(board, player, max_i, max_j) == TRUE) {
		cout << " Error entering move " << endl; 
		exit(0);
	}
}
void print_board(char board[Size][Size])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "| " << setw(2) << (j + 1 + (Size * i)) << " ";
		}
		cout << "|\t\t";

		for (int j = 0; j < 3; j++) {
			cout << "| " << board[j][i] << " ";
		}
		cout << "|" << endl;
	}
}
