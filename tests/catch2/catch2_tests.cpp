#include <catch2/catch_test_macros.hpp>
#include <Comparator/Comparator.hpp>

TEST_CASE("CompareTest", "[CompareLessThan]") { REQUIRE(compare(2, 3) == -1); }

TEST_CASE("CompareTest", "[CompareGreaterThan]") { REQUIRE(compare(3, 2) == +1); }

TEST_CASE("CompareTest", "[CompareEqual]") { REQUIRE(compare(2, 2) == 0); }
