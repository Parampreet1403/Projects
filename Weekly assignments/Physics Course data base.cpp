#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
#include <sstream>


void print_vector(std::vector<std::string> name) {
	if (!name.empty()) {
		for (auto iterator = name.begin(); iterator != name.end(); iterator++) {
			std::cout << *iterator << std::endl;
		}
	}
}

void year_print_vector(std::vector<std::string> name, std::string i) {
	if (!name.empty()) {
		for (auto iterator = name.begin(); iterator != name.end(); iterator++) {
			std::string iterator_str(1, (*iterator)[5]);
			if (iterator_str == i) {
				std::cout << *iterator << std::endl;
			}
		}	
	}
}

void vector_sort_code(std::vector<std::string> name) {
	sort(name.begin(), name.end());
	if (!name.empty()) {
		for (auto iterator = name.begin(); iterator != name.end(); iterator++) {
			std::cout << *iterator << std::endl;
		}
	}
}

void vector_sort_title(std::vector<std::string> name) {
	sort(name.begin(), name.end(), [](std::string a, std::string b) {
		return a[11] < b[11]; // PHYS xxxxx Aaaaaa A =[11]
		});
	if (!name.empty()) {
		for (auto iterator = name.begin(); iterator != name.end(); iterator++) {
			std::cout << *iterator << std::endl;
		}
	}
}

int main() {

	bool gate{ true };
	std::vector<std::string> code_vector{};
	std::vector<std::string> course_vector{};
	std::vector<std::string> full_course_vector{};
	std::string answer{};

	//Asks users to store courses
	while (gate == true) {

		std::cout << "Would you like to enter a course?" << std::endl; 
		std::cout << "Please enter y or n." << std::endl; 
		std::getline(std::cin, answer);

		if (answer == "y") {

			std::cout << "Please enter the course code and title. " << std::endl;
			std::cout << "Example input: 30762 Object-Oriented Programming in C++." << std::endl;
			std::string my_string{};
			std::getline(std::cin, my_string);
			const std::string prefix{ "PHYS" };
			std::cout << "The course code and title you entered was: " << prefix << " " << my_string << std::endl;

			//Separates code and title and stores them into two different vectors
			std::string delimiter{ " " };
			int location{};
			std::string code{};
			
			location = my_string.find(delimiter); //finds space between code and course
			code = my_string.substr(0, location);
			my_string.erase(0, location + delimiter.length()); //erases code and only leaves course

			code_vector.push_back(code);
			course_vector.push_back(my_string);
			std::stringstream ss;
			ss << prefix + " " + code + " " + my_string; //use of stringstream
			full_course_vector.push_back(ss.str());
		}
		else if (answer == "n") {
			std::cout << "Thank you for storing your data. " << std::endl;
			break;
		}
		else {
			std::cerr << "please either enter y or n." << std::endl;
		}
	}

	//Prints all courses stored
	std::cout << "Courses stored: " << std::endl;
	print_vector(full_course_vector);

	//Asks user to print courses stored from a specific year
	while (gate == true) {
		std::cout << "Would you like to print out course codes stored for a particular year?" << std::endl;
		std::cout << "Please enter the year 1, 2, 3, 4" << std::endl;
		std::getline(std::cin, answer);
		if (answer == "1" || "2" || "3" || "4") {
			std::cout << "Courses for year " << answer << ": "<< std::endl;
			year_print_vector(full_course_vector, answer);
			break;
		}
	}

	//Sorts course by code or title
	while (gate == true) {

		std::cout << "Please enter c if you would like to sort the courses by code or t for title." << std::endl;
		std::getline(std::cin, answer);
		if (answer == "c") {
			// sort by code
			vector_sort_code(full_course_vector);
			break;
		}
		else if (answer == "t") {
			//sort by title
			vector_sort_title(full_course_vector);
			break;
		}
		else {
			std::cerr << "Please enter either c or t." << std::endl;
		}
	}

	return 0;
}
