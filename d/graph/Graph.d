struct Graph(T) {
	bool chmin(T)(ref T a, in T b) {
		if (b < a) { a = b; return true; } else { return false; }
	}
	int N;
	auto G = new T[][](0, 0);
	this(int n, T[][] g) { N = n; G = g; }
	T[] bfs(T s, T t = -1) {
		import std.container : DList;
		auto dis = new T[](N); dis[] = T.max;
		auto vis = new bool[](N); dis[] = false;
		dis[s] = 0;
		vis[s] = true;
		auto q = DList!T(s);
		while (!q.empty) {
			T cur = q.front; q.removeFront;
			if (vis[cur]) continue;
			else vis[cur] = true;
			foreach (e; G[cur])
				if (chmin(dis[e], dis[cur] + 1))
					q.insertFront(e);
		}
		if (t == -1) return dis;
		else return T[](dis[t]);
	}
}

struct WeightedGraph(T) {
	import std.typecons;
	alias PTT = Tuple!(T, T);
	int N;
	auto G = new PTT[][](0, 0);
	bool chmin(T)(ref T a, in T b) {
		if (b < a) { a = b; return true; } else { return false; }
	}
	this(int n, PTT[][] g) { N = n; G = g; }
	T[] bfs(T s, T t = -1) {
		import std.container : DList;
		auto dis = new T[](N); dis[] = T.max;
		dis[s] = 0;
		auto q = DList!PTT([PTT(0, s)]);
		while (!q.empty) {
			auto cur = q.front; q.removeFront;
			if (cur[0] > dis[cur[1]]) continue;
			foreach (e; G[cur[1]])
				if (chmin(dis[e[1]], dis[cur[1]] + e[0]))
					q.insertFront(PTT(dis[e[1]], e[1]));
		}
		if (t == -1) return dis;
		else return [dis[t]];
	}
	T[] dijk(T s, T t = -1) {
		import std.container : heapify;
		auto dis = new T[](N); dis[] = T.max;
		dis[s] = 0;
		auto pq = heapify!"a[0] > b[0]"([PTT(0, s)]);
		while (!pq.empty) {
			auto cur = pq.removeAny;
			if (cur[0] > dis[cur[1]]) continue;
			foreach (e; G[cur[1]])
				if (chmin(dis[e[1]], dis[cur[1]] + e[0]))
					pq.insert(PTT(dis[e[1]], e[1]));
		}
		if (t == -1) return dis;
		else return [dis[t]];
	}
}