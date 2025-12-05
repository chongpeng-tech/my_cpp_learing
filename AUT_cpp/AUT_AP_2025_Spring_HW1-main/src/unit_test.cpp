
#include <vector>
#include "Q2_Sort_By_Distance.h"
#include "Q3_Count_Islands.h"
#include "gtest/gtest.h"

// ####################################
// ############## Q1 Tests ############
// ####################################

// TEST 1
// Helper lambda to compute the squared Euclidean distance of a point.
auto squared_distance = [](const std::array<double, 3>& pt) -> double {
	return pt[0] * pt[0] + pt[1] * pt[1] + pt[2] * pt[2];
};

// TEST 2
// Test case for an empty vector of points.
TEST(SortPointsByDistanceTest, EmptyVector) {
	std::vector<std::array<double, 3>> points;
	sort_points_by_distance(points);
	EXPECT_TRUE(points.empty())
		<< "Empty vector should remain empty after sorting.";
}

// TEST 3
// Test case for a vector with a single point.
TEST(SortPointsByDistanceTest, SingleElement) {
	std::vector<std::array<double, 3>> points = {{{1.0, 2.0, 3.0}}};
	sort_points_by_distance(points);
	ASSERT_EQ(points.size(), 1)
		<< "Single element vector should have exactly one element.";
	EXPECT_DOUBLE_EQ(points[0][0], 1.0)
		<< "Single element's x coordinate changed unexpectedly.";
	EXPECT_DOUBLE_EQ(points[0][1], 2.0)
		<< "Single element's y coordinate changed unexpectedly.";
	EXPECT_DOUBLE_EQ(points[0][2], 3.0)
		<< "Single element's z coordinate changed unexpectedly.";
}

// TEST 4
// Test case for multiple points.
// Verifies that after sorting, the points are in non-decreasing order of
// distance.
TEST(SortPointsByDistanceTest, MultiplePoints) {
	std::vector<std::array<double, 3>> points = {
		{{3, 4, 0}}, {{1, 1, 1}}, {{0, 0, 5}}};
	sort_points_by_distance(points);

	// Verify that the squared distances are in non-decreasing order.
	for (size_t i = 1; i < points.size(); ++i) {
		EXPECT_LE(squared_distance(points[i - 1]), squared_distance(points[i]))
			<< "Points not sorted correctly at indices " << i - 1 << " and "
			<< i << ".";
	}
}

// TEST 5
// Test case where all points have the same Euclidean distance.
TEST(SortPointsByDistanceTest, IdenticalDistances) {
	std::vector<std::array<double, 3>> points = {
		{{1, 2, 2}}, {{2, 1, 2}}, {{2, 2, 1}}};
	sort_points_by_distance(points);
	for (size_t i = 1; i < points.size(); ++i) {
		EXPECT_DOUBLE_EQ(squared_distance(points[i - 1]),
						 squared_distance(points[i]))
			<< "Points with identical distances do not have equal squared "
			   "distances at indices "
			<< i - 1 << " and " << i << ".";
	}
}

// ####################################
// ############## Q2 Tests ############
// ####################################

// TEST 1
// Test case for an empty grid.
TEST(CountIslandsTest, EmptyGrid) {
	std::vector<std::vector<int>> grid;
	EXPECT_EQ(count_islands(grid), 0) << "Empty grid should return 0 islands.";
}

// TEST 2
// Test case where the grid contains only water (0s).
TEST(CountIslandsTest, NoIslands) {
	std::vector<std::vector<int>> grid = {{0, 0, 0}, {0, 0, 0}};
	EXPECT_EQ(count_islands(grid), 0)
		<< "A grid with only water (0's) should return 0 islands.";
}

// TEST 3
// Test case for a grid that is entirely land (all 1s) forming a single island.
TEST(CountIslandsTest, SingleIslandAllOnes) {
	std::vector<std::vector<int>> grid = {{1, 1}, {1, 1}};
	EXPECT_EQ(count_islands(grid), 1)
		<< "A grid with all ones should count as 1 island.";
}

// TEST 4
// Test case using the example provided in the assignment.
// Expected islands count is 3.
TEST(CountIslandsTest, MultipleIslands) {
	std::vector<std::vector<int>> grid = {
		{1, 1, 0, 0, 0}, {1, 1, 0, 0, 1}, {0, 0, 1, 0, 1}, {0, 0, 0, 1, 1}};
	EXPECT_EQ(count_islands(grid), 3)
		<< "The provided example grid should have 3 islands.";
}

// TEST 5
// Test case to ensure that diagonal connections are not counted as connected.
TEST(CountIslandsTest, DiagonalIslandsNotConnected) {
	std::vector<std::vector<int>> grid = {{1, 0, 1}, {0, 1, 0}, {1, 0, 1}};
	// Expected islands: Each '1' is isolated (since diagonal adjacency is not
	// allowed).
	EXPECT_EQ(count_islands(grid), 5)
		<< "Diagonal islands should not be connected; expected 5 islands.";
}

// TEST 6
// Additional complex test case with a large grid that is challenging to count
// by hand.
TEST(CountIslandsTest, ComplexLargeGrid) {
	std::vector<std::vector<int>> grid = {
		{1, 0, 1, 0, 0, 1, 1, 0, 0, 0}, {1, 0, 1, 0, 1, 1, 1, 0, 1, 0},
		{0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, {1, 1, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 1, 1, 0, 0, 1, 0}, {1, 0, 0, 1, 0, 1, 0, 1, 1, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
		{0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, {1, 1, 1, 0, 0, 1, 1, 0, 1, 0}};

	EXPECT_EQ(count_islands(grid), 17)
		<< "The complex large grid should return 17 islands.";
}
