#include <iostream>
#include "ShapeAccumulator.h"

int main() {
	Circle ci1(0.5, "Circle 1");
	Circle ci2(0.75, "Circle 2");

	Square sq1(1, "Sqaure 1");
	Square sq2(2, "Square 2");

	Rectangle re1(1, 2, "Rectangle 1");
	Rectangle re2(2, 3, "Rectangle 2");

	Triangle tr1(0, 0, 0, 1, 1, 0, "Triangle 1");
	Triangle tr2(0, 0, 0, 3, 2, 2, "Triangle 2");

	std::list<IShape*> shapeList{ &ci1, &ci2, &sq1, &sq2, &re1, &re2, &tr1, &tr2 };

	Circle ci3(0.9, "Circle 3");

	ShapeAccumulator shAc;
	shAc.add(&ci3);
	shAc.addAll(&shapeList);

	std::cout
		<< "Max area: " << shAc.getMaxAreaShape()->getName() << std::endl
		<< "Max perimeter: " << shAc.getMaxPerimeterShape()->getName() << std::endl
		<< "Min area: " << shAc.getMaxPerimeterShape()->getName() << std::endl
		<< "Min perimeter: " << shAc.getMinPerimeterShape()->getName() << std::endl
		<< "Total area: " << shAc.getTotalArea() << std::endl
		<< "Total perimeter: " << shAc.getTotalPerimeter() << std::endl;

	return 0;
}