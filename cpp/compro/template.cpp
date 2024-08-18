#include <bits/stdc++.h>
#define COMPRO

#ifdef COMPRO
namespace m9::compro {
	template <class T> bool chmin(T& a, const T& b) { return a > b ? (a = b, true) : false; }
	template <class T> bool chmax(T& a, const T& b) { return a < b ? (a = b, true) : false; }
	long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
	long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
} // namespace m9::compro

#endif

#ifdef COMPRO
namespace m9::compro {
	using ll = long long;
	using ull = unsigned long long;
	using usize = size_t;
	using pii = std::pair<int, int>;
	using pll = std::pair<ll, ll>;
} // namespace m9::compro

namespace m9::compro {
	template <class T> using V = std::vector<T>;
	using vc = V<char>;
	using vb = V<int8_t>;
	using vi = V<int>;
	using vll = V<ll>;
	using vd = V<double>;
	using vs = V<std::string>;
	using vpii = V<pii>;
	using vpll = V<pll>;
	using vvc = V<vc>;
	using vvb = V<vb>;
	using vvi = V<vi>;
	using vvll = V<vll>;
	using vvd = V<vd>;
} // namespace m9::compro

#endif

#ifdef COMPRO
#include <unistd.h>

#define FASTIO
// #define OUTPUT_ONLY

namespace m9::compro::io {
	// standard i/o
	struct StandardIn {
		long long rd_ll() { long long tmp; std::cin >> tmp; return tmp; }
		int rd_int() { int tmp; std::cin >> tmp; return tmp; }
		double rd_dbl() { double tmp; std::cin >> tmp; return tmp; }
		char rd_chr() { char tmp; std::cin >> tmp; return tmp; }
		std::string rd_str() { std::string tmp; std::cin >> tmp; return tmp; }
	};
	struct StandardOut {
		void wt_ll(long long x) { std::cout << x; }
		void wt_ull(unsigned long long x) { std::cout << x; }
		void wt_dbl(double x) { std::cout << x; }
		void wt_chr(char x) { std::cout << x; }
		void wt_str(std::string x) { std::cout << x; }
	};
	// fast i/o
	struct FastIn {
		std::array<char, 1 << 20> buf;
		int width, pos;
#ifdef OUTPUT_ONLY
		FastIn() noexcept {}
#else
		FastIn() noexcept { start_reading(); }
#endif
		long long rd_ll() {
			long long ret = 0, sgn = 1;
			char ch = current_char();
			while (ch == ' ' or ch == '\n') ch = next_char();
			if (ch == '-') { sgn *= -1; ch = next_char(); }
			for (; '0' <= ch and ch <= '9'; ch = next_char()) ret = (ret * 10) + ch - '0';
			return ret * sgn;
		}
		double rd_dbl() {
			double ret = 0, sgn = 1;
			char ch = current_char();
			while (ch == ' ' or ch == '\n') ch = next_char();
			if (ch == '-') { sgn *= -1; ch = next_char(); }
			bool found_dot = false;
			double mul = 1;
			for (; ('0' <= ch and ch <= '9') or ch == '.'; ch = next_char()) {
				if (ch == '.') { found_dot = true; continue; }
				if (found_dot) ret = ret + (ch - '0') / (mul *= 10); else ret = (ret * 10) + ch - '0';
			}
			return ret * sgn;
		}
		int rd_int() {
			int ret = 0, sgn = 1;
			char ch = current_char();
			while (ch == ' ' or ch == '\n') ch = next_char();
			if (ch == '-') { sgn *= -1; ch = next_char(); }
			for (; '0' <= ch and ch <= '9'; ch = next_char()) ret = (ret * 10) + ch - '0';
			return ret * sgn;
		}
		std::string rd_str() {
			std::string res;
			char ch = current_char();
			while (ch == ' ' or ch == '\n') ch = next_char();
			for (; ch != -1 and ch != '\n' and ch != ' '; ch = next_char()) res += ch;
			return res;
		}
		char rd_chr() {
			char ch = current_char();
			while (ch == ' ' or ch == '\n') ch = next_char();
			next_char();
			return ch;
		}
	private:
		void start_reading() {
			auto r = read(0, &buf[0], buf.size());
			assert(r >= 0);
			width = r, pos = 0;
		}
		char next_char() { if (++pos == width) start_reading(); return current_char(); }
		char current_char() { return (pos == width ? -1 : buf[pos]); }
	};
	template <int float_format> struct FastOut {
		void wt_ll(long long x) noexcept {
			std::array<char, 1 << 5> buf;
			int idx = 0;
			if (x < 0) { x *= -1; putchar_unlocked('-'); }
			if (x == 0) putchar_unlocked('0');
			while (x > 0) { buf[idx++] = x % 10 + '0'; x /= 10; }
			while (idx--) putchar_unlocked(buf[idx]);
		}
		void wt_ull(unsigned long long x) noexcept {
			std::array<char, 1 << 5> buf;
			int idx = 0;
			if (x == 0) putchar_unlocked('0');
			while (x > 0) { buf[idx++] = x % 10 + '0'; x /= 10; }
			while (idx--) putchar_unlocked(buf[idx]);
		}
		void wt_chr(char x) noexcept { putchar_unlocked(x); }
		void wt_str(std::string x) noexcept {
			auto len = x.length();
			for (int i = 0; i < len; i++) putchar_unlocked(x[i]);
		}
		void wt_dbl(double x) noexcept {
			int k, r = 0;
			double v = 1;
			if (x < 0) { x *= -1; putchar_unlocked('-'); }
			x += 0.5 * pow(0.1, float_format);
			while (x >= 10 * v) { v *= 10; r++; }
			while (r--) {
				k = floor(x / v);
				if (k >= 10) k = 9;
				if (k <= -1) k = 0;
				x -= k * v;
				v *= 0.1;
				putchar_unlocked(k + '0');
			}
			if (float_format > 0) {
				putchar_unlocked('.');
				v = 1;
				for (int _ = 0; _ < float_format; _++) {
					v *= 0.1;
					k = floor(x / v);
					if (k >= 10) k = 9;
					if (k <= -1) k = 0;
					x -= k * v;
					putchar_unlocked(k + '0');
				}
			}
		}
	};
} // namespace m9::compro::io

namespace m9::compro::io {
	template <class, class = std::void_t<>> struct has_all_rd_functions : std::false_type {};
	template <class T> struct has_all_rd_functions<T, std::void_t<
		decltype(std::declval<T>().rd_ll()),
		decltype(std::declval<T>().rd_int()),
		decltype(std::declval<T>().rd_dbl()),
		decltype(std::declval<T>().rd_chr()),
		decltype(std::declval<T>().rd_str())>> : std::true_type {};
	template <class, class = std::void_t<>> struct has_all_wt_functions : std::false_type {};
	template <class T> struct has_all_wt_functions<T, std::void_t<
		decltype(std::declval<T>().wt_ll(std::declval<long long>())),
		decltype(std::declval<T>().wt_ull(std::declval<unsigned long long>())),
		decltype(std::declval<T>().wt_dbl(std::declval<double>())),
		decltype(std::declval<T>().wt_chr(std::declval<char>())),
		decltype(std::declval<T>().wt_str(std::declval<std::string>()))>> : std::true_type {};
	template <class Input, class Output> struct IOPair {
		static_assert(has_all_rd_functions<Input>::value); static_assert(has_all_wt_functions<Output>::value);
		Input is; Output os;
		long long rd_ll() { return is.rd_ll(); }
		int rd_int() { return is.rd_int(); }
		double rd_dbl() { return is.rd_dbl(); }
		char rd_chr() { return is.rd_chr(); }
		std::string rd_str() { return is.rd_str(); }
		void wt_ll(const long long& x) { os.wt_ll(x); }
		void wt_ull(const unsigned long long& x) { os.wt_ull(x); }
		void wt_dbl(const double& x) { os.wt_dbl(x); }
		void wt_chr(const char& x) { os.wt_chr(x); }
		void wt_str(const std::string& x) { os.wt_str(x); }
	};

	IOPair<FastIn, FastOut<15>> io;
	// IOPair<StandardIn, StandardOut> io;
} // namespace m9::compro::io

namespace m9::compro::io {
	// scan
	void scan(int& x) { x = io.rd_int(); }
	void scan(long& x) { x = (long)(sizeof(long) == 32 ? io.rd_int() : io.rd_ll()); }
	void scan(long long& x) { x = io.rd_ll(); }
	void scan(unsigned int& x) { int tmp = io.rd_int(); assert(tmp >= 0); x = tmp; }
	void scan(unsigned long& x) { long tmp; scan(tmp); assert(tmp >= 0l); x = tmp; }
	void scan(unsigned long long& x) { long long tmp = io.rd_ll(); assert(tmp >= 0ll); x = tmp; }
	void scan(double& x) { x = io.rd_dbl(); }
	void scan(long double& x) { x = (long double)(io.rd_dbl()); }
	void scan(char& x) { x = io.rd_chr(); }
	void scan(std::string& x) { x = io.rd_str(); }
	template <class T1, class T2> void scan(std::pair<T1, T2>& x) { scan(x.first); scan(x.second); }
	template <class T> void scan(std::vector<T>& x) { for (auto& e : x) scan(e); }
	void scan() {}
	template <class Car, class... Cdr> void scan(Car&& car, Cdr&&... cdr) { scan(car); scan(std::forward<Cdr>(cdr)...); }
	// wt
	void wt(const bool& x) { io.wt_ull(x ? 1 : 0); }
	void wt(const int& x) { io.wt_ll((long long)(x)); }
	void wt(const long& x) { io.wt_ll((long long)(x)); }
	void wt(const long long& x) { io.wt_ll(x); }
	void wt(const unsigned int& x) { io.wt_ull((unsigned long long)(x)); }
	void wt(const unsigned long& x) { io.wt_ull((unsigned long long)(x)); }
	void wt(const unsigned long long& x) { io.wt_ull(x); }
	void wt(const double& x) { io.wt_dbl(x); }
	void wt(const long double& x) { io.wt_dbl((double)(x)); }
	void wt(const char& x) { io.wt_chr(x); }
	void wt(const char x[]) { int idx = 0; while (x[idx] != '\0') io.wt_chr(x[idx++]); }
	void wt(const std::string& x) { io.wt_str(x); }
	template <class T1, class T2> void wt(const std::pair<T1, T2>& x) { wt(x.first); wt(' '); wt(x.second); }
	template <class T> void wt(const std::vector<T>& x) {
		auto len = x.size();
		for (int i = 0; i < len - 1; i++) { wt(x[i]); wt(' '); }
		if (not x.empty()) wt(x.back());
	}
	template <class T> void wt(const std::set<T>& x) {
		for (auto it = begin(x); it != end(x); ) {
			wt(*it);
			it++;
			if (it != end(x)) wt(' ');
		}
	}
	template <class Car, class... Cdr> void wt(const Car& car, const Cdr&... cdr) { wt(car); wt(cdr...); }
	// print
	int print() { wt('\n'); return 0; }
	template <class T> int print(const T& x) { wt(x); wt('\n'); return 0; }
	template <class T> int print(const std::vector<std::vector<T>>& x) { for (const auto& v : x) print(v); return 0; }
	template <class Car, class... Cdr> int print(const Car& car, const Cdr&... cdr) { wt(car); wt(' '); print(cdr...); return 0; }
	// drop, yn
	template <class... T> void drop(const T&... x) { print(x...); exit(0); }
	void yn(bool f = true) { print(f ? "Yes" : "No"); }
	void dyn(bool f = true) { drop(f ? "Yes" : "No"); }
} // namespace m9::compro::io
namespace m9::compro { using namespace m9::compro::io; } // namespace m9::compro

// macro
#define INT(...)  int __VA_ARGS__; scan(__VA_ARGS__)
#define LL(...)  long long __VA_ARGS__; scan(__VA_ARGS__)
#define ULL(...)  unsigned long long __VA_ARGS__; scan(__VA_ARGS__)
#define DBL(...)  double __VA_ARGS__; scan(__VA_ARGS__)
#define STR(...)  std::string __VA_ARGS__; scan(__VA_ARGS__)
#define CHR(...)  char __VA_ARGS__; scan(__VA_ARGS__)
#define VEC(a, type, n) std::vector<type> (a)(n); scan(a)
#define VVEC(a, type, h, w) std::vector<std::vector<type>> (a)(h, std::vector<type>(w)); scan(a)
#define VI(a, n) VEC(a, int, n)
#define VVI(a, h, w) VVEC(a, int, h, w)
#define VLL(a, n) VEC(a, long long, n)
#define VVLL(a, h, w) VVEC(a, long long, h, w)
#define VC(a, n) VEC(a, char, n)
#define VVC(a, h, w) VVEC(a, char, h, w)
#define VPII(a, n) VEC(a, pii, n)
#define VPLL(a, n) VEC(a, pll, n)
#define VD(a, n) VEC(a, double, n)
#define VS(a, n) VEC(a, std::string, n)

#define PVIVI(a, b, n) std::vector<int> (a)(n); std::vector<int> (b)(n); for (size_t i = 0; i < n; i++) scan(a[i], b[i]);
#define PVLVL(a, b, n) std::vector<long long> (a)(n); std::vector<long long> (b)(n); for (size_t i = 0; i < n; i++) scan(a[i], b[i]);

#endif

#ifdef COMPRO
#ifdef ONLINE_JUDGE
#	define dbg(...) void(0)
#else
#	define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
#endif
namespace m9::compro {
	template <class Car, class... Cdr> void debug_impl(const char* s, Car&& car, Cdr&&... cdr) {
		constexpr const char* open_bracket = (sizeof...(cdr) == 0 ? "" : "(");
		constexpr const char* close_bracket = (sizeof...(cdr) == 0 ? "" : ")");
#ifdef FASTIO
		wt(open_bracket, s, close_bracket, " : ", open_bracket, std::forward<Car>(car));
		(wt(", ", std::forward<Cdr>(cdr)), ...);
		wt(close_bracket, '\n');
#else
		std::cerr << open_bracket << s << close_bracket << " : " << open_bracket << std::forward<Car>(car);
		((std::cerr << ", " << std::forward<Cdr>(cdr)), ...);
		std::cerr << close_bracket << "\n";
#endif 
	}
} // namespace m9::compro

#endif

#ifdef COMPRO
namespace m9::compro {
	constexpr long long big_mod = (1ll << 61) - 1;
	constexpr long long mod_1000000007 = 1000000007;
	constexpr long long mod_998244353 = 998244353;
	constexpr int iinf = std::numeric_limits<int>::max() / 2;
	constexpr long long linf = std::numeric_limits<long long>::max() / 2;
	constexpr double eps = 1e-8;
	constexpr double pi = 3.141592653589793238462643383279;
} // namespace m9::compro

#endif

#ifdef COMPRO
#pragma GCC optimize("O3")
#define _OVERLOAD(_1, _2, _3, name, ...) name
#define _REP0(q) for ([[maybe_unused]] long long _ = 0; _ < (q); _++)
#define _REP1(i, n) for (long long i = 0; i < (n); i++)
#define _REP2(i, a, b) for (long long i = (a); i < (b); i++)
#define REP(...) _OVERLOAD(__VA_ARGS__, _REP2, _REP1, _REP0)(__VA_ARGS__)
#define FOR(e, v) for (auto&& e : v)
#define CFOR(e, v) for (const auto& e : v)
#define M_P make_pair
#define M_T make_tuple
#define CAUTO const auto&
#define ALL(x) begin(x), end(x)
#define SORT(x) sort(ALL(x))
#define RSORT(x) ({ sort(ALL(x)); reverse(ALL(x)); })
#define UNIQUE(x) x.erase(unique(ALL(x)), end(x))
#define L_B(v, e) distance(begin(v), lower_bound(ALL(v), (e)));
#define U_B(v, e) distance(begin(v), upper_bound(ALL(v), (e)));

#endif

#ifdef COMPRO
#include <atcoder/modint>
using mint = atcoder::modint998244353;

#endif

using namespace m9::compro;
using namespace std;

int main() {
	
}