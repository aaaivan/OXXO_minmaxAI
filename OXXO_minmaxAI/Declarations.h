#ifndef DECLARETIONS_H
#define DECLARETIONS_H
#include <string>
#include "Token.h"

enum class WinMode {
	allignColours, allignShapes
};

struct Player {
	Token::PlayerType playerType;
	WinMode winMode;
	const int initialTokens = 8;
	int tokensLeft = initialTokens;
};

void askWinningMode(Player& player, Player& AI);
int getPlayerInputRow();
int getPlayerInputCol();
void printTitleOfGame();
Token::Shape askFaceUp(Player& p);

#endif // !DECLARETIONS_H

