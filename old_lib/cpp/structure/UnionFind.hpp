#include <cassert>
#include <vector>
#include <algorithm>

namespace m9 {
class UnionFind {
	int SIZ;
	std::vector<int> a;
public:
	UnionFind(int n) : SIZ(n), a(n) { for(int i{}; i < SIZ; i++)a[i] = -1; }
	int root(int x) { assert(x < SIZ); return (a[x] < 0 ? x : (a[x] = root(a[x]))); }
	bool same(int x, int y) { assert(x < SIZ); assert(y < SIZ); return root(x) == root(y); }
	void merge(int x, int y)
	{
		assert(x < SIZ);
		assert(y < SIZ);
		x = root(x), y = root(y);
		if(x == y)return;
		if(a[x] > a[y])std::swap(x, y);
		a[x] += a[y], a[y] = x;
	}
	int size(int x) { assert(x < SIZ); return -a[root(x)]; }
	std::vector<std::vector<int>> groups()
	{
		std::vector<int> rootBuf(SIZ), groupSize(SIZ);
		for(int i{}; i < SIZ; i++)groupSize[rootBuf[i] = root(i)]++;
		std::vector<std::vector<int>> result(SIZ);
		for(int i{}; i < SIZ; i++)result[i].reserve(groupSize[i]);
		for(int i{}; i < SIZ; i++)result[rootBuf[i]].emplace_back(i);
		result.erase( \
			remove_if(std::begin(result),
				std::end(result),
				[&](const std::vector<int>& v) -> bool { return v.empty(); }),
			std::end(result));
		return result;
	}
};

using uni = UnionFind;
} // namespace m9