#include "Serialization.h"

int main() {
	try {
		std::list<IShape*> list;

		Circle circle(15);
		Square square(20);
		Rectangle rectangle(10, 30);
		Triangle triangle(1, 2, 3, 4, 10, 5);

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