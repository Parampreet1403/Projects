#include "myFile.h"

File::File() {}

File::~File() {}

// Access Private Variables
std::string& File::get_highScore() { return highScore; }

// Member Functions
bool File::checkFile()
{
	std::ifstream file(fileName);
	if (file.good())
	{
		std::cout << "WELCOME TO TETRIS\nUSE THE ARROW KEYS TO MOVE THE BLOCK.\nPRESS SPACEBAR TO ROTATE THE BLOCK." << std::endl;
		std::cout << "CREATE LINES IN ORDER TO SCORE POINTS.\nTHE MORE LINES YOU CREATE IN ONE MOVE THE MORE POINTS YOU SCORE!" << std::endl;
		return true;
	}
	else
	{
		std::cout << "ERROR: 'Score.txt' WAS NOT FOUND.\nPLEASE ENSURE IT IS SAVED WITH 'Source.cpp'\nIN ORDER TO LAUNCH THE GAME." << std::endl;
		return false;
	}
}

void File::clearFile()
{
	std::ofstream file(fileName);
	file << "Name                               " << "Score          " << std::endl;
	file.close();
}

void File::updateFile(Player Player)
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

void File::sortFile()
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
