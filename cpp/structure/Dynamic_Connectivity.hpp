#include <iostream>
#include <vector>
#include <functional>
#include <unordered_set>
#include <unordered_map>

template<class T>
class dynamic_connectivity
{
	using ll = long long;
	class euler_tour_tree
	{
	public:
		struct node;
		using nodeP = node*;

		struct node
		{
			nodeP ch[2] = {nullptr, nullptr};
			nodeP p = nullptr;
			int l, r, sz;
			T val = et, sum = et;
			bool exact;
			bool child_exact;
			bool edge_connected = false;
			bool child_edge_connected = false;
			node() {}
			node(int l, int r) : l(l), r(r), sz(l == r), exact(l < r), child_exact(l < r) {}
			bool is_root() { return !p; }
		};

		std::vector<std::unordered_map<int, nodeP>> ptr;

		nodeP get_node(int l, int r)
		{
			if(ptr[l].find(r) == ptr[l].end()) ptr[l][r] = new node(l, r);
			return ptr[l][r];
		}

		nodeP root(nodeP t)
		{
			if(!t) return t;
			while(t->p) t = t->p;
			return t;
		}

		bool same(nodeP s, nodeP t)
		{
			if(s) splay(s);
			if(t) splay(t);
			return root(s) == root(t);
		}

		nodeP reroot(nodeP t)
		{
			auto s = split(t);
			return merge(s.second, s.first);
		}

		std::pair<nodeP, nodeP> split(nodeP s)
		{
			splay(s);
			nodeP t = s->ch[0];
			if(t) t->p = nullptr;
			s->ch[0] = nullptr;
			return std::make_pair(t, update(s));
		}

		std::pair<nodeP, nodeP> split2(nodeP s)
		{
			splay(s);
			nodeP t = s->ch[0];
			nodeP u = s->ch[1];
			if(t) t->p = nullptr;
			s->ch[0] = nullptr;
			if(u) u->p = nullptr;
			s->ch[1] = nullptr;
			return std::make_pair(t, u);
		}

		std::tuple<nodeP, nodeP, nodeP> split(nodeP s, nodeP t)
		{
			auto u = split2(s);
			if(same(u.first, t))
			{
				auto r = split2(t);
				return std::make_tuple(r.first, r.second, u.second);
			}
			else
			{
				auto r = split2(t);
				return std::make_tuple(u.first, r.first, r.second);
			}
		}

		template<class Car, class... Cdr>
		nodeP merge(Car car, Cdr... cdr)
		{
			return merge(car, merge(cdr...));
		}

		nodeP merge(nodeP s, nodeP t)
		{
			if(!s) return t;
			if(!t) return s;
			while(s->ch[1]) s = s->ch[1];
			splay(s);
			s->ch[1] = t;
			if(t) t->p = s;
			return update(s);
		}

		int size(nodeP t) { return t ? t->sz : 0; }

		nodeP update(nodeP t)
		{
			t->sum = et;
			if(t->ch[0]) t->sum = fn(t->sum, t->ch[0]->sum);
			if(t->l == t->r) t->sum = fn(t->sum, t->val);
			if(t->ch[1]) t->sum = fn(t->sum, t->ch[1]->sum);

			t->sz = size(t->ch[0]) + (int)(t->l == t->r) + size(t->ch[1]);
			t->child_edge_connected = (
				t->ch[0] ? t->ch[0]->child_edge_connected : 0
				) | (t->edge_connected) | (
					t->ch[1] ? t->ch[1]->child_edge_connected : 0
					);
			t->child_exact = (
				t->ch[0] ? t->ch[0]->child_exact : 0
				) | (t->exact) | (
					t->ch[1] ? t->ch[1]->child_exact : 0
					);

			return t;
		}

		void push(nodeP t) {}

		void rot(nodeP t, bool b)
		{
			nodeP x = t->p, y = x->p;
			if(x->ch[1 - b] = t->ch[b]) t->ch[b]->p = x;
			t->ch[b] = x, x->p = t;
			update(x);
			update(t);
			if(t->p = y)
			{
				if(y->ch[0] == x) y->ch[0] = t;
				if(y->ch[1] == x) y->ch[1] = t;
				update(y);
			}
		}

		void splay(nodeP t)
		{
			push(t);
			while(!t->is_root())
			{
				nodeP q = t->p;

				if(q->is_root())
				{
					push(q);
					push(t);
					rot(t, (q->ch[0] == t));
				}
				else
				{
					nodeP r = q->p;
					push(r);
					push(q);
					push(t);
					bool b = (r->ch[0] == q);
					if(q->ch[1 - b] == t)
					{
						rot(q, b);
						rot(t, b);
					}
					else
					{
						rot(t, 1 - b);
						rot(t, b);
					}
				}
			}
		}

		void debug(nodeP t)
		{
			if(!t) return;
			debug(t->ch[0]);
			std::cerr << t->l << '-' << t->r << ' ';
			debug(t->ch[1]);
		}

	public:
		euler_tour_tree() {}
		euler_tour_tree(int sz)
		{
			ptr.resize(sz);
			for(int i = 0; i < sz; i++) ptr[i][i] = new node(i, i);
		}

		int size(int s)
		{
			nodeP t = get_node(s, s);
			splay(t);
			return t->sz;
		}

		bool same(int s, int t) { return same(get_node(s, s), get_node(t, t)); }

		void set_size(int sz)
		{
			ptr.resize(sz);
			for(int i = 0; i < sz; i++) ptr[i][i] = new node(i, i);
		}

		void update(int s, T x)
		{
			nodeP t = get_node(s, s);
			splay(t);
			t->val = fn(t->val, x);
			update(t);
		}
		/*
		void edge_update(int s, auto g)
		{
			nodeP t = get_node(s, s);
			splay(t);

			std::function<void(nodeP)> dfs = [&](nodeP t)
			{
				assert(t);
				if(t->l < t->r && t->exact)
				{
					splay(t);
					t->exact = 0;
					update(t);
					g(t->l, t->r);
					return;
				}

				if(t->ch[0] && t->ch[0]->child_exact) dfs(t->ch[0]);
				else dfs(t->ch[1]);
			};

			while(t && t->child_exact)
			{
				dfs(t);
				splay(t);
			}
		}

		bool try_reconnect(int s, auto f)
		{
			nodeP t = get_node(s, s);
			splay(t);
			std::function<bool(nodeP)> dfs = [&](nodeP t) -> bool
			{
				assert(t);
				if(t->edge_connected)
				{
					splay(t);
					return f(t->l);
				}

				if(t->ch[0] && t->ch[0]->child_edge_connected) return dfs(t->ch[0]);
				else return dfs(t->ch[1]);
			};

			while(t->child_edge_connected)
			{
				if(dfs(t)) return true;
				splay(t);
			}

			return false;
		}
		*/
		void edge_connected_update(int s, bool b)
		{
			nodeP t = get_node(s, s);
			splay(t);
			t->edge_connected = b;
			update(t);
		}

		bool link(int l, int r)
		{
			if(same(l, r)) return false;
			merge(reroot(get_node(l, l)), get_node(l, r), reroot(get_node(r, r)), get_node(r, l));
			return true;
		}

		bool cut(int l, int r)
		{
			if(ptr[l].find(r) == ptr[l].end()) return false;
			nodeP s, t, u;
			std::tie(s, t, u) = split(get_node(l, r), get_node(r, l));
			merge(s, u);
			nodeP p = ptr[l][r];
			nodeP q = ptr[r][l];
			ptr[l].erase(r);
			ptr[r].erase(l);

			delete p;
			delete q;

			return true;
		}

		T get_sum(int p, int v)
		{
			cut(p, v);
			nodeP t = get_node(v, v);
			splay(t);
			T res = t->sum;
			link(p, v);
			return res;
		}

		T get_sum(int s)
		{
			nodeP t = get_node(s, s);
			splay(t);
			return t->sum;
		}
	};
	int dep = 1;
	std::vector<euler_tour_tree> ett;
	std::vector<std::vector<std::unordered_set<int>>> edges;
	int sz;

public:
	dynamic_connectivity(int sz) : sz(sz)
	{
		ett.emplace_back(sz);
		edges.emplace_back(sz);
	}

	bool link(int s, int t)
	{
		if(s == t) return false;
		if(ett[0].link(s, t)) return true;
		edges[0][s].insert(t);
		edges[0][t].insert(s);
		if(edges[0][s].size() == 1) ett[0].edge_connected_update(s, 1);
		if(edges[0][t].size() == 1) ett[0].edge_connected_update(t, 1);

		return false;
	}

	bool same(int s, int t) { return ett[0].same(s, t); }

	int size(int s) { return ett[0].size(s); }

	std::vector<int> get_vertex(int s) { return ett[0].vertex_list(s); }

	void update(int s, T x) { ett[0].update(s, x); }

	T get_sum(int s) { return ett[0].get_sum(s); }

	bool cut(int s, int t)
	{
		if(s == t) return false;
		for(int i = 0; i < dep; i++)
		{
			edges[i][s].erase(t);
			edges[i][t].erase(s);
			if(edges[i][s].size() == 0) ett[i].edge_connected_update(s, 0);
			if(edges[i][t].size() == 0) ett[i].edge_connected_update(t, 0);
		}

		for(int i = dep - 1; i >= 0; i--)
		{
			if(ett[i].cut(s, t))
			{
				if(i == dep - 1)
				{
					dep++;
					ett.emplace_back(sz);
					edges.emplace_back(sz);
				}

				return !try_reconnect(s, t, i);
			}
		}

		return false;
	}

	bool try_reconnect(int s, int t, int k)
	{
		for(int i = 0; i < k; i++) ett[i].cut(s, t);

		for(int i = k; i >= 0; i--)
		{
			if(ett[i].size(s) > ett[i].size(t)) std::swap(s, t);
			auto g = [&](int s, int t) { ett[i + 1].link(s, t); };
			ett[i].edge_update(s, g);
			auto f = [&](int x) -> bool
			{
				for(auto itr = edges[i][x].begin(); itr != edges[i][x].end();)
				{
					auto y = *itr;
					itr = edges[i][x].erase(itr);
					edges[i][y].erase(x);

					if(edges[i][x].size() == 0) ett[i].edge_connected_update(x, 0);
					if(edges[i][y].size() == 0) ett[i].edge_connected_update(y, 0);

					if(ett[i].same(x, y))
					{
						edges[i + 1][x].insert(y);
						edges[i + 1][y].insert(x);
						if(edges[i + 1][x].size() == 1) ett[i + 1].edge_connected_update(x, 1);
						if(edges[i + 1][y].size() == 1) ett[i + 1].edge_connected_update(y, 1);
					}
					else
					{
						for(int j = 0; j <= i; j++) ett[j].link(x, y);
						return true;
					}
				}

				return false;
			};

			if(ett[i].try_reconnect(s, f)) return true;
		}
		return false;
	}

	constexpr static T et = T();
	constexpr static T fn(T s, T t) { return s + t; }
};
