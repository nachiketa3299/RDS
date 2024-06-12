#pragma once
#include <numeric>
#include <cstddef>

#include "allocator.h"

namespace rds {

template <class T>
class vector_it {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
public:
	vector_it(): ptr_(nullptr), off_(0) {}
	vector_it(T* ptr, std::size_t off=0): ptr_(ptr), off_(off) {}
	vector_it(const vector_it&) = default;
	vector_it(vector_it&&) = default;
	vector_it& operator=(const vector_it&) = default;
	vector_it& operator=(T* ptr) {
		ptr_ = ptr;
		off_ = 0;
		return *this;
	}
public:
	const reference operator*() const {
		return *(ptr_ + off_);
	}
	reference operator*() {
		return const_cast<reference>(static_cast<const vector_it&>(*this).operator*());
	}
	pointer operator->() const {
		return ptr_ + off_;
	}
public:
	// TODO 제대로 작동하는지 확인할 것
	auto operator<=>(const vector_it& o) const {
		return off_ <=> o.off_;
	}
public:
	vector_it& operator+=(const difference_type& diff) {
		off_ += diff;
		return *this;
	}
	vector_it& operator-=(const difference_type& diff) {
		off_ -= diff;
		return *this;
	}
	vector_it& operator++() {
		++off_;
		return *this;
	}
	vector_it& operator--() {
		--off_;
		return *this;
	}
	vector_it& operator++(int) {
		auto t(*this);
		++(*this);
		return t;
	}
	vector_it& operator--(int) {
		auto t(*this);
		--(*this);
		return t;
	}
	vector_it operator+(const difference_type& diff) {
		return vector_it(ptr_, off_ + diff);
	}
	vector_it operator-(const difference_type& diff) {
		return vector_it(ptr_, off_ - diff);
	}
	difference_type operator-(const vector_it& o) const {
		return off_ - o.off_;
	}
protected:
	T* ptr_;
	std::size_t off_;
}; // class vector_it

template <class T>
class vector_rit: public vector_it<T>{
public:
	using vector_it<T>::ptr_;
	using vector_it<T>::off_;
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;

public:
	vector_rit(): vector_it<T>() {}
	vector_rit(T* ptr, std::size_t off=0): vector_it<T>(ptr, off) {}
public:
	vector_rit(const vector_it<T>& o): vector_it<T>(o) {}
public: // TODO
	const reference operator*() const { }
	reference operator*() {}
}; // class vector_rit

template <class T, class alloc=allocator<T>>
class vector {
public:
	vector() = default;
	vector(const vector&) = default;
	vector(vector&&) = default;
	vector& operator=(const vector&) = default;
	vector& operator=(vector&&) = default;
	~vector() {
		// destroy all elements
		for (std::size_t i = 0; i < size_; ++i) {
			(data_ + i)->~T();
		}
		// deallocate
		::operator delete(data_);
	}
public: // TODO implement custom allocator
	vector(std::size_t size): size_(size), capacity_(size) {
		// allocate
		data_ = static_cast<T*>(::operator new(sizeof(T) * size));

		// construct
		for (std::size_t i = 0; i < size_; ++i) {
			::new (data_ + i) T();
		}
	}
	vector(std::size_t size, const T& val): size_(size), capacity_(size) {
		// allocate
		data_ = static_cast<T*>(::operator new(sizeof(T) * size));

		// construct
		for (std::size_t i = 0; i < size_; ++i) {
			::new (data_ + i) T(val);
		}
	}
public:
	void reserve(std::size_t cap) {
		if (cap <= capacity_) {
			return;
		}

		capacity_ = cap;

		const auto* prev = data_;

		// allocate
		data_ = static_cast<T*>(::operator new(sizeof(T) * capacity_));
		for (std::size_t i = 0; i < size_; ++i) {
			// construct
			::new (data_ + i) T(prev[i]);

			// destroy
			(prev + i)->~T();
		}

		// deallocate
		::operator delete(const_cast<T*>(prev));
	}
public:
	std::size_t size() const {
		return size_;
	}
	std::size_t capacity() const {
		return capacity_;
	}
	bool empty() const {
		return size_ == 0;
	}
	std::size_t max_size() const {
		return std::numeric_limits<std::size_t>::max();
	}

private:
	std::size_t size_ = 0;
	std::size_t capacity_ = 0;
	T* data_ = nullptr;
}; // class vector

}; // namespace rds