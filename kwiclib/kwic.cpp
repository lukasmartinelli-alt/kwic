#include "kwic.h"
#include <iterator>
#include <sstream>
#include <algorithm>

namespace kwic {
std::istream& operator>>(std::istream &is, std::vector<Word> &sentence) {
	using input = std::istream_iterator<Word>;
	auto line = std::string { };
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

void permuteLines(std::istream &is, std::ostream &os) {
	using input = std::istream_iterator<std::vector<Word>>;
	const auto lines = std::vector<std::vector<Word>>(input(is), input { });
	auto permutedLines = std::set<std::vector<Word>> { };

	for (auto sentence : lines) {
		auto permutations = permuteWords(sentence);
		permutedLines.insert(permutations.begin(), permutations.end());
	}

	for (auto lines : permutedLines) {
		os << lines << "\n";
	}
}

std::set<std::vector<Word>> permuteWords(std::vector<Word> words) {
	auto permutations = std::set<std::vector<Word>> { };

	for (auto _ : words) {
		std::rotate(words.begin(), words.begin() + 1, words.end());
		permutations.insert(words);
	}

	return permutations;
}
}

