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
	~Board();
	static bool addToken(int x1, int x2, Player &player, Token::Shape faceUp);
	static void removeToken(int x1, int x2, Player& player);
	static bool flipToken(int x1, int x2, const Player &player);
	static bool playerHasWon(const Player& player);
	static int boardEvaluation(const Player& user, const Player& AI);
	static int boardEvaluationControl(const Player& user, const Player& AI);
	static void print(const Player& player, const Player& AI);
	static Token* getTokenAtPositon(int x1, int x2);
	friend void makeMoveAI(Player& player, Player& AI, Board &b, int depth);
	friend int minimax(Board& b, Player& player, Player& AI, int depth, int alpha, int beta, bool maximazingAgent);
	friend void makeMoveRefAI(Player& player, Player& AI, Board& b, int depth);
	friend int minimaxReference(Board& b, Player& player, Player& AI, int depth, int alpha, int beta, bool maximazingAgent);
};

#endif // !BOARD_H