// つかいかた：
// https://atcoder.jp/contests/abc328/submissions/47510970
#include <vector>
#include <stack>
#include <numeric>

struct UndoUnionFind {
	std::vector<int> par, sz;
	std::stack<std::pair<int, std::pair<int, int>>> hist;
	UndoUnionFind(int N) : par(N), sz(N, 1) { std::iota(std::begin(par), std::end(par), 0); }
	int root(int x) const { return (par[x] == x) ? x : root(par[x]); }
	bool merge(int a, int b)
	{
		a = root(a); b = root(b);
		if(sz[a] < sz[b])std::swap(a, b);
		hist.emplace(b, std::make_pair(par[b], sz[a]));
		return a != b ? par[b] = a, sz[a] += sz[b], true : false;
	}
	void undo()
	{
		sz[par[hist.top().first]] = hist.top().second.second;
		par[hist.top().first] = hist.top().second.first;
		hist.pop();
	}
	int size(int x) const { return sz[root(x)]; }
	bool same(int a, int b) const { return root(a) == root(b); }
};