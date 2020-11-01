#include "Board.h"
#include "Token.h"
#include "Declarations.h"
#include <iostream>
#include <ctime>
#include <fstream>

int main() {
	//initialize random seed
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	int refWinsCount = 0;
	int AIWinsCount = 0;
	int numOfGames = 100;
	int maxDepth = 5;
	std::ofstream myfile;
	//test the AI against a reference AI on using minimax algorithms with depth 1 to maxDepth
	//for each depth, make the two AIs play numOfGames games.
	for (int depth = 5; depth <= maxDepth; depth++) {
		//in half of the games, the reference AI will start
		for (int i = 0; i < numOfGames / 2; i++) {
			Player refAI{ Token::PlayerType::user, WinMode::alignShapes };
			Player AI{ Token::PlayerType::AI, WinMode::alignColours };
			Board b = Board();
			bool refHasWon = false;
			bool aiHasWon = false;
			int moves = 0;
			while (moves<100) {//once each AI performs 100 moves, consider the game a tie
				refHasWon = b.playerHasWon(refAI);
				aiHasWon = b.playerHasWon(AI);
				if (refHasWon) {
					refWinsCount++;
					break;
				}
				else if (aiHasWon) {
					AIWinsCount++;
					break;
				}
				makeMoveRefAI(refAI, AI, b, depth);

				refHasWon = b.playerHasWon(refAI);
				aiHasWon = b.playerHasWon(AI);
				if (aiHasWon) {
					AIWinsCount++;
					break;
				}
				else if (refHasWon) {
					refWinsCount++;
					break;
				}
				makeMoveAI(refAI, AI, b, depth);
				moves++;
			}
			std::cout << "game " <<depth<<"."<< i << "\n";
		}
		//append the results to a txt file
		myfile.open("results.txt", std::ios::app);
		myfile << "\nFirst move: Control AI\nDepth: " << depth << "\nControl AI wins: " << refWinsCount <<
			"\nAdvanced AI wins: " << AIWinsCount << "\nRatio (advanced/reference): " << static_cast<float>(AIWinsCount) / (refWinsCount + AIWinsCount) << std::endl;
		myfile.close();
		refWinsCount = 0;
		AIWinsCount = 0;

		//in half of the games, the custom AI will start
		for (int i = 0; i < numOfGames / 2; i++) {
			Player refAI{ Token::PlayerType::user, WinMode::alignShapes };
			Player AI{ Token::PlayerType::AI, WinMode::alignColours };
			Board b = Board();
			bool userWins = false;
			bool aiWins = false;
			int moves = 0;
			while (moves < 100) {//once each AI performs 100 moves, consider the game a tie
				userWins = b.playerHasWon(refAI);
				aiWins = b.playerHasWon(AI);
				if (aiWins) {
					AIWinsCount++;
					break;
				}
				else if (userWins) {
					refWinsCount++;
					break;
				}
				makeMoveAI(refAI, AI, b, depth);

				userWins = b.playerHasWon(refAI);
				aiWins = b.playerHasWon(AI);
				if (userWins) {
					refWinsCount++;
					break;
				}
				else if (aiWins) {
					AIWinsCount++;
					break;
				}
				makeMoveRefAI(refAI, AI, b, depth);
				moves++;
			}
			std::cout << "game " << depth << "." << i+numOfGames/2 << "\n";
		}
		//append the results to a txt file
		myfile.open("results.txt", std::ios::app);
		myfile << "\nFirst move: Advances AI\nDepth: " << depth << "\nControl AI wins: " << refWinsCount <<
			"\nAdvanced AI wins: " << AIWinsCount << "\nRatio (advanced/reference): " << static_cast<float>(AIWinsCount) / (refWinsCount + AIWinsCount) << std::endl;
		myfile.close();
		refWinsCount = 0;
		AIWinsCount = 0;
	}
}