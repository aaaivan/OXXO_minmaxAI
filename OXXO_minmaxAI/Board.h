#ifndef BOARD_H
#define BOARD_H
#include "Token.h"
#include "Declarations.h"

class Board
{
public:
	static const int size;
private:
	static std::vector < std::vector<std::pair<int, int >>> lines;
	static std::vector<std::vector<Token*>> board;
public:
	Board();
	static bool addToken(int x1, int x2, PlayerData &player, Token::Shape faceUp);
	static bool flipToken(int x1, int x2, const PlayerData &player);
	static bool playerHasWon(const PlayerData& player);
	static int boardConfigScore(const PlayerData& user, const PlayerData& AI);
	static void print(const PlayerData& player, const PlayerData& AI);
	static Token* getTokenAtPositon(int x1, int x2);
};

#endif // !BOARD_H