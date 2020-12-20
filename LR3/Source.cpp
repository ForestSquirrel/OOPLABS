#include <string>
#include "book.h"

using namespace std;

void main() {
	phoneBook Book;

	Book.add_contact("John", "Stasey", make_pair("899912376796", phoneTypes::MOBILE));
	Book.add_contact("Bob", "Washington", make_pair("+79115687895", phoneTypes::WORK));
	Book.add_number("Bob", "Washington", make_pair("888-36-54", phoneTypes::HOME));


	Book.change_number("Bob", "Washington", make_pair("888-36-54", phoneTypes::HOME), make_pair("999-88-77", phoneTypes::HOME));

	Book.find("a");

	Book.remove_contact("John", "Stasey");
	Book.change_name("Bob", "Washington", "Dan");
	Book.change_second_name("Dan", "Washington", "Straus");
	
	system("pause");
}