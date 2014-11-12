#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "word.h"
#include "kwic.h"

void testWordShouldBeLessComparesInternalValue() {
	//Arrange
	const auto word1 = Word("abc");
	const auto word2 = Word("bcd");
	//Assert
	ASSERT_LESS(word1, word2);
}

void testWordShouldBeLessComparesCaseInsensitive() {
	//Arrange
	const auto word1 = Word("abc");
	const auto word2 = Word("BCD");
	//Assert
	ASSERT_LESS(word1, word2);
}

void testWordShiftLeftPrintsInternalValue() {
	//Arrange
	std::ostringstream out { };
	const auto word = Word("hallo");
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
	auto word = Word { };
	//Act
	in >> word;
	//Assert
	ASSERT_EQUAL(std::string { "abc" }, word.value);
}

void testWordIsEmptyIfStreamIsEmpty() {
	//Arrange
	std::istringstream in { "              " };
	auto word = Word { };
	//Act
	in >> word;
	//Assert
	ASSERT_EQUAL(0, word.value.length());
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
	ASSERT_EQUAL(std::string { "compl" }, word1.value);
	ASSERT_EQUAL(std::string { "tely" }, word2.value);
	ASSERT_EQUAL(std::string { "weird" }, word3.value);
	ASSERT_EQUAL(std::string { "matted" }, word4.value);
	ASSERT_EQUAL(std::string { "in" }, word5.value);
	ASSERT_EQUAL(std::string { "put" }, word6.value);
}

void testRotateSingleLineReturnsAllMutationsSorted() {
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
	auto expected1 = std::vector<Word> { mockWord3, mockWord4, mockWord1, mockWord2 };
	ASSERT_EQUAL(expected1, permuted.at(0));


	auto expected2 = std::vector<Word> { mockWord2, mockWord3, mockWord4, mockWord1 };
	ASSERT_EQUAL(expected2, permuted.at(1));


	auto expected3 = std::vector<Word> { mockWord4, mockWord1, mockWord2, mockWord3 };
	ASSERT_EQUAL(expected3, permuted.at(2));


	auto expected4 = std::vector<Word> { mockWord1, mockWord2, mockWord3, mockWord4 };
	ASSERT_EQUAL(expected4, permuted.at(3));
}

void testRotateMultipleLinesReturnsAllMutationsSorted() {
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

void testWordRightShiftPutsWordsIntoSentenceUntilEndOfLine() {
	//Arrange
	std::istringstream in { "this is a test" };
	auto sentence = std::vector<Word> { };
	//Act
	in >> sentence;
	//Assert
	ASSERT_EQUAL(Word("this"), sentence.at(0));
	ASSERT_EQUAL(Word("is"), sentence.at(1));
	ASSERT_EQUAL(Word("a"), sentence.at(2));
	ASSERT_EQUAL(Word("test"), sentence.at(3));
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
	s.push_back(CUTE(testRotateSingleLineReturnsAllMutationsSorted));
	s.push_back(CUTE(testRotateMultipleLinesReturnsAllMutationsSorted));
	s.push_back(CUTE(testWordRightShiftPutsWordsIntoSentenceUntilEndOfLine));

	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<> > lis(xmlfile.out);
	cute::makeRunner(lis, argc, argv)(s, "AllTests");
}

int main(int argc, char const *argv[]) {
	runAllTests(argc, argv);
	return 0;
}
