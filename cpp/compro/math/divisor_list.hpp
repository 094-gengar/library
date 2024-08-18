#ifdef COMPRO
#include <vector>
#include <algorithm>

namespace m9::compro {
	template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
	std::vector<T> divisor_list(const T& n) {
		std::vector<T> result;
		for (T i = 1; i * i <= n; i++) {
			if (n % i == 0) {
				result.emplace_back(i);
				if (i * i != n) result.emplace_back(n / i);
			}
		}
		sort(begin(result), end(result));
		return result;
	}
} // namespace m9::compro

#endif