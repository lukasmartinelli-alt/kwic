#include "kwic.h"
#include <iterator>

void kwic(std::istream &is, std::ostream &os){
	Word word{};
	std::vector<Word> words{};
	std::ostream_iterator<Word> out_it (os, " ");
	while(is >> word){
		words.push_back(word);
		word.value = "";
	}
	auto permutedVector = permuteWords(words);
	for (auto var = 0; var < permutedVector.size(); ++var) {
		std::copy(permutedVector.at(var).begin(), permutedVector.at(var).end(), out_it);
		os << "\n";
	}
}


std::vector<std::vector<Word>> permuteWords(std::vector<Word> words){
	std::vector<std::vector<Word>> permutedVector(words.size(), std::vector<Word>(words.size()));
	for (unsigned int var = 0; var < words.size(); ++var) {
		std::rotate_copy(words.begin(), words.begin()+var+1,words.end(), permutedVector.at(var).begin());
	}
	return permutedVector;
}

