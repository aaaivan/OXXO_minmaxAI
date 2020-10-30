#include "Board.h"
#include "Token.h"
#include "Declarations.h"
#include <iostream>
#include <ctime>

//int main() {
//	//initialize random seed
//	std::srand(static_cast<unsigned int>(std::time(nullptr)));
//
//	//print rules of the game
//	printTitleOfGame();
//	Player player{};
//	Player AI{};
//	Board b = Board();
//	askWinningMode(player, AI);
//	bool userWins = false;
//	bool aiWins = false;
//	while (true) {
//		b.print(player, AI);
//		userWins = b.playerHasWon(player);
//		aiWins = b.playerHasWon(AI);
//		if (userWins) {
//			std::cout << "YOU WON!\n**********************************************************************************" << std::endl;
//			break;
//		}
//		else if (aiWins) {
//			std::cout << "YOU LOST!\n**********************************************************************************" << std::endl;
//			break;
//		}
//		std::cout << "Your turn.\n";
//		while (true) {
//			int row = getPlayerInputRow();
//			int col = getPlayerInputCol();
//			if (b.getTokenAtPositon(row, col) == nullptr) {
//				if (b.addToken(row, col, player, askFaceUp(player)))
//					break;
//				else
//					std::cout << "No tokens left to place.\n";
//			}
//			else if (b.flipToken(row, col, player)) {
//				break;
//			}
//			else {
//				std::cout << "That is not your token.\n";
//			}
//		}
//		b.print(player, AI);
//		userWins = b.playerHasWon(player);
//		aiWins = b.playerHasWon(AI);
//		if (aiWins) {
//			std::cout << "YOU LOST!\n**********************************************************************************"<<std::endl;
//			break;
//		}
//		else if (userWins) {
//			std::cout << "YOU WON!\n**********************************************************************************" << std::endl;
//			break;
//		}
//		std::cout << "CPU's turn.\n";
//		//MOVE FROM AI
//		makeMoveAI(player, AI, b, 4);
//	}
//}

int main() {
	//initialize random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int controlWinsCount = 0;
	int AIWinsCount = 0;
	int numOfGames = 10;
	int depth = 4;
	for (int i = 0; i < numOfGames / 2; i++) {
		Player controlAI{ Token::PlayerType::user, WinMode::allignShapes };
		Player AI{ Token::PlayerType::AI, WinMode::allignColours };
		Board b = Board();
		bool userWins = false;
		bool aiWins = false;
		while (true) {
			userWins = b.playerHasWon(controlAI);
			aiWins = b.playerHasWon(AI);
			if (userWins) {
				controlWinsCount++;
				break;
			}
			else if (aiWins) {
				AIWinsCount++;
				break;
			}
			makeMoveControlAI(controlAI, AI, b, depth);

			userWins = b.playerHasWon(controlAI);
			aiWins = b.playerHasWon(AI);
			if (aiWins) {
				AIWinsCount++;
				break;
			}
			else if (userWins) {
				controlWinsCount++;
				break;
			}
			makeMoveAI(controlAI, AI, b, depth);
		}
	}
	
	std::cout << "\nFirst move: Control AI\nDepth: " << depth << "\nControl AI wins: " << controlWinsCount <<
		"\nAdvanced AI wins: " << AIWinsCount << "\nRatio (advanced/control): " << static_cast<float>(AIWinsCount) / (controlWinsCount+AIWinsCount) << std::endl;
	
	controlWinsCount = 0;
	AIWinsCount = 0;
	for (int i = 0; i < numOfGames / 2; i++) {
		Player controlAI{ Token::PlayerType::user, WinMode::allignShapes };
		Player AI{ Token::PlayerType::AI, WinMode::allignColours };
		Board b = Board();
		bool userWins = false;
		bool aiWins = false;
		while (true) {
			userWins = b.playerHasWon(controlAI);
			aiWins = b.playerHasWon(AI);
			if (aiWins) {
				AIWinsCount++;
				break;
			}
			else if (userWins) {
				controlWinsCount++;
				break;
			}
			makeMoveAI(controlAI, AI, b, depth);

			userWins = b.playerHasWon(controlAI);
			aiWins = b.playerHasWon(AI);
			if (userWins) {
				controlWinsCount++;
				break;
			}
			else if (aiWins) {
				AIWinsCount++;
				break;
			}
			makeMoveControlAI(controlAI, AI, b, depth);
		}
	}

	std::cout << "\nFirst move: Advances AI\nDepth: " << depth << "\nControl AI wins: " << controlWinsCount <<
		"\nAdvanced AI wins: " << AIWinsCount << "\nRatio (advanced/control): " << static_cast<float>(AIWinsCount) / (controlWinsCount + AIWinsCount) << std::endl;

}