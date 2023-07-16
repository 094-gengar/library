// #include <utility>
#include <iostream>

namespace m9 {

template<class T> auto GridtoT(const T width, const T x, const T y) -> T {
	return x * width + y;
}

template<class T> auto GridtoT(const T width, const std::pair<T, T> p) -> T {
	return p.first * width + p.second;
}

template<class T> auto TtoGrid(const T width, const T N) -> std::pair<T, T> {
	return std::make_pair(N / width, N % width);
}

} // namespace m9