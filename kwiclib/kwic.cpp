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
	std::vector<Word> sentence{};
	std::vector<std::vector<Word>> lines{};
	//copy lines into sentence vector
	while(is >> sentence){
		lines.push_back(sentence);
		std::cout << sentence;
		sentence.clear();
	}
	//permute each sentence and output
	std::for_each(lines.begin(), lines.end(), [&os](std::vector<Word> sentence){
		auto permutedVector = permuteWords(sentence);
		std::for_each(permutedVector.begin(), permutedVector.end(), [&os](std::vector<Word> sentence){
			os << sentence;
			os << "\n";
		});
	});
}

std::vector<std::vector<Word>> permuteWords(std::vector<Word> words) {
	std::vector<std::vector<Word>> permutations { };

	for (auto _ : words) {
		std::rotate(words.begin(), words.begin() + 1, words.end());
		permutations.push_back(words);
	}

	return permutations;
}

