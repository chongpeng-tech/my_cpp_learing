#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "Q1_Newton-Raphson.h"
#include "Q2_MapAndFilter.h"
#include "Q3_HTMLTagCreator.h"
}

//////////////////////////
//////   Q1 Tests   //////
//////////////////////////

// Example function f(x) = x^3 - 8
double func(double x) { return x * x * x - 8; }

// Test Case 1: Testing for a simple case where the root is known.
TEST(NewtonRaphsonTest, FindsRootOfFunc) {
	double root = newtonRaphson(func, -1.0);
	// Since we know that the root is 2.0 for f(x) = x^3 - 8, we assert it is
	// close to 2
	EXPECT_NEAR(root, 2.0, 1e-5);
}

// Test Case 2: Testing for a known positive root.
TEST(NewtonRaphsonTest, FindsPositiveRootOfFunc) {
	double root = newtonRaphson(func, 3.0);
	// The root of x^3 - 8 is 2.0, check if it's close to that value
	EXPECT_NEAR(root, 2.0, 1e-5);
}

// Test Case 3: Testing when starting with a value far from the root.
TEST(NewtonRaphsonTest, FindsRootFromDistantInitialGuess) {
	double root = newtonRaphson(func, 10.0);
	EXPECT_NEAR(root, 2.0, 1e-5);
}

// Test Case 4: Testing edge case where the function has a root at zero.
TEST(NewtonRaphsonTest, FindsRootAtZero) {
	// Function f(x) = x^3 - 8 has a root at x = 2, but if we use a function
	// with root at 0
	auto funcZero = [](double x) { return x * x; };	 // f(x) = x^2
	double root = newtonRaphson(funcZero, 10.0);
	EXPECT_NEAR(root, 0.0, 1e-5);
}

// Test Case 5: Checking for derivative approximation
TEST(NewtonRaphsonTest, Derivative) {
	double x = 2.0;
	double derivativeValue = derivative(func, x);
	double expectedDerivative = 12.0;  // Derivative of x^3 - 8 at x = 2 is 12

	EXPECT_NEAR(derivativeValue, expectedDerivative, 1e-5);
}

//////////////////////////
//////   Q2 Tests   //////
//////////////////////////

// Example functions for map and filter
double square(double x) { return x * x; }

bool isEven(double x) { return static_cast<int>(x) % 2 == 0; }

// Test Case 1: Testing the map function with squaring elements
TEST(MapTest, SquaresArrayElements) {
	double arr[] = {1.0, 2.0, 3.0, 4.0};
	int size = sizeof(arr) / sizeof(arr[0]);

	map(arr, size, square);

	// After applying map, the array should become {1.0, 4.0, 9.0, 16.0}
	EXPECT_DOUBLE_EQ(arr[0], 1.0);
	EXPECT_DOUBLE_EQ(arr[1], 4.0);
	EXPECT_DOUBLE_EQ(arr[2], 9.0);
	EXPECT_DOUBLE_EQ(arr[3], 16.0);
}

// Test Case 2: Testing the filter function with even-number check
TEST(FilterTest, FiltersEvenNumbers) {
	double arr[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
	int size = sizeof(arr) / sizeof(arr[0]);

	double* result = filter(arr, size, isEven);

	// After filtering, the result should only contain {2.0, 4.0, 6.0}
	EXPECT_DOUBLE_EQ(result[0], 2.0);
	EXPECT_DOUBLE_EQ(result[1], 4.0);
	EXPECT_DOUBLE_EQ(result[2], 6.0);

	// Don't forget to free the dynamically allocated memory
	delete[] result;
}

// Test Case 3: Testing the filter function with no elements passing the filter
TEST(FilterTest, NoElementsPassFilter) {
	double arr[] = {1.0, 3.0, 5.0, 7.0};
	int size = sizeof(arr) / sizeof(arr[0]);

	double* result = filter(arr, size, isEven);

	// After filtering, no elements should be returned as all numbers are odd
	EXPECT_EQ(result, nullptr);

	// Don't forget to free the dynamically allocated memory
	delete[] result;
}

// Test Case 4: Testing the filter function with an empty array
TEST(FilterTest, EmptyArrayReturnsNull) {
	double* arr = nullptr;
	int size = 0;

	double* result = filter(arr, size, isEven);

	// Since the array is empty, the result should be nullptr
	EXPECT_EQ(result, nullptr);
}

// Test Case 5: Testing map function with negative numbers
TEST(MapTest, HandlesNegativeNumbers) {
	double arr[] = {-1.0, -2.0, -3.0, -4.0};
	int size = sizeof(arr) / sizeof(arr[0]);

	map(arr, size, square);

	// After applying map, the array should become {1.0, 4.0, 9.0, 16.0}
	EXPECT_DOUBLE_EQ(arr[0], 1.0);
	EXPECT_DOUBLE_EQ(arr[1], 4.0);
	EXPECT_DOUBLE_EQ(arr[2], 9.0);
	EXPECT_DOUBLE_EQ(arr[3], 16.0);
}

//////////////////////////
//////   Q3 Tests   //////
//////////////////////////

// Test Case 1: Testing HTML tag creation with two attributes
TEST(CreateHTMLTagTest, TwoAttributes) {
	char* html = createHTMLTag("a", 2, "href", "https://example.com", "target",
							   "_blank");

	// Expected output: <a href="https://example.com" target="_blank"></a>
	EXPECT_STREQ(html,
				 "<a href=\"https://example.com\" target=\"_blank\"></a>");

	free(html);	 // Free the dynamically allocated memory
}

// Test Case 2: Testing HTML tag creation with no attributes
TEST(CreateHTMLTagTest, NoAttributes) {
	char* html = createHTMLTag("div", 0);

	// Expected output: <div></div>
	EXPECT_STREQ(html, "<div></div>");

	free(html);	 // Free the dynamically allocated memory
}

// Test Case 3: Testing HTML tag creation with multiple attributes
TEST(CreateHTMLTagTest, MultipleAttributes) {
	char* html = createHTMLTag("input", 3, "type", "text", "name", "username",
							   "value", "john_doe");

	// Expected output: <input type="text" name="username"
	// value="john_doe"></input>
	EXPECT_STREQ(
		html,
		"<input type=\"text\" name=\"username\" value=\"john_doe\"></input>");

	free(html);	 // Free the dynamically allocated memory
}

// Test Case 4: Testing HTML tag creation with attribute names containing
// special characters
TEST(CreateHTMLTagTest, SpecialCharactersInAttributes) {
	char* html =
		createHTMLTag("div", 2, "class", "container", "data-id", "1234");

	// Expected output: <div class="container" data-id="1234"></div>
	EXPECT_STREQ(html, "<div class=\"container\" data-id=\"1234\"></div>");

	free(html);	 // Free the dynamically allocated memory
}

// Test Case 5: Testing the memory allocation with a large number of attributes
TEST(CreateHTMLTagTest, ManyAttributes) {
	char* html = createHTMLTag("input", 5, "type", "text", "name", "field",
							   "placeholder", "Enter text", "maxlength", "255",
							   "required", "");

	EXPECT_STREQ(html,
				 "<input type=\"text\" name=\"field\" placeholder=\"Enter "
				 "text\" maxlength=\"255\" required=\"\"></input>");

	free(html);	 // Free the dynamically allocated memory
}
