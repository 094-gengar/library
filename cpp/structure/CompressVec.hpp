#include <map>

namespace m9 {
template<class T> struct compress {
private:
	int SIZ;
public:
	std::vector<T> C;
	compress(std::vector<T> a)
	{
		SIZ = a.size();
		C = a;
		std::map<T, T> mp{};
		for(int i{}; i < SIZ; i++)mp[C[i]] = -1;
		int c{};
		for(auto&[key, value] : mp)value = c++;
		for(int i{}; i < SIZ; i++)C[i] = mp[C[i]];
	}
	void init(std::vector<T> a)
	{
		SIZ = a.size();
		C = a;
		std::map<T, T> mp{};
		for(int i{}; i < SIZ; i++)mp[C[i]] = -1;
		int c{};
		for(auto&[key, value] : mp)value = c++;
		for(int i{}; i < SIZ; i++)C[i] = mp[C[i]];
	}
	T operator[](int idx) { assert(0 <= idx and idx < SIZ); return C[idx]; }
};
} // namespace m9