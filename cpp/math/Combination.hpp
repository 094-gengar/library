#include <cassert>
#include <vector>

namespace m9 {
template<class T> struct combination {
	using ll = long long;
	ll N;
	std::vector<T> fct;
	combination(ll n) : N(n)
	{
		fct.resize(N + 1);
		fct[0] = 1;
		for(ll i{1}; i <= N; i++)fct[i] = fct[i - 1] * i;
	}
	T nPr(ll n, ll r) { return n < 0 || r < 0 || n < r ? (T)(0) : fct[n] / fct[n - r]; }
	T nCr(ll n, ll r) { return n < 0 || r < 0 || n < r ? (T)(0) : nPr(n, r) / fct[r]; }
	T nHr(ll n, ll r) {return n < 0 || r + n - 1 < 0 || n < r + n - 1 ? (T)(0) : nCr(r + n - 1, r); }
};
} // namespace m9