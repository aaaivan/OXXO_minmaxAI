#ifndef DECLARETIONS_H
#define DECLARETIONS_H
#include <string>
#include "Token.h"

enum class WinMode {
	allignColours, allignShapes
};

struct PlayerData {
	Token::PlayerType playerType;
	WinMode winMode;
	const int initialpawns = 8;
	int pawnsLeft = initialpawns;
};

void askWinningMode(PlayerData& player, PlayerData& AI);
int getPlayerInputRow();
int getPlayerInputCol();
void printTitleOfGame();
Token::Shape askFaceUp(PlayerData& p);

#endif // !DECLARETIONS_H

