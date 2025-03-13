#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

struct Cord
{
	int x;
	int y;

	Cord()
	{
		x = 0;
		y = 0;
	}
	Cord(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Cord& right) const
	{
		return x == right.x && y == right.y;
	}

	bool operator!=(const Cord& right) const
	{
		return !(x == right.x && y == right.y);
	}

	Cord operator+=(const Cord& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Cord operator-=(const Cord& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}



};

struct MoveVect
{
	string start;
	string dest;

	MoveVect(string start, string dest)
	{
		this->start = start;
		this->dest = dest;
	}
};

struct Board_Index
{
	string id;
	Cord position;

	Board_Index()
	{
		id = "";
		position = Cord(-2, -2);
	}
	Board_Index(char letter, int num, Cord position)
	{
		this->id.push_back(letter);
		this->id += to_string(num);
		this->position = position;
	}
};

struct Board
{
	char** array;
	char current_player;
	int size;
	int kill_size;
	int white_pieces;
	int black_pieces;
	int white_reserve;
	int black_reserve;
	unordered_map<string, Cord> board_outer_indexes;
	unordered_map<string, Cord> board_inner_indexes;
	string game_state;

	Board& operator=(const Board& other)
	{
		int array_size = 2 * other.size - 1;

		this->array = new char* [array_size];
		for (int i = 0; i < array_size; ++i) {
			this->array[i] = new char[array_size];
		}

		for (int i = 0; i < array_size; i++)
		{
			for (int j = 0; j < array_size; j++)
			{
				this->array[i][j] = other.array[i][j];
			}
		}

		this->current_player = other.current_player;
		this->size = other.size;
		this->kill_size = other.kill_size;
		this->white_pieces = other.white_pieces;
		this->black_pieces = other.black_pieces;
		this->white_reserve = other.white_reserve;
		this->black_reserve = other.black_reserve;
		this->board_outer_indexes = other.board_outer_indexes;
		this->board_inner_indexes = other.board_inner_indexes;
		this->game_state = other.game_state;

		return *this;
	}
};

struct visitedCord
{
	Cord cord;
	int moveId;

	visitedCord(int x, int y, int k)
	{
		cord = Cord(x, y);
		moveId = k;
	}
};