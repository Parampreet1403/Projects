#include "myPlayer.h"

Player::Player() {}

Player::~Player() {}

int& Player::get_nScore() { return nScore; }
std::string& Player::get_name() { return name; }

void Player::getName()
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

int Player::askAgain()
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
