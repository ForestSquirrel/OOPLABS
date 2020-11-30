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
			for (auto outerIt = j.begin(); outerIt != j.end(); outerIt = std::next(outerIt)) {
				auto it = outerIt->begin();
				std::string currName = *it;
				//std::cout << currName << " and " << *(std::next(it)) << std::endl;
				
				if (currName == "circle") {
					list.push_back(new Circle(*std::next(it)));
				}
				else if (currName == "square") {
					list.push_back(new Square(*std::next(it)));
				}
				else if (currName == "rectangle") {
					list.push_back(new Rectangle(*std::next(it), *std::next(it, 2)));
				}
				else if (currName == "triangle") {
					//json stores it as x1 x2 x3 y1 y2 y3
					//constructor is x1 y1 x2 y2 x3 y3
					list.push_back(new Triangle(
						*std::next(it),
						*std::next(it, 4),
						*std::next(it, 2),
						*std::next(it, 5),
						*std::next(it, 3),
						*std::next(it, 6)));
				}
				else {
					throw(std::invalid_argument("File wasn't opened"));
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