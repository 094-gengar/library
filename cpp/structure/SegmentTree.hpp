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