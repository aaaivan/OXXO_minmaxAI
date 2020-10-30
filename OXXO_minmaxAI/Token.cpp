#include "Token.h"
#include <windows.h> //for SetConsoleTextAttribute()
#include <cstdio> // for printf()
#include <iostream>

const unsigned int Token::consolColour = 0x7;//white on black
const char Token::c[2] = { 'X', 'O' };

Token::Token(PlayerType _playerType, Shape _faceUp): playerType(_playerType) {
	if (playerType == PlayerType::user) {
		faces[0] = ( std::pair< ShapeColor, Shape>(ShapeColor::black, Shape::x) );
		faces[1] = ( std::pair< ShapeColor, Shape>(ShapeColor::red, Shape::o) );
		if (_faceUp == Shape::x)
			faceUp = 0;
		else
			faceUp = 1;
		tokenBgColours[0] = 0xf0; //black on white
		tokenBgColours[1] = 0xfc; //red on white
	}
	else{
		faces[0] = (std::pair< ShapeColor, Shape>(ShapeColor::red, Shape::x));
		faces[1] = (std::pair< ShapeColor, Shape>(ShapeColor::black, Shape::o));
		if (_faceUp == Shape::x)
			faceUp = 0;
		else
			faceUp = 1;
		tokenBgColours[0] = 0xec; //red on yellow
		tokenBgColours[1] = 0xe0; //black on yellow
	}
}


Token::PlayerType Token::getPlayerType() {
	return playerType;
}

Token::ShapeColor Token::getShapeColour() {
	return faces[faceUp].first;
}

Token::Shape Token::getShape() {
	return faces[faceUp].second;
}

void Token::print() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), tokenBgColours[faceUp]);
	std::cout << " " << c[faceUp] << " ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), consolColour);
}

void Token::flip() {
	faceUp = (faceUp + 1) % 2;
}
