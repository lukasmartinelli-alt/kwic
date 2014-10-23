#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "word.h"
#include <sstream>
#include <stdexcept>

void wordConsistsOfOnlyLetters() {
	//Arrange
	Word word {};
	std::istringstream in {"abc123"};
	//Act
	in >> word;

	//Assert
	ASSERT_EQUAL(3, word.characters.size());
	ASSERT_EQUAL('a', word.characters.at(0));
	ASSERT_EQUAL('b', word.characters[1]);
	ASSERT_EQUAL('c', word.characters[2]);
}

void emptyWordIfStreamIsEmpty() {
	//Arrange
	Word word {};
	std::istringstream in {"              "};

	//Act
	in >> word;

	//Assert
	ASSERT_EQUAL(0, word.characters.size());
}


void wordsAreDelimitedByNonAlphanumericCharacters() {
	//Arrange
	Word word1 {}, word2 {}, word3 {};
	std::istringstream in {"compl33tely - weird ~??"};

	//Act
	in >> word1;
	in >> word2;
	in >> word3;

	//Assert
	ASSERT_EQUAL(5, word1.characters.size());
	ASSERT_EQUAL('c', word1.characters.at(0));
	ASSERT_EQUAL('o', word1.characters.at(1));
	ASSERT_EQUAL('m', word1.characters.at(2));
	ASSERT_EQUAL('p', word1.characters.at(3));
	ASSERT_EQUAL('l', word1.characters.at(4));

	ASSERT_EQUAL(4, word2.characters.size());
	ASSERT_EQUAL('t', word2.characters.at(0));
	ASSERT_EQUAL('e', word2.characters.at(1));
	ASSERT_EQUAL('l', word2.characters.at(2));
	ASSERT_EQUAL('y', word2.characters.at(3));

	ASSERT_EQUAL(5, word3.characters.size());
	ASSERT_EQUAL('w', word3.characters.at(0));
	ASSERT_EQUAL('e', word3.characters.at(1));
	ASSERT_EQUAL('i', word3.characters.at(2));
	ASSERT_EQUAL('r', word3.characters.at(3));
	ASSERT_EQUAL('d', word3.characters.at(4));
}

void runAllTests(int argc, char const *argv[]){
	cute::suite s;

	s.push_back(CUTE(wordConsistsOfOnlyLetters));
	s.push_back(CUTE(wordsAreDelimitedByNonAlphanumericCharacters));
	s.push_back(CUTE(emptyWordIfStreamIsEmpty));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}
