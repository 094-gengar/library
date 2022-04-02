#include <vector>
#include <algorithm>
#include <set>

struct SCC
{
private:
	int n{};
	std::vector<std::vector<int>> g{}, rg{};
	std::vector<int> ord{}, comp{};
	std::vector<bool> usd{};

public:
	void dfs(int cur)
	{
		usd[cur] = true;
		for(const auto& e : g[cur])
			if(not usd[e])
				dfs(e);
		ord.emplace_back(cur);
	}
	void rdfs(int cur, int k)
	{
		comp[cur] = k;
		for(const auto& e : rg[cur])
			if(comp[e] == -1)
				rdfs(e, k);
	}
	SCC(std::vector<std::vector<int>>& _g) : g(_g)
	{
		(*this).n = static_cast<int>((*this).g.size());
		(*this).rg.resize(n);
		(*this).comp.assign(n, -1);
		(*this).usd.assign(n, false);
		for(int v = 0; v < n; v++)
			for(const auto& e : g[v])
				rg[e].emplace_back(v);
		for(int v = 0; v < n; v++)
			if(not usd[v])
				dfs(v);
		int k = 0;
		std::reverse(std::begin(ord), std::end(ord));
		for(const auto& v : ord)
			if(comp[v] == -1)
				rdfs(v, k++);
	};
	bool same(int u, int v)
	{
		return comp[u] == comp[v];
	}
	std::vector<std::vector<int>> rebuild()
	{
		int MX = *std::max_element(std::begin(comp), std::end(comp)) + 1;
		std::vector<std::vector<int>> rebuilded_g(n);
		std::set<std::pair<int, int>> conn{};
		for(int v = 0; v < MX; v++)
			for(const auto& e : g[v])
				if(comp[v] != comp[e] and not conn.count(std::make_pair(v, e)))
				{
					conn.emplace(v, e);
					rebuilded_g[comp[v]].emplace_back(comp[e]);
				}
		return rebuilded_g;
	}
};