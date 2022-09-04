struct UnionFind {
private:
	int N;
	auto A = new int[](0);
public:
	this(int n) {
		this.N = n;
		this.A = new int[](n);
		this.A[] = -1;
	}
	int root(int x) { return (A[x] < 0 ? x : (A[x] = root(A[x]))); }
	bool same(int x, int y) { return (root(x) == root(y)); }
	void merge(int x, int y) {
		import std.algorithm.mutation : swap;
		x = root(x), y = root(y);
		if (x == y) return;
		if (A[x] > A[y]) swap(x, y);
		A[x] += A[y], A[y] = x;
	}
	int size(int x) { return -A[root(x)]; }
}

@safe pure unittest
{
	auto uf = UnionFind(4);
	assert(!uf.same(0, 1));
	uf.merge(0, 1);
	uf.merge(2, 3);
	assert(uf.same(0, 1));
	assert(!uf.same(1, 2));
	uf.merge(0, 2);
	assert(uf.same(1, 3));
}