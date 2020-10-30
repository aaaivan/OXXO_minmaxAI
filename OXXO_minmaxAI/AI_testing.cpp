#include "Board.h"
#include "Token.h"
#include "Declarations.h"
#include <iostream>
#include <ctime>
#include <fstream>

int main() {
	//initialize random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int controlWinsCount = 0;
	int AIWinsCount = 0;
	int numOfGames = 100;
	int maxDepth = 4;
	std::ofstream myfile;
	//test the AI against a control AI on using minimax algorithms with depth 1 to maxDepth
	//for each depth, make the two AIs play numOfGames games.
	for (int depth = 1; depth <= maxDepth; depth++) {
		//in half of the games, the control AI will start
		for (int i = 0; i < numOfGames / 2; i++) {
			Player controlAI{ Token::PlayerType::user, WinMode::allignShapes };
			Player AI{ Token::PlayerType::AI, WinMode::allignColours };
			Board b = Board();
			bool controlHasWon = false;
			bool aiHasWon = false;
			int moves = 0;
			while (moves<100) {//once each AI performs 100 moves, consider the game a tie
				controlHasWon = b.playerHasWon(controlAI);
				aiHasWon = b.playerHasWon(AI);
				if (controlHasWon) {
					controlWinsCount++;
					break;
				}
				else if (aiHasWon) {
					AIWinsCount++;
					break;
				}
				makeMoveControlAI(controlAI, AI, b, depth);

				controlHasWon = b.playerHasWon(controlAI);
				aiHasWon = b.playerHasWon(AI);
				if (aiHasWon) {
					AIWinsCount++;
					break;
				}
				else if (controlHasWon) {
					controlWinsCount++;
					break;
				}
				makeMoveAI(controlAI, AI, b, depth);
				moves++;
			}
			std::cout << "game " <<depth<<"."<< i << "\n";
		}
		//append the results to a txt file
		myfile.open("results.txt", std::ios::app);
		myfile << "\nFirst move: Control AI\nDepth: " << depth << "\nControl AI wins: " << controlWinsCount <<
			"\nAdvanced AI wins: " << AIWinsCount << "\nRatio (advanced/control): " << static_cast<float>(AIWinsCount) / (controlWinsCount + AIWinsCount) << std::endl;
		myfile.close();
		controlWinsCount = 0;
		AIWinsCount = 0;

		//in half of the games, the custom AI will start
		for (int i = 0; i < numOfGames / 2; i++) {
			Player controlAI{ Token::PlayerType::user, WinMode::allignShapes };
			Player AI{ Token::PlayerType::AI, WinMode::allignColours };
			Board b = Board();
			bool userWins = false;
			bool aiWins = false;
			int moves = 0;
			while (moves < 100) {//once each AI performs 100 moves, consider the game a tie
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
				moves++;
			}
			std::cout << "game " << depth << "." << i+numOfGames/2 << "\n";
		}
		//append the results to a txt file
		myfile.open("results.txt", std::ios::app);
		myfile << "\nFirst move: Advances AI\nDepth: " << depth << "\nControl AI wins: " << controlWinsCount <<
			"\nAdvanced AI wins: " << AIWinsCount << "\nRatio (advanced/control): " << static_cast<float>(AIWinsCount) / (controlWinsCount + AIWinsCount) << std::endl;
		myfile.close();
		controlWinsCount = 0;
		AIWinsCount = 0;
	}
}