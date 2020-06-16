#include "myGame.h"
#include "myFile.h"
#include "myPlayer.h"

int main()
{
	Game Tetris;
	Player Player;
	File File;
	while (File.checkFile())
	{
		File.sortFile();
		Tetris.Start(Player, File);
	}
	return 0;
}

/*


s
#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <fstream>

#include "myGame.h";

// Global Variables
int nFieldWidth{ 12 }; // Game Size X
int nFieldHeight{ 18 }; // Game Size Y

class Player
{
private:
	int nScore{};
	std::string name{};
	bool bGate{};

public:

	Player() {}

	~Player() {}

	// Access Private Variables
	int& get_nScore() { return nScore; }
	std::string& get_name() { return name; }

	// Member Functions
	void getName()
	{
		while (!bGate)
		{
			std::cout << "PLEASE ENTER YOUR NAME: " << std::endl;
			std::string name{};
			std::getline(std::cin, name);
			if (name.length() < 36)
			{
				this->get_name() = name;
				break;
			}
			else std::cout << "PLEASE SELECT A SHORTER NAME." << std::endl;
		}
	}

	int askAgain()
	{
		while (!bGate)
		{
			std::string answer{};
			std::cout << "PRESS 'C' TO CONTINUE...\nPRESS 'N' TO CHANGE YOUR NAME... " << std::endl;
			std::getline(std::cin, answer);
			if (answer == "c") return 0;
			else if (answer == "n") getName();
		}
	}
};

class File
{
private:
	std::string fileName{"Score.txt"};
	std::string highScore{};

public:
	File() {}

	~File() {}

	// Access Private Variable
	std::string& get_highScore() { return highScore; }

	// Member Functions
	bool checkFile()
	{
		std::ifstream file(fileName);
		if (file.good())
		{
			std::cout << "WELCOME TO TETRIS\nUSE THE ARROW KEYS TO MOVE THE BLOCK.\nPRESS SPACEBAR TO ROTATE THE BLOCK." << std::endl;
			return true;
		}
		else
		{
			std::cout << "ERROR: 'Score.txt' WAS NOT FOUND.\nPLEASE ENSURE IT IS SAVED WITH 'Source.cpp'\nIN ORDER TO LAUNCH THE GAME." << std::endl;
			return false;
		}
	}

	void clearFile()
	{
		std::ofstream file(fileName);
		file << "Name                               " << "Score          " << std::endl;
		file.close();
	}

	void updateFile(Player Player)
	{
		std::fstream file(fileName, std::ios::app); // Appends to the file
		int size = 36 - Player.get_name().length();
		char* temp = new char[size]; // Creates an array of blank space to make all name inputs the same size
		for (int i{}; i < size; i++)
			temp[i] = ' ';
		temp[size - 1] = '\0'; // Null termination
		file << Player.get_name() << temp << Player.get_nScore() << std::endl;
		delete[] temp; // Avoid memory leak
	}

	void sortFile()
	{
		std::fstream file(fileName);
		std::pair<std::string, int> playerInfo{};
		std::vector<std::pair<std::string, int>> data{};
		std::string line{};
		std::vector<std::string> fileString{};
		std::string playerName{};
		std::string playerScore{};

		while (!file.eof()) // Reads file and turns file into a vector of strings; fileString
		{
			std::getline(file, line);
			fileString.push_back(line);
		}

		for (int i{ 1 }; i < fileString.size() - 1; i++) // Skips first line (Header) of fileString
		{
			for (int c{}; c < fileString[i].size(); c++) // Goes through each character of a string in fileString and separates name from score
				if (c < 35) // Names are 36 characters long
					playerName += fileString[i][c];
				else if (fileString[i][c] != ' ') // Remainder of string has to be score
					playerScore += fileString[i][c];

			// Creates pair for name and score
			playerInfo.first = playerName;
			if (!playerScore.empty())
				playerInfo.second = std::stoi(playerScore);

			// Push back pair onto new vector of pairs
			data.push_back(playerInfo);
			playerName.clear();
			playerScore.clear();
		}

		// Lambda function to sort vector of pairs by largest score
		std::sort(data.begin(), data.end(), [](auto& left, auto& right) { return left.second > right.second; });
		file.close();

		// Writes to file with sorted score with associated name
		clearFile();
		std::fstream newFile(fileName, std::ios::app);
		for (int z{}; z < data.size(); z++)
			newFile << data[z].first << data[z].second << std::endl;

		get_highScore() = std::to_string(data[0].second); // Largest score becomes high score
		newFile.close();
	}
};

class Tetromino
{
private:
	static int nTetrominoCounter; // Static to keep track number of blocks created
	int nIndex{};
	int nRotation{};
	int nPosX{nFieldWidth/2}; // Middle of game
	int nPosY{}; // Top of game
	int nFieldWidth{ 12 }; // Game Size X
	int nFieldHeight{ 18 }; // Game Size Y
	std::wstring shape{ L"..X...X...X...X." };

public:
	//Tetromino() { nTetrominoCounter++; }

	Tetromino(int nIndexIn, Player& Player)
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
		
	}

	~Tetromino() {}

	// Access Private Variables
	int& get_nTetrominoCounter() { return nTetrominoCounter; }
	std::wstring get_shape() { return shape; }
	int get_nIndex() { return nIndex; }
	int& get_nRotation() { return nRotation; }
	int& get_nPosX() { return nPosX; }
	int& get_nPosY() { return nPosY; }

	// Member Functions
	int Rotate(int x, int y, int nRotation) // Rotates block
	{
		switch (nRotation % 4)
		{
		case 0: return y * 4 + x;			// 0 degrees 
		case 1: return 12 + y - (x * 4);	// 90 degrees 
		case 2: return 15 - (y * 4) - x;	// 180 degrees 
		case 3: return 3 - y + (x * 4);		// 270 degrees 
		};
	}

	bool DoesPieceFit(int nRotation, int x, int y, unsigned char* pField) // Checks to see if tetromino block can fit
		// x and y are the top left of the tetromino block 
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
};
int Tetromino::nTetrominoCounter{};

class Game
{
private:
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
	Game() {};

	~Game() {};

	// Member Functions
	void blankScreen()
	{
		for (int i{}; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
	}

	void createBoard()
	{
		for (int x{}; x < nFieldWidth; x++) // Looping over board 
			for (int y{}; y < nFieldHeight; y++)
			{ // Assigning numerical numbers to sections of the board:
				if (pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1)) // Side boundaries
					pField[y * nFieldWidth + x] = 9;
				else if (pField[y * nFieldWidth + x] = y == nFieldHeight - 1) // Bottom boundary
					pField[y * nFieldWidth + x] = 10;
				else
					pField[y * nFieldWidth + x] = 0; // Inside
			}
	}

	void updateScreen()
	{
		for (int x{}; x < nFieldWidth; x++)
			for (int y{}; y < nFieldHeight; y++)
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG*|T"[pField[y * nFieldWidth + x]];

		// Numerical number character equivalent:
		/*
		0 = " "
		1 = A
		2 = B
		3 = C
		4 = D
		5 = E
		6 = F
		7 = G
		8 = *
		9 = |
		10 = T
		
	}

	void DrawString(int x, int y, std::string c) // Writes string to screen
	{
		for (size_t i = 0; i < c.size(); i++)
		{
			screen[y * nScreenWidth + x + i] = c[i];
		}
	}

	void displayStats(Player Player, File file) // Grants access to console, allowing me to manipulate any part of the screen
	{
		if (!bGameOver)
		{
			DrawString(6 + nFieldWidth, 2, "NAME: " + Player.get_name());
			DrawString(6 + nFieldWidth, 4, "SCORE: " + std::to_string(Player.get_nScore()));
			DrawString(26 + nFieldWidth, 4, "HIGH SCORE: " + file.get_highScore());
		}
	}

	void drawBlock(Tetromino Block)
	{
		for (int px{}; px < 4; px++)
			for (int py{}; py < 4; py++)
				if (Block.get_shape()[Block.Rotate(px, py, Block.get_nRotation())] == L'X') // Only draw the 'X' points
					screen[(Block.get_nPosY() + py + 2) * nScreenWidth + (Block.get_nPosX() + px + 2)] = Block.get_nIndex() + 65; // 65 = A in ASCII
	}

	void gameOver(Tetromino Block)
	{
		bGameOver = !Block.DoesPieceFit(Block.get_nRotation(), Block.get_nPosX(), Block.get_nPosY(), pField);
	}

	void Tick()
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		nSpeedCounter++;
	}

	void Delay(int time)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(time));
	}

	void lockBlock(Tetromino Block)
	{
		for (int px{}; px < 4; px++)
			for (int py{}; py < 4; py++)
				if (Block.get_shape()[Block.Rotate(px, py, Block.get_nRotation())] == L'X') // If tetromino block hits another block
				{
					pField[(Block.get_nPosY() + py) * nFieldWidth + (Block.get_nPosX() + px)] = Block.get_nIndex() + 1; // Update the field 
					bLock = true;
				}
	}

	void forceDown(Tetromino& Block)
	{
		bForceDown = (nSpeedCounter == nMaxSpeed); // Force down occurs after 20 game Ticks == 1 second
		if (bForceDown)
		{
			if (Block.DoesPieceFit(Block.get_nRotation(), Block.get_nPosX(), Block.get_nPosY() + 1, pField)) // If the block can move down, move it
			{
				Block.get_nPosY() = Block.get_nPosY() + 1;
			}
			else
			{
				lockBlock(Block); // Else the block cannot move so lock it
			}
			nSpeedCounter = 0; // Reset counter so bForceDown can occur again
		}
	}

	void increaseSpeed(Tetromino Block)
	{
		if (Block.get_nTetrominoCounter() % 10 == 0) // Every 10 blocks will cause nMaxSpeed to decrease by 1
			if (nMaxSpeed >= nMinSpeed) nMaxSpeed--; // The lower nMaxSpeed, the faster bForceDown occurs (less game Ticks needed)
	}

	void checkLine(Tetromino Block)
	{
		for (int py{}; py < 4; py++)
			if (Block.get_nPosY() + py < nFieldHeight - 1)
			{
				bool bLine{ true };
				for (int px{ 1 }; px < nFieldWidth - 1; px++) // Removes border in check
					bLine &= (pField[(Block.get_nPosY() + py) * nFieldWidth + px]) != 0; // Checking for empty spaces in line

				if (bLine)
				{
					// Set characters in line to *
					for (int px{ 1 }; px < nFieldWidth - 1; px++)
					{
						pField[(Block.get_nPosY() + py) * nFieldWidth + px] = 8;
					}
					vLines.push_back(Block.get_nPosY() + py); // Stores number of lines created
					updateScreen();
				}
			}
	}

	void removeLine(Player& Player, File file)
	{
		if (!vLines.empty())
		{
			updateScreen();
			displayStats(Player, file);
			Delay(400); // Display line for 0.4 of a second
			for (auto& v : vLines)
				for (int px{ 1 }; px < nFieldWidth - 1; px++)
				{
					for (int py{ v }; py > 0; py--)
					{
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px]; // Move line above, below
					}
					pField[px] = 0; // Set line to empty space
				}
			Player.get_nScore() += (1 << vLines.size()) * 100; // Increase score exponentially for n lines
		}
	}

	int randomNumberGenerator() // Generates TRUE random numbers
	{
		std::mt19937 generator;  // Defines random number engine
		generator.seed(std::time(0)); // seed prevents Pseudo-random
		std::uniform_int_distribution<uint32_t> random(nBlockMinValue, nBlockMaxValue);
		return random(generator);
	}

	void Move(Tetromino& Block, Player& Player, File file)
	{
		while (!bGameOver)
		{
			HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
			SetConsoleActiveScreenBuffer(hConsole);
			DWORD dwBytesWritten{};

			while (!bLock)
			{
				for (int k{}; k < 4; k++)								//  R   L    D Spacebar
					bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28\x20"[k]))) != 0; // Virtual Key Codes

				// Change coordinate of tetromino block dependent on key pressed
				Block.get_nPosY() += (bKey[2]) && (Block.DoesPieceFit(Block.get_nRotation(), Block.get_nPosX(), Block.get_nPosY() + 1, pField)) ? 1 : 0; // Down Key

				if (bKey[0]) // Right Key 
				{
					Block.get_nPosX() += (!bRightHold && (Block.DoesPieceFit(Block.get_nRotation(), Block.get_nPosX() + 1, Block.get_nPosY(), pField))) ? 1 : 0;
					bRightHold = true;
				}
				else
					bRightHold = false;

				if (bKey[1]) // Left Key 
				{
					Block.get_nPosX() -= (!bLeftHold && (Block.DoesPieceFit(Block.get_nRotation(), Block.get_nPosX() - 1, Block.get_nPosY(), pField))) ? 1 : 0;
					bLeftHold = true;
				}
				else
					bLeftHold = false;

				if (bKey[3]) // SpaceBar Key 
				{
					Block.get_nRotation() += (!bRotateHold && (Block.DoesPieceFit(Block.get_nRotation() + 1, Block.get_nPosX(), Block.get_nPosY(), pField))) ? 1 : 0;
					bRotateHold = true; // Stops from constant spinning when held
				}
				else
					bRotateHold = false;

				// Algorithm 1 - Will allow block to keep moving and cycle through functions untill bLock becomes true in forceDown()
				Tick();
				updateScreen();
				drawBlock(Block); // Constantly updating position of tetromino block relative to board
				forceDown(Block);
				checkLine(Block);
				displayStats(Player, file);
				WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
				removeLine(Player, file);
			}
			// Algorithm 2 - Causes recursion so function never ends and keeps creating new blocks untill game ends.
			bLock = false;
			vLines.clear();
			Tetromino nBlock(randomNumberGenerator(), Player);
			increaseSpeed(nBlock);
			drawBlock(nBlock);
			gameOver(nBlock); // Checks to see if game should be ended
			Move(nBlock, Player, file);
		}
	}

	int inLineText(std::string str) // Allows me to write to the middle of the screen 
	{
		int x = str.length() / 2;
		return x;
	}

	void End(Player Player, File& File)
	{
		HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);
		DWORD dwBytesWritten{};

		int x{ 9 };
		int y{ -8 };
		std::string str1{ "RESTART THE PROGRAM IF YOU WISH TO PLAY AGAIN" };
		std::string str2{ "VIEW YOUR RANK IN THE FILE CALLED Score.txt" };

		blankScreen(); // Clears screen

		// Write to screen
		DrawString((nScreenWidth / 2) - x, (nScreenHeight / 2) + y, "GAME OVER");
		DrawString((nScreenWidth / 2) - x, (nScreenHeight / 2) + y + 2, "NAME: " + Player.get_name());
		DrawString((nScreenWidth / 2) - x, (nScreenHeight / 2) + y + 4, "YOUR SCORE: " + std::to_string(Player.get_nScore()));
		DrawString(nScreenWidth / 2 - inLineText(str1), (nScreenHeight / 2) + y + 8, str1);
		DrawString(nScreenWidth / 2 - inLineText(str2), (nScreenHeight / 2) + y + 10, str2);


		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		File.updateFile(Player);
		File.sortFile();
		while (bGameOver) {}; // Never ending loop
	}

	int Start(Player& Player, File& File)
	{
		Player.getName();
		Player.askAgain();
		std::cout << "GAME WILL START IN 3 SECONDS..." << std::endl;
		Delay(3000);
		blankScreen();
		createBoard();
		updateScreen();
		Tetromino Block(randomNumberGenerator(), Player);
		drawBlock(Block);
		Move(Block, Player, File);
		End(Player, File);
		return 0;
	}
};

*/







