#ifndef NAVAL_BATTLE
#define NAVAL_BATTLE

#include <iostream>
#include <stdexcept>
#include <random>
#include <ctime>

enum class Title {
	EMPTY,
	SHIP,
	BORDER,
	HIT
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
	Blank,
	Opponent
};

const int
FIELD_SIZE = 12,
FIELD_SIZE_WITHOUT_BORDERS = 10,
OFFSET = 1,
BORDER_OFFSET = 3;

class GameHandler {
private:
	//both fields are 2d arrays, it's simple

	//fictional borders is something like this
	//F F F F F
	//F O O O F
	//F O O O F
	//F O O O F
	//F F F F F
	//where zeroes are meant to be the real field to play

	//it's just easy to handle collisions with fictional borders
	//like this situation (corner of the field, tiny ship)
	//O B B B O O O...
	//O B X B O O O
	//O B B B O O O
	//O O O O O O O
	//that 1-title ship is on the top of the field, and it's
	//the easy way to calculate collisions, simply with rectangles

	static Title PlayerField[FIELD_SIZE][FIELD_SIZE];

	//for user's game, it shows where you hit
	static Title BlankField[FIELD_SIZE][FIELD_SIZE];

	static Title OpponentField[FIELD_SIZE][FIELD_SIZE];


	//FUNCTIONS


	Title(*getFieldByPlayer(const Player& player))[FIELD_SIZE];

	//simply checks if title is empty or border (if bool is false)
	//use this for hit functions
	bool isOccupied(int y, int x, const Player& player, bool borderCounts);

	//changes the x and y arguments: that means, returns the empty title,
	//which is okay for chechking the entire collision box.
	//unless throws an exception if no titles on curr field
	void fastCheck(int& x, int& y, const Ship& shipType, Title currField[FIELD_SIZE][FIELD_SIZE]);

	//check if it's possible to put a ship of a certain size
	//onto a certain [y][x] title, unless throws an exception
	void collisionCheck(int &x, int &y, int &verOrHor, const Ship& shipType, Title currField[FIELD_SIZE][FIELD_SIZE]);

	//places an one ship
	void placeShip(Ship shipType, Title(*currField)[FIELD_SIZE]);

	//places all the ships for an player
	void placeAllShips(const Player& player);

	//shows any field
	void showField(const Player& player, bool debug);

	//shows two fields, the right is invisible
	void showGame(const Player& opponent, bool debug);

public:
	void handleGame();

	GameHandler();
	~GameHandler();
};

#endif