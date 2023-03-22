#include <vector>

namespace m9 {
struct LCA {
	std::vector<std::vector<int>> par;
	std::vector<int> dis;
	LCA(const std::vector<std::vector<int>>& g, int root = 0) { init(g, root); }
	void init(const std::vector<std::vector<int>>& g, int root = 0)
	{
		int v = g.size(), k = 1;
		for(; 1 << k < v; k++) {}
		par.assign(k, std::vector<int>(v, -1));
		dis.assign(v, -1);
		dfs(g, root, -1, 0);
		for(int i = 0; i < k - 1; i++)for(int j = 0; j < v; j++)
		{
			if(par[i][j] < 0)par[i + 1][j] = -1;
			else par[i + 1][j] = par[i][par[i][j]];
		}
	}
	void dfs(const std::vector<std::vector<int>>& g, int v, int p, int d)
	{
		par[0][v] = p;
		dis[v] = d;
		for(int e : g[v])if(e != p)dfs(g, e, v, d + 1);
	}
	int run(int u, int v)
	{
		if(dis[u] < dis[v])std::swap(u, v);
		int k = par.size();
		for(int i = 0; i < k; i++)if(dis[u] - dis[v] >> i & 1)u = par[i][u];
		if(u == v)return u;
		for(int i = k - 1; i >= 0; i--)if(par[i][u] != par[i][v])
		{
			u = par[i][u];
			v = par[i][v];
		}
		return par[0][u];
	}
	int distance(int u, int v) { return dis[u] + dis[v] - dis[run(u, v)] * 2; }
	bool isOnPath(int u, int v, int a) { return distance(u, a) + distance(a, v) == distance(u, v); }
};
} // namespace m9
