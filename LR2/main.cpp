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
		getShapeByInd(shapeList, minSInd)->getName() << std::endl <<

		"And now some testing for constructors with names (used in Lab 6):"
		<< std::endl << Square(5, "Cube").getName()
		<< std::endl << Rectangle(5, 10, "Brick").getName()
		<< std::endl << Circle(5, "Plate").getName()
		<< std::endl << Triangle(0, 0, 5, 5, 10, 0, "Triangled figure").getName() << std::endl;

	Circle newCircle("New circle", "50");
	Square newSquare("New square", "80");
	Rectangle newRectangle("New rect", "10 20");
	Triangle newTriangle("New triangle", "0 0 10 0 0 5");

	return 0;
}