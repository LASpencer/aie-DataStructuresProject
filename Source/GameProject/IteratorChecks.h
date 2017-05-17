#pragma once
#include <type_traits>
#include <iterator>

// Define templated types for SFINAE checking of iterator template parameters

//TODO make RequireIteratorType valid
//namespace las {
//
//	// Require Input Iterator referencing type T
//	template<typename Iterator, typename T>
//	using RequireIteratorType = typename std::enable_if<std::is_same<std::iterator_traits<Iterator>::value_type, T>::value, Iterator > ;
//}