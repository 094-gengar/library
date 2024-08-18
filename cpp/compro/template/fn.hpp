#ifdef COMPRO
namespace m9::compro {
	template <class T> bool chmin(T& a, const T& b) { return a > b ? (a = b, true) : false; }
	template <class T> bool chmax(T& a, const T& b) { return a < b ? (a = b, true) : false; }
	long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }
	long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
} // namespace m9::compro

#endif