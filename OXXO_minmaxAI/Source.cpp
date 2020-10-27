#include "Board.h"
#include "Pawn.h"
#include "Declarations.h"
#include <iostream>
#include <ctime>

int main() {
	//initialize random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	//print rules of the game
	printTitleOfGame();
	PlayerData player{};
	PlayerData AI{};
	Board b = Board();
	askWinningMode(player, AI);
	bool userWins = false;
	bool aiWins = false;
	while (true) {
		b.print(player, AI);
		userWins = b.playerHasWon(player);
		aiWins = b.playerHasWon(AI);
		if (userWins && !aiWins) {
			std::cout << "YOU WON!";
			break;
		}
		else if (aiWins) {
			std::cout << "YOU LOST!";
			break;
		}
		std::cout << "P1's turn.\n";
		while (true) {
			int row = getPlayerInputRow();
			int col = getPlayerInputCol();
			if (b.getPawnAtPositon(row, col) == nullptr) {
				b.addPawn(row, col, player, askFaceUp(player));
				break;
			}
			else if (b.flipPawn(row, col, player)) {
				break;
			}
			else {
				std::cout << "Invalid input.\n";
			}
		}
		b.print(player, AI);
		userWins = b.playerHasWon(player);
		aiWins = b.playerHasWon(AI);
		if (userWins && !aiWins) {
			std::cout << "YOU WON!";
			break;
		}
		else if (aiWins) {
			std::cout << "YOU LOST!";
			break;
		}
		std::cout << "P2's turn.\n";
		while (true) {
			int row = getPlayerInputRow();
			int col = getPlayerInputCol();
			if (b.getPawnAtPositon(row, col) == nullptr) {
				b.addPawn(row, col, AI, askFaceUp(AI));
				break;
			}
			else if (b.flipPawn(row, col, AI)) {
				break;
			}
			else {
				std::cout << "Invalid input.\n";
			}
		}
	}
}