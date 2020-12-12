#include "IShape.h"

IShape* getShapeByInd(std::list<IShape*> list, int ind) {
	try {
		if (ind >= (int)list.size())
			throw(std::exception("Wrong index, list is smaller."));
		int i = 0;
		for (IShape* shape : list) {
			if (i == ind)
				return shape;
			++i;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return nullptr;
}