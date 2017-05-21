// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Array.h"
#include "Stack.h"
#include "List.h"
#include <algorithm>

#include <vector>
#include <sstream>

TEST_CASE("Integer Array", "[array][container]") {
	las::Array<int> arr;

	REQUIRE((arr.size() == 0));
	REQUIRE(arr.empty());
	REQUIRE(arr.capacity() == las::Array<int>::def_capacity);

	SECTION("Value constructor") {
		las::Array<int> arr2(5, 2);
		REQUIRE(arr2.size() == 5);
		REQUIRE(arr2[4] == 2);
		CHECK(arr2.capacity() == std::max(las::Array<int>::def_capacity, 8u));
	}

	SECTION("Copy Constructor") {
		arr = { 1,1,2,3,5 };
		las::Array<int> arr2 = arr;
		REQUIRE(arr2[4] == 5);
	}

	SECTION("Initializer list") {
		arr = { 3,2,1,5,6 };
		REQUIRE(arr.size() == 5);
		REQUIRE(arr[0] == 3);
		REQUIRE(arr[2] == 1);
		REQUIRE(arr[4] == 6);
	}

	SECTION("Equality operator") {
		arr = las::Array<int>(2, 5);
		las::Array<int> arr2(3, 5);
		// Different sizes are not equal
		REQUIRE(!(arr == arr2));
		REQUIRE(arr != arr2);
		arr.push_back(5);
		// Same size and elements
		REQUIRE(arr == arr2);
		REQUIRE(!(arr != arr2));
		// Different elements are not equal
		arr[2] = 3;
		REQUIRE(arr != arr2);
		REQUIRE(!(arr == arr2));
	}

	SECTION("Subscript operator") {
		// Out of Bounds exception when index >= size
		REQUIRE_THROWS_AS(arr[3], std::out_of_range);
		arr = { 3,2,1,5,6 };
		REQUIRE_THROWS_AS(arr[5], std::out_of_range);
		// Can read from subscript
		REQUIRE(arr[3] == 5);
		// Can write with subscript
		arr[2] = 7;
		REQUIRE(arr[2] == 7);
	}

	SECTION("Reserve and shrink array") {
		// Reserve less than current capacity
		arr.reserve(3);
		REQUIRE(arr.capacity() == las::Array<int>::def_capacity);
		// Reserve increases to next power of 2
		arr.reserve(12);
		REQUIRE(arr.capacity() == 16);
		// Shrink to greater capacity does nothing
		arr.shrink_to_fit(30);
		REQUIRE(arr.capacity () == 16);
		// Shrink to smaller capacity
		arr.shrink_to_fit(3);
		REQUIRE(arr.capacity() == 4);
		// Shrink to current size
		arr.shrink_to_fit();
		REQUIRE(arr.capacity() == 2);
		arr.push_back(3, 9);
		arr.shrink_to_fit();
		REQUIRE(arr.capacity() == 16);
	}

	SECTION("Push and Pop") {
		arr.push_back(7);
		arr.push_back(3);
		arr.push_back(8, 3);
		REQUIRE(arr[0] == 7);
		REQUIRE(arr[1] == 3);
		REQUIRE(arr[2] == 8);
		REQUIRE(arr[4] == 8);
		REQUIRE(arr.pop_back() == 8);
		REQUIRE(arr.pop_back() == 8);
		REQUIRE(arr.pop_back() == 8);
		REQUIRE(arr.pop_back() == 3);
		REQUIRE(arr.size() == 1);
		REQUIRE(arr.pop_back() == 7);
		CHECK(arr.empty());
		REQUIRE_THROWS_AS(arr.pop_back(), std::out_of_range);	//Popping empty array throws exception
	}

	SECTION("Insert") {
		arr = { 1,2,3,4,5 };
		arr.insert(3, 9);
		REQUIRE(arr[3] == 9);
		REQUIRE(arr[2] == 3);
		REQUIRE(arr[4] == 4);
		REQUIRE(arr.size() == 6);
		arr.insert(2, 8, 3);
		REQUIRE(arr[1] == 2);
		REQUIRE(arr[2] == 8);
		REQUIRE(arr[4] == 8);
		REQUIRE(arr[5] == 3);
		REQUIRE(arr[6] == 9);
		REQUIRE(arr[7] == 4);
		REQUIRE(arr.size() == 9);
	}

	SECTION("Erase and clear") {
		arr = { 1,2,3,4,5,6 };
		REQUIRE_THROWS_AS(arr.erase(7), std::out_of_range);
		las::Array<int>::iterator next = arr.erase(3);
		REQUIRE(next == &(arr[3]));
		REQUIRE(*next == 5);
		REQUIRE(arr == las::Array<int>({1, 2, 3, 5, 6}));
		arr.clear();
		REQUIRE(arr == las::Array<int>());
	}
}

TEST_CASE("Array Iterator", "[array][container][iterator]") {
	las::Array<int> arr{ 1,2,3,5,8,13 };
	las::Array<int> arr2{ 2,4,8,16,32 };
	std::vector<int> vec = { 3,5,6,7,4 };
	SECTION("Range Constructor") {
		las::Array<int>::iterator start, end;
		las::Array<int> arr2(arr.begin(), arr.end());
		REQUIRE(arr == arr2);
		start = arr.begin() + 2;
		end = start + 3;
		las::Array<int> arr3(start, end);
		REQUIRE(arr3 == las::Array<int>({ 3,5,8 }));
		// Test Array
		arr3 = las::Array<int>(vec.begin(), vec.end());
		REQUIRE(arr3 == las::Array<int>({ 3,5,6,7,4 }));
	}
	SECTION("Insert") {
		arr.insert(arr.begin() + 2, 4);
		REQUIRE(arr == las::Array<int>({ 1,2,4,3,5,8,13 }));
		arr.insert(arr.begin() + 4, 9, 3);
		REQUIRE(arr == las::Array<int>({ 1,2,4,3,9,9,9,5,8,13 }));
		REQUIRE_THROWS(arr.insert(arr.end() + 1, 2));
		REQUIRE_THROWS(arr.insert(arr.begin() - 1, 2));
		REQUIRE_THROWS(arr.insert(arr.end() + 1, 2, 2));
		REQUIRE_THROWS(arr.insert(arr.begin() - 1, 2, 2));
	}
	SECTION("Insert from range") {
		arr.insert(arr.begin() + 3, arr2.begin() + 2, arr2.end());
		REQUIRE(arr == las::Array<int>({ 1,2,3,8,16,32,5,8,13 }));
		REQUIRE_THROWS(arr.insert(arr.begin() - 1, arr2.begin() + 2, arr2.end()));
		REQUIRE_THROWS(arr.insert(arr.end() + 1, arr2.begin() + 2, arr2.end()));
		REQUIRE_THROWS(arr.insert(arr.begin() + 3, arr2.end(), arr2.begin()+2));
		arr2.insert(arr2.begin() + 1, vec.begin()+1, vec.begin()+3);
		REQUIRE(arr2 == las::Array<int>({ 2,5,6,4,8,16,32 }));
	}
	SECTION("Erase from range") {
		REQUIRE(*(arr.erase(arr.begin() + 2)) == 5);
		REQUIRE(arr == las::Array<int>({ 1,2,5,8,13 }));
		las::Array<int>::iterator newEnd = arr.erase(arr.begin() + 3, arr.end());
		REQUIRE(newEnd == arr.end());
		REQUIRE(arr == las::Array<int>({ 1,2,5 }));
		REQUIRE_THROWS(arr.erase(arr.end() + 1));
		REQUIRE_THROWS(arr.erase(arr.begin() - 1));
		REQUIRE_THROWS(arr.erase(arr.begin(), arr.end() + 1));
		REQUIRE_THROWS(arr.erase(arr.begin() - 1, arr.begin() + 1));
		REQUIRE_THROWS(arr.erase(arr.end(), arr.end() + 1));
		REQUIRE_THROWS(arr.erase(arr.begin() + 2, arr.begin()+1));
	}
}

TEST_CASE("Array Input Iterator", "[array][container][iterator][io]") {
	std::istringstream in("Hello, world!");
	las::Array<char> arrchar;
	SECTION("Range Constructor") {
		las::Array<char>arrchar = las::Array<char>(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
		REQUIRE(arrchar == las::Array<char>({ 'H','e','l','l','o',',',' ','w','o','r','l','d','!' }));
	}
	SECTION("Insert from range") {
		arrchar.push_back('n', 4);
		arrchar.insert(arrchar.begin() + 2, std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
		REQUIRE(arrchar == las::Array<char>({ 'n','n','H','e','l','l','o',',',' ','w','o','r','l','d','!','n','n' }));
	}
}

TEST_CASE("Array Algorithms", "[array][container][iterator][algorithm]") {
	las::Array<int> arr{6,99,-3,48,12,354,-98,1,35,0};
	SECTION("Sort") {
		std::sort(arr.begin(), arr.end());
		REQUIRE(arr == las::Array<int>({ -98,-3,0,1,6,12,35,48,99,354 }));
	}
	SECTION("Rotate") {
		std::rotate(arr.begin(), arr.begin() + 4, arr.end());
		REQUIRE(arr == las::Array<int>({ 12,354,-98,1,35,0,6,99,-3,48 }));
	}
	SECTION("Search") {
		REQUIRE(std::find(arr.begin(), arr.end(), 48) == arr.begin() + 3);
	}
}

TEST_CASE("Integer Stack", "[stack][container]") {
	las::Stack<int> s;
	//TODO test cases
	SECTION("Push and Pop") {
		//Pop value from empty stack throws exception
		REQUIRE_THROWS(s.pop());
		REQUIRE_THROWS(s.top());
		s.push(8);
		REQUIRE(s.top() == 8);
		s.push(3);
		REQUIRE(s.top() == 3);
		REQUIRE(s.pop() == 3);
		REQUIRE(s.top() == 8);
		REQUIRE(s.pop() == 8);
		REQUIRE_THROWS(s.top());
	}
	SECTION("Size and Empty") {
		REQUIRE(s.empty());
		REQUIRE(s.size() == 0);
		s.push(3);
		REQUIRE_FALSE(s.empty());
		REQUIRE(s.size() == 1);
		s.push(1);
		s.push(19);
		s.push(-2423);
		REQUIRE(s.size() == 4);
		// add enough elements to force resize
		s.push(1);
		s.push(19);
		s.push(-2423);
		s.push(1);
		s.push(19);
		REQUIRE(s.size() == 9);
		s.pop();
		s.pop();
		s.pop();
		REQUIRE(s.size() == 6);
		s.pop();
		s.pop();
		s.pop();
		s.pop();
		s.pop();
		s.pop();
		REQUIRE(s.empty());
	}
	
	SECTION("Peek") {
		REQUIRE_THROWS(s.peek(0));
		s.push(3);
		s.push(8);
		REQUIRE(s.peek(0) == 8);	//Peek at top
		REQUIRE(s.peek(1) == 3);		//Peek at next element
		REQUIRE(s.peek(2) == 3);		//Peeking past bottom hits bottom
	}
	
	SECTION("Value Constructor") {
		s = { 12,16,4,72,5 };
		REQUIRE(s.size() == 5);
		REQUIRE(s.top() == 5);
		REQUIRE(s.peek(1) == 72);
		REQUIRE(s.peek(3) == 16);
	}
}

//TODO test list
TEST_CASE("Integer List", "[list][container]") {

}

/* TODO test ListIter, based on http://www.cplusplus.com/reference/iterator/ */

int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


