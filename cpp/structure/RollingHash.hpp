#include <vector>
#include <cassert>
#include <cmath>

namespace m9 {

using ll = long long;

template<class T> struct RollingHash {
private:
	int N;
	const ll MOD = (1ll << 61) - 1;
	ll base;
	std::vector<ll> Hs{}, Pw{};
	ll mul(ll x, ll y) const { return (__int128_t)(x) * y % MOD; }
public:
	RollingHash() = default;
	RollingHash(const T& s, ll base = -1) : N(s.size()) {
		if(base == -1){ base = base = 1e9 + 7; }
		Hs.assign(N + 1, 0); Pw.assign(N + 1, 1);
		for(int i{}; i < N; i++)
		{
			Hs[i + 1] = (mul(Hs[i], base) + s[i]) % MOD;
			Pw[i + 1] = (mul(Pw[i], base)) % MOD;
		}
	}

	ll get(const int l, const int r) const
	{
		assert(l <= r and 0 <= l and r <= N);
		return (Hs[r] - mul(Hs[l], Pw[r - l]) % MOD + MOD) % MOD;
	}

	ll getAll() const { return get(0, N);}

	int getLCP(const int a, const int b) const
	{
		assert(a >= 0 and b >= 0 and a < N and b < N);
		int ok{0}, ng{std::min(N - a, N - b)};
		while(abs(ok - ng) > 1)
		{
			int mid = (ok + ng) / 2;
			(get(a, a + mid) != get(b, b + mid) ? ng : ok) = mid;
		}
		return ok;
	}
};
}
