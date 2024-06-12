#pragma once

#include <initializer_list>
#include <iterator>

namespace rds {

template <class T>
class list_it {
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
public:

}; // class list_it

template <class T>
class list_rit: public list_it<T> {
}; // class list_rit

template <class T>
class list {
	template <class T>
	struct node2 {
		node2(): next(nullptr), prev(nullptr) {}
		node2(const T& val, node2* prev=nullptr, node2* next=nullptr): 
			val(val), next(next), prev(prev) {}
		node2* next, prev;
		T val;
	}; // struct node2

};


} // namespace rds