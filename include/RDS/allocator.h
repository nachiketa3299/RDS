#pragma once
#include <vector>
#include <utility>
#include <cstddef>
#include <memory>

namespace rds {

template <class T>
class allocator {
public:
	using value_type = T;
	using pointer = T*;
	using size_type = std::size_t;

	size_type max_size() const {
		return size_type(-1) / sizeof(T);
	}

	pointer allocate(size_type n) {
		if (n > max_size()) {
			throw std::bad_alloc();
		}

		return static_cast<pointer>(::operator new(n * sizeof(value_type)));
	}

	void deallocate(pointer p, size_type n) {
		::operator delete(p);
	}

	template <class U, class... Args>
	void construct(U* p, Args&&... args) {
		::new (static_cast<void*>(p)) U(std::forward<Args>(args)...);
	}

	template <class U>
	void destroy(U* p) {
		p->~U();
	}

};

template <class T, class U>
bool operator==(const allocator<T>&, const allocator<U>&) {
	return true;
}

template <class T, class U>
bool operator!=(const allocator<T>&, const allocator<U>&) {
	return false;
}

} // namespace rds