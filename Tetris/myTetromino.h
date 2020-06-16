#ifndef MY_TETROMINO_CLASS_H
#define MY_TETROMINO_CLASS_H

#include <string>
#include "myPlayer.h"

class Tetromino
{
private:
	int nFieldWidth{ 12 }; // Game Size X
	int nFieldHeight{ 18 }; // Game Size Y
	static int nTetrominoCounter; // Static to keep track number of blocks created
	int nIndex{};
	int nRotation{};
	int nPosX{ nFieldWidth / 2 }; // Middle of game
	int nPosY{}; // Top of game

	std::wstring shape{ L"..X...X...X...X." };

public:
	Tetromino(int nIndexIn, Player& Player);

	~Tetromino();

	// Access Private Variables
	int& get_nTetrominoCounter();
	std::wstring get_shape();
	int get_nIndex();
	int& get_nRotation();
	int& get_nPosX();
	int& get_nPosY();

	// Member Functions
	int Rotate(int x, int y, int nRotation);

	bool DoesPieceFit(int nRotation, int x, int y, unsigned char* pField);
};

#endif // MY_TETROMINO_CLASS_H
