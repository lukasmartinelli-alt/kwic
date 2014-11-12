#include "word.h"
#include <stdexcept>
#include <algorithm>

Word::Word(const std::string val) : value { val } {
	if (!std::all_of(value.begin(), value.end(), ::isalpha)) {
		throw std::invalid_argument("Word must only contain of alphabetical characters");
	}
}
