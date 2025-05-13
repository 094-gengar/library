#ifdef COMPRO
#include <vector>

namespace m9::compro {
	struct Combination {
		unsigned int n;
		std::vector<std::vector<long long>> combination;
		Combination(unsigned int n) : n(n) {
			combination.assign(n + 1, std::vector<long long>(n + 1, 0));
			combination[0][0] = 1;
			for (size_t i = 0; i < n; i++) for (size_t j = 0; j <= i; j++) {
				// combination[i][j] %= 1000000;
				combination[i + 1][j] += combination[i][j];
				combination[i + 1][j + 1] += combination[i][j];
			}
		}
	};

	template <class M> struct CombinationMint {
		unsigned int n;
		std::vector<M> fact;
		CombinationMint(unsigned int n) : n(n) {
			fact.resize(n + 1);
			fact[0] = 1;
			for (size_t i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
		}
		M nPr(int n, int r) { return n < 0 or r < 0 or n < r ? 0 : fact[n] / fact[n - r]; }
		M nCr(int n, int r) { return n < 0 or r < 0 or n < r ? 0 : nPr(n, r) / fact[r]; }
		M nHr(int n, int r) { return n < 0 or r + n - 1 < 0 or r + n - 1 < r ? 0 : nCr(r + n - 1, r); }
	};
}

#endif
