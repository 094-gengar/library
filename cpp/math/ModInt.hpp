// #include <iostream>

// namespace m9 {
// #define MY_MODINT
// 	template<long long Mod> struct modInt {
// 		long long x;
// 		constexpr modInt() noexcept : x() {}
// 		template<class T>
// 		constexpr modInt(T v = 0) noexcept : x(v% Mod) { if(x < 0)x += Mod; }
// 		constexpr long long val() const noexcept { return x; }
// 		constexpr modInt operator-() const noexcept { return x ? Mod - x : 0; }
// 		constexpr modInt operator+(const modInt& r) const noexcept { return modInt(*this) += r; }
// 		constexpr modInt operator-(const modInt& r) const noexcept { return modInt(*this) -= r; }
// 		constexpr modInt operator*(const modInt& r) const noexcept { return modInt(*this) *= r; }
// 		constexpr modInt operator/(const modInt& r) const noexcept { return modInt(*this) /= r; }
// 		constexpr modInt& operator+=(const modInt& r) noexcept { x += r.x; if(x >= Mod)x -= Mod; return *this; }
// 		constexpr modInt& operator-=(const modInt& r) noexcept { x -= r.x; if(x < 0)x += Mod; return *this; }
// 		constexpr modInt& operator*=(const modInt& r) noexcept { x = x * r.x % Mod; return *this; }
// 		constexpr modInt& operator/=(const modInt& r) noexcept { x = x * r.inv().val() % Mod; return *this; }
// 		constexpr modInt powm(long long n) noexcept
// 		{
// 			if(n < 0)return powm(-n).inv();
// 			modInt x = *this, r = 1;
// 			for(; n; x *= x, n >>= 1)if(n & 1)r *= x;
// 			return r;
// 		}
// 		constexpr modInt inv() const noexcept
// 		{
// 			long long a = x, b = Mod, u = 1, v = 0;
// 			while(b)
// 			{
// 				long long t = a / b;
// 				a -= t * b;
// 				std::swap(a, b);
// 				u -= t * v;
// 				std::swap(u, v);
// 			}
// 			return modInt(u);
// 		}
// 		constexpr modInt comb(long long a) noexcept
// 		{
// 			modInt n = *this, s = 1;
// 			for(int i = 0; i < a; i++)s *= (n - modInt(i));
// 			modInt m = 1;
// 			for(int i = 1; i <= a; i++)m *= modInt(i);
// 			return s * m.powm(Mod - 2);
// 		}
// 		constexpr bool operator==(const modInt& r) { return this->x == r.x; }
// 		constexpr bool operator!=(const modInt& r) { return this->x != r.x; }
// 		friend std::ostream& operator<<(std::ostream& os, const modInt<Mod>& a) { return os << a.x; }
// 		friend std::istream& operator>>(std::istream& is, modInt<Mod>& a)
// 		{
// 			long long v;
// 			is >> v;
// 			a = modInt<Mod>(v);
// 			return is;
// 		}
// 	};

// 	using mint = modInt<1000000007>;
// 	using mint2 = modInt<998244353>;
// } // namespace m9