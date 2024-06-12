#pragma once

#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <compare>

namespace rds {

template <class T, std::size_t N>
class array_it {
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;
public: // ctor
	array_it(): ptr_(nullptr), off_(0) {}
	array_it(T* ptr, std::size_t off=0): ptr_(ptr), off_(off) {}
	array_it(const array_it&) = default;
	array_it(array_it&&) = default;
	array_it& operator=(const array_it&) = default;
	array_it& operator=(T* ptr) {
		ptr_ = ptr;
		off_ = 0;
		return *this;
	}
public:
	const reference operator*() const {
		return *(ptr_ + off_);
	}
	reference operator*() {
		return const_cast<reference>(static_cast<const array_it&>(*this).operator*());
	}
	pointer operator->() const {
		return ptr_ + off_;
	}
public:
	bool operator==(const array_it& o) const {
		return ptr_ == o.ptr_ && off_ == o.off_;
	}
	bool operator!=(const array_it& o) const {
		return !operator==(o);
	}
	bool operator>(const array_it& o) const {
		return ptr_ == o.ptr_ && off_ > o.off_;
	}
	bool operator>=(const array_it& o) const {
		return operator>(o) || operator==(o);
	}
	bool operator<(const array_it& o) const {
		return ptr_ == o.ptr_ && off_ < o.off_;
	}
	bool operator<=(const array_it& o) const {
		return operator<(o) || operator==(o);
	}
public:
	array_it& operator+=(const difference_type& diff) {
		off_ += diff;
		return *this;
	}
	array_it& operator-=(const difference_type& diff) {
		off_ -= diff;
		return *this;
	}
	array_it& operator++() {
		++off_;
		return *this;
	}
	array_it& operator--() {
		--off_;
		return *this;
	}
	array_it operator++(int) {
		auto t(*this);
		++(*this);
		return t;
	}
	array_it operator--(int) {
		auto t(*this);
		--(*this);
		return t;
	}
	array_it operator+(const difference_type& diff) const {
		return array_it(ptr_, off_ + diff);
	}
	array_it operator-(const difference_type& diff) const {
		return array_it(ptr_, off_ - diff);
	}
	difference_type operator-(const array_it& o) const {
		return off_ - o.off_;
	}
protected:
	T* ptr_;
	std::size_t off_;
}; // class array_it

template <class T, std::size_t N>
class array_rit: public array_it<T, N> {
public:
	using array_it<T, N>::ptr_; // NOTE
	using array_it<T, N>::off_;
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type*;
	using reference = value_type&;

public:
	array_rit(): array_it<T, N>() {}
	array_rit(T* ptr, std::size_t off=0): array_it<T, N>(ptr, off) {}
public:
	array_rit(const array_it<T, N>& oth): array_it<T, N>(oth) {}
public:
	const reference operator*() const {
		return *(ptr_ + (N - 1 - off_));
	}
	reference operator*() {
		return const_cast<reference>(static_cast<const array_rit&>(*this).operator*());
	}
public:
}; // class array_rit

/// @brief 정적 배열 템플릿 클래스
template <class T, std::size_t N>
class array {
public: // 기본 생성자
	array() = default;
	array(const array&) = default;
	array(array&&) = default;
	array& operator=(const array&) = default;
	array& operator=(array&&) = default;
	~array() = default;
public: // 생성자
	array(const T& init) {
		for (std::size_t i = 0; i < N; ++i)
			data_[i] = init;
	}
	array(const std::initializer_list<T>& il) {
		for (std::size_t i = 0; i < N; ++i)
			data_[i] = *(il.begin() + i);
	}
	array& operator=(const std::initializer_list<T>& il) {
		for (std::size_t i = 0; i < N; ++i)
			data_[i] = *(il.begin() + i);
	}
public: // 접근
	const T& operator[](std::size_t i) const {
		return data_[i];
	}
	T& operator[](std::size_t i) {
		return const_cast<T&>(static_cast<const array&>(*this)[i]);
	}
	const T& front() const {
		return data_[0];
	}
	T& front() {
		return const_cast<T&>(static_cast<const array&>(*this).front());
	}
public: // 용량
	std::size_t capacity() const {
		return N;
	}
	std::size_t size() const {
		return N;
	}
	std::size_t max_size() const {
		return N;
	}
	bool empty() const {
		return false;
	}
public: // 연산
	void fill(const T& v) {
		for (std::size_t i = 0; i < N; ++i)
			data_[i] = v;
	}
	void swap(array& oth) {
		for (std::size_t i = 0; i < N; ++i)
			std::swap(data_[i], oth.data_[i]);
	}
public: // 반복자
	using iterator = array_it<T, N>;
	using const_iterator = array_it<const T, N>;
	using reverse_iterator = array_rit<T, N>;
	using const_reverse_iterator = array_rit<const T, N>;

	iterator begin() {
		return iterator(data_, 0);
	}
	iterator end() {
		return iterator(data_, N);
	}
	const_iterator cbegin() const {
		return const_iterator(data_, 0);
	}
	const_iterator cend() const {
		return const_iterator(data_, N);
	}
	reverse_iterator rbegin() {
		return reverse_iterator(data_, 0);
	}
	reverse_iterator rend() {
		return reverse_iterator(data_, N);
	}
	const_reverse_iterator crbegin() const {
		return const_reverse_iterator(data_, 0);
	}
	const_reverse_iterator crend() const {
		return const_reverse_iterator(data_, N);
	}
public:
	auto operator<=>(const array&) const = default;

private:
	T data_[N];
}; // class array

/// @brief array 템플릿 클래스의 크기 0인 특수화
template <class T>
class array<T, 0> {
public: // Default Ctor
	array() = default;
	array(const array&) = delete;
	array(array&&) = delete;
	array& operator=(const array&) = delete;
	array& operator=(array&&) = delete;
	~array() = default;
public:  // Capacity
	std::size_t capacity() const {
		return 0;
	}
	std::size_t size() const {
		return 0;
	}
	std::size_t max_size() const {
		return 0;
	}
	bool empty() const {
		return true;
	}
public: // Iterators
	using iterator = array_it<T, 0>;
	using const_iterator = array_it<const T, 0>;
	using reverse_iterator = array_rit<T, 0>;
	using const_reverse_iterator = array_rit<const T, 0>;

	iterator begin() {
		return iterator();
	}
	iterator end() {
		return iterator();
	}
	const_iterator cbegin() const {
		return const_iterator();
	}
	const_iterator cend() const {
		return const_iterator();
	}
	reverse_iterator rbegin() {
		return reverse_iterator();
	}
	reverse_iterator rend() {
		return reverse_iterator();
	}
	const_reverse_iterator crbegin() const {
		return const_reverse_iterator();
	}
	const_reverse_iterator crend() const {
		return const_reverse_iterator();
	}
private:
	T* data_ = nullptr;
}; // class array<T, 0>



}; // namespace rds