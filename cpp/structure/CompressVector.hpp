template <class T>
struct compress_vector
{
	int n;
	std::vector<T> a;
	compress_vector(int n_) : n(n_), a(n_) {};
	void compress()
	{
		std::map<T, T> mp;
		for(int i = 0; i < n; i++)
			mp[a[i]] = -1;
		int c = 0;
		for(auto& p : mp)
			p.second = c++;
		for(int i = 0; i < n; i++)
			a[i] = mp[a[i]];
	}
};