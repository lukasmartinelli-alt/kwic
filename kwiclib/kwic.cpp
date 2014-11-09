#include "kwic.h"
#include <iterator>
#include <sstream>
#include <algorithm>

std::istream& operator>>(std::istream &is, std::vector<Word> &sentence){
	std::string line{};
	if(getline(is, line)){
		std::istringstream lineStream{line};
		using input = std::istream_iterator<Word>;
		sentence=std::vector<Word>(input(lineStream), input{});
	}
	return is;
}

std::ostream& operator<<(std::ostream &os, std::vector<Word> const &sentence){
	copy(sentence.begin(), sentence.end(), std::ostream_iterator<Word>(os, " "));
	return os;
}

void kwic(std::istream &is, std::ostream &os){
	using input = std::istream_iterator<std::vector<Word>>;
	std::vector<std::vector<Word>> lines(input(is), input { });
	std::set<std::vector<Word>> permutedLines { };

	for(auto sentence : lines) {
		auto permutations = permuteWords(sentence);
		permutedLines.insert(permutations.begin(), permutations.end());
	}
	for(auto lines : permutedLines){
		os << lines << "\n";
	}
}

std::set<std::vector<Word>> permuteWords(std::vector<Word> words) {
	std::set<std::vector<Word>> permutations { };

	for (auto _ : words) {
		std::rotate(words.begin(), words.begin() + 1, words.end());
		permutations.insert(words);
	}

	return permutations;
}

