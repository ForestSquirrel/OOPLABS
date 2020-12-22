#pragma once

#include <utility>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <string_view>

//this file has some utility functions for better handling
//discord api. Since we can only work with messages we need 
//some parsing and askii art to make our bot user-friendly

//utility stuff for gameHandler
enum class Title {
	EMPTY,
	SHIP,
	BORDER,
	HIT,
	MISS,
	DESTROYED_SHIP
};

enum class Ship {
	//including borders!
	Large = 6,
	Big = 5,
	Medium = 4,
	Small = 3
};

enum class Player {
	Human,
	Opponent
};

const int
FIELD_SIZE = 12,
FIELD_SIZE_WITHOUT_BORDERS = 10,
OFFSET = 1,
BORDER_OFFSET = 3;

//Discord is kinda tricky thing when it comes to making UI
//since we cant realy use images to show users what is  happening
//Here comes the solution ASCII ART
//It may sound strange, but discord supports embeds and that's
//there ASCII art comes in handy

//ASCII art constants 
const std::string line =	"+===+===+===+===+===+===+===+===+===+===+===+\n";
const std::string letters = "|   | A | B | C | D | E | F | G | H | I | J |\n";
const std::string A =		"| 1 |";
const std::string B =		"| 2 |";
const std::string C =		"| 3 |";
const std::string D =		"| 4 |";
const std::string E =		"| 5 |";
const std::string F =		"| 6 |";
const std::string G =		"| 7 |";
const std::string H =		"| 8 |";
const std::string I =		"| 9 |";
const std::string J =		"| 10|";
const std::string ship =	"###";
const std::string water =	"~~~";
const std::string miss =	"<o>";
const std::string Dship =	">#<"; //destroyed ship or damaged ship
const std::string SP =		"|"; //spacer

std::string ASCIIartField(Title (*matrix)[FIELD_SIZE]) {
	std::string art;
	auto currField = matrix;
	//header
	art += "`";
	art += line;
	art += letters;
	art += line;
	for (int y = 1; y < FIELD_SIZE - 1; ++y) {
		switch (y) {
		case 1:
			art += A;
			break;
		case 2:
			art += B;
			break;
		case 3:
			art += C;
			break;
		case 4:
			art += D;
			break;
		case 5:
			art += E;
			break;
		case 6:
			art += F;
			break;
		case 7:
			art += G;
			break;
		case 8:
			art += H;
			break;
		case 9:
			art += I;
			break;
		case 10:
			art += J;
			break;
		}
		for (int x = 1; x < FIELD_SIZE - 1; ++x) {
			switch (currField[y][x]) {
			case Title::EMPTY:
				art += water;
				art += SP;
				break;
			case Title::SHIP:
				art += ship;
				art += SP;
				break;
			case Title::BORDER:
				art += water;
				art += SP;
				break;
			case Title::HIT:
				art += Dship;
				art += SP;
				break;
			case Title::MISS:
				art += miss;
				art += SP;
				break;
			case Title::DESTROYED_SHIP:
				art += Dship;
				art += SP;
				break;
			}
		}
		art += "\n";
		art += line;
	}
	art += "`";
	return art;
}
//input parsing
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