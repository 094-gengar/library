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