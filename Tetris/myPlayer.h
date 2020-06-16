#ifndef MY_PLAYER_CLASS_H
#define MY_PLAYER_CLASS_H

#include <string>
#include <iostream>

class Player
{
private:
	int nScore{};
	std::string name{};
	bool bGate{};

public:

	Player();

	~Player();

	// Access Private Variables
	int& get_nScore();
	std::string& get_name();

	// Member Functions
	void getName();

	int askAgain();
};



#endif // MY_PLAYER_CLASS_H
