#ifdef COMPRO
#include <vector>
#include <cassert>

namespace m9::compro::crt {
	template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>> T ext_gcd(T a, T b, T& x, T& y) {
		if (b == 0) { x = 1, y = 0; return a; }
		T d = ext_gcd(b, a % b, y, x);
		y -= a / b * x;
		return d;
	} 
} // namespace m9::compro::crt

namespace m9::compro {
	template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
	std::pair<T, T> chinese_remainder_theorem(std::vector<T>& r, std::vector<T>& m) {
		assert(r.size() == m.size());
		auto n = r.size();
		long long res_r = 0, res_m = 1;
		for (size_t i = 0; i < n; i++) {
			assert(m[i] >= 1);
			long long p = 0, q = 0;
			long long g = crt::ext_gcd(res_m, m[i], p, q);
			if ((r[i] - res_r) % g != 0) return std::pair{0, 0};
			long long tmp = (r[i] - res_r) / g * p % (m[i] / g);
			res_r += res_m * tmp;
			res_m *= m[i] / g;
			res_r = (res_r % res_m + res_m) % res_m;
		}
		return std::make_pair(res_r, res_m);
	}
} // namespace m9::compro

#endif