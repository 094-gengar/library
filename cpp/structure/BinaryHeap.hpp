#include <vector>
struct bheap
{
	std::vector<long> _a;
	bheap() { _a.push_back(0L); }
	void push(long _x)
	{
		_a.push_back(_x);
		long pos = _a.size() - 1;
		for(; pos > 1 && _a[pos] < _a[pos / 2]; std::swap(_a[pos], _a[pos / 2]), pos /= 2);
	}
	void pop()
	{
		_a[1] = _a[_a.size() - 1];
		_a.pop_back();
		if(_a.size() == 1)
			return;
		long pos = 1, lc, rc;
		for(; (lc = pos * 2) < _a.size();)
		{
			rc = lc + 1;
			if(lc == _a.size() - 1)
			{
				if(_a[pos] > _a[lc])
				{
					std::swap(_a[pos], _a[lc]);
					pos = lc;
				}
				else
					break;
			}
			else
			{
				if(_a[lc] < _a[rc])
				{
					if(_a[lc] < _a[pos])
					{
						std::swap(_a[pos], _a[lc]);
						pos = lc;
					}
					else
						break;
				}
				else
				{
					if(_a[rc] < _a[pos])
					{
						std::swap(_a[pos], _a[rc]);
						pos = rc;
					}
					else
						break;
				}
			}
		}
	}
	long getmin() { return _a[1]; }
	long siz() { return _a.size() - 1; }
	void cl()
	{
		_a.clear();
		_a.push_back(0L);
	}
};
