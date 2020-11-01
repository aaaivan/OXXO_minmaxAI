#include "Board.h"
#include "Token.h"
#include "Declarations.h"
#include <iostream>
#include <ctime>
#include <fstream>

int main() {
	//initialize random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//print rules of the game
	printTitleOfGame();
	Player player{};
	Player AI{};
	Board board = Board();
	int minimaxDepth = 3;
	askWinningMode(player, AI); //ask plyer if the want to allign colours or shapes
	bool userHasWon = false;
	bool aiHasWon = false;
	while (true) {
		board.print(player, AI);
		userHasWon = board.playerHasWon(player);
		aiHasWon = board.playerHasWon(AI);
		if (userHasWon) {
			std::cout << "YOU WON!\n**********************************************************************************" << std::endl;
			break;
		}
		else if (aiHasWon) {
			std::cout << "YOU LOST!\n**********************************************************************************" << std::endl;
			break;
		}
		std::cout << "Your turn.\n";
		//player move
		while (true) {
			int row = getPlayerInputRow();
			int col = getPlayerInputCol();
			if (board.getTokenAtPositon(row, col) == nullptr) {
				if (board.addToken(row, col, player, askFaceUp(player)))
					break;
				else
					std::cout << "No tokens left to place.\n";
			}
			else if (board.flipToken(row, col, player)) {
				break;
			}
			else {
				std::cout << "That is not your token.\n";
			}
		}
		board.print(player, AI);
		userHasWon = board.playerHasWon(player);
		aiHasWon = board.playerHasWon(AI);
		if (aiHasWon) {
			std::cout << "YOU LOST!\n**********************************************************************************"<<std::endl;
			break;
		}
		else if (userHasWon) {
			std::cout << "YOU WON!\n**********************************************************************************" << std::endl;
			break;
		}
		std::cout << "CPU's turn.\n";
		//AI's move
		makeMoveAI(player, AI, board, minimaxDepth);
	}
}