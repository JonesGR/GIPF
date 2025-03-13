#include "Struct.cpp"

using namespace std;

void GenerateOuterIndexes(Board& gipf_board)
{
	char letter = 'a';
	Cord pos(-1, 2 * gipf_board.size - 1);
	string gid;
	gid.push_back(letter);
	gid += to_string(1);
	gipf_board.board_outer_indexes.insert(make_pair(gid, pos));
	letter++;

	for (int i = 0; i < gipf_board.size; i++)
	{
		Cord pos2(0 + i, 2 * gipf_board.size - 1);
		string id;
		id.push_back(letter);
		id += to_string(1);
		gipf_board.board_outer_indexes.insert(make_pair(id, pos2));
		letter++;
	}
	for (int i = 0; i < gipf_board.size; i++)
	{
		Cord pos2(gipf_board.size + i, 2 * gipf_board.size - 2 - i);
		string id;
		id.push_back(letter);
		id += to_string(1);
		gipf_board.board_outer_indexes.insert(make_pair(id, pos2));
		letter++;

	}

	letter--;
	for (int i = 0; i < gipf_board.size; i++)
	{
		Cord pos2(2 * gipf_board.size - 1, gipf_board.size - 2 - i);
		string id;
		id.push_back(letter);
		id += to_string(2 + i);
		gipf_board.board_outer_indexes.insert(make_pair(id, pos2));

	}

	letter--;
	for (int i = 0; i < gipf_board.size; i++)
	{
		Cord pos2(2 * gipf_board.size - 2 - i, -1);
		string id;
		id.push_back(letter);
		id += to_string(gipf_board.size + 2 + i);
		gipf_board.board_outer_indexes.insert(make_pair(id, pos2));

		letter--;
		//done
	}

	for (int i = 0; i < gipf_board.size; i++)
	{
		Cord pos2(gipf_board.size - 2 - i, 0 + i);
		string id;
		id.push_back(letter);
		id += to_string(2 * gipf_board.size - i);
		gipf_board.board_outer_indexes.insert(make_pair(id, pos2));

		letter--;
	}

	for (int i = 0; i < gipf_board.size - 1; i++)
	{
		Cord pos2(-1, gipf_board.size + i);
		string id;
		id.push_back('a');
		id += to_string(gipf_board.size - i);
		gipf_board.board_outer_indexes.insert(make_pair(id, pos2));

	}
}

void GenerateInnerIndexes(Board& gipf_board)
{

	char letter = 'b';
	int xCh = -1;
	int yCh = 0;
	for (int i = 0; i < 2 * gipf_board.size - 1; i++)
	{
		if (i <= gipf_board.size - 1)
			xCh++;
		else
		{
			xCh--;
			yCh++;
		}

		for (int j = 0; j < gipf_board.size + xCh; j++)
		{
			Cord pos(0 + i, 2 * gipf_board.size - 2 - j - yCh);
			string id;
			id.push_back(letter);
			id += to_string(2 + j);
			gipf_board.board_inner_indexes.insert(make_pair(id, pos));
		}
		letter++;
	}

}

void GenerateIndexes(Board& gipf_board)
{
	GenerateOuterIndexes(gipf_board);
	GenerateInnerIndexes(gipf_board);

}

bool CheckForRows(Board& gipf_board)
{
	int found_rows = 0;
	int kill_size = gipf_board.kill_size;
	int array_size = 2 * gipf_board.size - 1;
	Cord allowedMoves[3] = { Cord(1,0),Cord(0,1),Cord(-1,1) };
	vector<visitedCord> toskip;

	for (int i = 0; i < array_size; i++)
	{
		for (int j = 0; j < array_size; j++)
		{
			bool skip = false;
			char playerPiece = gipf_board.array[i][j];
			if (playerPiece == 'W' || playerPiece == 'B')
			{
				for (int k = 0; k < 3; k++)
				{
					vector<visitedCord> buffer;
					for (visitedCord cordskip : toskip)
					{
						if (i == cordskip.cord.y && j == cordskip.cord.x && cordskip.moveId == k)
						{
							skip = true;
							break;
						}
					}
					if (skip)
					{
						skip = false;
						break;
					}
					for (int l = 1; l < kill_size; l++)
					{
						int x_change = j + l * allowedMoves[k].x;
						int y_change = i + l * allowedMoves[k].y;
						if (x_change < 0 || x_change >= array_size || y_change < 0 || y_change >= array_size)
							break;
						if (gipf_board.array[y_change][x_change] != playerPiece)
							break;
						buffer.push_back(visitedCord(x_change, y_change, k));
						if (l == kill_size - 1)
						{
							found_rows++;
							copy(buffer.begin(), buffer.end(), back_inserter(toskip));
						}
					}
				}
			}
		}
	}

	//found_rows /= kill_size;

	if (found_rows == 1)
	{
		cout << "ERROR_FOUND_1_ROW_OF_LENGTH_K" << endl;
		return false;
	}

	else if (found_rows > 1)
	{
		cout << "ERROR_FOUND_" + to_string(found_rows) + "_ROWS_OF_LENGTH_K" << endl;
		return false;
	}
	return true;
}

void SetGameState(Board& gipf_board)
{
	if (!gipf_board.white_reserve)
		gipf_board.game_state = "black_win";
	else if (!gipf_board.black_reserve)
		gipf_board.game_state = "white_win";
	else
		gipf_board.game_state = "in_progress";
}

void PrintGameBoard(Board& gipf_board)
{
	if (gipf_board.size == -1)
	{
		cout << "EMPTY_BOARD" << endl;
		return;
	}
	cout << gipf_board.size << " " << gipf_board.kill_size << " " << gipf_board.white_pieces
		<< " " << gipf_board.black_pieces << endl << gipf_board.white_reserve << " " <<
		gipf_board.black_reserve << " " << gipf_board.current_player << endl;

	int array_size = 2 * gipf_board.size - 1;
	int y = array_size - gipf_board.size, x = 0, next_Ydiag = 1, next_Xdiag = 0, space_offset = 1;
	bool space_minus = false;

	int piece_num = 0;

	for (int i = 0; i < gipf_board.size; i++)
	{
		if (i == gipf_board.size - 1)
			piece_num = piece_num * 2;
		piece_num += gipf_board.size + i;
	}

	for (int i = 0; i < gipf_board.size - 1; i++)
		cout << " ";

	for (int i = 0; i < piece_num; i++)
	{
		cout << gipf_board.array[y][x] << " ";
		y--;
		x++;

		if (y < 0 || x == array_size)
		{
			cout << endl;
			for (int j = 0; j < gipf_board.size - 1 - space_offset; j++)
			{
				cout << " ";
			}
			if (gipf_board.size - 1 - space_offset == 0)
				space_minus = true;

			if (!space_minus)
				space_offset++;
			else
				space_offset--;

			y = array_size - gipf_board.size + next_Ydiag;
			if (y != array_size - 1)
				next_Ydiag++;
			x = 0 + next_Xdiag;
			if (y == array_size - 1)
				next_Xdiag++;
		}
	}
	cout << endl;
}

bool LoadGameBoard(Board& gipf_board)
{
	Board new_board;
	cin >> new_board.size >> new_board.kill_size >> new_board.white_pieces
		>> new_board.black_pieces >> new_board.white_reserve >>
		new_board.black_reserve >> new_board.current_player;

	SetGameState(new_board);


	int array_size = 2 * new_board.size - 1;

	cin.ignore();

	new_board.array = new char* [array_size];
	for (int i = 0; i < array_size; ++i) {
		new_board.array[i] = new char[array_size];
	}

	int y = array_size - new_board.size, x = 0, next_Ydiag = 1, next_Xdiag = 0;

	int piece_num = 0;
	for (int i = 0; i < new_board.size; i++)
	{
		if (i == new_board.size - 1)
			piece_num = piece_num * 2;
		piece_num += new_board.size + i;
	}

	int counted_blacks = 0, counted_whites = 0;

	/*for (int i = 0; i < piece_num; i++)
	{
		char piece;
		cin >> piece;
		if (piece == 'W')
			counted_whites++;
		if (piece == 'B')
			counted_blacks++;

		new_board.array[y][x] = piece;
		y--;
		x++;


		if (y < 0 || x==array_size)
		{
			y = array_size - new_board.size + next_Ydiag;
			if(y!=array_size-1)
				next_Ydiag++;
			x = 0 + next_Xdiag;
			if (y == array_size - 1)
				next_Xdiag++;
		}
	}*/
	int line_size = new_board.size, line_size_change = 0;
	bool wrong_num = false;

	for (int i = 0; i < array_size; i++)
	{
		vector<char> characters;
		string line;
		getline(cin, line);

		for (char c : line)
		{
			if (c != ' ')
				characters.push_back(c);
			if (c == 'W')
				counted_whites++;
			if (c == 'B')
				counted_blacks++;
		}

		if (characters.size() != line_size + line_size_change)
			wrong_num = true;

		if (i < new_board.size - 1)
			line_size_change++;
		else
			line_size_change--;


		for (char c : characters)
		{
			new_board.array[y][x] = c;
			y--;
			x++;

			if (y < 0 || x == array_size)
			{
				y = array_size - new_board.size + next_Ydiag;
				if (y != array_size - 1)
					next_Ydiag++;
				x = 0 + next_Xdiag;
				if (y == array_size - 1)
					next_Xdiag++;
			}
		}
	}

	/*if (cin.peek()!='\n')
	{
		cout << "WRONG_BOARD_ROW_LENGTH" << endl;
		delete[] new_board.array;
		return false;
	}*/

	if (wrong_num)
	{
		cout << "WRONG_BOARD_ROW_LENGTH" << endl;
		delete[] new_board.array;
		gipf_board.size = -1;
		return false;
	}


	if (new_board.white_pieces < counted_whites + new_board.white_reserve)//powinno byc != ale stos trolluje
	{
		cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
		delete[] new_board.array;
		gipf_board.size = -1;
		return false;
	}
	else if (new_board.black_pieces < counted_blacks + new_board.black_reserve)//powinno byc != ale stos trolluje
	{
		cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
		delete[] new_board.array;
		gipf_board.size = -1;
		return false;
	}

	/*for (int i = 0; i < array_size; i++)
	{
		for (int j = 0; j < array_size; j++)
		{
			if (new_board.array[i][j] >= 'A' && new_board.array[i][j] <= 'z')
				cout << new_board.array[i][j];
			else
				cout << " ";
		}
		cout << endl;
	}*/

	if (!CheckForRows(new_board))
		return false;

	cout << "BOARD_STATE_OK" << endl;
	gipf_board = new_board;




	GenerateIndexes(gipf_board);

	return true;

}

bool IsDeadLocked(Board& gipf_board)
{
	int array_size = 2 * gipf_board.size - 1;
	int y = array_size - gipf_board.size, x = 0, next_Ydiag = 1, next_Xdiag = 0, space_offset = 1;
	bool space_minus = false;
	int piece_num = 0;

	for (int i = 0; i < gipf_board.size; i++)
	{
		if (i == gipf_board.size - 1)
			piece_num = piece_num * 2;
		piece_num += gipf_board.size + i;
	}

	for (int i = 0; i < piece_num; i++)
	{
		if (gipf_board.array[y][x] == '_')
			return false;
		y--;
		x++;

		if (y < 0 || x == array_size)
		{
			for (int j = 0; j < gipf_board.size - 1 - space_offset; j++)
			{
			}
			if (gipf_board.size - 1 - space_offset == 0)
				space_minus = true;

			if (!space_minus)
				space_offset++;
			else
				space_offset--;

			y = array_size - gipf_board.size + next_Ydiag;
			if (y != array_size - 1)
				next_Ydiag++;
			x = 0 + next_Xdiag;
			if (y == array_size - 1)
				next_Xdiag++;
		}
	}
	return true;
}

void PrintGameState(Board& gipf_board)
{
	if (IsDeadLocked(gipf_board))
	{
		gipf_board.game_state = "dead lock ";
		gipf_board.game_state.append(1, gipf_board.current_player);

	}

	cout << gipf_board.game_state << endl;
}

void IsGameOver(Board& gipf_board)
{
	if (IsDeadLocked(gipf_board))
	{
		if (gipf_board.current_player == 'W')
			cout << "THE_WINNER_IS_BLACK" << endl;
		else
			cout << "THE_WINNER_IS_WHITE" << endl;
		return;
	}

	if (gipf_board.game_state == "in_progress")
		cout << "GAME_IN_PROGRESS" << endl;
	else if (gipf_board.game_state == "white_win")
		cout << "THE_WINNER_IS_WHITE" << endl;
	else if (gipf_board.game_state == "black_win")
		cout << "THE_WINNER_IS_BLACK" << endl;
}

void DeleteRow(Board& gipf_board, int start_x, int start_y, Cord move, char toSave)
{
	int array_size = 2 * gipf_board.size - 1;
	int x = start_x;
	int y = start_y;

	while (x + move.x < array_size && y + move.y < array_size &&
		x + move.x >= 0 && y + move.y >= 0 && gipf_board.array[y + move.y][x + move.x] != '_')
	{
		x += move.x;
		y += move.y;
	}

	move.x *= -1;
	move.y *= -1;

	while (x < array_size && y < array_size &&
		x >= 0 && y >= 0 && gipf_board.array[y][x] != '_')
	{
		if (gipf_board.array[y][x] == 'W' && toSave == 'W')
			gipf_board.white_reserve++;
		else if (gipf_board.array[y][x] == 'B' && toSave == 'B')
			gipf_board.black_reserve++;
		gipf_board.array[y][x] = '_';
		x += move.x;
		y += move.y;
	}
}

bool CaptureChosenRow(Board& gipf_board, char player, const string start, const string end)
{
	char player_piece = toupper(player);
	Cord from;
	Cord to;

	/*for (Board_Index index : gipf_board.board_inner_indexes)
	{
		if (index.id == start)
		{
			fromIndex = index;
			break;
		}
	}*/

	if (gipf_board.board_inner_indexes.count(start))
		from = gipf_board.board_inner_indexes.at(start);
	else
	{
		cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
		return false;
	}

	if (gipf_board.board_inner_indexes.count(end))
		to = gipf_board.board_inner_indexes.at(end);
	else
	{
		cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
		return false;
	}



	Cord move(to.x - from.x, to.y - from.y);
	int divider = (abs(move.x) > abs(move.y)) ? abs(move.x) : abs(move.y);
	if (abs(divider) != gipf_board.kill_size - 1)
	{
		cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
		return false;
	}
	move.x /= divider;
	move.y /= divider;

	int x = from.x;
	int y = from.y;

	if (gipf_board.array[y][x] == player_piece)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int l = 1; l < gipf_board.kill_size; l++)
			{
				int x_change = x + l * move.x;
				int y_change = y + l * move.y;
				if (x_change < 0 || x_change >= 2 * gipf_board.size - 1 || y_change < 0 || y_change >= 2 * gipf_board.size - 1)
					break;
				if (gipf_board.array[y_change][x_change] != player_piece)
					break;
				if (l == gipf_board.kill_size - 1)
				{
					DeleteRow(gipf_board, x_change, y_change, move, player_piece);
					return true;
				}
			}
		}
	}
	else
	{
		cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
		return false;
	}

	return true;
}

int CountRows(Board& gipf_board)
{
	int count = 0;
	int kill_size = gipf_board.kill_size;
	int array_size = 2 * gipf_board.size - 1;
	Cord allowedMoves[3] = { Cord(1,0),Cord(0,1),Cord(-1,1) };
	for (int i = 0; i < array_size; i++)
	{
		for (int j = 0; j < array_size; j++)
		{
			char playerPiece = gipf_board.array[i][j];
			if (playerPiece == 'W' || playerPiece == 'B')
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 1; l < kill_size; l++)
					{
						int x_change = j + l * allowedMoves[k].x;
						int y_change = i + l * allowedMoves[k].y;
						if (x_change < 0 || x_change >= array_size || y_change < 0 || y_change >= array_size)
							break;
						if (gipf_board.array[y_change][x_change] != playerPiece)
							break;
						if (l == kill_size - 1)
						{
							count++;
						}
					}
				}
			}
		}
	}
	return count;
}

void CapturePieces(Board& gipf_board, int skipRow)
{
	int kill_size = gipf_board.kill_size;
	int array_size = 2 * gipf_board.size - 1;
	Cord allowedMoves[3] = { Cord(1,0),Cord(0,1),Cord(-1,1) };
	for (int i = 0; i < array_size; i++)
	{
		for (int j = 0; j < array_size; j++)
		{
			char playerPiece = gipf_board.array[i][j];
			if (playerPiece == 'W' || playerPiece == 'B')
			{
				for (int k = 0; k < 3; k++)
				{
					for (int l = 1; l < kill_size; l++)
					{
						int x_change = j + l * allowedMoves[k].x;
						int y_change = i + l * allowedMoves[k].y;
						if (x_change < 0 || x_change >= array_size || y_change < 0 || y_change >= array_size)
							break;
						if (gipf_board.array[y_change][x_change] != playerPiece)
							break;
						if (l == kill_size - 1)
						{
							if (skipRow > 0)
							{
								skipRow--;
								break;

							}
							DeleteRow(gipf_board, x_change, y_change, allowedMoves[k], playerPiece);
						}
					}
				}
			}
		}
	}
	SetGameState(gipf_board);
}

bool DoMove(Board& gipf_board, const string start, const string end, bool logs)
{
	Cord from;
	Cord to;

	if (gipf_board.board_outer_indexes.count(start))
		from = gipf_board.board_outer_indexes.at(start);
	else if (gipf_board.board_inner_indexes.count(start))
	{
		if (logs)
			cout << "BAD_MOVE_" + start + "_IS_WRONG_STARTING_FIELD" << endl;
		gipf_board.game_state = "bad_move ";
		gipf_board.game_state.append(1, gipf_board.current_player);
		gipf_board.game_state += " " + start + "-" + end;
		return false;
	}
	else
	{
		if (logs)
			cout << "BAD_MOVE_" + start + "_IS_WRONG_INDEX" << endl;
		gipf_board.game_state = "bad_move ";
		gipf_board.game_state.append(1, gipf_board.current_player);
		gipf_board.game_state += " " + start + "-" + end;
		return false;
	}

	if (gipf_board.board_inner_indexes.count(end))
		to = gipf_board.board_inner_indexes.at(end);
	else if (gipf_board.board_outer_indexes.count(end))
	{
		if (logs)
			cout << "BAD_MOVE_" + end + "_IS_WRONG_DESTINATION_FIELD" << endl;
		gipf_board.game_state = "bad_move ";
		gipf_board.game_state.append(1, gipf_board.current_player);
		gipf_board.game_state += " " + start + "-" + end;
		return false;
	}
	else
	{
		if (logs)
			cout << "BAD_MOVE_" + end + "_IS_WRONG_INDEX" << endl;
		gipf_board.game_state = "bad_move ";
		gipf_board.game_state.append(1, gipf_board.current_player);
		gipf_board.game_state += " " + start + "-" + end;
		return false;
	}

	Cord allowedMoves[6] = { Cord(1,0),Cord(-1,0),Cord(0,1),Cord(0,-1),Cord(-1,1),Cord(1,-1) };
	Cord move(to.x - from.x, to.y - from.y);
	for (int i = 0; i < 6; i++)
	{
		if (move == allowedMoves[i])
			break;
		if (i == 5)
		{
			if (logs)
				cout << "UNKNOWN_MOVE_DIRECTION" << endl;
			gipf_board.game_state = "bad_move ";
			gipf_board.game_state.append(1, gipf_board.current_player);
			gipf_board.game_state += " " + start + "-" + end;
			return false;
		}
	}
	Cord lastFree(to.x, to.y);
	Cord put = lastFree;
	char player_piece = gipf_board.current_player;
	stack<Cord> lineStack;
	int array_size = 2 * gipf_board.size - 1;

	while (lastFree.x >= 0 && lastFree.x < array_size && lastFree.y >= 0 && lastFree.y < array_size
		&& gipf_board.array[lastFree.y][lastFree.x] != '_')
	{
		lineStack.push(lastFree);
		lastFree += move;
	}

	if (lastFree.x < 0 || lastFree.x >= array_size || lastFree.y < 0 || lastFree.y >= array_size)
	{
		if (logs)
			cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		gipf_board.game_state = "bad_move ";
		gipf_board.game_state.append(1, gipf_board.current_player);
		gipf_board.game_state += " " + start + "-" + end;
		return false;
	}

	while (lastFree != put)
	{
		gipf_board.array[lastFree.y][lastFree.x] = gipf_board.array[lineStack.top().y][lineStack.top().x];
		lineStack.pop();
		lastFree -= move;
	}

	gipf_board.array[put.y][put.x] = player_piece;
	if (gipf_board.current_player == 'W')
	{
		gipf_board.white_reserve--;
		gipf_board.current_player = 'B';
	}
	else
	{
		gipf_board.black_reserve--;
		gipf_board.current_player = 'W';
	}
	return true;
}

void GenerateAllPossibleMoves(Board& gipf_board, vector<MoveVect>& possibleMoves)
{
	char startchar = 'a', endchar = 'b';
	int startint = 1, endint = 2;

	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 2 * gipf_board.size - 1; i++)
		{
			string start = string(1, startchar) + to_string(startint);
			string end = string(1, endchar) + to_string(endint);
			possibleMoves.push_back(MoveVect(start, end));
			if (!i)
				startchar++;
			if (i % 2)
				endchar++;
			if (!(i % 2) && i)
				startchar++;
		}

	for (int i = 0; i < 2 * gipf_board.size - 1; i++)
	{
		string start = string(1, startchar) + to_string(startint);
		string end = string(1, endchar) + to_string(endint);
		possibleMoves.push_back(MoveVect(start, end));
		if (!i)
			startint++;
		if (i % 2)
		{
			endint++;
		}
		if (!(i % 2) && i)
			startint++;
	}

	for (int i = 0; i < 2 * gipf_board.size - 1; i++)
	{
		string start = string(1, startchar) + to_string(startint);
		string end = string(1, endchar) + to_string(endint);
		possibleMoves.push_back(MoveVect(start, end));
		if (!i)
		{
			startchar--;
			startint++;
		}
		if (i % 2)
		{
			endint++;
			endchar--;
		}
		if (!(i % 2) && i)
		{
			startint++;
			startchar--;
		}
	}

	for (int i = 0; i < 2 * gipf_board.size - 1; i++)
	{
		string start = string(1, startchar) + to_string(startint);
		string end = string(1, endchar) + to_string(endint);
		possibleMoves.push_back(MoveVect(start, end));
		if (!i)
		{
			startchar--;
			startint--;
		}
		if (i % 2)
		{
			endint--;
			endchar--;
		}
		if (!(i % 2) && i)
		{
			startint--;
			startchar--;
		}
	}

	for (int i = 0; i < 2 * gipf_board.size - 1; i++)
	{
		string start = string(1, startchar) + to_string(startint);
		string end = string(1, endchar) + to_string(endint);
		possibleMoves.push_back(MoveVect(start, end));
		if (!i)
		{
			startint--;
		}
		if (i % 2)
		{
			endint--;
		}
		if (!(i % 2) && i)
		{
			startint--;
		}
	}
}

void GenerateAllMovesBase(Board& gipf_board, vector<Board>& possibleBoards, bool isEXT)
{
	vector<MoveVect> possibleMoves;

	GenerateAllPossibleMoves(gipf_board, possibleMoves);

	for (MoveVect mov : possibleMoves)
	{
		Board board;
		board = gipf_board;
		if (DoMove(board, mov.start, mov.dest, false))
		{
			for (int k = 0; k < CountRows(board) + 1; k++)
			{
				Board boardCopy;
				boardCopy = board;
				CapturePieces(boardCopy, k);
				if (k != 0)
					CapturePieces(boardCopy, 0);
				bool skip = false;

				for (Board board2 : possibleBoards)
				{
					skip = true;
					for (int i = 0; i < 2 * boardCopy.size - 1; i++)
					{
						for (int j = 0; j < 2 * boardCopy.size - 1; j++)
							if (boardCopy.array[i][j] != board2.array[i][j])
							{
								skip = false;
								break;
							}
						if (!skip)
							break;
					}
					if (skip)
						break;
				}
				if (!skip)
				{
					possibleBoards.push_back(boardCopy);
					if (isEXT && (!boardCopy.black_reserve || !boardCopy.white_reserve))
					{
						possibleBoards.clear();
						possibleBoards.push_back(boardCopy);
						return;
					}
				}

			}
		}
	}
}

void GenerateAllPositionMoves(Board& gipf_board)
{
	vector<Board> possibleBoards;
	GenerateAllMovesBase(gipf_board, possibleBoards, false);

	for (Board board : possibleBoards)
	{
		PrintGameBoard(board);
	}
}

void GenerateAllPositionMovesEXT(Board& gipf_board)
{
	vector<Board> possibleBoards;
	GenerateAllMovesBase(gipf_board, possibleBoards, true);

	for (Board board : possibleBoards)
	{
		PrintGameBoard(board);
	}
}

void GenerateAllPositionMovesNUM(Board& gipf_board)
{
	vector<Board> possibleBoards;
	GenerateAllMovesBase(gipf_board, possibleBoards, false);

	cout << possibleBoards.size() << "_UNIQUE_MOVES" << endl;
}

void GenerateAllPositionMovesEXT_NUM(Board& gipf_board)
{
	vector<Board> possibleBoards;
	GenerateAllMovesBase(gipf_board, possibleBoards, true);

	cout << possibleBoards.size() << "_UNIQUE_MOVES" << endl;
}

void WinningSequenceExist()
{

}

void SolveGameState()
{

}