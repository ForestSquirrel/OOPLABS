#ifndef ISHAPE_H
#define ISHAPE_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <stdexcept>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>

#include "json.h"

class IShape {
public:
	virtual double getP() = 0;
	virtual double getS() = 0;
	virtual std::string getName() = 0;
    virtual std::string getSpec() = 0;
	virtual nlohmann::json getJson() = 0;
};

class Circle : public IShape {
public:
	double radius;
	std::string name = "Circle";

	Circle(double radius) {
		if (radius > 0.0) {
			this->radius = radius;
		}
		else {
			throw std::invalid_argument("Negative argument in circle constructor.");
		}
	}

	Circle(double radius, std::string name) {
		if (radius > 0.0) {
			this->radius = radius;
		}
		else {
			throw std::invalid_argument("Negative argument in circle constructor.");
		}
		this->name = name;
	}
    std::string getSpec() override{
        return std::to_string(radius);
    }

	//used in lab6
	Circle(std::string name, std::string params) {
		this->name = name;
		try {
			double parsedRadius = std::stod(params);
			if (parsedRadius > 0.0) {
				this->radius = parsedRadius;
			}
			else {
				throw std::invalid_argument("Negative argument in circle constructor.");
			}
		}
		catch (std::invalid_argument & e) {
			std::cout << "Error circle constructor with " << params << " parameter"
				<< std::endl << e.what();
		}
	}

	virtual double getP() override {
		return 2 * radius * M_PI;
	}

	virtual double getS() override {
		return M_PI * radius * radius;
	}

    virtual std::string getName() override {
		return name;
	}

	virtual nlohmann::json getJson() override {
		nlohmann::json j = {
			{ "type", "circle"}, { "name", name }, { "radius", radius }
		};

	return j;
	}
};

class Square : public IShape {
public:
	double side;
	std::string name = "Square";

	Square(double side) {
		if (side > 0.0) {
			this->side = side;
		}
		else {
			throw std::invalid_argument("Negative argument in square constructor.");
		}
	}

	//used in lab6
	Square(std::string name, std::string params) {
		this->name = name;
		try {
			double parsedSide = std::stod(params);

			if (parsedSide > 0.0) {
				this->side = parsedSide;
			}
			else {
				throw std::invalid_argument("Negative argument in square constructor.");
			}
		}
		catch (std::invalid_argument & e) {
			std::cout << "Error creating square with " << params << " parameter"
				<< std::endl << e.what();
		}
	}
    std::string getSpec() override{
        return std::to_string(side);
    }

	Square(double side, std::string name) {
		if (side > 0.0) {
			this->side = side;
		}
		else {
			throw std::invalid_argument("Negative argument in square constructor.");
		}
		this->name = name;
	}

	virtual double getP() override {
		return 4 * side;
	}

	virtual double getS() override {
		return side * side;
	}

	virtual std::string getName() override {
		return name;
	}

	virtual nlohmann::json getJson() override {
		nlohmann::json j = {
			{ "type", "square"}, { "name", name }, { "side", side}
		};

		return j;
	}
};

class Rectangle : public IShape {
public:
	double width;
	double height;
	std::string name = "Rectangle";

	Rectangle(double w, double h) {
		if (w > 0.0 && h > 0) {
			this->width = w;
			this->height = h;
		}
		else {
			throw std::invalid_argument("Negative argument(s) in rectangle constructor.");
		}
	}

	Rectangle(double w, double h, std::string name) {
		if (w > 0.0 && h > 0) {
			this->width = w;
			this->height = h;
		}
		else {
			throw std::invalid_argument("Negative argument(s) in rectangle constructor.");
		}
		this->name = name;
	}

	//used in lab6
	Rectangle(std::string name, std::string params) {
		this->name = name;
		try {
			std::stringstream ss(params);
			double parsedWidth, parsedHeight;
			ss >> parsedWidth >> parsedHeight;

			if (parsedWidth > 0.0 && parsedHeight > 0) {
				this->width = parsedWidth;
				this->height = parsedHeight;
			}
			else {
				throw std::invalid_argument("Negative argument(s) in rectangle constructor.");
			}
		}
		catch (std::invalid_argument & e) {
			std::cout << "Error creating rect with " << params << " parameter"
				<< std::endl << e.what();
		}
	}
    std::string getSpec() override{
            return std::to_string(width) + " " + std::to_string(height);
        }

	virtual double getP() override {
		return 2 * (width + height);
	}

	virtual double getS() override {
		return width * height;
	}

	virtual std::string getName() override {
		return name;
	}

	virtual nlohmann::json getJson() override {
		nlohmann::json j = {
			{ "type", "rectangle"}, { "name", name}, { "side1", width}, {"side2", height}
		};

		return j;
	}
};

class Triangle : public IShape {
public:
	double
		x1, y1,
		x2, y2,
		x3, y3,
		side1, side2, side3;

	std::string name = "Triangle";

	Triangle(double x1, double y1, double x2, double y2, double x3, double y3) {
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->x3 = x3;
		this->y3 = y3;

		try {
			if ((x3 - x1) / (x2 - x1) == (y3 - y1) / (y2 - y1))
				throw std::invalid_argument("Three dots on an one line");
		}
		catch (const std::invalid_argument & e) {
			std::cout << "Error!" << std::endl << e.what();
		}

		side1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		side2 = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3));
		side3 = sqrt((x3 - x1) * (x3 - x1) + (y3 - y1) * (y3 - y1));
	}

	Triangle(double x1, double y1, double x2, double y2, double x3, double y3, std::string name) :
		Triangle(x1, y1, x2, y2, x3, y3)
	{
		this->name = name;
	}

	//side only constructor
	Triangle(double side1, double side2, double side3) {
		if (side1 > 0.0 && side2 > 0 && side3 > 0.0) {
			this->side1 = side1;
			this->side2 = side2;
			this->side3 = side3;
		}
		else {
			throw std::invalid_argument("Negative argument(s) in triangle constructor.");
		}

		if (this->getS() == 0) {
			throw std::invalid_argument("Wrong arguments in triangle constructor. Impossible sides.");
		}

		//since other methods only use sides, storing zeroes in coords would be okay
		x1 = y1 = x2 = y2 = x3 = y3 = 0;
	}

	virtual double getP() override {
		return side1 + side2 + side3;
	}

	virtual double getS() override {
		double p = this->getP() / 2;
		return sqrt(p * (p - side1) * (p - side2) * (p - side3));
	}

	virtual std::string getName() override {
		return name;
	}
    std::string getSpec() override{
            return std::to_string(side1) + " " + std::to_string(side2) + " " + std::to_string(side3);
        }

	Triangle(std::string name, std::string params) {
		this->name = name;
		try {
			std::stringstream ss(params);
            ss >> side1 >> side2 >> side3;
		}
		catch (std::invalid_argument & e) {
			std::cout << "Error creating triangle with " << params << " parameter"
				<< std::endl << e.what();
		}
	}

	virtual nlohmann::json getJson() override {
		nlohmann::json j;
		j["type"] = "triangle";
		j["name"] = name;
		j["x1"] = x1;
		j["y1"] = y1;
		j["x2"] = x2;
		j["y2"] = y2;
		j["x3"] = x3;
		j["y3"] = y3;
	
		return j;
	}
};

IShape* getShapeByInd(std::list<IShape*> list, int ind);

#endif
