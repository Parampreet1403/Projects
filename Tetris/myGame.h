#ifndef MY_GAME_CLASS_H
#define MY_GAME_CLASS_H

#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <random>

#include "myPlayer.h"
#include "myFile.h"
#include "myTetromino.h"


class Game
{
private:
	int nFieldWidth{ 12 }; // Game Size X
	int nFieldHeight{ 18 }; // Game Size Y
	int nScreenWidth{ 80 }; // Console Screen Size X
	int nScreenHeight{ 30 }; // Console Screen Size Y
	int nMaxSpeed{ 20 };
	int nMinSpeed{ 10 };
	int nSpeedCounter{};
	int nBlockMinValue{};
	int nBlockMaxValue{ 6 };

	bool bGameOver{};
	bool bKey[4]{};
	bool bLock{};
	bool bRotateHold{};
	bool bLeftHold{};
	bool bRightHold{};
	bool bForceDown{};
	bool bGate{};

	unsigned char* pField = new unsigned char[nFieldWidth * nFieldHeight]; // Create buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight]; // Console Screen
	std::vector<int> vLines{};

public:
	Game();

	~Game();

	// Member Functions
	void blankScreen();

	void createBoard();

	void updateScreen();

	void DrawString(int x, int y, std::string c);

	void displayStats(Player Player, File file);

	void drawBlock(Tetromino Block);

	void gameOver(Tetromino Block);

	void Tick();

	void Delay(int time);

	void lockBlock(Tetromino Block);

	void forceDown(Tetromino& Block);

	void increaseSpeed(Tetromino Block);

	void checkLine(Tetromino Block);

	void removeLine(Player& Player, File file);

	int randomNumberGenerator();

	void Move(Tetromino& Block, Player& Player, File file);

	int inLineText(std::string str);

	void End(Player Player, File& File);

	int Start(Player& Player, File& File);
};

#endif // MY_GAME_CLASS_H

