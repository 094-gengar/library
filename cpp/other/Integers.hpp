#include <iostream>

namespace m9 {
#define MY_MODINT
	template <long long Mod> struct modInt {
		long long x;
		constexpr modInt() noexcept : x() {}
		template <class T>
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

	template <long long M> inline void wt_any(const modInt<M>& x) { wt_any(x.val()); }

	using mint1000000007 = modInt<1000000007>;
	using mint998244353 = modInt<998244353>;
	mint1000000007 operator"" _m107(unsigned long long x) { return mint1000000007(x); }
	mint998244353 operator"" _m998(unsigned long long x) { return mint998244353(x); }

	struct cent_t {
	private:
		__int128_t N;
	public:
		template <class T>
		constexpr cent_t(T n) : N(static_cast<__int128_t>(n)) {}
		friend std::ostream& operator<<(std::ostream& os, const cent_t& a)
			{ if(a.N > INT64_MAX)return os << "too big integer"; else return os << static_cast<long long>(a.N); }
		friend std::istream& operator>>(std::istream& is, cent_t& a)
			{ long long tmp{}; is >> tmp; a.N = static_cast<__int128_t>(tmp); return is; }
		constexpr __int128_t val() const noexcept { return N; }
		constexpr cent_t operator-() const noexcept { return -N; }
		template <class INTEGER> constexpr cent_t operator+(const INTEGER& x) const noexcept { return N + x.N; }
		template <class INTEGER> constexpr cent_t operator-(const INTEGER& x) const noexcept { return N - x.N; }
		template <class INTEGER> constexpr cent_t operator*(const INTEGER& x) const noexcept { return N * x.N; }
		template <class INTEGER> constexpr cent_t operator/(const INTEGER& x) const noexcept { return N / x.N; }
		template <class INTEGER> constexpr cent_t operator<<(const INTEGER& x) const noexcept { return N << x; }
		template <class INTEGER> constexpr cent_t operator>>(const INTEGER& x) const noexcept { return N >> x; }
		template <class INTEGER> constexpr cent_t operator+=(const INTEGER& x) noexcept { N += x.N; return *this; }
		template <class INTEGER> constexpr cent_t operator-=(const INTEGER& x) noexcept { N -= x.N; return *this; }
		template <class INTEGER> constexpr cent_t operator*=(const INTEGER& x) noexcept { N *= x.N; return *this; }
		template <class INTEGER> constexpr cent_t operator/=(const INTEGER& x) noexcept { N /= x.N; return *this; }
		template <class INTEGER> constexpr cent_t operator<<=(const INTEGER& x) const noexcept { N <<= x.N; return *this; }
		template <class INTEGER> constexpr cent_t operator>>=(const INTEGER& x) const noexcept { N >>= x.N; return *this; }
		constexpr cent_t operator++() noexcept { N += 1; return *this; }
		constexpr cent_t operator--() noexcept { N -= 1; return *this; }
		template <class INTEGER> constexpr bool operator==(const INTEGER& x) { return this->N == x.N; }
		template <class INTEGER> constexpr bool operator!=(const INTEGER& x) { return this->N != x.N; }
		template <class INTEGER> constexpr bool operator<(const INTEGER& x) { return this->N < x.N; }
		template <class INTEGER> constexpr bool operator>(const INTEGER& x) { return this->N > x.N; }
		template <class INTEGER> constexpr bool operator<=(const INTEGER& x) { return this->N <= x.N; }
		template <class INTEGER> constexpr bool operator>=(const INTEGER& x) { return this->N >= x.N; }
	};

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
	cent_t operator"" _i128(unsigned long long x) { return cent_t(x); }

	using f32 = float;
	using f64 = double;
	double operator"" _f32(unsigned long long x) { return static_cast<f32>(x); }
	double operator"" _f64(unsigned long long x) { return static_cast<f64>(x); }
} // namespace m9
