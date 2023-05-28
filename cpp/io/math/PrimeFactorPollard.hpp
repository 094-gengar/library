#include <vector>
#include <numeric>
#include <algorithm>

namespace m9 {
using ll = long long;

namespace m9_pfp {
template<class T> T PM(T X, T N, T M)
{
	T ret{1};
	while(N > 0)
	{
		if(N & 1) { (ret *= X) %= M; }
		(X *= X) %= M;
		N >>= 1;
	}
	return ret;
}

bool IP(ll N)
{
	if(N <= 1) { return false; }
	if(N == 2 || N == 3) { return true; }
	if(N % 2 == 0) { return false; }
	auto A = std::vector<ll>{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	ll s{}, d{N - 1};
	while(d % 2 == 0) { s++; d >>= 1; }
	for(const auto& a : A)
	{
		if(a % N == 0) { return true; }
		ll t, x = PM<__int128_t>(a, d, N);
		if(x != 1)
		{
			for(t = 0; t < s; t++)
			{
				if(x == N - 1) { break; }
				x = (__int128_t)(x) * x % N;
			}
			if(t == s) { return false; }
		}
	}
	return true;
}

} // namespace m9_pfp

ll pollard(ll N)
{
	if(N % 2 == 0)return 2;
	if(m9_pfp::IP(N)) { return N; }
	auto f = [&](ll x) -> ll {
		return ((__int128_t(x) * x + 1) % N);
	};
	ll step{};
	while(true)
	{
		step++;
		ll x = step;
		ll y = f(x);
		while(true)
		{
			ll p = std::gcd(y - x + N, N);
			if(p == 0 || p == N) { break; }
			if(p != 1) { return p; }
			x = f(x);
			y = f(f(y));
		}
	}
}

std::vector<ll> primeFactPollard(ll N)
{
	if(N == 1) { return std::vector<ll>{}; }
	ll p = pollard(N);
	if(p == N) { return std::vector<ll>{p}; }
	std::vector<ll> L = primeFactPollard(p), R = primeFactPollard(N / p);
	L.insert(std::end(L), std::begin(R), std::end(R));
	std::sort(std::begin(L), std::end(L));
	return L;
}
}