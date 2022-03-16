template <class T>
struct segtree
{
	using F = std::function<T(T, T)>;
	int sz;
	std::vector<T> seg;
	const F f;
	const T m1;
	segtree(int n, const F f, const T& m1) : f(f), m1(m1)
	{
		for(sz = 1; sz < n; sz <<= 1);
		seg.assign(2 * sz, m1);
	}
	void update(int k, const T& x)
	{
		k += sz;
		seg[k] = x;
		for(; k >>= 1;)
			seg[k] = f(seg[2 * k], seg[2 * k + 1]);
	}
	void set(int k, const T& x) { seg[k + sz] = x; }
	void build()
	{
		for(int k = sz - 1; k > 0; k--)
			seg[k] = f(seg[2 * k], seg[2 * k + 1]);
	}
	T query(int a, int b)
	{
		T L = m1, R = m1;
		for(a += sz, b += sz; a < b; a >>= 1, b >>= 1)
		{
			if(a & 1)
				L = f(L, seg[a++]);
			if(b & 1)
				R = f(seg[--b], R);
		}
		return f(L, R);
	}
	T operator[](const int& k) const { return seg[k + sz]; }
	template <class C>
	int find_subtree(int a, const C& check, T& M, bool type)
	{
		for(; a < sz;)
		{
			T nxt = type ? f(seg[2 * a + type], M) : f(M, seg[2 * a + type]);
			if(check(nxt))
				a = 2 * a + type;
			else
				M = nxt, a = 2 * a + 1 - type;
		}
		return a - sz;
	}
	template <class C>
	int find_first(int a, const C& check)
	{
		T L = m1;
		if(a <= 0)
			return check(f(L, seg[1])) ? find_subtree(1, check, L, false) : -1;
		int b = sz;
		for(a += sz, b += sz; a < b; a >>= 1, b >>= 1)
		{
			if(a & 1)
			{
				T nxt = f(L, seg[a]);
				if(check(nxt))
					return find_subtree(a, check, L, false);
				L = nxt;
				a++;
			}
		}
		return -1;
	}
	template <class C>
	int find_last(int b, const C& check)
	{
		T R = m1;
		if(b >= sz)
			return check(f(seg[1], R)) ? find_subtree(1, check, R, true) : -1;
		int a = sz;
		for(b += sz; a < b; a >>= 1, b >>= 1)
		{
			if(b & 1)
			{
				T nxt = f(seg[--b], R);
				if(check(nxt))
					return find_subtree(b, check, R, true);
				R = nxt;
			}
		}
		return -1;
	}
};

// SegmentTree(n, f, M1):= サイズ n の初期化。
// f : 2つの区間の要素をマージする二項演算,
// M1 はモノイドの単位元である。
// set(k, x):= k 番目の要素に x を代入する。
// build():= セグメント木を構築する。
// query(a, b):= 区間 [a, b) に対して二項演算した結果を返す。
// update(k, x):= k 番目の要素を x に変更する。
// operator[k] := k 番目の要素を返す。
// find_first(a, check) := [a,x) が check を満たす最初の要素位置 x を返す。
// find_last(b, check) := [x,b) が check を満たす最後の要素位置 x を返す。
// for example : segtree<int>seg(n,[](int a,int b){return min(a,b);},INT32_MAX);
