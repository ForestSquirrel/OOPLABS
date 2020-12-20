#include "IShape.h"

int main() {
	Circle ci1(1);
	Circle ci2(2);
	
	Square sq1(1);
	Square sq2(2);

	Rectangle re1(1, 2);
	Rectangle re2(2, 3);

	Triangle tr1(0,0, 0,1, 1,0);
	Triangle tr2(0, 0, 0, 3, 2, 2);

	std::list<IShape*> shapeList{ &ci1, &ci2, &sq1, &sq2, &re1, &re2, &tr1, &tr2 };


	double sumS = 0,
		maxP = DBL_MIN,
		maxS = DBL_MIN,
		minP = DBL_MAX,
		minS = DBL_MAX,

		curP = 0,
		curS = 0;

	int maxPInd = 0,
		maxSInd = 0,
		minPInd = 0,
		minSInd = 0,

		i = 0;

	for (auto shape : shapeList) {
		curP = shape->getP();
		curS = shape->getS();
		
		sumS += curS;

		if (curP > maxP) {
			maxP = curP;
			maxPInd = i;
		}
		if (curP < minP) {
			minP = curP;
			minPInd = i;
		}

		if (curS > maxS) {
			maxS = curS;
			maxSInd = i;
		}
		if (curS < minS) {
			minS = curS;
			minSInd = i;
		}

		++i;
	}

	std::cout << "Sum sq. of shapes: " << sumS << std::endl <<

		"The highest perimeter is " << maxP << ", figure is " <<
		getShapeByInd(shapeList, maxPInd)->getName() << std::endl <<

		"The highest square is " << maxS << ", figure is " <<
		getShapeByInd(shapeList, maxSInd)->getName() << std::endl <<

		"The least perimeter is " << minP << ", figure is " <<
		getShapeByInd(shapeList, minPInd)->getName() << std::endl <<

		"The least square is " << minS << ", figure is " <<
		getShapeByInd(shapeList, minSInd)->getName() << std::endl;

	//used in lab6
	Circle newCircle("New circle", "50");
	Square newSquare("New square", "80");
	Rectangle newRectangle("New rect", "10 20");
	Triangle newTriangle("New triangle", "0 0 10 0 0 5");

	Triangle sideOnlyTriangle(1.0, 2.0, 2.0);
	std::cout << "That's the example of creating a sideOnlyTriangle with 1 2 2 sides: " <<
		std::endl << sideOnlyTriangle.getP() << " is perimeter" <<
		std::endl << sideOnlyTriangle.getS() << " is area" << std::endl;

	//testing negative arguments input
	try {
		Circle negativeCircle(-8.0);
	}
	catch (std::invalid_argument &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Square negativeSquare(-8.0);
	}
	catch (std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Rectangle negativeRectangle(-8.0, -6.0);
	}
	catch (std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Triangle negativeTriangle(-3.0, -2.0, -1.0);
	}
	catch (std::invalid_argument & e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}