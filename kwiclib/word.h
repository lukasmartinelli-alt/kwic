#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>
#include <istream>

struct Word {
	std::string value;
	explicit Word(const std::string value);
	Word() = default;

	bool operator ==(const Word& word) const;
	bool operator !=(const Word& word) const;
	bool operator <(const Word& word) const;
	bool operator >(const Word& word) const;
	bool operator <=(const Word& word) const;
	bool operator >=(const Word& word) const;

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
