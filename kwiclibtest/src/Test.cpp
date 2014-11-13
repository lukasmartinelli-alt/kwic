#include "word.h"
#include "kwic.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

void testWordShouldBeLessComparesInternalValue() {
	//Arrange
	const Word word1("abc");
	const Word word2("bcd");
	//Assert
	ASSERT_LESS(word1, word2);
}

void testWordShouldBeLessComparesCaseInsensitive() {
	//Arrange
	const Word word1("abc");
	const Word word2("BCD");
	//Assert
	ASSERT_LESS(word1, word2);
}

void testWordShiftLeftPrintsInternalValue() {
	//Arrange
	std::ostringstream out { };
	const Word word("hallo");
	//Act
	out << word;
	//Assert
	ASSERT_EQUAL("hallo", out.str());

}

void testConstructWordThrowsInvalidArgumentExceptionForNumber() {
	//Assert
	ASSERT_THROWS(Word("124abd"), std::invalid_argument);
}

void testConstructWordThrowsInvalidArgumentExceptionForSpecialCharacters() {
	//Assert
	ASSERT_THROWS(Word("dsl!*%"), std::invalid_argument);
}

void testWordConsistsOfOnlyLetters() {
	//Arrange
	std::istringstream in { "abc123%" };
	Word word { };
	//Act
	in >> word;
	//Assert
	ASSERT_EQUAL(Word("abc"), word);
}

void testWordIsEmptyIfStreamIsEmpty() {
	//Arrange
	std::istringstream in { "              " };
	Word word { };
	//Act
	in >> word;
	//Assert
	ASSERT_EQUAL(Word(""), word);
}

void testWordsAreDelimitedByNonAlphanumericCharacters() {
	//Arrange
	std::istringstream in { "compl33tely ~ weird !!??!! 4matted in_put" };
	Word word1 { }, word2 { }, word3 { }, word4 { }, word5 { }, word6 { };
	//Act
	in >> word1;
	in >> word2;
	in >> word3;
	in >> word4;
	in >> word5;
	in >> word6;
	//Assert
	ASSERT_EQUAL(Word("compl"), word1);
	ASSERT_EQUAL(Word("tely"), word2);
	ASSERT_EQUAL(Word("weird"), word3);
	ASSERT_EQUAL(Word("matted"), word4);
	ASSERT_EQUAL(Word("in"), word5);
	ASSERT_EQUAL(Word("put"), word6);
}

void testRotateSingleLineReturnsAllRotationsSorted() {
	//Arrange
	const Word mockWord1("this");
	const Word mockWord2("is");
	const Word mockWord3("a");
	const Word mockWord4("test");

	const std::vector<Word> words { Word("this"), Word("is"), Word("a"), Word("test") };

	//Act
	const auto rotatedWords = rotateWords(words);
	auto permuted = std::vector<std::vector<Word>> { };

	for (auto word : rotatedWords) {
		permuted.push_back(word);
	}

	//Assert
	const std::vector<Word> expected1 { mockWord3, mockWord4, mockWord1, mockWord2 };
	ASSERT_EQUAL(expected1, permuted.at(0));


	const std::vector<Word> expected2 { mockWord2, mockWord3, mockWord4, mockWord1 };
	ASSERT_EQUAL(expected2, permuted.at(1));


	const std::vector<Word> expected3 { mockWord4, mockWord1, mockWord2, mockWord3 };
	ASSERT_EQUAL(expected3, permuted.at(2));


	const std::vector<Word> expected4 { mockWord1, mockWord2, mockWord3, mockWord4 };
	ASSERT_EQUAL(expected4, permuted.at(3));
}

void testRotateMultipleLinesReturnsAllRotationsSorted() {
	//Arrange
	std::istringstream in { "this is a test\n"
							"this is another test" };
	std::ostringstream out { };
	//Act
	rotateLines(in, out);
	//Assert
	ASSERT_EQUAL("a test this is \n"
                 "another test this is \n"
                 "is a test this \n"
                 "is another test this \n"
                 "test this is a \n"
                 "test this is another \n"
                 "this is a test \n"
                 "this is another test \n", out.str());
}

void runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	s.push_back(CUTE(testWordConsistsOfOnlyLetters));
	s.push_back(CUTE(testWordsAreDelimitedByNonAlphanumericCharacters));
	s.push_back(CUTE(testWordIsEmptyIfStreamIsEmpty));
	s.push_back(CUTE(testConstructWordThrowsInvalidArgumentExceptionForNumber));
	s.push_back(CUTE(testConstructWordThrowsInvalidArgumentExceptionForSpecialCharacters));
	s.push_back(CUTE(testWordShiftLeftPrintsInternalValue));
	s.push_back(CUTE(testWordShouldBeLessComparesInternalValue));
	s.push_back(CUTE(testWordShouldBeLessComparesCaseInsensitive));
	s.push_back(CUTE(testRotateSingleLineReturnsAllRotationsSorted));
	s.push_back(CUTE(testRotateMultipleLinesReturnsAllRotationsSorted));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}
