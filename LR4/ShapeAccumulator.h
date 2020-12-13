#ifndef SHAPE_ACCUM
#define SHAPE_ACCUM

#include "IShape.h"

class ShapeAccumulator {
private:
	std::list<IShape*> shapeList;
public:
	ShapeAccumulator() {

	}

	~ShapeAccumulator() {
		for (auto it = shapeList.begin(); it != shapeList.end(); ) {
			//if exist
			if (!(*it)) {
				it = shapeList.erase(it);
			}
			else {
				++it;
			}
		}
	}

	void add(IShape* shape) {
		shapeList.push_back(shape);
	}

	void addAll(std::list<IShape*> *otherShapeList) {
		for (IShape* otherShape : *otherShapeList) {
			add(otherShape);
		}
	}

	IShape* getMaxAreaShape() {
		double maxS = 0;
		IShape* maxAreaShape = nullptr;
		for (IShape* shape : shapeList) {
			if (shape->getS() > maxS) {
				maxS = shape->getS();
				maxAreaShape = shape;
			}
		}
		return maxAreaShape;
	}

	IShape* getMinAreaShape() {
		double minS = std::numeric_limits<double>::max();
		IShape* minAreaShape = nullptr;
		for (IShape* shape : shapeList) {
			if (shape->getS() < minS) {
				minS = shape->getS();
				minAreaShape = shape;
			}
		}
		return minAreaShape;
	}

	IShape* getMaxPerimeterShape() {
		double maxP = 0;
		IShape* maxPerimeterShape = nullptr;
		for (IShape* shape : shapeList) {
			if (shape->getP() > maxP) {
				maxP = shape->getS();
				maxPerimeterShape = shape;
			}
		}
		return maxPerimeterShape;
	}

	IShape* getMinPerimeterShape() {
		double minP = std::numeric_limits<double>::max();
		IShape* minPerimeterShape = nullptr;
		for (IShape* shape : shapeList) {
			if (shape->getP() < minP) {
				minP = shape->getS();
				minPerimeterShape = shape;
			}
		}
		return minPerimeterShape;
	}

	double getTotalArea() {
		double s = 0;

		for (IShape* shape : shapeList) {
			s += shape->getS();
		}

		return s;
	}

	double getTotalPerimeter() {
		double p = 0;

		for (IShape* shape : shapeList) {
			p += shape->getP();
		}

		return p;
	}
};

#endif