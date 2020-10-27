#ifndef DECLARETIONS_H
#define DECLARETIONS_H
#include <string>
#include "Pawn.h"

enum class WinMode {
	allignColours, allignShapes
};

struct PlayerData {
	Pawn::PlayerType playerType;
	WinMode winMode;
	const int initialpawns = 8;
	int pawnsLeft = initialpawns;
};

void askWinningMode(PlayerData& player, PlayerData& AI);
int getPlayerInputRow();
int getPlayerInputCol();
void printTitleOfGame();
Pawn::Shape askFaceUp(PlayerData& p);

#endif // !DECLARETIONS_H

