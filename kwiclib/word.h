#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <istream>

struct Word {
	std::string value;

	explicit Word(const std::string value="");

	inline bool operator <(const Word& word) const {
		auto compareLowerCaseCharacters = [](const char c1, const char c2) {
			return std::tolower(c1) < std::tolower(c2);
		};
		return std::lexicographical_compare(this->value.begin(), this->value.end(), word.value.begin(), word.value.end(), compareLowerCaseCharacters);
	}

	inline bool operator >(const Word& word) const {
		return word < *this;
	}

	inline bool operator <=(const Word& word) const {
		return !(word < *this);
	}

	inline bool operator >=(const Word& word) const {
		return !(*this < word);
	}

	inline bool operator ==(const Word& word) const {
		return !(*this < word) && !(word < *this);
	}

	inline bool operator !=(const Word& word) const {
		return !(*this == word);
	}
};

inline std::istream& operator>>(std::istream& lhs, Word & rhs) {
	char c { };
	rhs.value.clear();

	while (lhs.get(c)) {
		if (std::isalpha(c)) {
			rhs.value += c;
		} else if (!rhs.value.empty()) {
			break;
		}
	}

	if (!rhs.value.empty()) {
		lhs.clear();
	}

	return lhs;
}

inline std::ostream& operator<<(std::ostream& out, Word const& word) {
	out << word.value;
	return out;
}

#endif
