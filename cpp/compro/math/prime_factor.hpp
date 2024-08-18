#ifdef COMPRO
#include <vector>

namespace m9::compro {
	template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
	std::vector<std::pair<T, T>> prime_factor(T n) {
		std::vector<std::pair<T, T>> ret;
		for (T i = 2; i * i <= n; i++) {
			if (n % i != 0) continue;
			T tmp = 0;
			while (n % i == 0) {
				tmp++;
				n /= i;
			}
			ret.emplace_back(i, tmp);
		}
		if (n != 1) ret.emplace_back(n, 1);
		return ret;
	}
} // m9::compro

#endif