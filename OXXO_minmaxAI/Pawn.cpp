#include "Pawn.h"
#include <windows.h> //for SetConsoleTextAttribute()
#include <cstdio> // for printf()
#include <iostream>

const unsigned int Pawn::consolColour = 0x7;
const char Pawn::c[2] = { 'X', 'O' };

Pawn::Pawn(PlayerType _playerType, Shape _faceUp): playerType(_playerType) {
	if (playerType == PlayerType::user) {
		faces[0] = ( std::pair< ShapeColor, Shape>(ShapeColor::black, Shape::x) );
		faces[1] = ( std::pair< ShapeColor, Shape>(ShapeColor::red, Shape::o) );
		if (_faceUp == Shape::x)
			faceUp = 0;
		else
			faceUp = 1;
		pawnColours[0] = 0xf0;
		pawnColours[1] = 0xfc;
	}
	else{
		faces[0] = (std::pair< ShapeColor, Shape>(ShapeColor::red, Shape::x));
		faces[1] = (std::pair< ShapeColor, Shape>(ShapeColor::black, Shape::o));
		if (_faceUp == Shape::x)
			faceUp = 0;
		else
			faceUp = 1;
		pawnColours[0] = 0xec;
		pawnColours[1] = 0xe0;
	}
}


Pawn::PlayerType Pawn::getPlayerType() {
	return playerType;
}

Pawn::ShapeColor Pawn::getShapeColour() {
	return faces[faceUp].first;
}

Pawn::Shape Pawn::getShape() {
	return faces[faceUp].second;
}

void Pawn::print() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pawnColours[faceUp]);
	std::cout << " " << c[faceUp] << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), consolColour);
}

void Pawn::flip() {
	faceUp = (faceUp + 1) % 2;
}
