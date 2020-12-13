#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <list>
#include <fstream>

#include "IShape.h"

class Serializator {
public:
	Serializator() {

	}

	~Serializator() {

	}


	void serialize(std::list<IShape*>* list) {
		std::ofstream o("shapes.json");
		if (o.is_open()) {
			nlohmann::json j;

			for (auto it = list->begin(); it != list->end(); it++) {
				j.push_back((**it).getJson());
			}

			o << j.dump();
			o.close();
		}
		else {
			throw(std::invalid_argument("File wasn't opened"));
		}
	}

	std::list<IShape*> deserialize(std::string filename) {
		std::list<IShape*> list;

		std::ifstream i(filename);
		if (i.is_open()) {
			nlohmann::json j;

			i >> j;
			for (auto it = j.begin(); it != j.end(); it = std::next(it)) {
				std::string currType = (*it)["type"];
				std::string currName = (*it)["name"];
				//std::cout << currType << " and " << *(std::next(it)) << std::endl;
				
				if (currType == "circle") {
					list.push_back(new Circle((double)((*it)["radius"]), (*it)["name"]));
				}
				else if (currType == "square") {
					list.push_back(new Square((double)((*it)["side"]), currName));
				}
				else if (currType == "rectangle") {
					list.push_back(new Rectangle(
						(double)((*it)["side1"]),
						(double)((*it)["side2"]),
						currName));
				}
				else if (currType == "triangle") {
					list.push_back(new Triangle(
						(double)((*it)["x1"]),
						(double)((*it)["y1"]),
						(double)((*it)["x2"]),
						(double)((*it)["y2"]),
						(double)((*it)["x3"]),
						(double)((*it)["y3"]),
						currName));
				}
				else {
					throw(std::invalid_argument("Error parsing " + currType + " with name " + currName));
				}
			}
		}
		else {
			throw(std::invalid_argument("Can't find such file"));
		}

		return list;
	}

};



#endif