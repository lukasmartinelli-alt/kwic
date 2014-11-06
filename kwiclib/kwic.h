#ifndef KWIC_H_
#define KWIC_H_

#include "word.h"

std::istream& operator>>(std::istream &is, std::vector<Word> &sentence);
void kwic(std::istream &is, std::ostream &os);
std::vector<std::vector<Word>> permuteWords(std::vector<Word> words);

#endif
