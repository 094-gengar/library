// Euler Tourもしてるやつ → https://atcoder.jp/contests/abc294/submissions/39948286
#ifdef COMPRO
#include <vector>

namespace m9::compro {
	struct Lca {
		Lca(const std::vector<std::vector<int>>& g, int root = 0) { init(g, root); }

		void init(const std::vector<std::vector<int>>& g, int root = 0) {
			int v = g.size(), k = 1;
			for (; 1 << k < v; k++) {}
			_par.assign(k, std::vector<int>(v, -1));
			_dist.assign(v, -1);
			dfs(g, root, -1, 0);
			for (int i = 0; i < k - 1; i++) for (int j = 0; j < v; j++) {
				if (_par[i][j] < 0) _par[i + 1][j] = -1;
				else _par[i + 1][j] = _par[i][_par[i][j]];
			}
		}

		void dfs(const std::vector<std::vector<int>>& g, int v, int p, int d) {
			_par[0][v] = p;
			_dist[v] = d;
			for (int e : g[v]) if(e != p) dfs(g, e, v, d + 1);
		}

		int run(int u, int v) {
			if (_dist[u] < _dist[v]) std::swap(u, v);
			int k = _par.size();
			for (int i = 0; i < k; i++) if (_dist[u] - _dist[v] >> i & 1) u = _par[i][u];
			if (u == v) return u;
			for (int i = k - 1; i >= 0; i--) if(_par[i][u] != _par[i][v]) {
				u = _par[i][u];
				v = _par[i][v];
			}
			return _par[0][u];
		}

		int distance(int u, int v) {
			return _dist[u] + _dist[v] - _dist[run(u, v)] * 2;
		}

		bool is_on_path(int u, int v, int a) {
			return distance(u, a) + distance(a, v) == distance(u, v);
		}
	
	private:
		std::vector<std::vector<int>> _par;
		std::vector<int> _dist;
	};
} // namespace m9::compro

#endif