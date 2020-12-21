#pragma once

#include <utility>
#include <string>
#include <stdexcept>
#include <algorithm>

//this file has some utility functions for better handling
//discord api. Since we can only work with messages we need 
//some parsing and askii art to make our bot user-friendly



std::pair<int, int> IdToIndex(std::string& Id) { // this function converts string to pair e.g. a1 -> <0, 0> or g8 -> <6, 7>
	if (Id.empty() || Id.size() > 3) {
		throw std::invalid_argument("Wrong index");
	}
	char letter = Id.at(0);
	std::string temp;
	for (auto i = 1; i < Id.size(); i++) {
		if (std::isdigit(Id.at(i)))
			temp += Id.at(i);
		else
			throw std::invalid_argument("Wrong index");
	}
	int number = stoi(temp) - 1; //minus 1 since starting index of an array is 0
	if (number > 10)
		throw std::invalid_argument("Wrong index");
	switch (letter)
	{
	case 'a':
		return std::make_pair(0, number);
	case 'b':
		return std::make_pair(1, number);
	case 'c':
		return std::make_pair(2, number);
	case 'd':
		return std::make_pair(3, number);
	case 'e':
		return std::make_pair(4, number);
	case 'f':
		return std::make_pair(5, number);
	case 'g':
		return std::make_pair(6, number);
	case 'h':
		return std::make_pair(7, number);
	case 'i':
		return std::make_pair(8, number);
	case 'j':
		return std::make_pair(9, number);
	default:
		throw std::invalid_argument("Wrong index");
	}
}