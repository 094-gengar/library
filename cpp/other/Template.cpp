#include <cstdlib>
#include <cmath>
#include <climits>
#include <cfloat>
#include <map>
#include <utility>
#include <set>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <sstream>
#include <deque>
#include <complex>
#include <stack>
#include <queue>
#include <cstdio>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <chrono>
#include <iterator>
#include <bitset>
#include <numeric>
#include <list>
#include <iomanip>
#include <cassert>
#include <array>
#include <tuple>
#include <initializer_list>
#include <unordered_set>
#include <unordered_map>
#include <forward_list>
#include <random>
#include <regex>
//#define INCLUDE_BOOST
#ifdef INCLUDE_BOOST
#if __has_include(<boost/range/irange.hpp>)
#include <boost/range/irange.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/classification.hpp>
#endif
#endif
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,fma,abm,mmx,avx,avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define all(x) begin(x), end(x)
#define Sort(x) sort(all(x))
#define rSort(x) sort(all(x)); reverse(all(x))
#define UNIQUE(v) v.erase(unique(all(v)), v.end())
#define uniq(v) sort(all(v)); UNIQUE(v)
#define l_b(c, x) distance(begin(c), lower_bound(all(c), (x)))
#define u_b(c, x) distance(begin(c), upper_bound(all(c), (x)))
#define fi first
#define se second
#define m_p make_pair
#define pb push_back
#define eb emplace_back
#define cauto const auto&
#define _overload3(_1, _2, _3, name, ...) name
#define _rep(i, n) repi(i, 0, n)
#define repi(i, a, b) for (ll i = (a), __B_SIZE__ = (b); i < __B_SIZE__; i++)
#define rep(...) _overload3(__VA_ARGS__, repi, _rep, )(__VA_ARGS__)
#define myceil(a, b) ((a) + ((b)-1)) / (b)

#include <utility>

//#define int long long
using ll = long long;
using ull = unsigned long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

#include <vector>
#include <string>

template<class T>
using Vec = std::vector<T>;
using vb = Vec<bool>;
using vi = Vec<int>;
using vu = Vec<unsigned>;
using vl = Vec<ll>;
using vul = Vec<ull>;
using vd = Vec<double>;
using vc = Vec<char>;
using vs = Vec<std::string>;
using vpii = Vec<pii>;
using vpll = Vec<pll>;

using vvb = Vec<vb>;
using vvi = Vec<vi>;
using vvu = Vec<vu>;
using vvl = Vec<vl>;
using vvul = Vec<vul>;
using vvd = Vec<vd>;
using vvc = Vec<vc>;
using vvs = Vec<vs>;
using vvpii = Vec<vpii>;
using vvpll = Vec<vpll>;

template <class T>
inline bool chmin(T& a, const T& b)
{
	if(b < a)
	{
		a = b;
		return true;
	}
	return false;
}
template <class T>
inline bool chmax(T& a, const T& b)
{
	if(a < b)
	{
		a = b;
		return true;
	}
	return false;
}

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
ll fact(ll n, ll m)
{
	ll f = n;
	for(ll i = n - 1; i >= 1; i--)
	{
		f *= i;
		if(m != -1)f %= m;
	}
	return f;
}
constexpr ll inf = 0x1fffffffffffffff;
constexpr ll mod = 1000000007LL;
constexpr ll mod2 = 998244353LL;
constexpr double eps = 1e-8;
constexpr double pi = 3.141592653589793238462643383279;
