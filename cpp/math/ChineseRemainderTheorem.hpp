#include <vector>
#include <cassert>

namespace m9 {
using ll = long long;

namespace m9_crt {
template<class T> T ext_gcd(T a, T b, T &x, T &y)
{
    if(b == 0)
	{
        x = 1, y = 0;
        return a;
    }
    T d = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

} // m9_crt

template<class T>
std::pair<T, T> ChnRemThm(std::vector<T>& r, std::vector<T>& m)
{
	assert(r.size() == m.size());
	int n = r.size();
	ll ret_r{0}, ret_m{1};
	for(int i{0}; i < n; i++)
	{
		assert(m[i] >= 1);
		ll p{}, q{};
		ll g = m9_crt::ext_gcd(ret_m, m[i], p, q);
		if((r[i] - ret_r) % g != 0) { return std::make_pair((T)0, (T)0); }
		ll tmp = (r[i] - ret_r) / g * p % (m[i] / g);
		ret_r += ret_m * tmp;
		ret_m *= m[i] / g;
		ret_r = (ret_r % ret_m + ret_m) % ret_m;
	}

	return std::make_pair(ret_r, ret_m);
}

} // namespace m9