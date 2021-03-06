#include "kwic.h"
#include <iterator>
#include <sstream>
#include <algorithm>

std::istream& operator>>(std::istream &is, std::vector<Word> &sentence) {
	using input = std::istream_iterator<Word>;
	std::string line { };
	if (getline(is, line)) {
		std::istringstream lineStream { line };
		sentence = std::vector<Word>(input(lineStream), input { });
	}
	return is;
}

std::ostream& operator<<(std::ostream &os, std::vector<Word> const &sentence) {
	copy(sentence.begin(), sentence.end(), std::ostream_iterator<Word>(os, " "));
	return os;
}

void rotateLines(std::istream &is, std::ostream &os) {
	using input = std::istream_iterator<std::vector<Word>>;
	const std::vector<std::vector<Word>> lines(input(is), input { });
	std::set<std::vector<Word>> rotatedLines{ };

	for (auto sentence : lines) {
		auto rotations = rotateWords(sentence);
		rotatedLines.insert(rotations.begin(), rotations.end());
	}

	for (auto lines : rotatedLines) {
		os << lines << "\n";
	}
}

std::set<std::vector<Word>> rotateWords(std::vector<Word> words) {
	std::set<std::vector<Word>> rotations { };

	for (auto _ : words) {
		std::rotate(words.begin(), words.begin() + 1, words.end());
		rotations.insert(words);
	}

	return rotations;
}


