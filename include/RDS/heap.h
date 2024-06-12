#pragma once

#include <cstddef>
#include <vector>
#include <functional>

namespace rds {

/// @brief vector를 사용하는 힙
/// @tparam HeapProp 적용할 힙 속성
template <class T, class HeapProp=std::greater<T>>
class Heap {
public:
	Heap() = default;
	Heap(std::vector<T> const& vec) {
		vec_.reserve(vec.capacity());
		for (auto const& e: vec)
			insert(e);
	}
	bool size() const {
		return vec_.size();
	}
	bool empty() const {
		return vec_.empty();
	}
	// TODO T const& 를 반환하는게 의미가 있는지
	T const& top() const {
		return vec_.front();
	}
	void insert(T const& v) {
		vec_.push_back();
		bubble_up(get_li_i(), get_p_i(get_l_i()));
	}
	T extract() {
		auto const ret = vec_.front();
		vec_.front() = vec_.back();
		vec_.pop_back();
		bubble_down(0);
		return ret;
	}
	T push_pop(T const& v) {
		if (empty()) {
			return v;
		}
		if (HeapProp()(v, top())) {
			return v;
		}
		auto const ret = top();
		vec_[0] = v;
		bubble_down(0);
	}
	std::size_t find_i(T const& v) const {
		return find_i(v, std::equal_to<T>());
	}
	template <class Compare>
	std::size_t find_i(T const& v, Compare comp) const {
		for (std::size_t i = 0; i < size(); ++i) {
			if (comp(vec_[i], v)) {
				return i;
			}
		}
		return size();
	}
	bool del(T const& v) {
		return del(v, equal_to<T>());
	}
	template <class Compare>
	bool del(T const& v, Compare comp) {
		auto const f_i = find_i(v, comp);

		if (f_i == size()) {
			return false;
		}
		vec_[f_i] = vec_[get_l_i()];
		vec_.pop_back();
		if (f_i != 0) {
			auto const p_i = get_p_i(f_i);

			if (!HeapProp()(vec_[p_i], vec_[f_i])) {
				bubble_up(f_i, p_i);
			} else {
				bubble_down(f_i);
			}
		} else {
			bubble_down(f_i);
		}
		return true;
	}
private:
	void bubble_up(std::size_t c_i, std::size_t p_i) {
		if (c_i == 0) {
			return;
		}
		auto& c = vec_[c_i];
		auto& p = vec_[p_i];

		if (!HeapProp()(c, p)) {
			return;
		}

		std::swap(c, p);
		bubble_up(p_i, get_p_i(p_i));
	}
	void bubble_down(std::size_t p_i) {
		auto const cl_i = get_cl_i(p_i);

		if (!(cl_i < size())) {
			return;
		}
		
		auto t_i = cl_i; // target index
		auto const cr_i = get_cr_i(p_i);

		if (cr_i < size()) {
			t_i = HeapProp()(vec_[cl_i], vec_[cr_i]) ? cl_i : cr_i;
		}

		if (HeapProp()(vec_[p_i], vec_[t_i])) {
			return;
		}

		std::swap(vec_[p_i], vec_[t_i]);
		bubble_down(t_i);j
	}
	std::size_t get_l_i() const {
		return vec_.size();
	}
	std::size_t get_p_i(std::size_t i) const {
		return --i / 2;
	}
	std::size_t get_cl_i(std::size_t i) const {
		return 2 * i + 1;
	}
	std::size_t get_cr_i(std::size_t i) const {
		return get_cl_i(i) + 1;
	}
	std::vector<T> vec_;
};

}; // namespace rds;