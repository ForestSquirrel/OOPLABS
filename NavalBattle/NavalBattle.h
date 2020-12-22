#ifndef NAVAL_BATTLE
#define NAVAL_BATTLE

#include <iostream>
#include <stdexcept>
#include <random>
#include <ctime>
#include <string>
#include <sstream>

#include "utility.h"

//border is used only when ships set


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

	int
		firstPlayerPoints = 0,
		secondPlayerPoints = 0;

	std::string
		firstPlayerName,
		secondPlayerName;

	Title FirstPlayerField[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };

	Title FirstPlayerFieldForEnemy[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };

	//AI uses it, or the second player
	Title SecondPlayerField[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };

	//for user's game, it shows where you hit
	Title SecondPlayerFieldForEnemy[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };
public:
	//FUNCTIONS
	int getFirstPlayerPoints() {
		return firstPlayerPoints;
	}

	int getSecondPlayerPoints() {
		return secondPlayerPoints;
	}
	void clear() {
		firstPlayerName.clear();
		secondPlayerName, clear();
		for (int y = 0; y < FIELD_SIZE; ++y) {
			for (int x = 0; x < FIELD_SIZE; ++x) {
				FirstPlayerField[y][x] = Title::EMPTY;
				SecondPlayerField[y][x] = Title::EMPTY;
				FirstPlayerFieldForEnemy[y][x] = Title::EMPTY;
				SecondPlayerFieldForEnemy[y][x] = Title::EMPTY;
			}
		}

		placeAllShips(Player::Human);
		placeAllShips(Player::Opponent);
	}
	//recieves only player inputted coordinates!
	//that means, (1..10; 1..10)
	//fills titles for destroyed if player destroyed the ship
	void ifShipDestroyed(const int& x, const int& y,
		const std::string& shooter) {

		auto opponentField = SecondPlayerField;
		auto displayField = SecondPlayerFieldForEnemy;

		if (shooter == firstPlayerName) {
			//do nothing
		}
		else if (shooter == secondPlayerName) {
			opponentField = FirstPlayerField;
			displayField = FirstPlayerFieldForEnemy;
		}
		else {
			throw(std::invalid_argument("There is no such player"));
		}

		if (((x * y) == 0) || (x == 11) || (y == 11)) {
			throw(std::invalid_argument("Fictional coordinates in ifShipDestroyed method!!!"));
		}

		//x,y is hit by definition
		int xForCheck = x - 1,
			yForCheck = y - 1;

		//we imply there's no ships in the of curr title
		bool noShips = true;

		for (int yForCheck = y - 1; (yForCheck < y + 2) && noShips; ++yForCheck) {
			for (int xForCheck = x - 1; (xForCheck < x + 2) && noShips; ++xForCheck) {
				if (opponentField[yForCheck][xForCheck] == Title::SHIP) {
					noShips = false;
				}
			}
		}

		if (!noShips) {
			return;
		}

		opponentField[yForCheck + 1][xForCheck + 1] = Title::DESTROYED_SHIP;
		displayField[yForCheck + 1][xForCheck + 1] = Title::DESTROYED_SHIP;

		int xForNextIteration = -1,
			yForNextIteration = -1;

		for (int yForCheck = y - 1; yForCheck < y + 2; ++yForCheck) {
			for (int xForCheck = x - 1; xForCheck < x + 2; xForCheck++) {
				if (opponentField[yForCheck][xForCheck] == Title::BORDER) {
					displayField[yForCheck][xForCheck] = Title::MISS;
					opponentField[yForCheck][xForCheck] = Title::MISS;
				}
				else if (opponentField[yForCheck][xForCheck] == Title::HIT) {
					xForNextIteration = xForCheck;
					yForNextIteration = yForCheck;
				}
			}
		}

		if (xForNextIteration != -1) {
			ifShipDestroyed(xForNextIteration, yForNextIteration, shooter);
		}


	}

	//unless throws an exception if no titles on curr field
	//changes the x and y arguments: that means, returns the empty title,
	//which is okay for chechking the entire collision box. or throws an exception if no titles on curr field;
	void fastCheck(int& x, int& y, const Ship& shipType, Title currField[FIELD_SIZE][FIELD_SIZE]) {
		do {
			//we take 0..10-shipLength titles, first title is always border so it'd be ok
			y = std::rand() % (FIELD_SIZE - (int)shipType + OFFSET);
			x = std::rand() % (FIELD_SIZE_WITHOUT_BORDERS);
		} while (currField[y][x] == Title::SHIP);

		return;
	}

	//check if it's possible to put a ship of a certain size
	//onto a certain [y][x] title, unless throws an exception
	//check if it's possible to put a ship of a certain size
	//onto a certain [y][x] title
	void collisionCheck(int& x, int& y, int& verOrHor, const Ship& shipType, Title currField[FIELD_SIZE][FIELD_SIZE]) {
		int	putCounter = 0;

		bool collisionMet = true;

		while (collisionMet) {
			if (putCounter > 50000) {
				if (currField == FirstPlayerField) {
					throw(std::logic_error("There's no place on the player's field to place the ship!"));

				}
				else {
					throw(std::logic_error("There's no place on the enemy's field to place the ship!"));
				}
			}

			//we check the single title before collision check, it'd be faster
			//counter will throw an exception if currField is full
			//we check for an exception in main method.
			//anyway, if it's thrown, something's definitely wrong
			fastCheck(x, y, shipType, currField);

			//now we check collisions
			//but we skip it for large ship
			if (shipType == Ship::Large) {
				return;
			}

			verOrHor = std::rand() % 2;
			//if it's vertical
			if (verOrHor % 2 == 1) {
				std::swap(x, y);
			}

			//we imply this iteration would be with no collisions
			collisionMet = false;
			//ver
			if (verOrHor % 2 == 0) {
				for (int y_iter = y; (y_iter < (y + int(shipType))) && !collisionMet; ++y_iter) {
					for (int x_iter = x; (x_iter < (x + BORDER_OFFSET)) && !collisionMet; ++x_iter) {
						if (currField[y_iter][x_iter] == Title::SHIP) {
							collisionMet = true;
						}
					}
				}
			}

			//hor
			else {
				for (int x_iter = x; (x_iter < (x + int(shipType))) && !collisionMet; ++x_iter) {
					for (int y_iter = y; (y_iter < (y + BORDER_OFFSET)) && !collisionMet; ++y_iter) {
						if (currField[y_iter][x_iter] == Title::SHIP) {
							collisionMet = true;
						}
					}
				}
			}

			++putCounter;
		}

		return;
	}

	//places an one ship
	void placeShip(Ship shipType, Title(*currField)[FIELD_SIZE]) {
		int x = 0,
			y = 0,
			verOrHor = 0;

		collisionCheck(x, y, verOrHor, shipType, currField);

		//vertical
		if (verOrHor % 2 == 0) {
			for (int y_iter = y; y_iter < (y + (int)shipType); ++y_iter) {
				for (int x_iter = x; x_iter < (x + BORDER_OFFSET); ++x_iter) {
					if ((y_iter != y && (y_iter != (y + (int)shipType - OFFSET))) && (x_iter == (x + OFFSET))) {
						currField[y_iter][x_iter] = Title::SHIP;
					}
					else {
						currField[y_iter][x_iter] = Title::BORDER;
					}
				}
			}
		}
		//horizontal
		else {
			for (int x_iter = x; x_iter < (x + (int)shipType); ++x_iter) {
				for (int y_iter = y; y_iter < (y + BORDER_OFFSET); ++y_iter) {
					if ((x_iter != x && (x_iter != (x + (int)shipType - OFFSET))) && (y_iter == (y + OFFSET))) {
						currField[y_iter][x_iter] = Title::SHIP;
					}
					else {
						currField[y_iter][x_iter] = Title::BORDER;
					}
				}
			}
		}

	}

	//places all the ships for an player
	void placeAllShips(const Player& player) {
		auto currField = FirstPlayerField;

		if (player == Player::Opponent) {
			currField = SecondPlayerField;
		}

		placeShip(Ship::Large, currField);

		placeShip(Ship::Big, currField);
		placeShip(Ship::Big, currField);

		placeShip(Ship::Medium, currField);
		placeShip(Ship::Medium, currField);
		placeShip(Ship::Medium, currField);

		placeShip(Ship::Small, currField);
		placeShip(Ship::Small, currField);
		placeShip(Ship::Small, currField);
		placeShip(Ship::Small, currField);
	}

public:
	void setfirstPlayerName(std::string &newName) {
		this->firstPlayerName = newName;
		return;
	}

	std::string getFirstPlayerName() {
		return firstPlayerName;
	}

	void setSecondPlayerName(std::string &newName) {
		this->secondPlayerName = newName;
		return;
	}

	std::string getSecondPlayerName() {
		return secondPlayerName;
	}

	//eastern egg
	void korol() {

	}

	void shoot(std::string shooter, std::string stringCoords) {
		auto fieldToShoot = SecondPlayerField;
		auto displayFieldForShooter = SecondPlayerFieldForEnemy;

		if (shooter == firstPlayerName) {
			//do nothing
		}
		else if (shooter == secondPlayerName) {
			fieldToShoot = FirstPlayerField;
			displayFieldForShooter = FirstPlayerFieldForEnemy;
		}
		else {
			throw(std::invalid_argument("There is no such player"));
		}

		int x = -1,
			y = -1;

		//parse coords
		std::pair<int, int> coords = IdToIndex(stringCoords);
		x = coords.first + 1;
		y = coords.second + 1;


		if (fieldToShoot[y][x] == Title::SHIP) {
			fieldToShoot[y][x] = Title::HIT;
			displayFieldForShooter[y][x] = Title::HIT;

			if (shooter == firstPlayerName) {
				firstPlayerPoints++;
			}
			else {
				secondPlayerPoints++;
			}
			ifShipDestroyed(x, y, shooter);
		}
		else if ((fieldToShoot[y][x] == Title::EMPTY) || (fieldToShoot[y][x] == Title::BORDER)) {
			fieldToShoot[y][x] = Title::MISS;
			displayFieldForShooter[y][x] = Title::MISS;
		}
	}

	//if blank returns field of your hits
	//if no, returns your field
	std::string getBlankFieldByPlayer(std::string username, bool blank) {
		auto currField = SecondPlayerFieldForEnemy;

		if (!blank) {
			currField = FirstPlayerField;
		}

		if (username == firstPlayerName) {
			//do nothing
		}
		else if (username == secondPlayerName) {
			if (blank) {
				currField = FirstPlayerFieldForEnemy;
			}
			else {
				currField = SecondPlayerField;
			}
		}
		else {
			throw(std::invalid_argument("There is no such player"));
		}

		std::string stringFieldToReturn = "`";

		for (int y = 1; y < FIELD_SIZE - 1; ++y) {
			for (int x = 1; x < FIELD_SIZE - 1; ++x) {
				switch (currField[y][x]) {
				case Title::EMPTY:
					stringFieldToReturn += "0";
					break;
				case Title::SHIP:
					stringFieldToReturn += "S";
					break;
				case Title::BORDER:
					stringFieldToReturn += "B";
					break;
				case Title::HIT:
					stringFieldToReturn += "H";
					break;
				case Title::MISS:
					stringFieldToReturn += "M";
					break;
				case Title::DESTROYED_SHIP:
					stringFieldToReturn += "D";
					break;
				}
				stringFieldToReturn += " ";
			}
			stringFieldToReturn += "\n";
		}
		stringFieldToReturn += "\n";
		stringFieldToReturn += "`";

		return stringFieldToReturn;
	}

	//returns matrix, for ascii art
	Title(*getBlankFieldByPlayerMatrix(std::string username, bool blank))[FIELD_SIZE] {
		auto currField = SecondPlayerFieldForEnemy;

		if (!blank) {
			currField = FirstPlayerField;
		}

		if (username == firstPlayerName) {
			//do nothing
		}
		else if (username == secondPlayerName) {
			if (blank) {
				currField = FirstPlayerFieldForEnemy;
			}
			else {
				currField = SecondPlayerField;
			}
		}
		else {
			throw(std::invalid_argument("There is no such player"));
		}

		return currField;
	}
	bool isMiss(std::pair<int, int> &coords, const std::string& username) {
		int x = coords.first + 1;
		int y = coords.second + 1;
	auto currField = SecondPlayerField;
		if (username == secondPlayerName) {
			currField = FirstPlayerField;
		}
		if (currField[y][x] == Title::MISS) {
			return true;
		}
		else {
			return false;
		}
	}

	GameHandler(std::string firstPlayerName, std::string secondPlayerName) {
		this->firstPlayerName = firstPlayerName;
		this->secondPlayerName = secondPlayerName;

		std::srand(std::time(nullptr));

		placeAllShips(Player::Human);
		placeAllShips(Player::Opponent);
	};

	GameHandler() {
		std::srand(std::time(nullptr));

		placeAllShips(Player::Human);
		placeAllShips(Player::Opponent);
	};

	~GameHandler() {

	};
};

#endif