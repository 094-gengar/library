#ifdef COMPRO
#include <string>
#include <vector>
#include <cassert>
#include <cmath>

namespace m9::compro {
	struct RollingHash {
		RollingHash(const std::string& s, long long base = -1) : _n(s.size()) {
			if (base == -1) base = 1e9 + 7;
			hs.assign(_n + 1, 0);
			pw.assign(_n + 1, 1);
			for (size_t i = 0; i < _n; i++) {
				hs[i + 1] = (mul(hs[i], base) + s[i]) % mod;
				pw[i + 1] = mul(pw[i], base) % mod;
			}
		}

		long long get(int l, int r) {
			assert(l <= r and 0 <= l and r <= _n);
			return (hs[r] - mul(hs[l], pw[r - l]) % mod + mod) % mod;
		}

		long long get_all() {
			return get(0, _n);
		}

		int get_LongestCommonPrefix(int a, int b) {
			assert(a >= 0 and b >= 0 and a < _n and b < _n);
			int ok = 0, ng = std::min(_n - a, _n - b);
			while (abs(ok - ng) > 1) {
				int mid = (ok + ng) / 2;
				(get(a, a + mid) != get(b, b + mid) ? ng : ok) = mid;
			}
			return ok;
		}

	private:
		int _n;
		const long long mod = (1ll << 61) - 1;
		long long base;
		std::vector<long long> hs{}, pw{};

		long long mul(long long x, long long y) {
			return (__int128_t)(x) * y % mod;
		}
	};
} // namespace m9::compro

#endif