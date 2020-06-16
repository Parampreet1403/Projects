#include "myGame.h"

Game::Game() {};

Game::~Game() {};

// Member Functions
void Game::blankScreen()
{
	for (int i{}; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
}

void Game::createBoard()
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

void Game::updateScreen()
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
	*/
}

void Game::DrawString(int x, int y, std::string c) // Writes string to screen
{
	for (size_t i = 0; i < c.size(); i++)
	{
		screen[y * nScreenWidth + x + i] = c[i];
	}
}

void Game::displayStats(Player Player, File file) 
{
	if (!bGameOver)
	{
		DrawString(6 + nFieldWidth, 2, "NAME: " + Player.get_name());
		DrawString(6 + nFieldWidth, 4, "SCORE: " + std::to_string(Player.get_nScore()));
		DrawString(26 + nFieldWidth, 4, "HIGH SCORE: " + file.get_highScore());
	}
}

void Game::drawBlock(Tetromino Block)
{
	for (int px{}; px < 4; px++)
		for (int py{}; py < 4; py++)
			if (Block.get_shape()[Block.Rotate(px, py, Block.get_nRotation())] == L'X') // Only draw the 'X' points
				screen[(Block.get_nPosY() + py + 2) * nScreenWidth + (Block.get_nPosX() + px + 2)] = Block.get_nIndex() + 65; // 65 = A in ASCII
}

void Game::gameOver(Tetromino Block)
{
	bGameOver = !Block.DoesPieceFit(Block.get_nRotation(), Block.get_nPosX(), Block.get_nPosY(), pField);
}

void Game::Tick()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	nSpeedCounter++;
}

void Game::Delay(int time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void Game::lockBlock(Tetromino Block)
{
	for (int px{}; px < 4; px++)
		for (int py{}; py < 4; py++)
			if (Block.get_shape()[Block.Rotate(px, py, Block.get_nRotation())] == L'X') // If tetromino block hits another block
			{
				pField[(Block.get_nPosY() + py) * nFieldWidth + (Block.get_nPosX() + px)] = Block.get_nIndex() + 1; // Update the field 
				bLock = true;
			}
}

void Game::forceDown(Tetromino& Block)
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

void Game::increaseSpeed(Tetromino Block)
{
	if (Block.get_nTetrominoCounter() % 10 == 0) // Every 10 blocks will cause nMaxSpeed to decrease by 1
		if (nMaxSpeed >= nMinSpeed) nMaxSpeed--; // The lower nMaxSpeed, the faster bForceDown occurs (less game Ticks needed)
}

void Game::checkLine(Tetromino Block)
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

void Game::removeLine(Player& Player, File file)
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

int Game::randomNumberGenerator() // Generates TRUE random numbers
{
	std::mt19937 generator;  // Defines random number engine
	generator.seed(std::time(0)); // seed prevents Pseudo-random
	std::uniform_int_distribution<uint32_t> random(nBlockMinValue, nBlockMaxValue);
	return random(generator);
}

void Game::Move(Tetromino& Block, Player& Player, File file)
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
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten); // Writing to console
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

int Game::inLineText(std::string str) // Allows me to write to the middle of the screen 
{
	int x = str.length() / 2;
	return x;
}

void Game::End(Player Player, File& File)
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

int Game::Start(Player& Player, File& File)
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
