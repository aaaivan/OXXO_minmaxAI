#ifndef TOKEN_H
#define TOKEN_H
#include <utility>
#include <vector>

class Token
{
public:
	enum class PlayerType
	{
		AI = -1, user=+1
	};
	enum class ShapeColor
	{
		red=-1, black=1
	};
	enum class Shape
	{
		x=-1, o=1
	};
private:
	unsigned short tokenBgColours[2];//for printing on the console
	PlayerType playerType;
	std::pair<ShapeColor, Shape> faces[2];
	short faceUp;
	static const unsigned int consolColour;
	static const char c[2];
public:
	Token(PlayerType _playerType, Shape _faceUp);
	PlayerType getPlayerType();
	ShapeColor getShapeColour();
	Shape getShape();
	void print();
	void flip();
};

#endif // !TOKEN_H
