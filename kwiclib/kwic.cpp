#include "kwic.h"
#include <iterator>

void kwic(std::istream &is, std::ostream &os) {
	Word word { };
	std::vector<Word> words { };
	std::ostream_iterator<Word> out_it(os, " ");
	while (is >> word) {
		words.push_back(word);
		word.value = "";
	}
	auto permutedVector = permuteWords(words);
	for (auto var = 0; var < permutedVector.size(); ++var) {
		std::copy(permutedVector.at(var).begin(), permutedVector.at(var).end(), out_it);
		os << "\n";
	}
}

std::vector<std::vector<Word>> permuteWords(const std::vector<Word> words) {
	std::vector<std::vector<Word>> allPermutations { };

	for (auto it = words.begin(); it != words.end(); ++it) {
		std::vector<Word> permutedWords(words.size());
		std::rotate_copy(words.begin(), it, words.end(), permutedWords.begin());
		allPermutations.push_back(permutedWords);
	}

	return allPermutations;
}

