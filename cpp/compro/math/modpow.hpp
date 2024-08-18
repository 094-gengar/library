#ifdef COMPRO
#include <iostream>

namespace m9::compro {
	long long mod_inv(long long x, const long long& mod) {
		long long a = x, b = mod, u = 1, v = 0;
		while (b) {
			long long t = a / b;
			a -= t * b;
			std::swap(a, b);
			u -= t * v;
			std::swap(u, v);
		}
		return (u % mod + mod) % mod;
	}

	long long mod_pow(long long x, long long n, const long long& mod)  {
		if (n < 0) return mod_inv(mod_pow(x, -n, mod), mod);
		long long r = 1;
		for (; n; x *= x, n >>= 1) if (n & 1) {
			(r *= x) %= mod;
		}
		return (r % mod + mod) % mod;
	}
} // m9::compro

#endif