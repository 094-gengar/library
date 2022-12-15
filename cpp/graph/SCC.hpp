#include <cassert>
#include <vector>
#include <algorithm>
#include <set>

namespace m9 {
class SCC {
	int SIZ;
	std::vector<std::vector<int>> g, rg;
	std::vector<int> ord, comp;
	std::vector<std::int8_t> used;
public:
	void dfs(int cur)
	{
		used[cur] = true;
		for(const auto& e : g[cur])if(not used[e])dfs(e);
		ord.emplace_back(cur);
	}
	void rdfs(int cur, int k)
	{
		comp[cur] = k;
		for(const auto& e : rg[cur])if(comp[e] == -1)rdfs(e, k);
	}
	SCC(std::vector<std::vector<int>>& tmp) : g(tmp)
	{
		SIZ = static_cast<int>(g.size());
		rg.resize(SIZ);
		comp.assign(SIZ, -1);
		used.assign(SIZ, false);
		for(int v{}; v < SIZ; v++)
			for(const auto& e : g[v])
				rg[e].emplace_back(v);
		for(int v{}; v < SIZ; v++)if(not used[v])dfs(v);
		int k{};
		std::reverse(std::begin(ord), std::end(ord));
		for(const auto& v: ord)if(comp[v] == -1)rdfs(v, k++);
	}
	bool same(int u, int v)
	{
		assert(0 <= u and u < SIZ);
		assert(0 <= v and v < SIZ);
		return comp[u] == comp[v];
	}
	std::vector<std::vector<int>> rebuild()
	{
		int MX = *std::max_element(std::begin(comp), std::end(comp)) + 1;
		std::vector<std::vector<int>> rebuildedGraph(SIZ);
		std::set<std::pair<int, int>> conn{};
		for(int v{}; v < MX; v++)
			for(const auto& e : g[v])
				if(comp[v] != comp[e] and not conn.count(std::make_pair(v, e)))
					conn.emplace(v, e), rebuildedGraph[comp[v]].emplace_back(comp[e]);
		return rebuildedGraph;
	}
};
} // namespace m9