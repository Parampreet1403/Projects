//Parampreet Singh - 18/06/20
//Learning how to manipulate bits

#include <iostream>
#include <vector>

	// The Lonely Interger
int lonelyInt(std::vector<int> arr) {
	int ans{};
	for (auto value : arr) {
		ans ^= value;
	}
	return ans;
}

int main()
{
	// Byte: 00000000
	// Bit:			1

	/*
	AND &
	0 & 0 = 0
	0 & 1 = 0
	1 & 1 = 1

	OR |
	0 | 0 = 1
	0 | 1 = 1
	1 | 1 = 1

	XOR ^
	0 ^ 0 = 0
	0 ^ 1 = 1
	1 ^ 1 = 0
	*/
	
	int x{ 1 }; //				00000001 = 1
	int result{}; //			00000000 = 0

	// Left shift operator : Moves bits to the left and pads spaces with 0
	// [Variable] << [Number of Places]
	result = x << 1; //			00000010 = 2
	std::cout << result << std::endl;

	// Right shift operator : Moves bits to the right and pads spaces with 0
	result = result >> 1; //	00000001 = 1
	std::cout << result << std::endl;

	// Bitwise complement operator ~ : Flips every bit (0 = 1) && (1 = 0)
	unsigned int max = ~x; //  11111110 = 4294967294
	std::cout << max << std::endl;

	// Get the ith bit
	// (x & (1 << i))
	// Places a 1 in the position of interest and if x has a 1 in that position it will return a 1
	// If it contains a 0 it will return a 0

	// Set the ith bit
	// (x | (1 << i))
	// Places a 1 in the position of interest and if x has a 0 or a 1 in that position
	// it will place a 1 in that position

	// Clear the ith bit
	// (x & (~(1 << i))
	// Place a 1 in the position of interest, then invert all the bits.
	// resulting in a 0 being in the ith position and AND operator reults that position going into a 0
	// due to the only possible operations being 0 & 1 || 0 & 0 which result in 0 reguardless

	// Finds single int in an array of duplicates
	std::vector<int> myArr{ 1, 3, 3, 4, 1, 4, 5};
	std::cout << lonelyInt(myArr) << std::endl; // 5

	// XOR operations of all duplicates will cancel out leaving only a 0
	// lonelyInt^0 = lonelyInt

	// Rule 1: IntA^IntA = 0
	// Rule 2: anyInt^0 = anyInt

	//  0011 = 3
	// ^0011 = 3
	//  0000 = 0

	return 0;
}