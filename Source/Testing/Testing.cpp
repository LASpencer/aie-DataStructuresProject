// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Array.h"
#include "Stack.h"
#include "List.h"
#include "Queue.h"
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
	las::List<int> list;
	
	SECTION("Front and Back") {
		//TODO test front and back values
		REQUIRE_THROWS(list.front());	//empty list has no front
		REQUIRE_THROWS(list.back());
		list.push_back(5);
		REQUIRE(list.front() == 5);
		REQUIRE(list.back() == 5);
		list.push_back(7);
		REQUIRE(list.front() == 5);
		REQUIRE(list.back() == 7);
		list.push_front(12);
		REQUIRE(list.front() == 12);
	}
	SECTION("Push and Pop") {
		REQUIRE_THROWS(list.pop_back());
		REQUIRE_THROWS(list.pop_front());
		list.push_front(3);
		list.push_front(7);
		list.push_back(8);
		REQUIRE(list.front() == 7);
		REQUIRE(list.back() == 8);
		REQUIRE(list.pop_back() == 8);
		REQUIRE(list.back() == 3);
		REQUIRE(list.pop_front() == 7);

	}
	SECTION("Initializer List Constructor") {
		//TODO test constructors
		las::List<int> list2{ 7,11,13,17,19,5,3 };
		REQUIRE(list2.front() == 7);
		REQUIRE(list2.back() == 3);
		REQUIRE(list2.pop_front() == 7);
		REQUIRE(list2.pop_front() == 11);
		REQUIRE(list2.pop_back() == 3);
		REQUIRE(list2.pop_back() == 5);
		REQUIRE(list2.pop_front() == 13);
		REQUIRE(list2.pop_front() == 17);
		REQUIRE(list2.pop_front() == 19);
		REQUIRE_THROWS(list2.pop_front());
	}
	//TODO test move, move assignment
	//TODO test copy, copy assignment
	SECTION("List Equality") {
		las::List<int> list2;
		REQUIRE(list == list2);
		REQUIRE_FALSE(list != list2);
		list.push_back(7);
		REQUIRE_FALSE(list == list2);
		REQUIRE(list != list2);
		list2 = { 7,5,3 };
		list.push_back(5);
		list.push_back(3);
		REQUIRE(list == list2);
		REQUIRE_FALSE(list != list2);
	}
	SECTION("Insert") {
		list = { 1,2,3,4,5 };
		las::List<int>::iterator it = list.begin();
		las::List<int>::iterator returned;
		returned = list.insert(it, 0);
		// Test insert single value
		REQUIRE(list == las::List<int>({ 0,1,2,3,4,5 }));
		REQUIRE(returned == it);
		it = it + 2;
		returned = list.insert(it, 9);
		REQUIRE(list == las::List<int>({ 0,1,2,9,3,4,5 }));
		REQUIRE(returned == it);
		returned = list.insert(list.end(), 10);
		REQUIRE(list == las::List<int>({ 0,1,2,9,3,4,5,10 }));
		REQUIRE(returned == list.end());
		// Test fill insert
		list.insert(it, 0, 9);
		REQUIRE(list == las::List<int>({ 0,1,2,9,3,4,5,10 }));
		list.insert(it, 2, 7);
		REQUIRE(list == las::List<int>({ 0,1,2,9,7,7,3,4,5,10 }));
		list.insert(list.begin(), 3, 12);
		REQUIRE(list == las::List<int>({ 12,12,12,0,1,2,9,7,7,3,4,5,10 }));
		list.insert(list.end(), 2, 8);
		REQUIRE(list == las::List<int>({ 12,12,12,0,1,2,9,7,7,3,4,5,10,8,8 }));
		las::List<int> list2;
		list2.insert(list2.end(), 3, 8);
		REQUIRE(list2 == las::List<int>({ 8,8,8 }));
	}
	SECTION("Erase") {
		list = { 1,2,3,4,5,6 };
		las::List<int>::iterator pos = list.begin();
		pos = list.erase(pos);
		REQUIRE(*pos == 2);
		REQUIRE(list == las::List<int>({ 2,3,4,5,6 }));
		REQUIRE(list.front() == 2);
		pos = pos + 2;
		REQUIRE(*(list.erase(pos)) == 5);
		REQUIRE(list == las::List<int>({ 2,3,5,6 }));
		REQUIRE_THROWS(list.erase(list.end()));
		// Erase from middle of list
		list = { 1,2,3,4,5,6,7,8 };
		pos = list.begin()+2;
		las::List<int>::iterator last = pos+2;
		// Throw if invalid range
		REQUIRE_THROWS(list.erase(last, pos));
		list.erase(pos, last);
		REQUIRE(list == las::List<int>({1,2,5,6,7,8}));
		// Erase from end of list
		pos = list.end()-2;
		list.erase(pos, list.end());
		REQUIRE(list == las::List<int>({ 1,2,5,6}));
		REQUIRE(list.back() == 6);
		// erase from front of list
		last = list.begin()+2;
		list.erase(list.begin(), last);
		REQUIRE(list == las::List<int>({ 5,6 }));
		REQUIRE(list.front() == 5);
		// erase entire list
		list.erase(list.begin(), list.end());
		REQUIRE(list.size() == 0);
		REQUIRE_THROWS(list.front());
		REQUIRE_THROWS(list.back());

		//TODO erase throws exception if iterator not from list
	}
	SECTION("Clear") {
		list = { 1,2,3,4,5,6 };
		CHECK(list.size() == 6);
		list.clear();
		REQUIRE(list.size() == 0);
		REQUIRE_THROWS(list.front());
		REQUIRE_THROWS(list.back());
	}
	SECTION("Remove") {
		list = { 1,2,5,2,3,5,4,1 };
		list.remove(2);
		REQUIRE(list == las::List<int>({ 1,5,3,5,4,1 }));
		list.remove(1);
		REQUIRE(list == las::List<int>({ 5,3,5,4 }));
	}
}

TEST_CASE("List Iterator", "[list][container][iterator]") {
	las::List<int> list{ 1,2,3,4,5,6 };
	SECTION("Insert by range") {
		las::List<int> list2{ 20,30,40,50,60 };
		las::List<int> list3;
		las::List<int>::iterator first = list.begin() + 2;
		las::List<int>::iterator last = list.end() - 1;
		las::List<int>::iterator pos = list2.begin() + 2;
		list2.insert(pos, first, last);
		REQUIRE_THROWS(list2.insert(first, first, last));
		REQUIRE(list2 == las::List<int>({ 20,30,3,4,5,40,50,60 }));
		list3.insert(list3.end(), first, last);
		REQUIRE(list3 == las::List<int>({ 3,4,5 }));
	}
	SECTION("Range constructor") {
		las::List<int>::iterator first = list.begin()+2;
		las::List<int>::iterator last = list.end()-1;
		las::List<int> list2(first, last);
		REQUIRE(list2 == las::List<int>({ 3,4,5 }));
	}
	/* TODO test ListIter, based on http://www.cplusplus.com/reference/iterator/ */
	// TODO insert from list iterator to stl container
}

TEST_CASE("List Algorithms", "[list][container][iterator][algorithm]") {
	las::List<int> list{5,1,9,-6,4,2};
	SECTION("Is Sorted") {
		las::List<int> list2{ -6,1,2,4,5,7 };
		REQUIRE_FALSE(std::is_sorted(list.begin(),list.end()));
		REQUIRE(std::is_sorted(list2.begin(), list2.end()));
	}
	SECTION("Rotate") {
		las::List<int>::iterator middle = list.begin() + 3;
		std::rotate(list.begin(), middle, list.end());
	}
	SECTION("Reverse") {
		std::reverse(list.begin(), list.end());
		REQUIRE(list == las::List<int>({ 2,4,-6,9,1,5 }));
	}
}

TEST_CASE("Integer Queue", "[queue][container") {
	las::Queue<int> queue;
	SECTION("Size and Empty") {
		REQUIRE(queue.empty());
		REQUIRE(queue.size() == 0);
		las::Queue<int> q2{ 1,2,3,4,5 };
		REQUIRE_FALSE(q2.empty());
		REQUIRE(q2.size() == 5);
	}
	SECTION("Front and Back") {
		queue = { 1,2,3,4,5 };
		REQUIRE(queue.front() == 1);
		REQUIRE(queue.back() == 5);
		queue.front() = 10;
		REQUIRE(queue.front() == 10);
	}
	SECTION("Push and Pop") {
		REQUIRE_THROWS(queue.pop());
		queue.push(7);
		queue.push(3);
		queue.push(9);
		REQUIRE(queue.front() == 7);
		REQUIRE(queue.back() == 9);
		REQUIRE(queue.size() == 3);
		REQUIRE(queue.pop() == 7);
		REQUIRE(queue.size() == 2);
		REQUIRE(queue.pop() == 3);
		REQUIRE(queue.pop() == 9);
		REQUIRE_THROWS(queue.pop());
		REQUIRE(queue.empty());
	}
}

TEST_CASE("Integer Deque", "[queue][deque][container]") {
	las::Deque<int> deque;
	SECTION("Size and Empty") {
		REQUIRE(deque.empty());
		REQUIRE(deque.size() == 0);
		las::Deque<int> deque2{ 1,2,3,4,5 };
		REQUIRE_FALSE(deque2.empty());
		REQUIRE(deque2.size() == 5);
	}
	SECTION("Front and Back") {
		deque = { 1,2,3,4,5 };
		REQUIRE(deque.front() == 1);
		REQUIRE(deque.back() == 5);
		deque.front() = 10;
		REQUIRE(deque.front() == 10);
		deque.back() = 9;
		REQUIRE(deque.back() == 9);
	}
	SECTION("Push and Pop") {
		REQUIRE_THROWS(deque.pop_back());
		REQUIRE_THROWS(deque.pop_front());
		deque.push_back(7);
		deque.push_back(10);
		deque.push_front(13);
		deque.push_front(8);
		REQUIRE(deque.front() == 8);
		REQUIRE(deque.back() == 10);
		REQUIRE(deque.pop_front() == 8);
		REQUIRE(deque.pop_back() == 10);
		REQUIRE(deque.pop_back() == 7);
		REQUIRE(deque.pop_back() == 13);
		REQUIRE_THROWS(deque.pop_back());
		REQUIRE_THROWS(deque.pop_front());
		REQUIRE(deque.empty());
	}
	SECTION("Peek") {
		REQUIRE_THROWS(deque.peek(0));
		deque = { 1,2,3,4,5 };
		REQUIRE(deque.peek(0) == 1);
		REQUIRE(deque.peek(3) == 4);
		REQUIRE(deque.peek(4) == 5);
		REQUIRE(deque.peek(5) == 5);
	}

}

int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


