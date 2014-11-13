#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <iosfwd>

struct Word {
	explicit Word(const std::string value="");

	void read(std::istream& in);
	void print(std::ostream& out) const;

	inline bool operator <(const Word& word) const {
		return std::lexicographical_compare(this->value.begin(), this->value.end(),
											word.value.begin(), word.value.end(),
											compareLowerCaseCharacters);
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
		return std::equal(this->value.begin(), this->value.end(), word.value.begin(), [](const char c1, const char c2) {
			return std::tolower(c1) == std::tolower(c2);
		});
	}

	inline bool operator !=(const Word& word) const {
		return !(*this == word);
	}

private:
	std::string value;
	static bool compareLowerCaseCharacters(const char c1, const char c2) {
		return std::tolower(c1) < std::tolower(c2);
	}

};

inline std::istream& operator>>(std::istream& in, Word & word) {
	word.read(in);
	return in;
}

inline std::ostream& operator<<(std::ostream& out, const Word& word) {
	word.print(out);
	return out;
}

#endif
