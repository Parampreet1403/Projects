#ifndef MY_FILE_CLASS_H
#define MY_FILE_CLASS_H

#include "myPlayer.h"

#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class File
{
private:
	std::string fileName{ "Score.txt" };
	std::string highScore{};

public:
	File();

	~File();

	// Access Private Variable
	std::string& get_highScore();

	// Member Functions
	bool checkFile();

	void clearFile();

	void updateFile(Player Player);

	void sortFile();
};


#endif // MY_FILE_CLASS_H
