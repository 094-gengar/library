#include <vector>
#include <algorithm>

struct uni
{
	int n_;
	std::vector<int> par, siz;
	uni(int n) : n_(n), par(n), siz(n, 1LL)
	{
		for(int i = 0; i < n; i++)
			par[i] = i;
	}
	void init(int n)
	{
		par.resize(n);
		siz.assign(n, 1LL);
		for(int i = 0; i < n; i++)
			par[i] = i;
	}
	void merge(int x, int y)
	{
		int rx = root(x);
		int ry = root(y);
		if(rx == ry)
			return;
		if(siz[rx] < siz[ry])
			std::swap(rx, ry);
		siz[rx] += siz[ry];
		par[ry] = rx;
		return;
	}
	int root(int x) { return par[x] == x ? x : par[x] = root(par[x]); }
	bool same(int x, int y) { return root(x) == root(y); }
	int size(int x) { return siz[root(x)]; }
	std::vector<std::vector<int>> groups()
	{
		std::vector<int> rbuf(n_), grsiz(n_);
		for(int i = 0; i < n_; i++)
			grsiz[(rbuf[i] = root(i))]++;
		std::vector<std::vector<int>> res(n_);
		for(int i = 0; i < n_; i++)
			res[i].reserve(grsiz[i]);
		for(int i = 0; i < n_; i++)
			res[rbuf[i]].push_back(i);
		res.erase(remove_if(res.begin(), res.end(), [&](const std::vector<int>& v)
			{ return v.empty(); }),
			res.end());
		return res;
	}
};
