#include <vector>
// 1-indexed
template <class T>
struct BIT
{
	int n;
	std::vector<T> _Bit;
	BIT(int n_ = 0, T init = 0) : n(n_), _Bit(n_ + 1, init) {}
	T sum(int i)
	{
		T ans = 0;
		for(; i > 0; i -= i & -i)
			ans += _Bit[i];
		return ans;
	}
	void add(int i, T a)
	{
		if(!i)
			return;
		for(; i <= n; i += i & -i)
			_Bit[i] += a;
	}
	int l_b_Bit(T k)
	{
		if(k <= 0)
			return 0;
		int ret = 0, i = 1;
		for(; (i << 1) <= n; i <<= 1);
		for(; i; i >>= 1)
			if(ret + i <= n && _Bit[ret + i] < k)
				k -= _Bit[ret += i];
		return (ret + 1);
	}
};