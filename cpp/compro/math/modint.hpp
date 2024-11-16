#ifdef COMPRO
namespace m9::compro {
	template <int m, std::enable_if_t<(1 <= m)>* = nullptr> struct static_modint {
		using mint = static_modint;
		static constexpr int mod() { return m; }
		static mint raw(int v) { mint x; x._v = v; return x; }
		static_modint() : _v(0) {}
		template <class T, std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>* = nullptr> static_modint(T v) {
			long long x = (long long)(v % (long long)(umod()));
			if (x < 0) x += umod();
			_v = (unsigned int)(x);
		}
		template <class T, std::enable_if_t<std::is_integral_v<T> && std::is_unsigned_v<T>>* = nullptr> static_modint(T v) {
			_v = (unsigned int)(v % umod());
		}
		unsigned int val() const { return _v; }
		mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this; }
		mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this; }
		mint operator++(int) { mint res = *this; ++*this; return res; }
		mint operator--(int) { mint res = *this; --*this; return res; }
		mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod(); return *this; }
		mint& operator-=(const mint& rhs) { _v -= rhs._v; if (_v >= umod()) _v += umod(); return *this; }
		mint& operator*=(const mint& rhs) { unsigned long long z = _v; z *= rhs._v; _v = (unsigned int)(z % umod()); return *this; }
		mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
		mint operator-() const { return mint() - *this; }
		mint pow(long long n) const {
			assert(0 <= n);
			mint x = *this, r = 1;
			while (n) {
				if (n & 1) r *= x;
				x *= x;
				n >>= 1;
			}
			return r;
		}
		mint inv() const { assert(_v); return pow(umod() - 2); }
		mint operator+(const mint& rhs) { return mint(*this) += rhs; }
		mint operator-(const mint& rhs) { return mint(*this) -= rhs; }
		mint operator*(const mint& rhs) { return mint(*this) *= rhs; }
		mint operator/(const mint& rhs) { return mint(*this) /= rhs; }
		mint operator==(const mint& rhs) { return this->_v == rhs._v; }
		mint operator!=(const mint& rhs) { return this->_v != rhs._v; }
	private:
		unsigned int _v;
		static constexpr unsigned int umod() { return m; }
	};

	using modint1000000007 = static_modint<1000000007>;
	using modint998244353 = static_modint<998244353>;
} // namespace m9::compro

#endif