#include <vector>
#include <cstddef>
#include <cmath>
#include <cstdio>

namespace rds {

/// @brief Complete Binary Template Class
/// @details Implemented with array(vector)
template <class T>
class cbtree {
private: // Utilities
	using size_t = std::size_t;
	/// @brief  \p i 번째 노드의 부모의 인덱스를 반환
	static inline size_t get_pi(size_t i) {
		return i / 2;
	}
	/// @brief \p i 번재 노드의 좌측 자식의 인덱스를 반환
	static inline size_t get_lchi(size_t i) {
		return 2 * i + 1;
	}
	/// @brief \p i 번째 노드가 속한 레벨을 반환
	static inline size_t get_lv(size_t i) {
		return static_cast<size_t>(std::log2(++i));
	}
	/// @brief \p lvi 번 레벨의 \p ioff 번째 노드의 번호를 반환
	static inline size_t i_by_lv(size_t lvi, size_t ioff) {
		return static_cast<size_t>(std::pow(2, lvi)) - 1 + ioff;
	}
	/// @brief \p lv 의 갯수에 얼마나 많은 노드가 들어있어야 하는지 반환
	static size_t get_full_size(size_t lv) {
		if (lv == 0) 
			return 1;
		return static_cast<size_t>(std::pow(2, lv)) + get_full_size(lv - 1);
	}
public: // ctors
	cbtree(std::vector<T> const& nodes): nodes_(nodes) {}
	cbtree(size_t size, bool size_is_lv=false) {
		if (!size_is_lv) {
			nodes_ = std::vector<T>(size);
		} else {
			nodes_ = std::vector<T>(get_full_size(size));
		}
	}
	cbtree(size_t size, T const& v, bool size_is_lv=false) {
		if (!size_is_lv) {
			nodes_ = std::vector<T>(size, v);
		} else {
			nodes_ = std::vector<T>(get_full_size(size), v);
		}
	}
public: // sizes
	/// @brief 존재하는 노드의 총 갯수를 반환
	size_t size() const {
		return nodes_.size();
	}
	/// @brief 존재하는 레벨의 총 갯수를 반환
	size_t lv() const {
		return get_lv(size() - 1) + 1;
	}
	/// @brief 트리가 포화 상태인지 여부를 반환
	bool full() const {
		return size() == get_full_size(lv() - 1);
	}
public: // member access
	/// @brief \p i 번 노드 값의 참조를 반환
	T const& at(size_t i) const {
		return nodes_[i];
	}
	T& at(size_t i) {
		return const_cast<T&>(static_cast<cbtree<T> const&>(*this).at(i));
	}
	/// @brief \p lvi 번 레벨의 \p io 번째 노드 값의 참조를 반환
	T const& at_lv(size_t lvi, size_t io) const {
		return nodes_[i_by_lv(lv, io)];
	}
	T& at_lv(size_t lvi, size_t io) {
		return const_cast<T&>(static_cast<cbtree<T> const&>(*this).at_lv(lvi, io));
	}
	/// @brief 루트 노드 값의 참조를 반환
	T const& root() const {
		return nodes_.front();
	}
	T& root() {
		return const_cast<T&>(static_cast<cbtree<T> const&>(*this).root());
	}
	/// @brief 최하단 레벨의 최우측 노드 값의 참조를 반환
	T const& back() const {
		return nodes_.back();
	}
	T& back() {
		return const_cast<T&>(static_cast<cbtree<T> const&>(*this).back());
	}
public: // modifiers
	void push_back(T const& v) {
		nodes_.push_back(v);
	}
	void pop_back() {
		nodes_.pop_back();
	}
	template <class U>
	friend void println(cbtree<U> const&);

private:
	std::vector<T> nodes_;
};

template <class U>
void println(cbtree<U> const& t) { /* no impl */ }

#ifdef _MSC_VER
#include <format>

template <>
void println(cbtree<int> const& t) {
	std::cout << 
	std::format("==cbtree(size: {:0>2} level: {:0>2})==\n", t.size(), t.lv());

	int lv = -1;	
	for (int i = 0; i < t.size(); ++i) {
		const auto clv = cbtree<int>::get_lv(i); // current level printing
		if (clv != lv) {
			if (i != 0) 
				std::cout << '\n';
			std::cout << std::format("lv{:0>2}: ", clv)
			lv = clv;
		}

		std::cout << format("[{:0>2}] ", t.at(i));
	}
	cout << '\n';
}
#else
template <>
void println(cbtree<int> const& t) {
	std::printf("==cbtree(size: %d lvs: %d)==\n", t.size(), t.lv());

	int lv = -1;	
	for (int i = 0; i < t.size(); ++i) {
		const auto clv = cbtree<int>::get_lv(i); // current level printing
		if (clv != lv) {
			if (i != 0) 
				std::printf("\n");
			std::printf("lv%d: ", clv);
			lv = clv;
		}

		std::printf("[%d] ", t.at(i));
	}
	std::printf("\n");
}
#endif
}; // namespace rds;