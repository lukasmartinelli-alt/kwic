#include "word.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

Word::Word(const std::string val) : value { val } {
	if (!std::all_of(value.begin(), value.end(), ::isalpha)) {
		throw std::invalid_argument("Word must only contain of alphabetical characters");
	}
}


void Word::read(std::istream& in) {
	char c { };
	std::string newValue { };

	while (in.get(c)) {
		if (std::isalpha(c)) {
			newValue += c;
		} else if (!newValue.empty()) {
			break;
		}
	}

	if (!newValue.empty()) {
		in.clear();
	}

	this->value = newValue;
}

void Word::print(std::ostream& out) const {
	out << (*this).value;
}
