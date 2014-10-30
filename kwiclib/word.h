#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>
#include <istream>
#include <locale>
#include <iostream>
#include <ios>
#include <algorithm>


struct Word {
	std::string value;
	explicit Word(const std::string value);
	Word()=default;

	bool operator ==(const Word& word) const;
	bool operator !=(const Word& word) const;
	bool operator <(const Word& word) const;
	bool operator >(const Word& word) const;
	bool operator <=(const Word& word) const;
	bool operator >=(const Word& word) const;

};

inline std::istream& operator>>(std::istream& lhs, Word & rhs){
	char c{};
	while(lhs.get(c)){
		if(std::isalpha(c)){
			rhs.value += c;
		}else if(rhs.value.length() != 0){
			break;
		}
	}
	return lhs;
}

inline std::ostream& operator<<(std::ostream& out, Word &word){
	out << word.value;
	return out;
}


#endif
