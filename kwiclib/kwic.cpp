#include "kwic.h"
#include <iterator>
#include <sstream>

std::istream& operator>>(std::istream &is, std::vector<Word> &sentence){
	std::string line{};
	if(getline(is, line)){
		std::istringstream lineStream{line};
		using input = std::istream_iterator<Word>;
		sentence=std::vector<Word>(input(lineStream), input{});
		std::cout << line;
	}
	return is;
}

std::ostream& operator<<(std::ostream &os, std::vector<Word> const &sentence){
	copy(sentence.begin(), sentence.end(), std::ostream_iterator<Word>(os, " "));
	return os;
}

void kwic(std::istream &is, std::ostream &os){
	using input = std::istream_iterator<std::vector<Word>>;
	std::vector<std::vector<Word>> lines (input(is), input{});

	for(auto sentence : lines) {
		auto permutations = permuteWords(sentence);
		copy(permutations.begin(), permutations.end(), std::ostream_iterator<Word>(os, "\n"));
	}
}

std::vector<std::vector<Word>> permuteWords(std::vector<Word> words) {
	std::vector<std::vector<Word>> permutations { };

	for (auto _ : words) {
		std::rotate(words.begin(), words.begin() + 1, words.end());
		permutations.push_back(words);
	}

	return permutations;
}

