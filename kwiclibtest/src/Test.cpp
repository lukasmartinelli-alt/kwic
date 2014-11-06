#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <sstream>
#include <stdexcept>
#include "word.h"
#include "kwic.h"


void testWordsWithLessThanOperator(){
	//Arrange
	Word word1("abc");
	Word word2("bcd");
	//Assert
	ASSERT_LESS(word1, word2);
}

void testWordsWithLessThanOperatorIgnoringLetterCase(){
	//Arrange
	Word word1("abc");
	Word word2("BCD");
	//Assert
	ASSERT_LESS(word1, word2);
}

void testPrintValueOfWord() {
	//Arrange
	std::ostringstream out {};
	Word word("hallo");

	//Act
	out << word;

	//Assert
	ASSERT_EQUAL("hallo", out.str());

}

void constructWordThrowsInvalidArgumentExceptionForNumberInWord() {
	//Assert
	ASSERT_THROWS(Word("124abd"),std::invalid_argument);
}

void constructWordThrowsInvalidArgumentExceptionForSpecialCharacters() {
	//Assert
	ASSERT_THROWS(Word("dsl!*%"), std::invalid_argument);
}

void wordConsistsOfOnlyLetters() {
	//Arrange
	Word word {};
	std::istringstream in {"abc123"};
	//Act
	in >> word;

	//Assert
	ASSERT_EQUAL(std::string {"abc"}, word.value);
}

void emptyWordIfStreamIsEmpty() {
	//Arrange
	Word word {};
	std::istringstream in {"              "};

	//Act
	in >> word;

	//Assert
	ASSERT_EQUAL(0, word.value.length());
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
	ASSERT_EQUAL(std::string {"compl"}, word1.value);
	ASSERT_EQUAL(std::string {"tely"}, word2.value);
	ASSERT_EQUAL(std::string {"weird"}, word3.value);
}

void permuteSingleSentence() {
	//Arrange
	Word mockWord1 ("this");
	Word mockWord2 ("is");
	Word mockWord3 ("a");
	Word mockWord4 ("test");
	Word word1 {}, word2 {}, word3 {}, word4 {};
	std::istringstream in {"this is a test"};

	in >> word1;
	in >> word2;
	in >> word3;
	in >> word4;

	std::vector<Word> words {word1, word2, word3, word4};

	//Act
	std::vector<std::vector<Word>> permuted = permuteWords(words);

	//Assert
	ASSERT_EQUAL(mockWord1,permuted.at(0).at(0)); // this is a test
	ASSERT_EQUAL(mockWord2,permuted.at(0).at(1));
	ASSERT_EQUAL(mockWord3,permuted.at(0).at(2));
	ASSERT_EQUAL(mockWord4,permuted.at(0).at(3));

	ASSERT_EQUAL(mockWord2,permuted.at(1).at(0)); //is a test this
	ASSERT_EQUAL(mockWord3,permuted.at(1).at(1));
	ASSERT_EQUAL(mockWord4,permuted.at(1).at(2));
	ASSERT_EQUAL(mockWord1,permuted.at(1).at(3));

	ASSERT_EQUAL(mockWord3,permuted.at(2).at(0)); // a test this is
	ASSERT_EQUAL(mockWord4,permuted.at(2).at(1));
	ASSERT_EQUAL(mockWord1,permuted.at(2).at(2));
	ASSERT_EQUAL(mockWord2,permuted.at(2).at(3));

	ASSERT_EQUAL(mockWord4,permuted.at(3).at(0)); // test this is a
	ASSERT_EQUAL(mockWord1,permuted.at(3).at(1));
	ASSERT_EQUAL(mockWord2,permuted.at(3).at(2));
	ASSERT_EQUAL(mockWord3,permuted.at(3).at(3));
}

void permuteMultipleSentence(){
	//Arrange
	std::istringstream is{"this is a test"};
	std::ostringstream os{};

	//Act
	kwic(is, os);

	//Assert
	ASSERT_EQUAL("is a test this\n"
				 "a test this is\n"
				 "test this is a\n"
				 "this is a test\n"
			     /*"is another test this\n"
				 "another test this is\n"
			     "test this is another\n"
			     "this is another test"*/, os.str());
}


void runAllTests(int argc, char const *argv[]){
	cute::suite s{};

	s.push_back(CUTE(wordConsistsOfOnlyLetters));
	s.push_back(CUTE(wordsAreDelimitedByNonAlphanumericCharacters));
	s.push_back(CUTE(emptyWordIfStreamIsEmpty));
	s.push_back(CUTE(constructWordThrowsInvalidArgumentExceptionForNumberInWord));
	s.push_back(CUTE(constructWordThrowsInvalidArgumentExceptionForSpecialCharacters));
	s.push_back(CUTE(testPrintValueOfWord));
	s.push_back(CUTE(testWordsWithLessThanOperator));
	s.push_back(CUTE(testWordsWithLessThanOperatorIgnoringLetterCase));
	s.push_back(CUTE(permuteSingleSentence));
	s.push_back(CUTE(permuteMultipleSentence));

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}
