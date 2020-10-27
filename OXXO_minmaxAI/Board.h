#ifndef BOARD_H
#define BOARD_H
#include "Pawn.h"
#include "Declarations.h"

class Board
{
public:
	static const int size;
private:
	static std::vector < std::vector<std::pair<int, int >>> lines;
	static std::vector<std::vector<Pawn*>> board;
public:
	Board();
	static bool addPawn(int x1, int x2, PlayerData &player, Pawn::Shape faceUp);
	static bool flipPawn(int x1, int x2, const PlayerData &player);
	static bool playerHasWon(const PlayerData& player);
	static int boardConfigScore(const PlayerData& user, const PlayerData& AI);
	static void print(const PlayerData& player, const PlayerData& AI);
	static Pawn* getPawnAtPositon(int x1, int x2);
};

#endif // !BOARD_H