#include "Declarations.h"
#include "Board.h"
#include <iostream>

void askWinningMode(PlayerData &player, PlayerData &AI){
	std::cout << "How do you want to win?" << std::endl;
	while (true)
	{
		std::cout << "allign 4 shapes(s) OR allign 4 colours(c): ";
		char input{};
		std::string tempStr{};
		std::cin >> tempStr;
		input = toupper(tempStr[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tempStr.length() != 1)
			std::cout << "Invalid input. Try again." << std::endl;
		else if (input == 'S') {
			player.winMode = WinMode::allignShapes;
			AI.winMode = WinMode::allignColours;
			player.playerType = Token::PlayerType::user;
			AI.playerType = Token::PlayerType::AI;
			std::cout << "Great! Your opponent will have to allign 4 colors, then.\nYOU WILL USE THE WHITE TOKENS!\n" << std::endl;
			return;
		}
		else if (input == 'C') {
			AI.winMode = WinMode::allignShapes;
			player.winMode = WinMode::allignColours;
			player.playerType = Token::PlayerType::user;
			AI.playerType = Token::PlayerType::AI;
			std::cout << "Great! Your opponent will have to allign 4 shapes, then.\nYOU WILL USE THE WHITE TOKENS!\n" << std::endl;
			return;
		}
		else
			std::cout << "Invalid input. Try again." << std::endl;
	}
}

int getPlayerInputRow()
{
	while (true)
	{
		int rowNum{};
		std::cout << "Enter the number for the row: ";
		std::cin >> rowNum;
		//input validation
		if (std::cin.fail())	//if the extraction fails, clear the buffer and print error message
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Try again." << std::endl;
		}
		else if (rowNum >= 1 && rowNum <= Board::size)	//if rowNum is in range
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
			return rowNum - 1;
		}
		else
		{
			std::cout << "Your input is out of range. Try again." << std::endl;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		}
	}

}

int getPlayerInputCol()
{
	while (true)
	{
		std::cout << "Enter the letter for the column: ";
		std::string input{};
		char columnLetter{};
		std::cin >> input;
		columnLetter = toupper(input[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove any residual input in the buffer
		if (input.length() != 1)
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
		else if (columnLetter >= 65 && columnLetter < 65 + Board::size)
		{
			return columnLetter - 65;
		}
		else if (columnLetter >= 65 + Board::size && columnLetter < 91)
		{
			std::cout << "Your input is out of range. Try again." << std::endl;
		}
		else
		{
			std::cout << "Invalid input. Try again." << std::endl;
		}
	}
}

void printTitleOfGame() {
	std::cout << ">";
	Token(Token::PlayerType::user, Token::Shape::o).print();
	std::cout << " ";
	Token(Token::PlayerType::user, Token::Shape::x).print();
	std::cout << " ";
	Token(Token::PlayerType::AI, Token::Shape::x).print();
	std::cout << " ";
	Token(Token::PlayerType::AI, Token::Shape::o).print();
	std::cout << "<";
	std::cout << "\nThe aim of the game is for one player to allign 4 Xs or 4 Os and for the other" <<
		"\nto allign 4 black or 4 red symbols. Line-ups along the two diagonals are also valid." <<
		"\nOn their turn, players can place a new token on an empty square or flip one of" <<
		"\nTHEIR tokens alredy on the board. Each player has 8 tokens in total. If you make a" <<
		"\nmove that causes both players to win, then you will automatically loose the game.\n"<< std::endl;
}

Token::Shape askFaceUp(PlayerData &p) {
	std::cout << "How so you want to win?" << std::endl;
	while (true)
	{
		std::cout << "Which face up? ";
		Token(p.playerType, Token::Shape::o).print();
		std::cout << "(o) or ";
		Token(p.playerType, Token::Shape::x).print();
		std::cout << "(x): ";
		char input{};
		std::string tempStr{};
		std::cin >> tempStr;
		input = toupper(tempStr[0]);
		//input validation
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (tempStr.length() != 1)
			std::cout << "Invalid input. Try again." << std::endl;
		else if (input == 'X') {
			return Token::Shape::x;
		}
		else if (input == 'O') {
			return Token::Shape::o;
		}
		else
			std::cout << "Invalid input. Try again." << std::endl;
	}

}