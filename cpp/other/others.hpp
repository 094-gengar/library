#include <cstdlib>
#include <cmath>
#include <climits>
#include <cfloat>
#include <map>
// #include <utility>
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
// #include <bit>
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
#define all(x) std::begin(x), std::end(x)
#define Sort(x) sort(all(x))
#define rSort(x) sort(all(x)); reverse(all(x))
#define UNIQUE(v) v.erase(unique(all(v)), v.end())
#define uniq(v) sort(all(v)); UNIQUE(v)
#define l_b(c, x) distance(begin(c), lower_bound(all(c), (x)))
#define u_b(c, x) distance(begin(c), upper_bound(all(c), (x)))
#define fi first
#define se second
#define m_p make_pair
#define m_t make_tuple
#define pb push_back
#define eb emplace_back
#define cauto const auto&
#define _rep_overload(_1, _2, _3, _4, name, ...) name
#define _rep1(i, n) _rep2(i, 0, n)
#define _rep2(i, a, b) for(ll i = (a); i < (b); i++)
#define _rep3(i, a, b, c) for(ll i = (a); i < (b); i += c)
#define rep(...) _rep_overload(__VA_ARGS__, _rep3, _rep2, _rep1)(__VA_ARGS__)
#define myceil(a, b) ((a) + ((b) - 1)) / (b)
#define continue_with(...) ({__VA_ARGS__; continue;})
#define break_with(...) ({__VA_ARGS__; break;})

namespace m9 {
	using ll = long long;
	using ull = unsigned long long;
	using pii = std::pair<int, int>;
	using pll = std::pair<ll, ll>;
} // namespace m9

namespace m9 {
	template <class T> using V = std::vector<T>;
	using vb = V<std::int8_t>;
	using vi = V<int>;
	using vu = V<unsigned>;
	using vll = V<ll>;
	using vull = V<ull>;
	using vd = V<double>;
	using vc = V<char>;
	using vs = V<std::string>;
	using vpii = V<pii>;
	using vpll = V<pll>;

	using vvb = V<vb>;
	using vvi = V<vi>;
	using vvu = V<vu>;
	using vvll = V<vll>;
	using vvull = V<vull>;
	using vvd = V<vd>;
	using vvc = V<vc>;
	using vvs = V<vs>;
	using vvpii = V<vpii>;
	using vvpll = V<vpll>;

	template <class T>
	inline bool chmin(T& a, const T& b) { if(b < a) { a = b; return true; } return false; }
	template <class T>
	inline bool chmax(T& a, const T& b) { if(a < b) { a = b; return true; } return false; }

	ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
	ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
	ll fact(ll n, ll m) { ll f = n; for(ll i = n - 1; i >= 1; i--) { f *= i; if(m != -1)f %= m; } return f; }

	constexpr ll inf = 0x1fffffffffffffff;
	constexpr ll mod = 1000000007LL;
	constexpr ll mod2 = 998244353LL;
	constexpr double eps = 1e-8;
	constexpr double pi = 3.141592653589793238462643383279;
} // namespace m9

namespace m9 {
	struct sorted_operator {
		template <class T> friend std::vector<T> operator>>(std::vector<T>a, sorted_operator)
			{ std::sort(std::begin(a), std::end(a)); return a; }
		friend std::string operator>>(std::string a, sorted_operator)
			{ std::sort(std::begin(a), std::end(a)); return a; }
	} Sor;
	struct reversed_operator {
		template <class T> friend std::vector<T> operator>>(std::vector<T> a, reversed_operator)
			{ std::reverse(std::begin(a), std::end(a)); return a; }
		friend std::string operator>>(std::string a, reversed_operator)
			{ std::reverse(std::begin(a), std::end(a)); return a; }
	} Rev;
	struct unique_operator {
		template <class T> friend std::vector<T> operator>>(std::vector<T> a, unique_operator)
			{ a.erase(unique(std::begin(a), std::end(a)), std::end(a)); return a; }
		friend std::string operator>>(std::string a, unique_operator)
			{ a.erase(unique(std::begin(a), std::end(a)), std::end(a)); return a; }	
	} Set;
	template <class T>
	void INCVEC(std::vector<T>& a) { for(T& e : a)e++; }
	template <class T>
	void DECVEC(std::vector<T>& a) { for(T& e : a)e--; }
	struct inc_operator {
		template <class T> friend std::vector<T> operator>>(std::vector<T> a, inc_operator)
			{ INCVEC(a); return a; }
	} Inc;
	struct dec_operator {
		template <class T> friend std::vector<T> operator>>(std::vector<T> a, dec_operator)
			{ DECVEC(a); return a; }
	} Dec;
	template <class T, class F>
	auto operator>> (std::vector<T> a, F f) -> std::vector<decltype(f(a.front()))>
	{
		std::vector<decltype(f(a.front()))> res{};
		for(const T& e : a)res.emplace_back(f(e));
		return res;
	}
} // namespace m9

// debug

#ifdef ONLINE_JUDGE
#define dbg(...) void(0)
#else
#define dbg(...) _debug(#__VA_ARGS__, __VA_ARGS__)
#endif

namespace m9 {
	template <class Car, class... Cdr>
	void _debug(const char* s, Car&& car, Cdr&&... cdr)
	{
		constexpr const char* open_br = sizeof...(cdr) == 0 ? "" : "(";
		constexpr const char* close_br = sizeof...(cdr) == 0 ? "" : ")";
#ifdef MY_FASTIO_VER2
		wt_any(open_br); wt_any(s); wt_any(close_br);
		wt_any(" : ");
		wt_any(open_br); wt_any(std::forward<Car>(car));
		((wt_any(", "), wt_any(std::forward<Cdr>(cdr))), ...);
		wt_any(close_br); wt_any("\n");
#else
		std::cerr << open_br << s << close_br << " : " << open_br << std::forward<Car>(car);
		((std::cerr << ", " << std::forward<Cdr>(cdr)), ...);
		std::cerr << close_br << "\n";
#endif
	}
} // namespace m9