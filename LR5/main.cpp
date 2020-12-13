#include "Serialization.h"

int main() {
	try {
		std::list<IShape*> list;

		Circle circle("Kolobok", "15");
		Square square("Dice", "20");
		Rectangle rectangle("Brick", "10 20");
		Triangle triangle("Pyramid", "0 0 10 0 0 5");

		Serializator ser;

		list.push_back(&circle);
		list.push_back(&square);
		list.push_back(&rectangle);
		list.push_back(&triangle);

		ser.serialize(&list);
		std::list<IShape*> readFromFileList = ser.deserialize("shapes.json");

		for (auto x : readFromFileList) {
			std::cout << x->getJson() << std::endl;
		}
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}