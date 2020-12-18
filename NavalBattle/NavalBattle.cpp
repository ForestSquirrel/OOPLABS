#include "NavalBattle.h"

Title GameHandler::PlayerField[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };
Title GameHandler::OpponentField[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };
Title GameHandler::BlankField[FIELD_SIZE][FIELD_SIZE] = { Title::EMPTY };

Title (*GameHandler::getFieldByPlayer(const Player& player))[FIELD_SIZE] {
	switch (player) {
	case Player::Human:
		return PlayerField;
		break;
	case Player::Blank:
		return BlankField;
		break;
	case Player::Opponent:
		return OpponentField;
		break;
	}
}

//simply checks if title is empty or border (if bool is false)
bool GameHandler::isOccupied(int y, int x, const Player& player, bool borderCounts) {
	auto currField = getFieldByPlayer(player);

	if (borderCounts) {
		if (currField[y][x] == Title::EMPTY) {
			return true;
		}
	}
	else {
		if (currField[y][x] == Title::EMPTY) {
			return true;
		}
		else if (currField[y][x] == Title::BORDER) {
			return true;
		}
	}

	return false;
}

//changes the x and y arguments: that means, returns the empty title,
//which is okay for chechking the entire collision box. or throws an exception if no titles on curr field;
void GameHandler::fastCheck(int& x, int& y, const Ship& shipType, Title currField[FIELD_SIZE][FIELD_SIZE]) {
	do {
		//we take 0..10-shipLength titles, first title is always border so it'd be ok
		y = std::rand() % (FIELD_SIZE - (int)shipType + OFFSET);
		x = std::rand() % (FIELD_SIZE_WITHOUT_BORDERS);
	} while (currField[y][x] == Title::SHIP);

	return;
}

//check if it's possible to put a ship of a certain size
//onto a certain [y][x] title
void GameHandler::collisionCheck(int &x, int &y, int &verOrHor, const Ship& shipType, Title currField[FIELD_SIZE][FIELD_SIZE]){
	int	putCounter = 0;

	bool collisionMet = true;

	while (collisionMet) {
		if (putCounter > 50000) {
			if (currField == PlayerField) {
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


void GameHandler::placeShip(Ship shipType, Title(*currField)[FIELD_SIZE]) {
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

void GameHandler::placeAllShips(const Player& player) {
	Title (*currField)[FIELD_SIZE] = getFieldByPlayer(player);

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

//debug shows 12*12 field (with fictional borders)
void GameHandler::showField(const Player& player, bool debug) {
	auto currField = getFieldByPlayer(player);

	for (int y = 0 + !debug; y < FIELD_SIZE - !debug; ++y) {
		for (int x = 0 + !debug; x < FIELD_SIZE - !debug; ++x) {
			switch (currField[y][x]) {
			case Title::EMPTY:
				std::cout << "0";
				break;
			case Title::SHIP:
				std::cout << "\x1B[31mS\033[0m";
				break;
			case Title::BORDER:
				std::cout << "\x1B[32mB\033[0m";
				break;
			case Title::HIT:
				std::cout << "X";
				break;
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}


//debug shows 12*12 field (with fictional borders)
//in handleGame() debug is false (by default)
void GameHandler::showGame(const Player& opponent, bool debug) {
	auto opponentField = getFieldByPlayer(opponent);
	auto currField = PlayerField;

	for (int y = 0 + !debug; y < FIELD_SIZE - !debug; ++y) {
		for (int x = 0 + !debug; x < FIELD_SIZE - !debug; ++x) {
			switch (currField[y][x]) {
			case Title::EMPTY:
				std::cout << "0";
				break;
			case Title::SHIP:
				std::cout << "\x1B[31mS\033[0m";
				break;
			case Title::BORDER:
				std::cout << "\x1B[32mB\033[0m";
				break;
			case Title::HIT:
				std::cout << "X";
				break;
			}
			std::cout << " ";
		}

		std::cout << "\t\t";

		for (int x = 0 + !debug; x < FIELD_SIZE - !debug; ++x) {
			switch (opponentField[y][x]) {
			case Title::EMPTY:
				std::cout << "0";
				break;
			case Title::SHIP:
				std::cout << "\x1B[31mS\033[0m";
				break;
			case Title::BORDER:
				std::cout << "\x1B[32mB\033[0m";
				break;
			case Title::HIT:
				std::cout << "\033[3;42;30mX\033[0m";
				break;
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void GameHandler::handleGame() {
	//colored text examples, useful!
	/*printf("\n");
	printf("\x1B[31mTexting\033[0m\t\t");
	printf("\x1B[32mTexting\033[0m\t\t");
	printf("\x1B[33mTexting\033[0m\t\t");
	printf("\x1B[34mTexting\033[0m\t\t");
	printf("\x1B[35mTexting\033[0m\n");

	printf("\x1B[36mTexting\033[0m\t\t");
	printf("\x1B[36mTexting\033[0m\t\t");
	printf("\x1B[36mTexting\033[0m\t\t");
	printf("\x1B[37mTexting\033[0m\t\t");
	printf("\x1B[93mTexting\033[0m\n");

	printf("\033[3;42;30mTexting\033[0m\t\t");
	printf("\033[3;43;30mTexting\033[0m\t\t");
	printf("\033[3;44;30mTexting\033[0m\t\t");
	printf("\033[3;104;30mTexting\033[0m\t\t");
	printf("\033[3;100;30mTexting\033[0m\n");

	printf("\033[3;47;35mTexting\033[0m\t\t");
	printf("\033[2;47;35mTexting\033[0m\t\t");
	printf("\033[1;47;35mTexting\033[0m\t\t");
	printf("\t\t");
	printf("\n");*/

	//for random
	std::srand(std::time(nullptr));
	//for color

	placeAllShips(Player::Human);
	placeAllShips(Player::Opponent);

	auto blankField = getFieldByPlayer(Player::Blank);
	auto enemyField = getFieldByPlayer(Player::Opponent);

	showGame(Player::Blank, false);

	std::cout << std::endl
		<< "Welcome to Naval Battle! Please type row, then column to shoot!" << std::endl
		<< "It's 1 to 10. Example: 2 3" << std::endl;

	int x = 0,
		y = 0,
		points = 0;

	while (points < 23) {
		std::string line;
		getline(std::cin, line);

		try {
			bool goodInput = false;
			while (!goodInput) {
				if (!line.empty()) {
					std::stringstream ss(line);
					ss >> y >> x;
				}
				if ((y <= 0 || y > 10) || (x <= 0 || x > 10)) {
					std::cout << "Wrong numbers. It's 1 to 10. Try again." << std::endl;
				}
				else {
					goodInput = true;
				}
			}
		}
		catch (std::exception & e) {
			std::cout << e.what() << std::endl;
			return;
		}

		if (enemyField[y][x] == Title::SHIP) {
			enemyField[y][x] = Title::HIT;
			blankField[y][x] = Title::HIT;
		}
		//clear screen
		std::cout << "\x1B[2J\x1B[H";

		showGame(Player::Blank, false);
	}
}


GameHandler::GameHandler() {

}

GameHandler::~GameHandler() {

}