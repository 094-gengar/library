#ifdef COMPRO
#include <cassert>
#include <vector>

namespace m9::compro {
	template <class Monoid> struct SegmentTree {
		using T = typename Monoid::valueType;
		std::vector<T> seg;
		int sz;

		SegmentTree(int n) {
			for (sz = 1; sz < n; ) sz <<= 1;
			seg.assign(2 * sz, Monoid::id);
		}

		void update(int k, const T& x) {
			assert(0 <= k and k < sz);
			for (seg[k += sz] = x; k>>= 1; ) seg[k] = Monoid::op(seg[2 * k], seg[2 * k + 1]);
		}

		void set(int k, const T& x) { assert(0 <= k and k < sz); seg[k + sz] = x; }

		void build() {
			for (int k = sz - 1; k > 0; k--) seg[k] = Monoid::op(seg[2 * k], seg[2 * k + 1]);
		}

		T query(int a, int b) {
			assert(0 <= a and a <= b and b <= sz);
			auto L = Monoid::id;
			auto R = Monoid::id;
			for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) {
				if (a & 1) L = Monoid::op(L, seg[a++]);
				if (b & 1) R = Monoid::op(seg[--b], R);
			}
			return Monoid::op(L, R);
		}

		template<class C> int find_subtree(int a, const C& check, T& mono, bool type) {
			for (; a < sz; ) {
				auto next = Monoid::op(seg[2 * a + type], mono);
				if (check(next)) a = 2 * a + type;
				else mono = next, a = 2 * a + !type;
			}
			return (a - sz);
		}

		template<class C> int find_first(int a, const C& check) {
			assert(0 <= a and a <= sz);
			auto L = Monoid::id;
			if (a <= 0) {
				return (check(Monoid::op(L, seg[1])) ? find_subtree(1, check, L, false) : -1);
			}
			int b = sz;
			for (a += sz, b += sz; a < b; a >>= 1, b >>= 1) if (a & 1) {
				auto next = Monoid::op(L, seg[a]);
				if (check(next)) return find_subtree(a, check, L, false);
				L = next;
				a++;
			}
			return -1;
		}

		template<class C> int find_last(int b, const C& check) 	{
			assert(0 <= b and b <= sz);
			auto R = Monoid::id;
			if (b >= sz) {
				return (check(Monoid::op(seg[1], R)) ? find_subtree(1, check, R, true) : -1);
			}
			int a = sz;
			for (b += sz; a < b; a >>= 1, b >>= 1) if (b & 1) {
				auto next = Monoid::op(seg[--b], R);
				if (check(next)) return find_subtree(b, check, R, true);
				R = next;
			}
			return -1;
		}
	};

	struct RSumQ {
		using valueType = int;
		static int op(int a, int b) { return a + b; }
		static inline int id = 0;
	};
	struct RSumQLL {
		using valueType = long long;
		static long long op(long long a, long long b) { return a + b; }
		static inline long long id = 0;
	};
	struct RMaxQ {
		using valueType = int;
		static int op(int a, int b) { return std::max(a, b); }
		static inline int id = std::numeric_limits<int>::min() / 2;
	};
	struct RMaxQLL {
		using valueType = long long;
		static long long op(long long a, long long b) { return std::max(a, b); }
		static inline long long id = std::numeric_limits<long long>::min() / 2;
	};
	struct RminQ {
		using valueType = int;
		static int op(int a, int b) { return std::min(a, b); }
		static inline int id = std::numeric_limits<int>::max() / 2;
	};
	struct RminQLL {
		using valueType = long long;
		static long long op(long long a, long long b) { return std::min(a, b); }
		static inline long long id = std::numeric_limits<long long>::max() / 2;
	};
} // namespace m9::compro

#endif