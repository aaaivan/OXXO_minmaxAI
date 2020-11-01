#include "Declarations.h"
#include "Board.h"
#include "Token.h"
#include <iostream>
#include <limits>

void askWinningMode(Player &player, Player &AI){
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
			player.winMode = WinMode::alignShapes;
			AI.winMode = WinMode::alignColours;
			player.playerType = Token::PlayerType::user;
			AI.playerType = Token::PlayerType::AI;
			std::cout << "Great! Your opponent will have to allign 4 colors then.\nYOU WILL USE THE WHITE TOKENS!\n" << std::endl;
			return;
		}
		else if (input == 'C') {
			AI.winMode = WinMode::alignShapes;
			player.winMode = WinMode::alignColours;
			player.playerType = Token::PlayerType::user;
			AI.playerType = Token::PlayerType::AI;
			std::cout << "Great! Your opponent will have to allign 4 shapes then.\nYOU WILL USE THE WHITE TOKENS!\n" << std::endl;
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

Token::Shape askFaceUp(Player &p) {
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

void makeMoveAI(Player &player, Player &AI, Board &b, int depth) {
	//the AI will be the minimizing agent
	int minEval = std::numeric_limits<int>::max();
	//for alpha-beta pruning
	int alpha= std::numeric_limits<int>::min();
	int beta= std::numeric_limits<int>::max();

	//these will store information on the next move with 
	//the lowest evaluation score
	std::pair<int, int> nextMovePos = {0,0};
	Token::Shape nextMoveFaceUp=Token::Shape::o;

	std::vector<std::pair<int, int>> allMoves;

	//loop through all the squares of the board
	int loopIterations = (Board::size) * (Board::size);
	for (unsigned int i = 0, j = 0; i * Board::size + j < loopIterations;) {
		int eval;
		if (b.flipToken(i, j, AI)) {//try to flip the token
			//evaluate new configuration
			eval = minimax(b, player, AI, depth - 1, alpha, beta, true);
			allMoves.push_back({ i,j });
			if (eval < minEval) {
				minEval = eval;
				nextMovePos = { i,j };
			}
			//restore initial configuuration
			b.flipToken(i, j, AI);
			beta = std::min(beta, eval);
			if (beta <= alpha)
				break;
		}
		else {
			if (b.addToken(i, j, AI, Token::Shape::o)) {//try to add an O
				//evaluate new configuration
				eval = minimax(b, player, AI, depth - 1, alpha, beta, true);
				allMoves.push_back({ i,j });
				if (eval < minEval) {
					minEval = eval;
					nextMovePos = { i,j };
					nextMoveFaceUp = b.board[i][j]->getShape();
				}
				//restore initial configuuration
				b.removeToken(i, j, AI);
				beta = std::min(beta, eval);
				if (beta <= alpha)
					break;
			}
			if (b.addToken(i, j, AI, Token::Shape::x)) {//try to add an X
				//evaluate new configuration
				eval = minimax(b, player, AI, depth - 1, alpha, beta, true);
				allMoves.push_back({ i,j });
				if (eval < minEval) {
					minEval = eval;
					nextMovePos = { i,j };
					nextMoveFaceUp = b.board[i][j]->getShape();
				}
				//restore initial configuuration
				b.removeToken(i, j, AI);
				beta = std::min(beta, eval);
				if (beta <= alpha)
					break;
			}
		}
		j++;
		if (j == Board::size) {
			i++;
			j = 0;
		}
	}

	//if all possible moves are evaluated to +infinity make a random move
	if (minEval == std::numeric_limits<int>::max()) {
		std::pair<int, int> randomMove = allMoves[std::rand() % allMoves.size()];
		if (b.flipToken(randomMove.first, randomMove.second, AI)) {
		}
		else
			b.addToken(randomMove.first, randomMove.second, AI, static_cast<Token::Shape>(2*(std::rand()%2)-1));
	}
	else {//make the move with the lowest evaluation
		if (b.flipToken(nextMovePos.first, nextMovePos.second, AI)) {
		}
		else
			b.addToken(nextMovePos.first, nextMovePos.second, AI, nextMoveFaceUp);
	}
}

int minimax(Board& b, Player& player, Player& AI, int depth, int alpha, int beta, bool maximazingAgent) {
	bool playerHasWon = b.playerHasWon(player);
	bool AIHasWon = b.playerHasWon(AI);
	if (playerHasWon && !AIHasWon) //player wins
		return std::numeric_limits<int>::max();
	else if (!playerHasWon && AIHasWon) //AI wins
		return std::numeric_limits<int>::min();
	else if (playerHasWon && AIHasWon)
		//both players have a winning line, so the winner depends on whose turn is it
		return maximazingAgent ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();

	if (depth == 0)
		return b.boardEvaluation(player, AI);

	if (maximazingAgent) {
		int maxEval = std::numeric_limits<int>::min();
		//loop through all the squares in the board
		int loopIterations = (Board::size) * (Board::size);
		for (unsigned int i = 0, j = 0; i * Board::size + j < loopIterations;) {
			int eval;
			if (b.flipToken(i, j, player)) {//try to flip the token
				//evaluate new configuration
				eval = minimax(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
				//restore initial configuuration
				b.flipToken(i, j, player);
				maxEval = std::max(maxEval, eval);
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
					break;
			}
			else {
				if (b.addToken(i, j, player, Token::Shape::o)) {//try to add an O
					//evaluate new configuration
					eval = minimax(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuration
					b.removeToken(i, j, player);
					maxEval = std::max(maxEval, eval);
					alpha = std::max(alpha, eval);
					if (beta <= alpha)
						break;
				}
				if (b.addToken(i, j, player, Token::Shape::x)) {//try to add an X
					//evaluate new configuration
					eval = minimax(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuuration
					b.removeToken(i, j, player);
					maxEval = std::max(maxEval, eval);
					alpha = std::max(alpha, eval);
					if (beta <= alpha)
						break;
				}
			}
			j++;
			if (j == Board::size)
			{
				i++;
				j = 0;
			}
		}
		return maxEval;
	}
	else {
		int minEval = std::numeric_limits<int>::max();
		int loopIterations = (Board::size) * (Board::size);
		for (unsigned int i = 0, j = 0; i * Board::size + j < loopIterations;) {
			int eval;
			if (b.flipToken(i, j, AI)) {//try to flip the token
				//evaluate new configuration
				eval = minimax(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
				//restore initial configuration
				minEval = std::min(minEval, eval);
				b.flipToken(i, j, AI);
				beta = std::min(beta, eval);
				if (beta <= alpha)
					break;
			}
			else {
				if (b.addToken(i, j, AI, Token::Shape::o)) {//try to add an O
					//evaluate new configuration
					eval = minimax(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuuration
					b.removeToken(i, j, AI);
					minEval = std::min(minEval, eval);
					beta = std::min(beta, eval);
					if (beta <= alpha)
						break;
				}
				if (b.addToken(i, j, AI, Token::Shape::x)) {//try to add an X
					//evaluate new configuration
					eval = minimax(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuuration
					minEval = std::min(minEval, eval);
					b.removeToken(i, j, AI);
					beta = std::min(beta, eval);
					if (beta <= alpha)
						break;
				}
			}
			j++;
			if (j == Board::size) {
				i++;
				j = 0;
			}
		}
		return minEval;
	}
}

void makeMoveRefAI(Player& player, Player& AI, Board& b, int depth) {
	//the reference AI will be the maximizing agent
	int maxEval = std::numeric_limits<int>::min();
	//for alpha-beta pruning
	int alpha = std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();

	//these will store information on the next move with 
	//the highest evaluation score
	std::pair<int, int> nextMove = { 0,0 };
	Token::Shape faceUp = Token::Shape::o;

	std::vector<std::pair<int, int>> allMoves;

	//loop through all the squares of the board
	int loopIterations = (Board::size) * (Board::size);
	for (unsigned int i = 0, j = 0; i * Board::size + j < loopIterations;) {
		int eval;
		if (b.flipToken(i, j, player)) {//try to flip the token
			//evaluate new configuration
			eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, false);
			allMoves.push_back({ i,j });
			if (eval > maxEval) {
				maxEval = eval;
				nextMove = { i,j };
			}
			//restore initial configuration
			b.flipToken(i, j, player);
			alpha = std::max(alpha, eval);
			if (beta <= alpha)
				break;
		}
		else {
			if (b.addToken(i, j, player, Token::Shape::o)) {//try to add an O
				//evaluate new configuration
				eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, false);
				allMoves.push_back({ i,j });
				if (eval > maxEval) {
					maxEval = eval;
					nextMove = { i,j };
					faceUp = b.board[i][j]->getShape();
				}
				//restore initial configuration
				b.removeToken(i, j, player);
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
					break;
			}
			if (b.addToken(i, j, player, Token::Shape::x)) {//try to add an X
				//evaluate new configuration
				eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, false);
				allMoves.push_back({ i,j });
				if (eval > maxEval) {
					maxEval = eval;
					nextMove = { i,j };
					faceUp = b.board[i][j]->getShape();
				}
				//restore initial configuration
				b.removeToken(i, j, player);
				alpha = std::max(alpha, eval);
				if (beta <= alpha)
					break;
			}
		}
		j++;
		if (j == Board::size) {
			i++;
			j = 0;
		}
	}
	//if all possible moves are evaluated to +infinity make a random move
	if (maxEval == std::numeric_limits<int>::min()) {
		std::pair<int, int> randomMove = allMoves[std::rand() % allMoves.size()];
		if (b.flipToken(randomMove.first, randomMove.second, player)) {
		}
		else
			b.addToken(randomMove.first, randomMove.second, player, static_cast<Token::Shape>(2 * (std::rand() % 2) - 1));
	}
	else {//make the move with the highest evaluation
		if (b.flipToken(nextMove.first, nextMove.second, player)) {
		}
		else
			b.addToken(nextMove.first, nextMove.second, player, faceUp);
	}
}

int minimaxReference(Board& b, Player& player, Player& AI, int depth, int alpha, int beta, bool maximazingAgent) {
	bool refHasWon = b.playerHasWon(player);
	bool AIHasWon = b.playerHasWon(AI);
	if (refHasWon && !AIHasWon) //reference AI wins
		return std::numeric_limits<int>::max();
	else if (!refHasWon && AIHasWon) //AI wins
		return std::numeric_limits<int>::min();
	else if (refHasWon && AIHasWon)
		//both players have a winning line, so the winner depends on whose turn is it
		return maximazingAgent ? std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
	
	if (depth == 0)
		return b.boardEvaluationControl(player, AI);

	if (maximazingAgent) {
		int maxEval = std::numeric_limits<int>::min();
		//loop through all the squares in the board
		int loopIterations = (Board::size) * (Board::size);
		for (unsigned int i = 0, j = 0; i * Board::size + j < loopIterations;) {
			int eval;
			if (b.flipToken(i, j, player)) {// try to flip the token
				//evaluate new configuration
				eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
				//restore initial configuration
				b.flipToken(i, j, player);
				maxEval = std::max(maxEval, eval);
				alpha = std::max(alpha, maxEval);
				if (beta <= alpha)
					break;
			}
			else {
				if (b.addToken(i, j, player, Token::Shape::o)) {//try to add an O
					//evaluate new configuration
					eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuration
					b.removeToken(i, j, player);
					maxEval = std::max(maxEval, eval);
					alpha = std::max(alpha, maxEval);
					if (beta <= alpha)
						break;
				}
				if (b.addToken(i, j, player, Token::Shape::x)) {
					//evaluate new configuration
					eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuration
					b.removeToken(i, j, player);
					maxEval = std::max(maxEval, eval);
					alpha = std::max(alpha, maxEval);
					if (beta <= alpha)
						break;
				}
			}
			j++;
			if (j == Board::size)
			{
				i++;
				j = 0;
			}
		}
		return maxEval;
	}
	else {
		int minEval = std::numeric_limits<int>::max();
		//loop through all the squares in the board
		int loopIterations = (Board::size) * (Board::size);
		for (unsigned int i = 0, j = 0; i * Board::size + j < loopIterations;) {
			int eval;
			if (b.flipToken(i, j, AI)) {//try to flip the token
				//evaluate new configuration
				eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
				//restore initial configuration
				minEval = std::min(minEval, eval);
				b.flipToken(i, j, AI);
				beta = std::min(beta, minEval);
				if (beta <= alpha)
					break;
			}
			else {
				if (b.addToken(i, j, AI, Token::Shape::o)) {//try to add an O
					//evaluate new configuration
					eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuration
					b.removeToken(i, j, AI);
					minEval = std::min(minEval, eval);
					beta = std::min(beta, minEval);
					if (beta <= alpha)
						break;
				}
				if (b.addToken(i, j, AI, Token::Shape::x)) {//try to add an X
					//evaluate new configuration
					eval = minimaxReference(b, player, AI, depth - 1, alpha, beta, !maximazingAgent);
					//restore initial configuration
					minEval = std::min(minEval, eval);
					b.removeToken(i, j, AI);
					beta = std::min(beta, minEval);
					if (beta <= alpha)
						break;
				}
			}
			j++;
			if (j == Board::size)
			{
				i++;
				j = 0;
			}
		}
		return minEval;
	}
}