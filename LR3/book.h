#pragma once
#include "contact.h"
#include "phoneTypes.h"
#include<vector>
#include <iostream>
class phoneBook {
private:
	vector<contact> phone_book;
public:
	phoneBook() {}
	//book getter to work with frameworks etc.
	vector<contact> getBook() {
		return this->phone_book;
	}

	void add_contact(string name, string second_name, pair<string, phoneTypes> number) {
			this->phone_book.push_back(contact(name, second_name, number));
	}
	void add_number(string name, string second_name, pair<string, phoneTypes> number) {
		for (auto i = 0; i < this->phone_book.size();i++) {
			if (this->phone_book.at(i).get_name() == name && this->phone_book.at(i).get_second_name() == second_name) {
				this->phone_book.at(i).add_phone(number);
				break;
			}
		}
	}
	void change_number(string name, string second_name, pair<string, phoneTypes> numberbase, pair<string, phoneTypes> numbernew) {
		for (auto i = 0; i < this->phone_book.size();i++) {
			if (this->phone_book.at(i).get_name() == name && this->phone_book.at(i).get_second_name() == second_name) {
				this->phone_book.at(i).change_phone(numberbase, numbernew);
				break;
			}
		}
	}
	void remove_number(string name, string second_name, pair<string, phoneTypes> number) {
		for (auto i = 0; i < this->phone_book.size();i++) {
			if (this->phone_book.at(i).get_name() == name && this->phone_book.at(i).get_second_name() == second_name) {
				this->phone_book.at(i).remove_phone(number);
				break;
			}
		}
	}
	void change_name(string basename, string basesecond_name, string newname) {
		for (auto i = 0; i < this->phone_book.size(); i++) {
			if (this->phone_book.at(i).get_name() == basename && this->phone_book.at(i).get_second_name() == basesecond_name) {
				this->phone_book.at(i).set_name(newname);
				break;
			}
		}
	}
	void change_second_name(string basename, string basesecond_name, string newsecond_name) {
		for (auto i = 0; i < this->phone_book.size();i++) {
			if (this->phone_book.at(i).get_name() == basename && this->phone_book.at(i).get_second_name() == basesecond_name) {
				this->phone_book.at(i).set_second_name(newsecond_name);
				break;
			}
		}
	}
	void remove_contact(string name, string second_name) {
		for (auto i = 0; i < this->phone_book.size();i++) {
			if (this->phone_book.at(i).get_name() == name && this->phone_book.at(i).get_second_name() == second_name) {
				this->phone_book.erase(this->phone_book.begin()+i);
				break;
			}
		}
	}
	//find() now returns std vector of contacts which can be passed anywhere
	vector<contact> find(string str) {
		vector<contact> temp;
		for (auto i = 0; i < this->phone_book.size();i++) {
			if (this->phone_book.at(i).get_name().find(str) != string::npos) {
				temp.push_back(this->phone_book.at(i));
			}
			if (this->phone_book.at(i).get_second_name().find(str) != string::npos) {
				temp.push_back(this->phone_book.at(i));
			}
		}
		return temp;
	}
};