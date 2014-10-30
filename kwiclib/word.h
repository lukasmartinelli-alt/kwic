#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>
#include <istream>
#include <locale>
#include <iostream>

struct Word {
	std::string value;
};

std::istream& operator>>(std::istream& in, Word& word) {
	char c {};
	while (in.get(c)) {
		if (std::isalpha(c)) {
			word.value += c;
		} else if(word.value.length() > 0) {
			break;
		}
	}
	return in;
}

#endif
