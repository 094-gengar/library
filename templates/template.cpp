// made by https://github.com/094-gengar/add_lib_to_templ
#if !__INCLUDE_LEVEL__
#include __FILE__

int main()
{
	using namespace std;
	using namespace m9;
	
}

#else


// #line 2 "graph/Graph.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

namespace m9 {
template<class T> struct Graph {
	template<class _T> inline bool chmin(_T& a, const _T& b)
	{
		if(b < a) { a = b; return true; }
		else return false;
	}
	int SIZ;
	// bool isOffset;
	// bool isDirected;
	std::vector<std::vector<T>> G;
	Graph() = default;
	Graph(int n) : SIZ(n) {}
	// Graph(int n, bool offset, bool directed) : SIZ(n), isOffset(offset), isDirected(directed), G(n) {}

	void init(std::vector<std::vector<T>> g) { SIZ = g.size(); G = g; }
	std::vector<T> bfs(T s, T t = -1)
	{
		assert(0 <= s and s < SIZ);
		assert((t == -1) or (0 <= s or s < SIZ));
		std::vector<T> dist(SIZ, std::numeric_limits<T>::max() / 2);
		std::vector<std::int8_t> vis(SIZ, false);
		dist[s] = 0;
		std::queue<T> q{};
		q.emplace(s);
		while(!q.empty())
		{
			T cur = q.front(); q.pop();
			for(const auto& e : G[cur])if(chmin(dist[e], dist[cur] + 1))q.emplace(e);
		}
		return (t == -1 ? dist : std::vector<T>{dist[t]});
	}
};

// #include <utility>

template<class T> struct weightedGraph {
	using PTT = std::pair<T, T>;
	template<class _T> inline bool chmin(_T& a, const _T& b)
	{
		if(b < a) { a = b; return true; }
		else return false;
	}
	int SIZ;
	// bool isOffset;
	// bool isDirected;
	std::vector<std::vector<PTT>> G;
	weightedGraph() = default;
	weightedGraph(int n) : SIZ(n) {}
	// weightedGraph(int n, bool os, bool drc) : SIZ(n), isOffset(os), isDirected(drc), G(n) {}

	void init(std::vector<std::vector<PTT>> g) { SIZ = g.size(); G = g; }
	std::vector<T> bfs(T s, T t = -1)
	{
		assert(0 <= s and s < SIZ);
		assert((t == -1) or (0 <= s or s < SIZ));
		std::vector<T> dist(SIZ, std::numeric_limits<T>::max() / 2);
		std::vector<std::int8_t> vis(SIZ, false);
		dist[s] = 0;
		std::queue<PTT> q{};
		q.emplace(0, s);
		while(!q.empty())
		{
			const auto [curCst, curE]= q.front(); q.pop();
			if(curCst > dist[curE])continue;
			for(const auto&[cst, e] : G[curE])if(chmin(dist[e], dist[curE] + cst))q.emplace(dist[e], e);
		}
		return (t == -1 ? dist : std::vector<T>{dist[t]});
	}
	std::vector<T> dijk(T s, T t = -1)
	{
		assert(0 <= s and s < SIZ);
		assert((t == -1) or (0 <= s or s < SIZ));
		std::vector<T> dist(SIZ, std::numeric_limits<T>::max() / 2);
		std::vector<std::int8_t> vis(SIZ, false);
		dist[s] = 0;
		std::priority_queue<PTT, std::vector<PTT>, std::greater<>> pq{};
		pq.emplace(0, s);
		while(!pq.empty())
		{
			const auto [curCst, curE]= pq.top(); pq.pop();
			if(curCst > dist[curE])continue;
			for(const auto&[cst, e] : G[curE])if(chmin(dist[e], dist[curE] + cst))pq.emplace(dist[e], e);
		}
		return (t == -1 ? dist : std::vector<T>{dist[t]});
	}
};
} // namespace m9


// #line 2 "graph/LCA.hpp"
#include <vector>

// Euler Tourもしてるやつ → https://atcoder.jp/contests/abc294/submissions/39948286

namespace m9 {
struct LCA {
	std::vector<std::vector<int>> par;
	std::vector<int> dis;
	LCA(const std::vector<std::vector<int>>& g, int root = 0) { init(g, root); }
	void init(const std::vector<std::vector<int>>& g, int root = 0)
	{
		int v = g.size(), k = 1;
		for(; 1 << k < v; k++) {}
		par.assign(k, std::vector<int>(v, -1));
		dis.assign(v, -1);
		dfs(g, root, -1, 0);
		for(int i = 0; i < k - 1; i++)for(int j = 0; j < v; j++)
		{
			if(par[i][j] < 0)par[i + 1][j] = -1;
			else par[i + 1][j] = par[i][par[i][j]];
		}
	}
	void dfs(const std::vector<std::vector<int>>& g, int v, int p, int d)
	{
		par[0][v] = p;
		dis[v] = d;
		for(int e : g[v])if(e != p)dfs(g, e, v, d + 1);
	}
	int run(int u, int v)
	{
		if(dis[u] < dis[v])std::swap(u, v);
		int k = par.size();
		for(int i = 0; i < k; i++)if(dis[u] - dis[v] >> i & 1)u = par[i][u];
		if(u == v)return u;
		for(int i = k - 1; i >= 0; i--)if(par[i][u] != par[i][v])
		{
			u = par[i][u];
			v = par[i][v];
		}
		return par[0][u];
	}
	int distance(int u, int v) { return dis[u] + dis[v] - dis[run(u, v)] * 2; }
	bool isOnPath(int u, int v, int a) { return distance(u, a) + distance(a, v) == distance(u, v); }
};
} // namespace m9



// #line 2 "heuristic/RandInt.hpp"
#include <random>
#include <ctime>

namespace m9 {
struct RandInt {
private:
	std::mt19937 mt;
public:
	RandInt() { mt.seed((unsigned int)time(0)); }
	auto seed() -> std::mt19937 { return mt; }
	unsigned int next() { return mt(); }
	unsigned int roll(int high)
	{
		std::uniform_int_distribution<unsigned int> die(0, high - 1);
		return die(mt);
	}
} ri;
} // namespace m9
using m9::ri;


// #line 2 "heuristic/Timer.hpp"
#include <chrono>

namespace m9 {
struct Timer {
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
} // namespace m9
using m9::timer;


// #line 2 "io/FastIO.hpp"
#include <cstdint>
#include <cassert>
#include <cmath>
#include <unistd.h>
#include <string>
#include <array>
#include <vector>
#include <set>

#define MY_FASTIO_VER2
//#define IS_OUTPUT_ONLY

namespace m9 {
struct fastin
{
	std::array<signed char, 1048576> _buf;
	ssize_t n_w, n_r;
#ifdef IS_OUTPUT_ONLY
	fastin() {}
#else
	fastin() { _do_read(); }
#endif
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
	double rd_dbl() noexcept
	{
		double ret{}, sgn = 1;
		signed char ch = _current_char();
		while(ch == ' ' or ch == '\n')ch = _next_char();
		if(ch == '-')sgn *= -1, ch = _next_char();
		bool foundDot = false;
		double mul = 1;
		for(; ('0' <= ch && ch <= '9') or ch == '.'; ch = _next_char())
		{
			if(ch == '.') { foundDot = true; continue; }
			if(foundDot) { ret = ret + (ch - '0') / (mul *= 10); }
			else { ret = (ret * 10) + ch - '0'; }
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
		_next_char();
		// signed char discard = _next_char();
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
	// const char* const END = '\n';
	// const char* const SPLIT = ' ';
} fo;

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
// inline void scan(double& x) noexcept { x = static_cast<double>(fi.rd_ll()); }
inline void scan(double& x) noexcept { x = fi.rd_dbl(); }
inline void scan(char& x) noexcept { x = fi.rd_chr(); }
inline void scan(std::string& x) noexcept { x = fi.rd_str(); }
template<class T, class U>
inline void scan(std::pair<T, U>& x) { scan(x.first); scan(x.second); }
template<class T>
inline void scan(std::vector<T>& x) { for(auto& e : x)scan(e); }
void IN() {}
template<class Car, class... Cdr>
void IN(Car&& car, Cdr &&...cdr)
{
	scan(car);
	IN(std::forward<Cdr>(cdr)...);
}

inline void wt_any(const bool& x) noexcept { fo.wt_bool(x); }
inline void wt_any(const int& x) noexcept { fo.wt_int(x); }
inline void wt_any(const long& x) noexcept { fo.wt_ll(static_cast<long>(x)); }
inline void wt_any(const long long& x) noexcept { fo.wt_ll(x); }
inline void wt_any(const unsigned& x) noexcept { fo.wt_ull(static_cast<unsigned long long>(x)); }
inline void wt_any(const unsigned long& x) noexcept { fo.wt_ull(static_cast<unsigned long long>(x)); }
inline void wt_any(const unsigned long long& x) noexcept { fo.wt_ull(x); }
inline void wt_any(const double& x) noexcept { fo.wt_dbl(x); }
inline void wt_any(const char& x) noexcept { fo.wt_chr(x); }
inline void wt_any(const char x[]) noexcept
{
	size_t _siz = 0;
	while(x[_siz] != '\0')fo.wt_chr(x[_siz++]);
}
inline void wt_any(const std::string& x) noexcept { fo.wt_str(x); }
template<class T, class U>
inline void wt_any(const std::pair<T, U>& x)
{
	wt_any(x.first);
	wt_any(' ');
	wt_any(x.second);
}
template<class T>
inline void wt_any(const std::vector<T>& x)
{
	ssize_t _siz = x.size();
	for(ssize_t i = 0; i < _siz - 1; i++)wt_any(x[i]), wt_any(' ');
	if(not x.empty())wt_any(x.back());
}
template<class T>
inline void wt_any(const std::set<T>& x)
{
	for(const auto& e : x)wt_any(e), wt_any(' ');
}

int print() { wt_any('\n'); return 0; }
template<class T>
int print(const T& t)
{
	wt_any(t);
	wt_any('\n');
	return 0;
}
template<class T>
int print(const std::vector<std::vector<T>>& x)
{
	for(const auto& v : x)print(v);
	return 0;
}
template<class Car, class... Cdr>
int print(const Car& car, const Cdr &...cdr)
{
	wt_any(car);
	wt_any(' ');
	print(cdr...);
	return 0;
}
template<class T>
int wt(const T& t)
{
	wt_any(t);
	return 0;
}
template<class Car, class... Cdr>
int wt(const Car& car, const Cdr &...cdr)
{
	wt_any(car);
	wt(cdr...);
	return 0;
}
void yn(bool fl = true) { print(fl ? "Yes" : "No"); }
template<class... T>
void drop(const T&... x) { print(x...); exit(0); }
void dyn(bool fl = true) { print(fl ? "Yes" : "No"); exit(0); }
// void setEND(const char* c) { fo.END = c; }
// void setSPLIT(const char* c) { fo.SPLIT = c; }

#define INT(...)  int __VA_ARGS__; IN(__VA_ARGS__)
#define LL(...)  long long __VA_ARGS__; IN(__VA_ARGS__)
#define ULL(...)  unsigned long long __VA_ARGS__; IN(__VA_ARGS__)
#define STR(...)  std::string __VA_ARGS__; IN(__VA_ARGS__)
#define CHR(...)  char __VA_ARGS__; IN(__VA_ARGS__)
#define DBL(...)  double __VA_ARGS__; IN(__VA_ARGS__)

using ll = long long;
using ull = unsigned long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

#define VEC(a, type, n) std::vector<type> (a)(n); IN(a)
#define VVEC(a, type, h, w) std::vector<std::vector<type>> (a)(h, std::vector<type>(w)); IN(a)

#define VI(a, n) VEC(a, int, n)
#define VVI(a, h, w) VVEC(a, int, h, w)
#define VPII(a, n) VEC(a, pii, n)
#define VVPII(a, h, w) VVEC(a, pii, h, w)
#define VLL(a, n) VEC(a, ll, n)
#define VVLL(a, h, w) VVEC(a, ll, h, w)
#define VPLL(a, n) VEC(a, pll, n)
#define VVPLL(a, h, w) VVEC(a, pll, h, w)
#define VULL(a, n) VEC(a, ull, n)
#define VVULL(a, h, w) VVEC(a, ull, h, w)
#define VC(a, n) VEC(a, char, n)
#define VVC(a, h, w) VVEC(a, char, h, w)
#define VD(a, n) VEC(a, double, n)
#define VVD(a, h, w) VVEC(a, double, h, w)
#define VS(a, n) VEC(a, std::string, n)
} // namespace m9



// #line 2 "math/Argsort.hpp"
// #include <utility>
#include <iostream>

namespace m9 {
template<class T> bool arg_cmp(const std::pair<T, T>& p, const std::pair<T, T>& q)
{
	auto area = [](const std::pair<T, T>& a) -> int {
		const auto&[x, y] = a;
		if(y < 0)return -1;
		else if(y == 0 and 0 <= x)return 0;
		else return 1;
	};
	const int ap = area(p);
	const int aq = area(q);
	if(ap != aq)return ap < aq;
	else
	{
		const auto& [px, py] = p;
		const auto& [qx, qy] = q;
		return (0 < (px * qy - py * qx));
	}
}
} // namespace m9


// #line 2 "math/ChineseRemainderTheorem.hpp"
#include <vector>
#include <cassert>

namespace m9 {
using ll = long long;

namespace m9_cht {
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

} // m9_cht

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
		ll g = m9_cht::ext_gcd(ret_m, m[i], p, q);
		if((r[i] - ret_r) % g != 0) { return std::make_pair((T)0, (T)0); }
		ll tmp = (r[i] - ret_r) / g * p % (m[i] / g);
		ret_r += ret_m * tmp;
		ret_m *= m[i] / g;
		ret_r = (ret_r % ret_m + ret_m) % ret_m;
	}

	return std::make_pair(ret_r, ret_m);
}

} // namespace m9


// #line 2 "math/Combination.hpp"
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


// #line 2 "math/DivisorList.hpp"
#include <vector>
#include <algorithm>

namespace m9 {
template<class T> std::vector<T> divisorList(const T& N)
{
	std::vector<T> result{};
	for(T i{1}; i * i <= N; i++)
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
} // namespace m9


// #line 2 "math/ModInt.hpp"
#include <iostream>

namespace m9 {
#define MY_MODINT
template<long long Mod> struct modInt {
	long long x;
	constexpr modInt() noexcept : x() {}
	template<class T>
	constexpr modInt(T v = 0) noexcept : x(v% Mod) { if(x < 0)x += Mod; }
	constexpr long long val() const noexcept { return x; }
	constexpr modInt operator-() const noexcept { return x ? Mod - x : 0; }
	constexpr modInt operator+(const modInt& r) const noexcept { return modInt(*this) += r; }
	constexpr modInt operator-(const modInt& r) const noexcept { return modInt(*this) -= r; }
	constexpr modInt operator*(const modInt& r) const noexcept { return modInt(*this) *= r; }
	constexpr modInt operator/(const modInt& r) const noexcept { return modInt(*this) /= r; }
	constexpr modInt& operator+=(const modInt& r) noexcept { x += r.x; if(x >= Mod)x -= Mod; return *this; }
	constexpr modInt& operator-=(const modInt& r) noexcept { x -= r.x; if(x < 0)x += Mod; return *this; }
	constexpr modInt& operator*=(const modInt& r) noexcept { x = x * r.x % Mod; return *this; }
	constexpr modInt& operator/=(const modInt& r) noexcept { x = x * r.inv().val() % Mod; return *this; }
	constexpr modInt powm(long long n) noexcept
	{
		if(n < 0)return powm(-n).inv();
		modInt x = *this, r = 1;
		for(; n; x *= x, n >>= 1)if(n & 1)r *= x;
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
		for(int i = 0; i < a; i++)s *= (n - modInt(i));
		modInt m = 1;
		for(int i = 1; i <= a; i++)m *= modInt(i);
		return s * m.powm(Mod - 2);
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

using mint = modInt<1000000007>;
using mint2 = modInt<998244353>;
} // namespace m9


// #line 2 "math/PrimeFactor.hpp"
#include <vector>

namespace m9 {
template<class T> std::vector<std::pair<T, T>> prime_factor(T n)
{
	std::vector<std::pair<T, T>> ret;
	for(T i{2}; i * i <= n; i++)
	{
		if(n % i != 0)continue;
		T tmp = 0;
		while(n % i == 0)
		{
			tmp++;
			n /= i;
		}
		ret.push_back(std::make_pair(i, tmp));
	}
	if(n != 1)
		ret.push_back(std::make_pair(n, 1));
	return ret;
}
} // namespace m9


// #line 2 "math/PrimeFactorPollard.hpp"
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


// #line 2 "other/Integers.hpp"
#include <iostream>

namespace m9 {
struct cent_t {
private:
	__int128_t N;
public:
	template<class T>
	constexpr cent_t(T n) : N(static_cast<__int128_t>(n)) {}
	friend std::ostream& operator<<(std::ostream& os, const cent_t& a)
		{ if(a.N > INT64_MAX)return os << "too big integer"; else return os << static_cast<long long>(a.N); }
	friend std::istream& operator>>(std::istream& is, cent_t& a)
		{ long long tmp{}; is >> tmp; a.N = static_cast<__int128_t>(tmp); return is; }
	constexpr __int128_t val() const noexcept { return N; }
	constexpr cent_t operator-() const noexcept { return -N; }
	template<class INTEGER> constexpr cent_t operator+(const INTEGER& x) const noexcept { return N + x.N; }
	template<class INTEGER> constexpr cent_t operator-(const INTEGER& x) const noexcept { return N - x.N; }
	template<class INTEGER> constexpr cent_t operator*(const INTEGER& x) const noexcept { return N * x.N; }
	template<class INTEGER> constexpr cent_t operator/(const INTEGER& x) const noexcept { return N / x.N; }
	template<class INTEGER> constexpr cent_t operator<<(const INTEGER& x) const noexcept { return N << x; }
	template<class INTEGER> constexpr cent_t operator>>(const INTEGER& x) const noexcept { return N >> x; }
	template<class INTEGER> constexpr cent_t operator+=(const INTEGER& x) noexcept { N += x.N; return *this; }
	template<class INTEGER> constexpr cent_t operator-=(const INTEGER& x) noexcept { N -= x.N; return *this; }
	template<class INTEGER> constexpr cent_t operator*=(const INTEGER& x) noexcept { N *= x.N; return *this; }
	template<class INTEGER> constexpr cent_t operator/=(const INTEGER& x) noexcept { N /= x.N; return *this; }
	template<class INTEGER> constexpr cent_t operator<<=(const INTEGER& x) const noexcept { N <<= x.N; return *this; }
	template<class INTEGER> constexpr cent_t operator>>=(const INTEGER& x) const noexcept { N >>= x.N; return *this; }
	constexpr cent_t operator++() noexcept { N += 1; return *this; }
	constexpr cent_t operator--() noexcept { N -= 1; return *this; }
	template<class INTEGER> constexpr bool operator==(const INTEGER& x) { return this->N == x.N; }
	template<class INTEGER> constexpr bool operator!=(const INTEGER& x) { return this->N != x.N; }
	template<class INTEGER> constexpr bool operator<(const INTEGER& x) { return this->N < x.N; }
	template<class INTEGER> constexpr bool operator>(const INTEGER& x) { return this->N > x.N; }
	template<class INTEGER> constexpr bool operator<=(const INTEGER& x) { return this->N <= x.N; }
	template<class INTEGER> constexpr bool operator>=(const INTEGER& x) { return this->N >= x.N; }
};
} // namespace m9

using i8 = signed char;
using u8 = unsigned char;
using i32 = signed int;
using u32 = unsigned int;
using i64 = signed long long;
using u64 = unsigned long long;

i8 operator"" _i8(unsigned long long x) { return static_cast<i8>(x); }
u8 operator"" _u8(unsigned long long x) { return static_cast<u8>(x); }
i32 operator"" _i32(unsigned long long x) { return static_cast<i32>(x); }
u32 operator"" _u32(unsigned long long x) { return static_cast<u32>(x); }
i64 operator"" _i64(unsigned long long x) { return static_cast<i64>(x); }
u64 operator"" _u64(unsigned long long x) { return static_cast<u64>(x); }
m9::cent_t operator"" _i128(unsigned long long x) { return m9::cent_t(x); }

using f32 = float;
using f64 = double;
double operator"" _f32(unsigned long long x) { return static_cast<f32>(x); }
double operator"" _f64(unsigned long long x) { return static_cast<f64>(x); }


// #line 2 "other/gridtoInt.hpp"
// #include <utility>
#include <iostream>

namespace m9 {

template<class T> auto GridtoT(const T width, const T x, const T y) -> T {
	return x * width + y;
}

template<class T> auto GridtoT(const T width, const std::pair<T, T> p) -> T {
	return p.first * width + p.second;
}

template<class T> auto TtoGrid(const T width, const T N) -> std::pair<T, T> {
	return std::make_pair(N / width, N % width);
}

} // namespace m9


// #line 2 "other/others.hpp"
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
//#include <bit>
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

// #include <utility>

//#define int long long
using ll = long long;
using ull = unsigned long long;
using pii = std::pair<int, int>;
using pll = std::pair<ll, ll>;

#include <vector>
#include <string>

template<class T>
using Vec = std::vector<T>;
using vb = Vec<std::int8_t>;
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

#include <vector>
#include <algorithm>
#include <string>

struct sorted_operator {
	template<class T> friend std::vector<T> operator>>(std::vector<T>a, sorted_operator)
		{ std::sort(std::begin(a), std::end(a)); return a; }
	friend std::string operator>>(std::string a, sorted_operator)
		{ std::sort(std::begin(a), std::end(a)); return a; }
} Sor;
struct reversed_operator {
	template<class T> friend std::vector<T> operator>>(std::vector<T> a, reversed_operator)
		{ std::reverse(std::begin(a), std::end(a)); return a; }
	friend std::string operator>>(std::string a, reversed_operator)
		{ std::reverse(std::begin(a), std::end(a)); return a; }
} Rev;
struct unique_operator {
	template<class T> friend std::vector<T> operator>>(std::vector<T> a, unique_operator)
		{ a.erase(unique(std::begin(a), std::end(a)), std::end(a)); return a; }
	friend std::string operator>>(std::string a, unique_operator)
		{ a.erase(unique(std::begin(a), std::end(a)), std::end(a)); return a; }	
} Set;
template <class T>
void INCVEC(std::vector<T>& a) { for(T& e : a)e++; }
template <class T>
void DECVEC(std::vector<T>& a) { for(T& e : a)e--; }
struct inc_operator {
	template<class T> friend std::vector<T> operator>>(std::vector<T> a, inc_operator)
		{ INCVEC(a); return a; }
} Inc;
struct dec_operator {
	template<class T> friend std::vector<T> operator>>(std::vector<T> a, dec_operator)
		{ DECVEC(a); return a; }
} Dec;
template <class T, class F>
auto operator>> (std::vector<T> a, F f) -> std::vector<decltype(f(a.front()))>
{
	std::vector<decltype(f(a.front()))> res{};
	for(const T& e : a)res.emplace_back(f(e));
	return res;
}

#include <iostream>

namespace m9 {
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
	io.wt_any(open_br); io.wt_any(s); io.wt_any(close_br);
	io.wt_any(" : ");
	io.wt_any(open_br); io.wt_any(std::forward<Car>(car));
	((io.wt_any(", "), io.wt_any(std::forward<Cdr>(cdr))), ...);
	io.wt_any(close_br); io.wt_any("\n");
#else
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
#endif
}
#endif
} // namespace m9


// #line 2 "structure/BinaryIndexedTree.hpp"
#include <cassert>
#include <vector>

namespace m9 {
template<class T> class BIT {
	int SIZ;
	std::vector<T> tree;
public:
	BIT(int n = 0, T x = 0) : SIZ(n), tree(n, x) {}
	T sum(int i)
	{
		assert(0 <= i and i <= SIZ);
		T result{0};
		for(; i > 0; i -= (i & -i))result += tree[i - 1];
		return result;
	}
	T sum(int l, int r) { return sum(r) - sum(l); }
	void add(int i, T a) { assert(0 <= i and i < SIZ); for(i++; i <= SIZ; i += (i & -i))tree[i - 1] += a; }
	int lowerBound(T k)
	{
		if(k <= 0)return 0;
		int result{0}, i{1};
		for(; (i << 1) <= SIZ; )i <<= 1;
		for(; i; i >>= 1)if(result + i <= SIZ and tree[result + i] < k)k -= tree[result += i];
		return result;
	}
};
} // namespace m9


// #line 2 "structure/CompressVec.hpp"
#include <map>

namespace m9 {
template<class T> struct compress {
private:
	int SIZ;
public:
	std::vector<T> C;
	compress(std::vector<T> a)
	{
		SIZ = a.size();
		C = a;
		std::map<T, T> mp{};
		for(int i{}; i < SIZ; i++)mp[C[i]] = -1;
		int c{};
		for(auto&[key, value] : mp)value = c++;
		for(int i{}; i < SIZ; i++)C[i] = mp[C[i]];
	}
	void init(std::vector<T> a)
	{
		SIZ = a.size();
		C = a;
		std::map<T, T> mp{};
		for(int i{}; i < SIZ; i++)mp[C[i]] = -1;
		int c{};
		for(auto&[key, value] : mp)value = c++;
		for(int i{}; i < SIZ; i++)C[i] = mp[C[i]];
	}
	T operator[](int idx) { assert(0 <= idx and idx < SIZ); return C[idx]; }
};
} // namespace m9


// #line 2 "structure/Cumsum.hpp"
#include <cassert>

namespace m9 {
template<class T> struct cumsum {
private:
	int SIZ;
public:
	std::vector<T> S;
	cumsum(std::vector<T> a)
	{
		SIZ = a.size();
		S.assign(SIZ + 1, 0);
		for(int i{}; i < SIZ; i++)S[i + 1] = S[i] + a[i];
	}
	void init(std::vector<T> a)
	{
		SIZ = a.size();
		S.assign(SIZ + 1, 0);
		for(int i{}; i < SIZ; i++)S[i + 1] = S[i] + a[i];
	}
	T operator[](int idx) { assert(0 <= idx and idx <= SIZ); return S[idx]; }
};
} // namespace m9


// #line 2 "structure/RollingHash.hpp"
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



// #line 2 "structure/SegmentTree.hpp"
#include <cassert>
#include <vector>

namespace m9 {
template<class M> class segmentTree {
	using T = typename M::valueType;
	std::vector<T> seg;
	int SIZ;
public:
	segmentTree(int n) { for(SIZ = 1; SIZ < n; )SIZ <<= 1; seg.assign(2 * SIZ, M::id);}
	void update(int k, const T& x) { assert(0 <= k and k < SIZ); for(seg[k += SIZ] = x; k>>= 1; )seg[k] = M::op(seg[2 * k], seg[2 * k + 1]); }
	void set(int k, const T& x) { assert(0 <= k and k < SIZ); seg[k + SIZ] = x; }
	T operator[](const int& k) const { assert(0 <= k and k < SIZ); return seg[k + SIZ]; }
	void build() { for(int k = SIZ - 1; k > 0; k--)seg[k] = M::op(seg[2 * k], seg[2 * k + 1]); }
	T query(int a, int b)
	{
		assert(0 <= a and a <= b and b <= SIZ);
		auto L = M::id;
		auto R = M::id;
		for(a += SIZ, b += SIZ; a < b; a >>= 1, b >>= 1)
		{
			if(a & 1)L = M::op(L, seg[a++]);
			if(b & 1)R = M::op(seg[--b], R);
		}
		return M::op(L, R);
	}
	template<class C> int findSubtree(int a, const C& check, T& mono, bool type)
	{
		for(; a < SIZ; )
		{
			auto next = M::op(seg[2 * a + type], mono);
			if(check(next))a = 2 * a + type;
			else mono = next, a = 2 * a + !type;
		}
		return (a - SIZ);
	}
	template<class C> int findFirst(int a, const C& check)
	{
		assert(0 <= a and a <= SIZ);
		auto L = M::id;
		if(a <= 0)return (check(M::op(L, seg[1])) ? findSubtree(1, check, L, false) : -1);
		int b = SIZ;
		for(a += SIZ, b += SIZ; a < b; a >>= 1, b >>= 1)
		{
			if(a & 1)
			{
				auto next = M::op(L, seg[a]);
				if(check(next))return findSubtree(a, check, L, false);
				L = next;
				a++;
			}
		}
		return -1;
	}
	template<class C> int findLast(int b, const C& check)
	{
		assert(0 <= b and b <= SIZ);
		auto R = M::id;
		if(b >= SIZ)return (check(M::op(seg[1], R)) ? findSubtree(1, check, R, true) : -1);
		int a = SIZ;
		for(b += SIZ; a < b; a >>= 1, b >>= 1)
		{
			if(b & 1)
			{
				auto next = M::op(seg[--b], R);
				if(check(next))return findSubtree(b, check, R, true);
				R = next;
			}
		}
		return -1;
	}
};

struct RSumQ {
	using valueType = int;
	static int op(int a, int b) { return a + b; }
	static inline int id{0};
};
struct RSumQLL {
	using valueType = long long;
	static long long op(long long a, long long b) { return a + b; }
	static inline long long id{0};
};
struct RMaxQ {
	using valueType = int;
	static int op(int a, int b) { return std::max(a, b); }
	static inline int id{-(1 << 29)};
};
struct RMaxQLL {
	using valueType = long long;
	static long long op(long long a, long long b) { return std::max(a, b); }
	static inline long long id{-(1ll << 60)};
};
struct RminQ {
	using valueType = int;
	static int op(int a, int b) { return std::min(a, b); }
	static inline int id{1 << 29};
};
struct RminQLL {
	using valueType = long long;
	static long long op(long long a, long long b) { return std::min(a, b); }
	static inline long long id{1ll << 60};
};
} // namespace m9


// #line 2 "structure/Trie.hpp"
#include <string>
#include <algorithm>
#include <vector>

namespace m9 {
template<int BAND_SIZE> struct TrieSub {
	int16_t C{};
	int common;
	std::vector<int> child;
	std::vector<int> accept{};
	TrieSub(int16_t C) : C(C), common(0)
	{
		child.assign(BAND_SIZE, -1);
	}
};

template<int BAND_SIZE, int16_t BASE_CHAR> struct Trie {
	using Node = TrieSub<BAND_SIZE>;
	std::vector<Node> Nodes{};
	int root{0};

	Trie() { Nodes.emplace_back(Node(root)); }
	void insert(const std::string& word, int word_id)
	{
		int len = word.length();
		int node_id{0};
		for(int i{0}; i < len; i++)
		{
			int16_t c = (int16_t)(word[i]) - BASE_CHAR;
			int& next_id = Nodes[node_id].child[c];
			if(next_id == -1)
			{
				next_id = (int)(Nodes.size());
				Nodes.emplace_back(Node(c));
			}
			Nodes[node_id].common++;
			node_id = next_id;
		}
		Nodes[node_id].common++;
		Nodes[node_id].accept.emplace_back(word_id);
	}

	void insert(const std::string& word)
	{
		insert(word, Nodes[0].common);
	}

	bool search(const std::string& word, bool prefix = false)
	{
		int len = word.length();
		int node_id{0};
		for(int i{0}; i < len; i++)
		{
			int16_t C = (int16_t)(word[i]) - BASE_CHAR;
			int& next_id = Nodes[node_id].child[C];
			if(next_id == -1) { return false; }
			node_id = next_id;
		}
		return (prefix || (Nodes[node_id].accept.size() > 0));
	}

	bool search_prefix(const std::string& prefix)
	{
		return search(prefix, true);
	}

	int count() const { return (Nodes.front().common); }
	long long size() const { return Nodes.size(); }
};
} // namespace m9



// #line 2 "structure/UnionFind.hpp"
#include <cassert>
#include <vector>
#include <algorithm>

namespace m9 {
class UnionFind {
	int SIZ;
	std::vector<int> a;
public:
	UnionFind(int n) : SIZ(n), a(n) { for(int i{}; i < SIZ; i++)a[i] = -1; }
	int root(int x) { assert(x < SIZ); return (a[x] < 0 ? x : (a[x] = root(a[x]))); }
	bool same(int x, int y) { assert(x < SIZ); assert(y < SIZ); return root(x) == root(y); }
	void merge(int x, int y)
	{
		assert(x < SIZ);
		assert(y < SIZ);
		x = root(x), y = root(y);
		if(x == y)return;
		if(a[x] > a[y])std::swap(x, y);
		a[x] += a[y], a[y] = x;
	}
	int size(int x) { assert(x < SIZ); return -a[root(x)]; }
	std::vector<std::vector<int>> groups()
	{
		std::vector<int> rootBuf(SIZ), groupSize(SIZ);
		for(int i{}; i < SIZ; i++)groupSize[rootBuf[i] = root(i)]++;
		std::vector<std::vector<int>> result(SIZ);
		for(int i{}; i < SIZ; i++)result[i].reserve(groupSize[i]);
		for(int i{}; i < SIZ; i++)result[rootBuf[i]].emplace_back(i);
		result.erase( \
			remove_if(std::begin(result),
				std::end(result),
				[&](const std::vector<int>& v) -> bool { return v.empty(); }),
			std::end(result));
		return result;
	}
};

using uni = UnionFind;
} // namespace m9


#endif