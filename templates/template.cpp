// made by https://github.com/094-gengar/add_lib_to_templ
#if !__INCLUDE_LEVEL__
#include __FILE__

int32_t main()
{
	using namespace std;
	
}

#else

// #line 2 "graph/Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

template <class T>
struct graph
{
	template <class _T>
	inline bool chmin(_T& a, const _T& b)
	{
		if(b < a)
		{
			a = b;
			return true;
		}
		return false;
	}
	int _n;
	bool _idx;
	bool _drc;
	std::vector<std::vector<T>> _g;
	graph(int n, bool drc = false, bool idx = 1)
		: _n(n), _drc(drc), _idx(idx), _g(n)
	{
	}
	void init(int m)
	{
		T a, b;
		for(int i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			a -= _idx;
			b -= _idx;
			_g[a].emplace_back(b);
			if(!_drc)
				_g[b].emplace_back(a);
		}
	}
	std::vector<T> bfs(T s, T t = -1)
	{
		std::vector<T> dis(_n, 1ll << 29);
		std::vector<bool> vis(_n, false);
		dis[s] = 0;
		std::queue<T> q;
		q.emplace(s);
		while(q.size())
		{
			T cur = q.front();
			q.pop();
			for(auto e : _g[cur])
				if(chmin(dis[e], dis[cur] + 1))
					q.emplace(e);
		}
		if(t == -1)
			return dis;
		else
			return std::vector<T>{dis[t]};
	}
};

template <class T>
struct weighted_graph
{
	using ptt = std::pair<T, T>;
	int _n;
	bool _idx;
	bool _drc;
	std::vector<std::vector<ptt>> _g;
	weighted_graph(int n, bool drc = false, bool idx = 1)
		: _n(n), _drc(drc), _idx(idx), _g(n)
	{
	}
	void init(int m, bool cst = true)
	{
		T a, b, c = 1;
		for(int i = 0; i < m; i++)
		{
			if(cst)
				scanf("%d %d %d", &a, &b, &c);
			else
				scanf("%d %d", &a, &b);
			a -= _idx;
			b -= _idx;
			_g[a].emplace_back(c, b);
			if(!_drc)
				_g[b].emplace_back(c, a);
		}
	}
	std::vector<T> bfs(T s, T t = -1)
	{
		std::vector<T> dis(_n, 1ll << 29);
		std::vector<bool> vis(_n, false);
		dis[s] = 0;
		std::queue<ptt> q;
		q.emplace(0, s);
		while(q.size())
		{
			ptt cur = q.front();
			q.pop();
			if(cur.first > dis[cur.second])
				continue;

			for(auto e : _g[cur.second])
				if(chmin(dis[e.second], dis[cur.second] + e.first))
					q.emplace(dis[e.second], e.second);
		}
		if(t == -1)
			return dis;
		else
			return std::vector<T>{dis[t]};
	}

	std::vector<T> dijkstra(T s, T t = -1)
	{
		std::vector<T> dis(_n, 1ll << 29);
		std::vector<bool> vis(_n, false);
		dis[s] = 0;
		std::priority_queue<ptt, std::vector<ptt>, std::greater<>> pq;
		pq.emplace(0, s);
		while(pq.size())
		{
			ptt cur = pq.top();
			pq.pop();
			if(cur.first > dis[cur.second])
				continue;
			for(auto e : _g[cur.second])
				if(chmin(dis[e.second], dis[cur.second] + e.first))
					pq.emplace(dis[e.second], e.second);
		}
		if(t == -1)
			return dis;
		else
			return std::vector<T>{dis[t]};
	}
};


// #line 2 "graph/SCC.hpp"
#include <vector>
#include <algorithm>
#include <set>

struct SCC
{
private:
	int n{};
	std::vector<std::vector<int>> g{}, rg{};
	std::vector<int> ord{}, comp{};
	std::vector<bool> usd{};

public:
	void dfs(int cur)
	{
		usd[cur] = true;
		for(const auto& e : g[cur])
			if(not usd[e])
				dfs(e);
		ord.emplace_back(cur);
	}
	void rdfs(int cur, int k)
	{
		comp[cur] = k;
		for(const auto& e : rg[cur])
			if(comp[e] == -1)
				rdfs(e, k);
	}
	SCC(std::vector<std::vector<int>>& _g) : g(_g)
	{
		(*this).n = static_cast<int>((*this).g.size());
		(*this).rg.resize(n);
		(*this).comp.assign(n, -1);
		(*this).usd.assign(n, false);
		for(int v = 0; v < n; v++)
			for(const auto& e : g[v])
				rg[e].emplace_back(v);
		for(int v = 0; v < n; v++)
			if(not usd[v])
				dfs(v);
		int k = 0;
		std::reverse(std::begin(ord), std::end(ord));
		for(const auto& v : ord)
			if(comp[v] == -1)
				rdfs(v, k++);
	};
	bool same(int u, int v)
	{
		return comp[u] == comp[v];
	}
	std::vector<std::vector<int>> rebuild()
	{
		int MX = *std::max_element(std::begin(comp), std::end(comp)) + 1;
		std::vector<std::vector<int>> rebuilded_g(n);
		std::set<std::pair<int, int>> conn{};
		for(int v = 0; v < MX; v++)
			for(const auto& e : g[v])
				if(comp[v] != comp[e] and not conn.count(std::make_pair(v, e)))
				{
					conn.emplace(v, e);
					rebuilded_g[comp[v]].emplace_back(comp[e]);
				}
		return rebuilded_g;
	}
};


// #line 2 "heuristic/RandInt.hpp"
#include <random>
#include <ctime>

struct RandInt
{
private:
	std::mt19937 mt;
public:
	RandInt() { mt.seed((unsigned int)time(0)); }
	unsigned int next() { return mt(); }
	unsigned int roll(int high)
	{
		std::uniform_int_distribution<unsigned int> die(0, high - 1);
		return die(mt);
	}
} ri;


// #line 2 "heuristic/Timer.hpp"
#include <chrono>

struct Timer
{
private:
	std::chrono::system_clock::time_point m_start;
public:
	Timer() : m_start(std::chrono::system_clock::time_point::min()) { (*this).start(); }
	void clear() { m_start = std::chrono::system_clock::time_point::min(); }
	bool is_started() const { return (m_start.time_since_epoch() != std::chrono::system_clock::duration(0)); }
	void start() { m_start = std::chrono::system_clock::now(); }
	unsigned long long get_time()
	{
		if(is_started())
		{
			std::chrono::system_clock::duration diff;
			diff = std::chrono::system_clock::now() - m_start;
			return (unsigned long long)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() + 50;
		}
		return 0;
	}
} timer;


// #line 2 "io/FastIO.hpp"
#include <cstdint>
#include <cassert>
#include <cmath>
#include <unistd.h>
#include <string>
#include <array>
#include <vector>

#define MY_FASTIO

constexpr bool _is_output_only = false;
//constexpr bool _is_output_only = true;

class FastIO
{
private:
	struct fastin
	{
		std::array<signed char, 1048576> _buf;
		ssize_t n_w, n_r;
		fastin() { if constexpr(!_is_output_only)_do_read(); }
		long long rd_ll() noexcept
		{
			long long ret = 0, sgn = 1;
			signed char ch = _current_char();
			while(ch == ' ' || ch == '\n')ch = _next_char();
			if(ch == '-') sgn *= -1, ch = _next_char();
			for(; '0' <= ch && ch <= '9'; ch = _next_char())
			{
				ret = (ret * 10) + ch - '0';
			}
			return sgn * ret;
		}
		int rd_int() noexcept
		{
			long long _result = rd_ll();
			assert(-2147483648ll <= _result && _result <= 2147483647ll);
			return static_cast<int>(_result);
		}
		std::string rd_str() noexcept
		{
			std::string _res{};
			signed char ch = _current_char();
			while(ch == ' ' || ch == '\n')ch = _next_char();
			for(; ch != -1 && ch != '\n' && ch != ' '; ch = _next_char())
			{
				_res += std::string(1, ch);
			}
			return _res;
		}
		char rd_chr() noexcept
		{
			signed char ch = _current_char();
			while(ch == ' ' || ch == '\n')ch = _next_char();
			signed char discard = _next_char();
			return ch;
		}
	private:
		void _do_read() noexcept
		{
			ssize_t r = read(0, &_buf[0], _buf.size());
			assert(r >= 0);
			n_w = r, n_r = 0;
		}
		inline signed char _next_char() noexcept
		{
			if(++n_r == n_w)_do_read();
			return _current_char();
		}
		inline signed char _current_char() noexcept
		{
			return (n_r == n_w ? -1 : _buf[n_r]);
		}
	} fi;

	struct fastout
	{
		unsigned _wt_double_digit = 15;
		inline void wt_bool(bool x) noexcept { putchar_unlocked(x ? '1' : '0'); }
		inline void wt_ll(long long x) noexcept
		{
			std::array<signed char, 32> _buf;
			ssize_t _siz = 0;
			if(x < 0)
			{
				x *= -1;
				putchar_unlocked('-');
			}
			if(x == 0)putchar_unlocked('0');
			while(x > 0)
			{
				_buf[_siz++] = x % 10 + '0';
				x /= 10;
			}
			while(_siz--)putchar_unlocked(_buf[_siz]);
		}
		inline void wt_int(int x) noexcept { wt_ll(static_cast<long long>(x)); }
		inline void wt_ull(unsigned long long x) noexcept
		{
			std::array<signed char, 32> _buf;
			ssize_t _siz = 0;
			if(x < 0)
			{
				x *= -1;
				putchar_unlocked('-');
			}
			if(x == 0)putchar_unlocked('0');
			while(x > 0)
			{
				_buf[_siz++] = x % 10 + '0';
				x /= 10;
			}
			while(_siz--)putchar_unlocked(_buf[_siz]);
		}
		inline void wt_chr(char x) noexcept { putchar_unlocked(x); }
		inline void wt_str(std::string x) noexcept
		{
			ssize_t _siz = static_cast<ssize_t>(x.length());
			for(ssize_t i = 0; i < _siz; i++)putchar_unlocked(x[i]);
		}
		inline void wt_dbl(double x) noexcept
		{
			int k, r = 0;
			double v = 1;
			if(x < 0)
			{
				x *= -1;
				putchar_unlocked('-');
			}
			x += 0.5 * pow(0.1, _wt_double_digit);
			while(x >= 10 * v)v *= 10, r++;
			while(r-- >= 0)
			{
				k = floor(x / v);
				if(k >= 10)k = 9;
				if(k <= -1)k = 0;
				x -= k * v;
				v *= 0.1;
				putchar_unlocked(k + '0');
			}
			if(_wt_double_digit > 0)
			{
				putchar_unlocked('.');
				v = 1;
				for(ssize_t _ = 0; _ < _wt_double_digit; _++)
				{
					v *= 0.1;
					k = floor(x / v);
					if(k >= 10)k = 9;
					if(k <= -1)k = 0;
					x -= k * v;
					putchar_unlocked(k + '0');
				}
			}
		}
	} fo;

public:
	inline void set_digit(unsigned d) { fo._wt_double_digit = d; }
	inline void scan(int& x) noexcept { x = fi.rd_int(); }
	inline void scan(long& x) noexcept { x = (sizeof(long) == 32 ? fi.rd_int() : fi.rd_ll()); }
	inline void scan(long long& x) noexcept { x = fi.rd_ll(); }
	inline void scan(unsigned& x) noexcept
	{
		int a = fi.rd_int();
		assert(a >= 0);
		x = a;
	}
	inline void scan(unsigned long& x) noexcept
	{
		long a;
		scan(a);
		assert(a >= 0l);
		x = a;
	}
	inline void scan(unsigned long long& x) noexcept
	{
		long long a = fi.rd_ll();
		assert(a >= 0ll);
		x = a;
	}
	inline void scan(double& x) noexcept { x = static_cast<double>(fi.rd_ll()); }
	inline void scan(char& x) noexcept { x = fi.rd_chr(); }
	inline void scan(std::string& x) noexcept { x = fi.rd_str(); }
	template <class T, class U>
	inline void scan(std::pair<T, U>& x) { scan(x.first); scan(x.second); }
	template <class T>
	inline void scan(std::vector<T>& x) { for(auto& e : x)scan(e); }
	void IN() {}
	template <class Car, class... Cdr>
	void IN(Car&& car, Cdr &&...cdr)
	{
		scan(car);
		IN(std::forward<Cdr>(cdr)...);
	}

	inline void print(const bool& x) noexcept { fo.wt_bool(x); }
	inline void print(const int& x) noexcept { fo.wt_int(x); }
	inline void print(const long& x) noexcept { fo.wt_ll(static_cast<long>(x)); }
	inline void print(const long long& x) noexcept { fo.wt_ll(x); }
	inline void print(const unsigned& x) noexcept { fo.wt_ull(static_cast<unsigned long long>(x)); }
	inline void print(const unsigned long& x) noexcept { fo.wt_ull(static_cast<unsigned long long>(x)); }
	inline void print(const unsigned long long& x) noexcept { fo.wt_ull(x); }
	inline void print(const double& x) noexcept { fo.wt_dbl(x); }
	inline void print(const char& x) noexcept { fo.wt_chr(x); }
	inline void print(const char x[]) noexcept
	{
		size_t _siz = 0;
		while(x[_siz] != '\0')fo.wt_chr(x[_siz++]);
	}
	inline void print(const std::string& x) noexcept { fo.wt_str(x); }
	template <class T, class U>
	inline void print(const std::pair<T, U>& x)
	{
		print(x.first);
		print(' ');
		print(x.second);
	}
	template <class T>
	inline void print(const std::vector<T>& x)
	{
		size_t _siz = x.size();
		for(size_t i = 0; i < _siz - 1; i++)print(x[i]), print(' ');
		print(x.back());
	}
	int put() { print('\n'); return 0; }
	template <class T>
	int put(const T& t)
	{
		print(t);
		print('\n');
		return 0;
	}
	template <class Car, class... Cdr>
	int put(const Car& car, const Cdr &...cdr)
	{
		print(car);
		print(' ');
		put(cdr...);
		return 0;
	}
	void yn(bool fl = true) { put(fl ? "Yes" : "No"); }
	template <class T>
	void drop(T x) { put(x); exit(0); }
	void dYes() { drop("Yes"); }
	void dNo() { drop("No"); }
} io;

#define INT(...)  int __VA_ARGS__; io.IN(__VA_ARGS__)
#define LL(...)  long long __VA_ARGS__; io.IN(__VA_ARGS__)
#define ULL(...)  unsigned long long __VA_ARGS__; io.IN(__VA_ARGS__)
#define STR(...)  std::string __VA_ARGS__; io.IN(__VA_ARGS__)
#define CHR(...)  char __VA_ARGS__; io.IN(__VA_ARGS__)
#define DBL(...)  double __VA_ARGS__; io.IN(__VA_ARGS__)


// #line 2 "math/Argsort.hpp"
#include <utility>

template <class T>
bool arg_cmp(
	const std::pair<T, T>& p,
	const std::pair<T, T>& q)
{
	auto area = [](std::pair<T, T> a) -> int
	{
		const auto& [x, y] = a;
		if(y < 0)
			return -1;
		if(y == 0 && 0 <= x)
			return 0;
		else
			return 1;
	};
	const int ap = area(p);
	const int aq = area(q);
	if(ap != aq)
		return ap < aq;
	else
	{
		const auto& [px, py] = p;
		const auto& [qx, qy] = q;
		return 0 < (px * qy - py * qx);
	}
}


// #line 2 "math/Comb.hpp"
#include <vector>

template <class T>
struct COMB
{
	long long n;
	std::vector<T> fa, ifa;
	COMB(long long n_) : n(n_)
	{
		fa.resize(n + 1);
		ifa.resize(n + 1);
		fa[0] = 1;
		for(long long i = 1; i <= n; i++)
			fa[i] = fa[i - 1] * i;
		ifa[n] = (T)(1) / fa[n];
		for(long long i = n - 1; i >= 0; i--)
			ifa[i] = ifa[i + 1] * (i + 1);
	}
	T comb(long long n, long long r)
	{
		return n < 0 || r < 0 || n < r ? (T)(0) : fa[n] * ifa[r] * ifa[n - r];
	}
};

// #line 2 "math/DivisorList.hpp"
#include <vector>
#include <algorithm>

template<class T>
std::vector<T> divisorList(const T& N)
{
	std::vector<T> result{};
	for(T i = 1; i * i <= N; i++)
	{
		if(N % i == 0)
		{
			result.emplace_back(i);
			if(i * i != N)result.emplace_back(N / i);
		}
	}
	std::sort(std::begin(result), std::end(result));
	return result;
}

// #line 2 "math/ModInt.hpp"
template <long long Mod>
struct modInt
{
	long long x;
	constexpr modInt() noexcept : x() {}
	template <class T>
	constexpr modInt(T v = 0) noexcept : x(v% Mod)
	{
		if(x < 0)
			x += Mod;
	}
	constexpr long long getval() const noexcept { return x; }
	constexpr modInt operator-() const noexcept { return x ? Mod - x : 0; }
	constexpr modInt operator+(const modInt& r) const noexcept { return modInt(*this) += r; }
	constexpr modInt operator-(const modInt& r) const noexcept { return modInt(*this) -= r; }
	constexpr modInt operator*(const modInt& r) const noexcept { return modInt(*this) *= r; }
	constexpr modInt operator/(const modInt& r) const noexcept { return modInt(*this) /= r; }
	constexpr modInt& operator+=(const modInt& r) noexcept
	{
		x += r.x;
		if(x >= Mod)
			x -= Mod;
		return *this;
	}
	constexpr modInt& operator-=(const modInt& r) noexcept
	{
		x -= r.x;
		if(x < 0)
			x += Mod;
		return *this;
	}
	constexpr modInt& operator*=(const modInt& r) noexcept
	{
		x = x * r.x % Mod;
		return *this;
	}
	constexpr modInt& operator/=(const modInt& r) noexcept
	{
		x = x * r.inv().getval() % Mod;
		return *this;
	}
	constexpr modInt powm(long long n) noexcept
	{
		if(n < 0)
			return powm(-n).inv();
		modInt x = *this, r = 1;
		for(; n; x *= x, n >>= 1)
			if(n & 1)
				r *= x;
		return r;
	}
	constexpr modInt inv() const noexcept
	{
		long long a = x, b = Mod, u = 1, v = 0;
		while(b)
		{
			long long t = a / b;
			a -= t * b;
			std::swap(a, b);
			u -= t * v;
			std::swap(u, v);
		}
		return modInt(u);
	}
	constexpr modInt comb(long long a) noexcept
	{
		modInt n = *this, s = 1;
		for(int i = 0; i < a; i++)
			s *= (n - modInt(i));
		modInt m = 1;
		for(int i = 1; i <= a; i++)
			m *= modInt(i);
		return s * m.powm(Mod - 2); //Fermat's little thm
	}
	constexpr bool operator==(const modInt& r) { return this->x == r.x; }
	constexpr bool operator!=(const modInt& r) { return this->x != r.x; }
	friend std::ostream& operator<<(std::ostream& os, const modInt<Mod>& a) { return os << a.x; }
	friend std::istream& operator>>(std::istream& is, modInt<Mod>& a)
	{
		long long v;
		is >> v;
		a = modInt<Mod>(v);
		return is;
	}
};

//const long long mod=1000000007;
//using mint=modInt<mod>;
using mint = modInt<1000000007>;
using mint2 = modInt<998244353>;

// #line 2 "math/PrimeFactor.hpp"
#include <vector>

template <class T>
std::vector<std::pair<T, T>> prime_factor(T n)
{
	std::vector<std::pair<T, T>> ret;
	for(T i = 2; i * i <= n; i++)
	{
		if(n % i != 0)continue;
		T tmp = 0;
		while(n % i == 0)
		{
			tmp++;
			n /= i;
		}
		ret.push_back(make_pair(i, tmp));
	}
	if(n != 1)
		ret.push_back(make_pair(n, 1));
	return ret;
}


// #line 2 "other/Template.cpp"
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
#define m_t make_tuple
#define pb push_back
#define eb emplace_back
#define cauto const auto&
#define _overload3(_1, _2, _3, name, ...) name
#define _rep(i, n) repi(i, 0, n)
#define repi(i, a, b) for (ll i = (a), SIZ = (b); i < SIZ; i++)
#define rep(...) _overload3(__VA_ARGS__, repi, _rep, )(__VA_ARGS__)
#define myceil(a, b) ((a) + ((b) - 1)) / (b)
#define continue_with(...) ({__VA_ARGS__; continue;})
#define break_with(...) ({__VA_ARGS__; break;})

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
using vll = Vec<ll>;
using vull = Vec<ull>;
using vd = Vec<double>;
using vc = Vec<char>;
using vs = Vec<std::string>;
using vpii = Vec<pii>;
using vpll = Vec<pll>;

using vvb = Vec<vb>;
using vvi = Vec<vi>;
using vvu = Vec<vu>;
using vvll = Vec<vll>;
using vvull = Vec<vull>;
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

#include <vector>
#include <algorithm>
#include <string>

struct sorted_operator
{
	template<class T> friend std::vector<T> operator>(std::vector<T>a, sorted_operator)
		{ std::sort(std::begin(a), std::end(a)); return a; }
	friend std::string operator>(std::string a, sorted_operator)
		{ std::sort(std::begin(a), std::end(a)); return a; }
} Sor;
struct reversed_operator
{
	template<class T> friend std::vector<T> operator>(std::vector<T> a, reversed_operator)
		{ std::reverse(std::begin(a), std::end(a)); return a; }
	friend std::string operator>(std::string a, reversed_operator)
		{ std::reverse(std::begin(a), std::end(a)); return a; }
} Rev;
struct unique_operator
{
	template<class T> friend std::vector<T> operator>(std::vector<T> a, unique_operator)
		{ a.erase(unique(std::begin(a), std::end(a)), std::end(a)); return a; }
	friend std::string operator>(std::string a, unique_operator)
		{ a.erase(unique(std::begin(a), std::end(a)), std::end(a)); return a; }	
} Set;

#include <iostream>

#ifdef ONLINE_JUDGE
#define dbg(...) void(0)

#else
#define dbg(...) _DEBUG(#__VA_ARGS__, __VA_ARGS__)

template<class Car, class... Cdr>
void _DEBUG(const char* s, Car&& car, Cdr&&... cdr)
{
	constexpr const char* open_br = sizeof...(cdr) == 0 ? "" : "(";
	constexpr const char* close_br = sizeof...(cdr) == 0 ? "" : ")";
#ifdef MY_FASTIO
	io.print(open_br); io.print(s); io.print(close_br);
	io.print(" : ");
	io.print(open_br); io.print(std::forward<Car>(car));
	((io.print(", "), io.print(std::forward<Cdr>(cdr))), ...);
	io.print(close_br); io.print("\n");
#else
	std::cerr << open_br << s << close_br << " : " << open_br << std::forward<Car>(car);
	((std::cerr << ", " << std::forward<Cdr>(cdr)), ...);
	std::cerr << close_br << "\n";
#endif
}
#endif

// #line 2 "structure/BinaryHeap.hpp"
#include <vector>
struct bheap
{
	std::vector<long> _a;
	bheap() { _a.push_back(0L); }
	void push(long _x)
	{
		_a.push_back(_x);
		long pos = _a.size() - 1;
		for(; pos > 1 && _a[pos] < _a[pos / 2]; std::swap(_a[pos], _a[pos / 2]), pos /= 2);
	}
	void pop()
	{
		_a[1] = _a[_a.size() - 1];
		_a.pop_back();
		if(_a.size() == 1)
			return;
		long pos = 1, lc, rc;
		for(; (lc = pos * 2) < _a.size();)
		{
			rc = lc + 1;
			if(lc == _a.size() - 1)
			{
				if(_a[pos] > _a[lc])
				{
					std::swap(_a[pos], _a[lc]);
					pos = lc;
				}
				else
					break;
			}
			else
			{
				if(_a[lc] < _a[rc])
				{
					if(_a[lc] < _a[pos])
					{
						std::swap(_a[pos], _a[lc]);
						pos = lc;
					}
					else
						break;
				}
				else
				{
					if(_a[rc] < _a[pos])
					{
						std::swap(_a[pos], _a[rc]);
						pos = rc;
					}
					else
						break;
				}
			}
		}
	}
	long getmin() { return _a[1]; }
	long siz() { return _a.size() - 1; }
	void cl()
	{
		_a.clear();
		_a.push_back(0L);
	}
};


// #line 2 "structure/BinaryIndexedTree.hpp"
#include <vector>
// 1-indexed
template <class T>
struct BIT
{
	int n;
	std::vector<T> _Bit;
	BIT(int n_ = 0, T init = 0) : n(n_), _Bit(n_ + 1, init) {}
	T sum(int i)
	{
		T ans = 0;
		for(; i > 0; i -= i & -i)
			ans += _Bit[i];
		return ans;
	}
	void add(int i, T a)
	{
		if(!i)
			return;
		for(; i <= n; i += i & -i)
			_Bit[i] += a;
	}
	int l_b_Bit(T k)
	{
		if(k <= 0)
			return 0;
		int ret = 0, i = 1;
		for(; (i << 1) <= n; i <<= 1);
		for(; i; i >>= 1)
			if(ret + i <= n && _Bit[ret + i] < k)
				k -= _Bit[ret += i];
		return (ret + 1);
	}
};

// #line 2 "structure/CompressVector.hpp"
template <class T>
struct compress_vector
{
	int n;
	std::vector<T> a;
	compress_vector(int n_) : n(n_), a(n_) {};
	void compress()
	{
		std::map<T, T> mp;
		for(int i = 0; i < n; i++)
			mp[a[i]] = -1;
		int c = 0;
		for(auto& p : mp)
			p.second = c++;
		for(int i = 0; i < n; i++)
			a[i] = mp[a[i]];
	}
};

// #line 2 "structure/Dynamic_Connectivity.hpp"
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_set>
#include <unordered_map>

template<class T>
class dynamic_connectivity
{
	using ll = long long;
	class euler_tour_tree
	{
	public:
		struct node;
		using nodeP = node*;

		struct node
		{
			nodeP ch[2] = {nullptr, nullptr};
			nodeP p = nullptr;
			int l, r, sz;
			T val = et, sum = et;
			bool exact;
			bool child_exact;
			bool edge_connected = false;
			bool child_edge_connected = false;
			node() {}
			node(int l, int r) : l(l), r(r), sz(l == r), exact(l < r), child_exact(l < r) {}
			bool is_root() { return !p; }
		};

		std::vector<std::unordered_map<int, nodeP>> ptr;

		nodeP get_node(int l, int r)
		{
			if(ptr[l].find(r) == ptr[l].end()) ptr[l][r] = new node(l, r);
			return ptr[l][r];
		}

		nodeP root(nodeP t)
		{
			if(!t) return t;
			while(t->p) t = t->p;
			return t;
		}

		bool same(nodeP s, nodeP t)
		{
			if(s) splay(s);
			if(t) splay(t);
			return root(s) == root(t);
		}

		nodeP reroot(nodeP t)
		{
			auto s = split(t);
			return merge(s.second, s.first);
		}

		std::pair<nodeP, nodeP> split(nodeP s)
		{
			splay(s);
			nodeP t = s->ch[0];
			if(t) t->p = nullptr;
			s->ch[0] = nullptr;
			return std::make_pair(t, update(s));
		}

		std::pair<nodeP, nodeP> split2(nodeP s)
		{
			splay(s);
			nodeP t = s->ch[0];
			nodeP u = s->ch[1];
			if(t) t->p = nullptr;
			s->ch[0] = nullptr;
			if(u) u->p = nullptr;
			s->ch[1] = nullptr;
			return std::make_pair(t, u);
		}

		std::tuple<nodeP, nodeP, nodeP> split(nodeP s, nodeP t)
		{
			auto u = split2(s);
			if(same(u.first, t))
			{
				auto r = split2(t);
				return std::make_tuple(r.first, r.second, u.second);
			}
			else
			{
				auto r = split2(t);
				return std::make_tuple(u.first, r.first, r.second);
			}
		}

		template<class Car, class... Cdr>
		nodeP merge(Car car, Cdr... cdr)
		{
			return merge(car, merge(cdr...));
		}

		nodeP merge(nodeP s, nodeP t)
		{
			if(!s) return t;
			if(!t) return s;
			while(s->ch[1]) s = s->ch[1];
			splay(s);
			s->ch[1] = t;
			if(t) t->p = s;
			return update(s);
		}

		int size(nodeP t) { return t ? t->sz : 0; }

		nodeP update(nodeP t)
		{
			t->sum = et;
			if(t->ch[0]) t->sum = fn(t->sum, t->ch[0]->sum);
			if(t->l == t->r) t->sum = fn(t->sum, t->val);
			if(t->ch[1]) t->sum = fn(t->sum, t->ch[1]->sum);

			t->sz = size(t->ch[0]) + (int)(t->l == t->r) + size(t->ch[1]);
			t->child_edge_connected = (
				t->ch[0] ? t->ch[0]->child_edge_connected : 0
				) | (t->edge_connected) | (
					t->ch[1] ? t->ch[1]->child_edge_connected : 0
					);
			t->child_exact = (
				t->ch[0] ? t->ch[0]->child_exact : 0
				) | (t->exact) | (
					t->ch[1] ? t->ch[1]->child_exact : 0
					);

			return t;
		}

		void push(nodeP t) {}

		void rot(nodeP t, bool b)
		{
			nodeP x = t->p, y = x->p;
			if(x->ch[1 - b] = t->ch[b]) t->ch[b]->p = x;
			t->ch[b] = x, x->p = t;
			update(x);
			update(t);
			if(t->p = y)
			{
				if(y->ch[0] == x) y->ch[0] = t;
				if(y->ch[1] == x) y->ch[1] = t;
				update(y);
			}
		}

		void splay(nodeP t)
		{
			push(t);
			while(!t->is_root())
			{
				nodeP q = t->p;

				if(q->is_root())
				{
					push(q);
					push(t);
					rot(t, (q->ch[0] == t));
				}
				else
				{
					nodeP r = q->p;
					push(r);
					push(q);
					push(t);
					bool b = (r->ch[0] == q);
					if(q->ch[1 - b] == t)
					{
						rot(q, b);
						rot(t, b);
					}
					else
					{
						rot(t, 1 - b);
						rot(t, b);
					}
				}
			}
		}

		void debug(nodeP t)
		{
			if(!t) return;
			debug(t->ch[0]);
			std::cerr << t->l << '-' << t->r << ' ';
			debug(t->ch[1]);
		}

	public:
		euler_tour_tree() {}
		euler_tour_tree(int sz)
		{
			ptr.resize(sz);
			for(int i = 0; i < sz; i++) ptr[i][i] = new node(i, i);
		}

		int size(int s)
		{
			nodeP t = get_node(s, s);
			splay(t);
			return t->sz;
		}

		bool same(int s, int t) { return same(get_node(s, s), get_node(t, t)); }

		void set_size(int sz)
		{
			ptr.resize(sz);
			for(int i = 0; i < sz; i++) ptr[i][i] = new node(i, i);
		}

		void update(int s, T x)
		{
			nodeP t = get_node(s, s);
			splay(t);
			t->val = fn(t->val, x);
			update(t);
		}
		/*
		void edge_update(int s, auto g)
		{
			nodeP t = get_node(s, s);
			splay(t);

			std::function<void(nodeP)> dfs = [&](nodeP t)
			{
				assert(t);
				if(t->l < t->r && t->exact)
				{
					splay(t);
					t->exact = 0;
					update(t);
					g(t->l, t->r);
					return;
				}

				if(t->ch[0] && t->ch[0]->child_exact) dfs(t->ch[0]);
				else dfs(t->ch[1]);
			};

			while(t && t->child_exact)
			{
				dfs(t);
				splay(t);
			}
		}

		bool try_reconnect(int s, auto f)
		{
			nodeP t = get_node(s, s);
			splay(t);
			std::function<bool(nodeP)> dfs = [&](nodeP t) -> bool
			{
				assert(t);
				if(t->edge_connected)
				{
					splay(t);
					return f(t->l);
				}

				if(t->ch[0] && t->ch[0]->child_edge_connected) return dfs(t->ch[0]);
				else return dfs(t->ch[1]);
			};

			while(t->child_edge_connected)
			{
				if(dfs(t)) return true;
				splay(t);
			}

			return false;
		}
		*/
		void edge_connected_update(int s, bool b)
		{
			nodeP t = get_node(s, s);
			splay(t);
			t->edge_connected = b;
			update(t);
		}

		bool link(int l, int r)
		{
			if(same(l, r)) return false;
			merge(reroot(get_node(l, l)), get_node(l, r), reroot(get_node(r, r)), get_node(r, l));
			return true;
		}

		bool cut(int l, int r)
		{
			if(ptr[l].find(r) == ptr[l].end()) return false;
			nodeP s, t, u;
			std::tie(s, t, u) = split(get_node(l, r), get_node(r, l));
			merge(s, u);
			nodeP p = ptr[l][r];
			nodeP q = ptr[r][l];
			ptr[l].erase(r);
			ptr[r].erase(l);

			delete p;
			delete q;

			return true;
		}

		T get_sum(int p, int v)
		{
			cut(p, v);
			nodeP t = get_node(v, v);
			splay(t);
			T res = t->sum;
			link(p, v);
			return res;
		}

		T get_sum(int s)
		{
			nodeP t = get_node(s, s);
			splay(t);
			return t->sum;
		}
	};
	int dep = 1;
	std::vector<euler_tour_tree> ett;
	std::vector<std::vector<std::unordered_set<int>>> edges;
	int sz;

public:
	dynamic_connectivity(int sz) : sz(sz)
	{
		ett.emplace_back(sz);
		edges.emplace_back(sz);
	}

	bool link(int s, int t)
	{
		if(s == t) return false;
		if(ett[0].link(s, t)) return true;
		edges[0][s].insert(t);
		edges[0][t].insert(s);
		if(edges[0][s].size() == 1) ett[0].edge_connected_update(s, 1);
		if(edges[0][t].size() == 1) ett[0].edge_connected_update(t, 1);

		return false;
	}

	bool same(int s, int t) { return ett[0].same(s, t); }

	int size(int s) { return ett[0].size(s); }

	std::vector<int> get_vertex(int s) { return ett[0].vertex_list(s); }

	void update(int s, T x) { ett[0].update(s, x); }

	T get_sum(int s) { return ett[0].get_sum(s); }

	bool cut(int s, int t)
	{
		if(s == t) return false;
		for(int i = 0; i < dep; i++)
		{
			edges[i][s].erase(t);
			edges[i][t].erase(s);
			if(edges[i][s].size() == 0) ett[i].edge_connected_update(s, 0);
			if(edges[i][t].size() == 0) ett[i].edge_connected_update(t, 0);
		}

		for(int i = dep - 1; i >= 0; i--)
		{
			if(ett[i].cut(s, t))
			{
				if(i == dep - 1)
				{
					dep++;
					ett.emplace_back(sz);
					edges.emplace_back(sz);
				}

				return !try_reconnect(s, t, i);
			}
		}

		return false;
	}

	bool try_reconnect(int s, int t, int k)
	{
		for(int i = 0; i < k; i++) ett[i].cut(s, t);

		for(int i = k; i >= 0; i--)
		{
			if(ett[i].size(s) > ett[i].size(t)) std::swap(s, t);
			auto g = [&](int s, int t) { ett[i + 1].link(s, t); };
			ett[i].edge_update(s, g);
			auto f = [&](int x) -> bool
			{
				for(auto itr = edges[i][x].begin(); itr != edges[i][x].end();)
				{
					auto y = *itr;
					itr = edges[i][x].erase(itr);
					edges[i][y].erase(x);

					if(edges[i][x].size() == 0) ett[i].edge_connected_update(x, 0);
					if(edges[i][y].size() == 0) ett[i].edge_connected_update(y, 0);

					if(ett[i].same(x, y))
					{
						edges[i + 1][x].insert(y);
						edges[i + 1][y].insert(x);
						if(edges[i + 1][x].size() == 1) ett[i + 1].edge_connected_update(x, 1);
						if(edges[i + 1][y].size() == 1) ett[i + 1].edge_connected_update(y, 1);
					}
					else
					{
						for(int j = 0; j <= i; j++) ett[j].link(x, y);
						return true;
					}
				}

				return false;
			};

			if(ett[i].try_reconnect(s, f)) return true;
		}
		return false;
	}

	constexpr static T et = T();
	constexpr static T fn(T s, T t) { return s + t; }
};


// #line 2 "structure/Segtree.hpp"
template <class T>
struct segtree
{
	using F = std::function<T(T, T)>;
	int sz;
	std::vector<T> seg;
	const F f;
	const T m1;
	segtree(int n, const F f, const T& m1) : f(f), m1(m1)
	{
		for(sz = 1; sz < n; sz <<= 1);
		seg.assign(2 * sz, m1);
	}
	void update(int k, const T& x)
	{
		k += sz;
		seg[k] = x;
		for(; k >>= 1;)
			seg[k] = f(seg[2 * k], seg[2 * k + 1]);
	}
	void set(int k, const T& x) { seg[k + sz] = x; }
	void build()
	{
		for(int k = sz - 1; k > 0; k--)
			seg[k] = f(seg[2 * k], seg[2 * k + 1]);
	}
	T query(int a, int b)
	{
		T L = m1, R = m1;
		for(a += sz, b += sz; a < b; a >>= 1, b >>= 1)
		{
			if(a & 1)
				L = f(L, seg[a++]);
			if(b & 1)
				R = f(seg[--b], R);
		}
		return f(L, R);
	}
	T operator[](const int& k) const { return seg[k + sz]; }
	template <class C>
	int find_subtree(int a, const C& check, T& M, bool type)
	{
		for(; a < sz;)
		{
			T nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
			if(check(nxt))
				a = 2 * a + type;
			else
				M = nxt, a = 2 * a + 1 - type;
		}
		return a - sz;
	}
	template <class C>
	int find_first(int a, const C& check)
	{
		T L = m1;
		if(a <= 0)
			return check(f(L, seg[1])) ? find_subtree(1, check, L, false) : -1;
		int b = sz;
		for(a += sz, b += sz; a < b; a >>= 1, b >>= 1)
		{
			if(a & 1)
			{
				T nxt = f(L, seg[a]);
				if(check(nxt))
					return find_subtree(a, check, L, false);
				L = nxt;
				a++;
			}
		}
		return -1;
	}
	template <class C>
	int find_last(int b, const C& check)
	{
		T R = m1;
		if(b >= sz)
			return check(f(seg[1], R)) ? find_subtree(1, check, R, true) : -1;
		int a = sz;
		for(b += sz; a < b; a >>= 1, b >>= 1)
		{
			if(b & 1)
			{
				T nxt = f(seg[--b], R);
				if(check(nxt))
					return find_subtree(b, check, R, true);
				R = nxt;
			}
		}
		return -1;
	}
};

// SegmentTree(n, f, M1):= サイズ n の初期化。
// f : 2つの区間の要素をマージする二項演算,
// M1 はモノイドの単位元である。
// set(k, x):= k 番目の要素に x を代入する。
// build():= セグメント木を構築する。
// query(a, b):= 区間 [a, b) に対して二項演算した結果を返す。
// update(k, x):= k 番目の要素を x に変更する。
// operator[k] := k 番目の要素を返す。
// find_first(a, check) := [a,x) が check を満たす最初の要素位置 x を返す。
// find_last(b, check) := [x,b) が check を満たす最後の要素位置 x を返す。
// for example : segtree<int>seg(n,[](int a,int b){return min(a,b);},INT32_MAX);


// #line 2 "structure/UnionFind.hpp"
#include <vector>
#include <algorithm>

struct uni
{
	int n_;
	std::vector<int> par, siz;
	uni(int n) : n_(n), par(n), siz(n, 1LL)
	{
		for(int i = 0; i < n; i++)
			par[i] = i;
	}
	void init(int n)
	{
		par.resize(n);
		siz.assign(n, 1LL);
		for(int i = 0; i < n; i++)
			par[i] = i;
	}
	void merge(int x, int y)
	{
		int rx = root(x);
		int ry = root(y);
		if(rx == ry)
			return;
		if(siz[rx] < siz[ry])
			std::swap(rx, ry);
		siz[rx] += siz[ry];
		par[ry] = rx;
		return;
	}
	int root(int x) { return par[x] == x ? x : par[x] = root(par[x]); }
	bool same(int x, int y) { return root(x) == root(y); }
	int size(int x) { return siz[root(x)]; }
	std::vector<std::vector<int>> groups()
	{
		std::vector<int> rbuf(n_), grsiz(n_);
		for(int i = 0; i < n_; i++)
			grsiz[(rbuf[i] = root(i))]++;
		std::vector<std::vector<int>> res(n_);
		for(int i = 0; i < n_; i++)
			res[i].reserve(grsiz[i]);
		for(int i = 0; i < n_; i++)
			res[rbuf[i]].push_back(i);
		res.erase(remove_if(res.begin(), res.end(), [&](const std::vector<int>& v)
			{ return v.empty(); }),
			res.end());
		return res;
	}
};


#endif