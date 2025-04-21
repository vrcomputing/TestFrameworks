#include <gtest/gtest.h>
#include <Comparator/Comparator.hpp>

// Test case
TEST(CompareTest, CompareLessThan) { EXPECT_EQ(compare(2, 3), -1); }

TEST(CompareTest, CompareGreaterThan) { EXPECT_EQ(compare(3, 2), +1); }

TEST(CompareTest, CompareEqual) { EXPECT_EQ(compare(3, 3), 0); }