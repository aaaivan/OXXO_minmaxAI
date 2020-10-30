#include "Board.h"
#include <cstdlib>
#include <iostream>

const int Board::size = 4;
std::vector<std::vector<Token*>> Board::board;
std::vector < std::vector<std::pair<int, int >>> Board::lines;


Board::Board() {
	board.clear();
	lines.clear();

	for (int i = 0; i < size; i++) {
		board.push_back(std::vector<Token*>());
		for (int j = 0; j < size; j++) {
			board[i].push_back(nullptr);
		}
	}

	for (int x1 = 0; x1 < size; x1++) {
		lines.push_back(std::vector<std::pair<int, int>>());
		lines.push_back(std::vector<std::pair<int, int>>());
		for (int x2 = 0; x2 < size; x2++) {
			lines[x1 * 2].push_back(std::pair<int, int>(x1, x2));
			lines[x1 * 2 + 1].push_back(std::pair<int, int>(x2, x1));
		}
	}
	lines.push_back(std::vector<std::pair<int, int>>());
	lines.push_back(std::vector<std::pair<int, int>>());
	for (int x = 0; x < size; x++) {
		lines[size * 2].push_back(std::pair<int, int>(x, x));
		lines[size * 2 + 1].push_back(std::pair<int, int>(x, size - 1 - x));
	}
}

bool Board::addToken(int x1, int x2, Player &player, Token::Shape faceUp) {
	if (board[x1][x2] != nullptr)
		return false;
	if (player.tokensLeft == 0)
		return false;
	player.tokensLeft--;
	board[x1][x2] = new Token(player.playerType, faceUp);
	return true;
}

void Board::removeToken(int x1, int x2, Player &player) {
	board[x1][x2] = nullptr;
	player.tokensLeft++;
}

bool Board::flipToken(int x1, int x2, const Player &player) {
	if (board[x1][x2] == nullptr)
		return false;
	else if (board[x1][x2]->getPlayerType() != player.playerType)
		return false;
	board[x1][x2]->flip();
	return true;
}

bool Board::playerHasWon(const Player& player) {
	int (*getAttribute)(Token*); //function pointer
	//if the player is aligning COLOURS, getAttribute will return the colour of the Token
	if (player.winMode == WinMode::allignColours) {
		getAttribute = [](Token* p)
		{
			return (static_cast<int>(p->getShapeColour()));
		};
	}
	//if the player is aligning SHAPES, getAttribute will return the shape of the Token
	else {
		getAttribute = [](Token* p)
		{
			return (static_cast<int>(p->getShape()));
		};
	}
	//loop through all the lines in the board:
	//4 rows + 4 cols + 2 diagonals.
	for (unsigned int i = 0; i < lines.size(); i++) {
		bool won = true;
		for (int lineCount = 0; lineCount < size - 1; lineCount++) {
			//if one of the squares in the line is empty, this line is not winning
			if (board[lines[i][lineCount].first][lines[i][lineCount].second] == nullptr ||
				board[lines[i][lineCount + 1].first][lines[i][lineCount + 1].second] == nullptr) {
				won = false;
				break;
			}
			//if two tokens on the same line have different attributes (either SHAPES or COLOURS
			//depending on which function getAttribute points to.), this line is not winning
			if (getAttribute(board[lines[i][lineCount].first][lines[i][lineCount].second]) !=
				getAttribute(board[lines[i][lineCount + 1].first][lines[i][lineCount + 1].second])) {
				won = false;
				break;
			}
		}
		if (won)
			return true;
	}
	return false;
}

int Board::boardEvaluation(const Player& player, const Player& AI) {
	int eval = 0;
	for (unsigned i = 0; i < lines.size(); i++) {
		int matchesScore=0;
		int colourUnbalance = 0;
		int shapeUnbalance = 0;
		int tokenDominionScore = 0;
		int tokenUnbalance = 0;
		for (int lineCount = 0; lineCount < size; lineCount++) {
			if (board[lines[i][lineCount].first][lines[i][lineCount].first] == nullptr)
				continue;
			colourUnbalance += static_cast<int>(board[lines[i][lineCount].first][lines[i][lineCount].first]->getShapeColour());
			shapeUnbalance += static_cast<int>(board[lines[i][lineCount].first][lines[i][lineCount].first]->getShape());
			tokenUnbalance += static_cast<int>(board[lines[i][lineCount].first][lines[i][lineCount].first]->getPlayerType());
		}
		matchesScore = colourUnbalance * colourUnbalance - shapeUnbalance * shapeUnbalance;
		if (player.winMode == WinMode::allignShapes)
			matchesScore *= -1;
		if (abs(tokenUnbalance) < 3 && tokenUnbalance!=0)
			tokenDominionScore = (tokenUnbalance / abs(tokenUnbalance)) * tokenUnbalance * tokenUnbalance;
		eval += matchesScore + tokenDominionScore + (player.tokensLeft - AI.tokensLeft)/2 + std::rand() % 8 - 4;
	}
	return eval;
}

int Board::boardEvaluationControl(const Player& user, const Player& AI) {
	return rand() % 32;
}

void Board::print(const Player &player, const Player &AI) {
		//PRINT LETTERS ON TOP
		std::cout << std::endl;
		std::cout << "   ";
		char ascii = 65;	//ascii code for 'A'
		for (int colCount = 0; colCount < size; colCount++)
		{
			std::cout << "  " << ascii << " ";
			ascii++;
		}
		std::cout << std::endl;
		//PRINT TOP EDGE OF THE BOARD
		std::cout << "   " << static_cast<char>(218);
		for (int count = 0; count < size - 1; count++)
		{
			std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(194);
		}
		std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(191) << std::endl;
		//PRINT TOP ROW OF THE BOARD
		std::cout << " " << 1 << " " << static_cast<char>(179);
		for (int count = 0; count < size; count++)
		{
			if (board[0][count] != nullptr)
				board[0][count]->print();
			else
				std::cout << "   ";
			std::cout<< static_cast<char>(179);
		}
		std::cout << std::endl;
		//PRINT ALL THE REMAINING ROWS
		for (int rowCount = 1; rowCount < size; rowCount++)
		{
			//solid line
			std::cout << "   " << static_cast<char>(195);
			for (int colCount = 0; colCount < size - 1; colCount++)
			{
				std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196);
				std::cout << static_cast<char>(197);
			}
			std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196);
			std::cout << static_cast<char>(180) << std::endl;
			//row
			printf("%2d", rowCount + 1);
			std::cout << " " << static_cast<char>(179);
			for (int colCount = 0; colCount < size; colCount++)
			{
				if (board[rowCount][colCount] != nullptr)
					board[rowCount][colCount]->print();
				else
					std::cout << "   ";

					std::cout << static_cast<char>(179);
			}
			std::cout << std::endl;
		}
		//PRINT THE BOTTOM EDGE
		std::cout << "   " << static_cast<char>(192);
		for (int count = 0; count < size - 1; count++)
		{
			std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(193);
		}
		std::cout << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(196) << static_cast<char>(217) << std::endl;

		//PRINT PAWNS YET TO PLAY
		std::cout << "You: ";
		for (int i = 0, s = -1; i < player.tokensLeft; i++) {
			s *=-1;
			std::cout << " ";
			Token(player.playerType, static_cast<Token::Shape>(s)).print();
			std::cout << " ";
		}
		std::cout << "(" << player.tokensLeft << ")" << std::endl;
		std::cout << "\nCPU: ";
		for (int i = 0, s = -1; i < AI.tokensLeft; i++) {
			s *= -1;
			std::cout << " ";
			Token(AI.playerType, static_cast<Token::Shape>(s)).print();
			std::cout << " ";
		}
		std::cout << "(" << AI.tokensLeft << ")\n"<<std::endl;

}

Token* Board::getTokenAtPositon(int x1, int x2) {
	return board[x1][x2];
}
