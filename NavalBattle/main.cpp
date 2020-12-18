#include "NavalBattle.h"

int main() {
	try {
		GameHandler GH;
		GH.handleGame();
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}

	return 0;
}