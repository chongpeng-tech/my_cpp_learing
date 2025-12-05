
#include <map>
#include <string>
#include <vector>

#include "Q1_Variadic_Template_sum.h"
#include "Q2_Word_Frequency.h"
#include "gtest/gtest.h"

// --------------------------
// Tests for the sum function
// --------------------------

// Test with all integers.
TEST(SumTest, AllIntegers) {
	auto result = sum(1, 2, 3, 4);
	EXPECT_EQ(result, 10)
		<< "Test failed: sum(1, 2, 3, 4) should equal 10, but got " << result;
}

// Test with a mix of integers, floating points, and string-based numbers.
TEST(SumTest, MixedTypes) {
	// 1 + 2.5 + 3 + 4.5 = 11
	auto result = sum(1, 2.5, 3, "4.5");
	EXPECT_EQ(result, 11)
		<< "Test failed: sum(1, 2.5, 3, \"4.5\") should equal 11, but got "
		<< result;
}

// Test with string-based numbers only.
TEST(SumTest, StringsOnly) {
	auto result = sum("10", "20", "30");
	EXPECT_EQ(result, 60)
		<< "Test failed: sum(\"10\", \"20\", \"30\") should equal 60, but got "
		<< result;
}

// Test with floating point and string-based number.
TEST(SumTest, FloatingPointConversion) {
	// 3.5 + 2.5 = 6.0
	auto result = sum(3.5, "2.5");
	EXPECT_EQ(result, 6.0)
		<< "Test failed: sum(3.5, \"2.5\") should equal 6, but got " << result;
}

// Test with negative numbers.
TEST(SumTest, NegativeNumbers) {
	// -1 + (-2) + 3.0 = 0.0
	auto result = sum(-1, "-2", 3.0);
	EXPECT_EQ(result, 0.0)
		<< "Test failed: sum(-1, \"-2\", 3.0) should equal 0, but got "
		<< result;
}

// -------------------------------
// Tests for the countWords function
// -------------------------------

TEST(CountWordsTest, BasicTest) {
	std::string text = "Hello world! This is a test. hello again, world.";
	auto wordCounts = countWords(text);

	// Expected frequencies (assuming words are converted to lower-case and
	// punctuation removed)
	std::map<std::string, int> expected = {
		{"hello", 2}, {"world", 2}, {"this", 1}, {"is", 1},
		{"a", 1},	  {"test", 1},	{"again", 1}};

	// Check the size first.
	EXPECT_EQ(wordCounts.size(), expected.size())
		<< "Test failed: Expected " << expected.size()
		<< " unique words, but got " << wordCounts.size();

	// Check each word count.
	for (const auto& [word, count] : expected) {
		auto it = wordCounts.find(word);
		ASSERT_NE(it, wordCounts.end()) << "Test failed: Expected word '"
										<< word << "' not found in the result.";
		EXPECT_EQ(it->second, count)
			<< "Test failed: Word '" << word << "' should appear " << count
			<< " times, but got " << it->second;
	}
}

// Additional test to check punctuation handling and case sensitivity.
// **Replace Punctuations with SPACE**
TEST(CountWordsTest, PunctuationAndCase) {
	std::string text = "C++ is great. Isn't C++ great? Yes, C++ is great!";
	auto wordCounts = countWords(text);

	std::map<std::string, int> expected = {
		{"c", 3},  // "C++" becomes "c" after removing punctuation.
		{"is", 2}, {"great", 3}, {"isn", 1}, {"t", 1}, {"yes", 1}};

	EXPECT_EQ(wordCounts.size(), expected.size())
		<< "Test failed: Expected " << expected.size()
		<< " unique words, but got " << wordCounts.size();

	for (const auto& [word, count] : expected) {
		auto it = wordCounts.find(word);
		ASSERT_NE(it, wordCounts.end()) << "Test failed: Expected word '"
										<< word << "' not found in the result.";
		EXPECT_EQ(it->second, count)
			<< "Test failed: Word '" << word << "' should appear " << count
			<< " times, but got " << it->second;
	}
}
