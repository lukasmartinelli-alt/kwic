#include "word.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace kwic {

	Word::Word(const std::string val) : value { val } {
		if (!std::all_of(value.begin(), value.end(), ::isalpha)) {
			throw std::invalid_argument("Word must only contain of alphabetical characters");
		}
	}

	bool compareLowerCaseCharacters(const char c1, const char c2) {
		return std::tolower(c1) < std::tolower(c2);
	}

	bool Word::operator <(const Word& word) const {
		return std::lexicographical_compare(this->value.begin(), this->value.end(), word.value.begin(), word.value.end(), compareLowerCaseCharacters);
	}

	bool Word::operator >(const Word& word) const {
		return word.value < value;
	}

	bool Word::operator <=(const Word& word) const {
		return !(word < *this);
	}

	bool Word::operator >=(const Word& word) const {
		return !(*this < word);
	}

	bool Word::operator ==(const Word& word) const {
		return !(*this < word) && !(word < *this);
	}

	bool Word::operator !=(const Word& word) const {
		return !(*this == word);
	}

}
