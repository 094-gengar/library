// つかいかた：
// https://atcoder.jp/contests/abc328/submissions/47511359
#include <vector>
#include <numeric>

template <class S> struct WeightedUnionFind {
	std::vector<int> par, sz;
	std::vector<S> pot;
	WeightedUnionFind(int N = 0) : par(N), sz(N, 1), pot(N) {
		std::iota(begin(par), end(par), 0);
	}
	int root(int x)
	{
		if(par[x] != x)
		{
			int r = root(par[x]);
			pot[x] = pot[x] + pot[par[x]];
			par[x] = r;
		}
		return par[x];
	}
	bool merge(int a, int b, S rel_diff)
	{
		// マージできるときはtrue、出来ないときはfalseを返す
		rel_diff = rel_diff + weight(a) + (-weight(b));
		a = root(a);
		b = root(b);
		if(a == b)return rel_diff == 0;
		if(sz[a] < sz[b])std::swap(a, b), rel_diff *= -1;
		par[b] = a;
		sz[a] += sz[b];
		pot[b] = rel_diff;
		return true;
	}
	S weight(int x) { root(x); return pot[x]; }
	S diff(int a, int b) { return weight(b) + (-weight(a)); }
	int size(int x) { return sz[root(x)]; }
	bool same(int a, int b) { return root(a) == root(b); }
};