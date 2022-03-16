#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

template <class T>
struct graph
{
	template <class _T>
	inline bool chmin(_T& a, const _T& b)
	{
		if(b < a)
		{
			a = b;
			return true;
		}
		return false;
	}
	int _n;
	bool _idx;
	bool _drc;
	std::vector<std::vector<T>> _g;
	graph(int n, bool drc = false, bool idx = 1)
		: _n(n), _drc(drc), _idx(idx), _g(n)
	{
	}
	void init(int m)
	{
		T a, b;
		for(int i = 0; i < m; i++)
		{
			scanf("%d %d", &a, &b);
			a -= _idx;
			b -= _idx;
			_g[a].emplace_back(b);
			if(!_drc)
				_g[b].emplace_back(a);
		}
	}
	std::vector<T> bfs(T s, T t = -1)
	{
		std::vector<T> dis(_n, 1ll << 29);
		std::vector<bool> vis(_n, false);
		dis[s] = 0;
		std::queue<T> q;
		q.emplace(s);
		while(q.size())
		{
			T cur = q.front();
			q.pop();
			for(auto e : _g[cur])
				if(chmin(dis[e], dis[cur] + 1))
					q.emplace(e);
		}
		if(t == -1)
			return dis;
		else
			return std::vector<T>{dis[t]};
	}
};

template <class T>
struct weighted_graph
{
	using ptt = std::pair<T, T>;
	int _n;
	bool _idx;
	bool _drc;
	std::vector<std::vector<ptt>> _g;
	weighted_graph(int n, bool drc = false, bool idx = 1)
		: _n(n), _drc(drc), _idx(idx), _g(n)
	{
	}
	void init(int m, bool cst = true)
	{
		T a, b, c = 1;
		for(int i = 0; i < m; i++)
		{
			if(cst)
				scanf("%d %d %d", &a, &b, &c);
			else
				scanf("%d %d", &a, &b);
			a -= _idx;
			b -= _idx;
			_g[a].emplace_back(c, b);
			if(!_drc)
				_g[b].emplace_back(c, a);
		}
	}
	std::vector<T> bfs(T s, T t = -1)
	{
		std::vector<T> dis(_n, 1ll << 29);
		std::vector<bool> vis(_n, false);
		dis[s] = 0;
		std::queue<ptt> q;
		q.emplace(0, s);
		while(q.size())
		{
			ptt cur = q.front();
			q.pop();
			if(cur.first > dis[cur.second])
				continue;

			for(auto e : _g[cur.second])
				if(chmin(dis[e.second], dis[cur.second] + e.first))
					q.emplace(dis[e.second], e.second);
		}
		if(t == -1)
			return dis;
		else
			return std::vector<T>{dis[t]};
	}

	std::vector<T> dijkstra(T s, T t = -1)
	{
		std::vector<T> dis(_n, 1ll << 29);
		std::vector<bool> vis(_n, false);
		dis[s] = 0;
		std::priority_queue<ptt, std::vector<ptt>, std::greater<>> pq;
		pq.emplace(0, s);
		while(pq.size())
		{
			ptt cur = pq.top();
			pq.pop();
			if(cur.first > dis[cur.second])
				continue;
			for(auto e : _g[cur.second])
				if(chmin(dis[e.second], dis[cur.second] + e.first))
					pq.emplace(dis[e.second], e.second);
		}
		if(t == -1)
			return dis;
		else
			return std::vector<T>{dis[t]};
	}
};
