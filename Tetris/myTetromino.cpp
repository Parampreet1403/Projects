#include "myTetromino.h"

Tetromino::Tetromino(int nIndexIn, Player& Player)
{
	nTetrominoCounter++;
	Player.get_nScore() += 25; // Score increases each time tetromino block created
	nIndex = nIndexIn;
	switch (nIndexIn) // Index determines shape
	{
	case 0: shape = L"..X...X...X...X."; break;
	case 1: shape = L".....XX..XX....."; break;
	case 2: shape = L".....XX...X...X."; break;
	case 3: shape = L"......XX..X...X."; break;
	case 4: shape = L"..X..XX..X......"; break;
	case 5: shape = L".X...XX...X....."; break;
	case 6: shape = L"..X..XX...X....."; break;
	}
	// How Shapes Work:
	/*
	..X.
	..X.
	..X.
	..X.

	....
	.XX.
	.XX.
	....

	....
	.XX.
	..X.
	..X.

	etc...
	*/
}

Tetromino::~Tetromino() {}

// Access Private Variables
int& Tetromino::get_nTetrominoCounter() { return nTetrominoCounter; }
std::wstring Tetromino::get_shape() { return shape; }
int Tetromino::get_nIndex() { return nIndex; }
int& Tetromino::get_nRotation() { return nRotation; }
int& Tetromino::get_nPosX() { return nPosX; }
int& Tetromino::get_nPosY() { return nPosY; }

// Member Functions
int Tetromino::Rotate(int x, int y, int nRotation) // Rotates block
{
	switch (nRotation % 4)
	{
	case 0: return y * 4 + x;			// 0 degrees 
	case 1: return 12 + y - (x * 4);	// 90 degrees 
	case 2: return 15 - (y * 4) - x;	// 180 degrees 
	case 3: return 3 - y + (x * 4);		// 270 degrees 
	};
}

bool Tetromino::DoesPieceFit(int nRotation, int x, int y, unsigned char* pField) // Checks to see if tetromino block can fit
{
	for (int px{}; px < 4; px++) // For loop over tetromino
		for (int py{}; py < 4; py++)
		{
			// Get index into tetromino block
			int pi = Rotate(px, py, nRotation);

			// Get index into field
			int fi = (y + py) * nFieldWidth + (x + px);

			if (x + px >= 0 && x + px < nFieldWidth) // Checks to see if tetromino block is within game boundaries
			{
				if (y + py >= 0 && y + py < nFieldHeight)
				{
					// Collision detection: Reads only 'X' points of shape and checks if field is empty
					if (this->shape[pi] == L'X' && pField[fi] != 0)
						return false; // fail on first hit
				}
			}
		}
	return true; // Tetromino block fits and return true
}

int Tetromino::nTetrominoCounter{}; // Defind outside of class
