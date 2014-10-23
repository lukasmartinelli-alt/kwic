#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>
#include <istream>
#include <locale>
#include <iostream>

struct Word {
	std::vector<char> characters;
};

std::istream& operator>>(std::istream& in, Word& word) {
	char c {};
	while (in.get(c)) {
		if (std::isalpha(c)) {
			word.characters.push_back(c);
		} else if(word.characters.size() > 0) {
			break;
		}
	}
	return in;
}

#endif
