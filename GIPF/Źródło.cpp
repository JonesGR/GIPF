#include <SFML/Graphics.hpp>
#include "GameFunctions.h"
#define START_DRAWX 200.f
#define START_DRAWY 100.f

void DrawTEST()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GIPF");

	sf::RectangleShape button(sf::Vector2f(50, 50));  // rozmiar przycisku
	button.setFillColor(sf::Color::White);  // kolor przycisku
	button.setPosition({ 200, 100});  // pozycja przycisku w oknie

	bool isButtonPressed = false;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		window.draw(button);
		window.draw(button);
		window.display();
	}
}

void DrawBoard(Board& gipf_board)
{
	int size = gipf_board.size;
	int side = 3 * size - 2;

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "GIPF");

	float cube_size = 50;
	// Wektor przycisków
	std::vector<sf::RectangleShape> buttons;

	// Tworzenie 10 przycisków
	//for (int i = 0; i < 50; ++i) {
	//	sf::RectangleShape button(sf::Vector2f(cube_size, cube_size));
	//	button.setFillColor(sf::Color::White); // Kolor przycisku
	//	button.setPosition({ START_DRAWX + 60 * i, START_DRAWY }); 
	//	buttons.push_back(button); // Dodanie przycisku do wektora
	//}
	float x_pos = START_DRAWX, y_pos = START_DRAWY;

	int array_size = 2 * gipf_board.size - 1;
	int y = array_size - gipf_board.size, x = 0, next_Ydiag = 1, next_Xdiag = 0, space_offset = 1;
	bool space_minus = false;
	int gap = (cube_size + 10) / 2;

	int piece_num = 0;

	for (int i = 0; i < gipf_board.size; i++)
	{
		if (i == gipf_board.size - 1)
			piece_num = piece_num * 2;
		piece_num += gipf_board.size + i;
	}

	for (int i = 0; i < gipf_board.size - 1; i++)
		x_pos += gap;
		//cout << " ";

	for (int i = 0; i < piece_num; i++)
	{
		sf::RectangleShape button(sf::Vector2f(cube_size, cube_size));
		if (gipf_board.array[y][x] == 'B')
			button.setFillColor(sf::Color::Blue);
		else if (gipf_board.array[y][x] == 'W')
			button.setFillColor(sf::Color::Red);
		else
			button.setFillColor(sf::Color::White);
		
		button.setPosition({ x_pos, y_pos });
		x_pos += cube_size+10;
		buttons.push_back(button); 
		//cout << gipf_board.array[y][x] << " ";
		y--;
		x++;

		if (y < 0 || x == array_size)
		{
			y_pos += cube_size + 10;
			x_pos = START_DRAWX;
			//cout << endl;
			for (int j = 0; j < gipf_board.size - 1 - space_offset; j++)
			{
				x_pos += gap;
				//cout << " ";
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

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear();
		for (const auto& button : buttons) {
			window.draw(button);
		}
		window.display();
	}

}

void ReadCommand(Board& gipf_board)
{
	string command;
	bool exit = false;

	while (!exit)
	{
		getline(cin, command);
			
		if (command == "PRINT_GAME_BOARD")
		{
			PrintGameBoard(gipf_board);
			DrawBoard(gipf_board);
		}	
		else if (command == "PRINT_GAME_STATE")
			PrintGameState(gipf_board);
		else if (command == "IS_GAME_OVER")
			IsGameOver(gipf_board);
		else if (command == "LOAD_GAME_BOARD")
			LoadGameBoard(gipf_board);
		else if (command == "GEN_ALL_POS_MOV")
			GenerateAllPositionMoves(gipf_board);
		else if (command == "GEN_ALL_POS_MOV_EXT")
			GenerateAllPositionMovesEXT(gipf_board);
		else if (command == "GEN_ALL_POS_MOV_NUM")
			GenerateAllPositionMovesNUM(gipf_board);
		else if (command == "GEN_ALL_POS_MOV_EXT_NUM")
			GenerateAllPositionMovesEXT_NUM(gipf_board);
		else if (command == "WINNING_SEQUENCE_EXIST <N>")
			WinningSequenceExist();
		else if (command == "SOLVE_GAME_STATE")
			SolveGameState();
		else if (command.substr(0, 8) == "DO_MOVE ")
		{
			string xN = command.substr(8, 2);
			string yM = command.substr(11, 2);
			
			if (!DoMove(gipf_board, xN, yM, true))
				continue;
			if (command.size() > 13)
			{
				char player = command[14];
				string rowStart = command.substr(17, 2);
				string rowEnd = command.substr(20, 2);
				if (!CaptureChosenRow(gipf_board, player, rowStart, rowEnd))
					continue;
			}
			CapturePieces(gipf_board, 0);
			cout << "MOVE_COMMITTED" << endl;
		}

		if (cin.eof()) {
			exit = true;
			break;
		}
	}
	
}

int main()
{
	
	Board gipf_board;
	ReadCommand(gipf_board);

	//delete gipf_board;
}