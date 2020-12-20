#pragma once
#include <string>
#include <map>
#include "phoneTypes.h"

using namespace std;

class contact {
private:
	string name;
	string second_name;
	map<string, phoneTypes> phones;
public:
	contact(string name, string second_name, pair<string, phoneTypes> number) {
		this->name = name;
		this->second_name = second_name;
		this->phones.insert(number);
	}
	//geters
	string get_name() {
		return this->name;
	}
	string get_second_name() {
		return this->second_name;
	}
	map<string, phoneTypes> get_phones() {
		return this->phones;
	}
	//seters
	void set_name(string name) {
		this->name = name;
	}
	void set_second_name(string second_name) {
		this->second_name = second_name;
	}
	void add_phone(pair<string, phoneTypes> number) {
		this->phones.insert(number);
	}
	void change_phone(pair<string, phoneTypes> numberbase, pair<string, phoneTypes> numbernew) {
		this->phones.erase(numberbase.first);
		this->phones.insert(numbernew);
	}
	void remove_phone(pair<string, phoneTypes> number) {
		this->phones.erase(number.first);
	}
};