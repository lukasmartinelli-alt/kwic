#ifndef KWIC_H_
#define KWIC_H_

#include "word.h"
#include <set>

namespace kwic {
std::istream& operator>>(std::istream &is, std::vector<Word> &sentence);
void permuteLines(std::istream &is, std::ostream &os);
std::set<std::vector<Word>> permuteWords(std::vector<Word> words);
}

#endif
