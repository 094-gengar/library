#include <vector>
#include <algorithm>

namespace m9 {
template<class T> std::vector<T> divisorList(const T& N)
{
	std::vector<T> result{};
	for(T i{1}; i * i <= N; i++)
	{
		if(N % i == 0)
		{
			result.emplace_back(i);
			if(i * i != N)result.emplace_back(N / i);
		}
	}
	std::sort(std::begin(result), std::end(result));
	return result;
}
} // namespace m9