#include <cassert>

namespace m9 {
template<class T> struct cumsum {
private:
	int SIZ;
public:
	std::vector<T> S;
	cumsum(std::vector<T> a)
	{
		SIZ = a.size();
		S.assign(SIZ + 1, 0);
		for(int i{}; i < SIZ; i++)S[i + 1] = S[i] + a[i];
	}
	void init(std::vector<T> a)
	{
		SIZ = a.size();
		S.assign(SIZ + 1, 0);
		for(int i{}; i < SIZ; i++)S[i + 1] = S[i] + a[i];
	}
	T operator[](int idx) { assert(0 <= idx and idx <= SIZ); return S[idx]; }
};
} // namespace m9