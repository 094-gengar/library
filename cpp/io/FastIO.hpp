#include <cstdint>
#include <cassert>
#include <cmath>
#include <unistd.h>
#include <string>
#include <array>
#include <vector>

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
	// const char* const END = "\n";
	// const char* const SPLIT = " ";
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
inline void scan(double& x) noexcept { x = static_cast<double>(fi.rd_ll()); }
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
	wt_any(" ");
	wt_any(x.second);
}
template<class T>
inline void wt_any(const std::vector<T>& x)
{
	size_t _siz = x.size();
	for(size_t i = 0; i < _siz - 1; i++)wt_any(x[i]), wt_any(" ");
	wt_any(x.back());
}
int print() { wt_any("\n"); return 0; }
template<class T>
int print(const T& t)
{
	wt_any(t);
	wt_any("\n");
	return 0;
}
template<class Car, class... Cdr>
int print(const Car& car, const Cdr &...cdr)
{
	wt_any(car);
	wt_any(" ");
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
template<class T>
void drop(T x) { print(x); exit(0); }
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
