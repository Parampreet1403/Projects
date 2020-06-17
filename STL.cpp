// Parampreet Singh - 11/06/20
// Exploring the Standard Template Library (STL)

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>

bool comparitiveFunction(int x, int y) // Comparitive functions return true or false
{
	return x > y;
}

void vectorDemo()
{
	std::vector<int> A{ 11, 2, 3, 14 };

	// Accessing element of the vector
	std::cout << A[1] << std::endl; // 2 

	std::sort(A.begin(), A.end()); // O(NlogN) time 

	//  A = (2, 3, 11, 14)

	// Checks to see if element is present 
	// O(logN) time
	bool present = std::binary_search(A.begin(), A.end(), 3); // True
	present = std::binary_search(A.begin(), A.end(), 4); // False

	A.push_back(100); // Adding element to vector 
	present = std::binary_search(A.begin(), A.end(), 100); // True

	// A = (2, 3, 11, 14, 100)
	A.push_back(100);
	A.push_back(100);
	A.push_back(100);
	A.push_back(100);
	A.push_back(123);
	// A = (2, 3, 11, 14, 100, 100, 100, 100, 100, 123)

	std::vector<int>::iterator it = std::lower_bound(A.begin(), A.end(), 100); // instance >= 100
	auto it2 = std::upper_bound(A.begin(), A.end(), 100); // instance > 100

	std::cout << *it << " " << *it2 << std::endl;
	std::cout << it2 - it << std::endl; // 5 (5 = 9 - 4)

	std::sort(A.begin(), A.end(), comparitiveFunction);
	// A = (123, 100, 100, 100, 100, 100, 14, 11, 3, 2)

	for (int& x : A) // Iteratre by reference
	{
		x++;
	}

	// A = (124 101 101 101 101 101 15 12 4 3)

	for (int x : A)
	{
		std::cout << x << " ";
	}
}

void setDemo()
{
	std::set<int> S;
	S.insert(1); // log(N) time
	S.insert(2);
	S.insert(-1);
	S.insert(-10);

	for (int x : S) 
		std::cout << x << " ";
	std::cout << std::endl;

	// S = -10 -1 1 2
	auto it = S.find(-1);
	if (it == S.end()) // If element is not found it will return the end of the set
	{
		std::cout << "Not present\n";
	}
	else std::cout << "Present: " << *it << std::endl;

	auto it2 = S.lower_bound(-1); // instance >= -1
	auto it3 = S.upper_bound(-1); // instance > -1
	std::cout << *it2 << " " << *it3 << std::endl; // -1 && 1

	auto it4 = S.upper_bound(1);
	if (it4 == S.end()) // If element is not found it will return the end of the set
		std::cout << "Cannot find instance greater than given value." << std::endl;
	else std::cout << "Found: " << *it4 << std::endl;

	S.erase(2);
	it4 = S.upper_bound(1);
	if (it4 == S.end())
		std::cout << "Cannot find instance greater than given value." << std::endl;
	else std::cout << "Found: " << *it4 << std::endl;
}

void mapDemo()
{
	std::map<int, int> M;
	M[1] = 100;
	M[2] = -1;
	M[3] = 200;
	M[100023] = 1;

	std::map<char, int> cnt;
	std::string name{ "Parampreet Singh" };

	for (char c : name)
	{
		cnt[c]++;
	}

	std::cout << cnt['a'] << " " << cnt['z'] << std::endl;

	auto search = M.find(1);
	if (search != M.end()) 
		std::cout << "Found " << search->first << " " << search->second << '\n';
	else std::cout << "Not found\n";

	M.erase(1 );

	search = M.find(1);
	if (search != M.end())
		std::cout << "Found " << search->first << " " << search->second << '\n';
	else std::cout << "Not found\n";
}

void intInRange() // Algorithm
{
	// Finding which pair an integer lies in

	std::set<std::pair<int, int>> S;
	
	S.insert({ 401, 450 });
	S.insert({2, 3});
	S.insert({ 10, 20});
	S.insert({ 30, 400});
	
	// 2, 3
	// 10, 20
	// 30, 400
	// 401, 450

	int point{ 460 }; // Input

	auto it = S.upper_bound({ point, INT_MAX }); 
	if (it == S.begin())
	{
		std::cout << "Not present \n";
		return;
	}
	
	it--;
	std::pair<int, int> current = *it;
	if ((*it).first <= point && point <= (*it).second)
		std::cout << "Present: " << (*it).first << " " << (*it).second << std::endl;
	else std::cout << "Not in interval" << std::endl;
}

void unorderedMapDemo()
{
	std::map<char, int> M;
	std::unordered_map<char, int> U;

	std::string str{ "Parampreet Singh" };

	// Operation - ordered, unordered map
	// add(key, value) - logN, O(1)
	// erase(key) - logN, O(1)

	for (char c : str) M[c]++; // O(NlogN) N = |s| (size of string)

	for (char c : str) U[c]++; // O(N)

}


int main()
{
	void unorderedMapDemo();

	return 0;
}