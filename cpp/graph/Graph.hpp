#include <cassert>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

namespace m9 {
template<class T> struct Graph {
	template<class _T> inline bool chmin(_T& a, const _T& b)
	{
		if(b < a) { a = b; return true; }
		else return false;
	}
	int SIZ;
	// bool isOffset;
	// bool isDirected;
	std::vector<std::vector<T>> G;
	Graph() = default;
	Graph(int n) : SIZ(n) {}
	// Graph(int n, bool offset, bool directed) : SIZ(n), isOffset(offset), isDirected(directed), G(n) {}

	void init(std::vector<std::vector<T>> g) { SIZ = g.size(); G = g; }
	std::vector<T> bfs(T s, T t = -1)
	{
		assert(0 <= s and s < SIZ);
		assert((t == -1) or (0 <= s or s < SIZ));
		std::vector<T> dist(SIZ, std::numeric_limits<T>::max() / 2);
		std::vector<std::int8_t> vis(SIZ, false);
		dist[s] = 0;
		std::queue<T> q{};
		q.emplace(s);
		while(!q.empty())
		{
			T cur = q.front(); q.pop();
			for(const auto& e : G[cur])if(chmin(dist[e], dist[cur] + 1))q.emplace(e);
		}
		return (t == -1 ? dist : std::vector<T>{dist[t]});
	}
};

// #include <utility>

template<class T> struct weightedGraph {
	using PTT = std::pair<T, T>;
	template<class _T> inline bool chmin(_T& a, const _T& b)
	{
		if(b < a) { a = b; return true; }
		else return false;
	}
	int SIZ;
	// bool isOffset;
	// bool isDirected;
	std::vector<std::vector<PTT>> G;
	weightedGraph() = default;
	weightedGraph(int n) : SIZ(n) {}
	// weightedGraph(int n, bool os, bool drc) : SIZ(n), isOffset(os), isDirected(drc), G(n) {}

	void init(std::vector<std::vector<PTT>> g) { SIZ = g.size(); G = g; }
	std::vector<T> bfs(T s, T t = -1)
	{
		assert(0 <= s and s < SIZ);
		assert((t == -1) or (0 <= s or s < SIZ));
		std::vector<T> dist(SIZ, std::numeric_limits<T>::max() / 2);
		std::vector<std::int8_t> vis(SIZ, false);
		dist[s] = 0;
		std::queue<PTT> q{};
		q.emplace(0, s);
		while(!q.empty())
		{
			const auto [curCst, curE]= q.front(); q.pop();
			if(curCst > dist[curE])continue;
			for(const auto&[cst, e] : G[curE])if(chmin(dist[e], dist[curE] + cst))q.emplace(dist[e], e);
		}
		return (t == -1 ? dist : std::vector<T>{dist[t]});
	}
	std::vector<T> dijk(T s, T t = -1)
	{
		assert(0 <= s and s < SIZ);
		assert((t == -1) or (0 <= s or s < SIZ));
		std::vector<T> dist(SIZ, std::numeric_limits<T>::max() / 2);
		std::vector<std::int8_t> vis(SIZ, false);
		dist[s] = 0;
		std::priority_queue<PTT, std::vector<PTT>, std::greater<>> pq{};
		pq.emplace(0, s);
		while(!pq.empty())
		{
			const auto [curCst, curE]= pq.top(); pq.pop();
			if(curCst > dist[curE])continue;
			for(const auto&[cst, e] : G[curE])if(chmin(dist[e], dist[curE] + cst))pq.emplace(dist[e], e);
		}
		return (t == -1 ? dist : std::vector<T>{dist[t]});
	}
};
} // namespace m9