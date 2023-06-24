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