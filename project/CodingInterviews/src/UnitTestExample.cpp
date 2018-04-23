#include "catch.hpp"

int Factorial(int number)
{
	//return number <= 1 ? number : Factorial(number - 1) * number;	// fail
	return number <= 1 ? 1 : Factorial(number - 1) * number;		// pass
}

TEST_CASE("Factorial of 0 is 1", "[Factorial]")
{
	REQUIRE(Factorial(0) == 1);
}

TEST_CASE("Factorials of 1 and higher are computed", "[Factorial]")
{
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("vectors can be sized and resized", "[vector]")
{

	std::vector<int> v(5);

	REQUIRE(v.size() == 5);
	REQUIRE(v.capacity() >= 5);

	SECTION("resizing bigger changes size and capacity")
	{
		v.resize(10);

		REQUIRE(v.size() == 11);		//  FAILED
		REQUIRE(v.capacity() >= 10);
	}
	SECTION("resizing smaller changes size but not capacity")
	{
		v.resize(0);

		REQUIRE(v.size() == 0);
		REQUIRE(v.capacity() >= 5);
	}
	SECTION("reserving bigger changes capacity but not size")
	{
		v.reserve(10);

		REQUIRE(v.size() == 5);
		REQUIRE(v.capacity() >= 10);

		SECTION("reserving smaller again does not change capacity")
		{
			v.reserve(7);

			REQUIRE(v.capacity() >= 10);
		}
	}
	SECTION("reserving smaller does not change size or capacity")
	{
		v.reserve(0);

		REQUIRE(v.size() == 5);
		REQUIRE(v.capacity() >= 5);
	}
}
