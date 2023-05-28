#include <utility>

namespace m9 {
template<class T> bool arg_cmp(const std::pair<T, T>& p, const std::pair<T, T>& q)
{
	auto area = [](const std::pair<T, T>& a) -> int {
		const auto&[x, y] = a;
		if(y < 0)return -1;
		else if(y == 0 and 0 <= x)return 0;
		else return 1;
	};
	const int ap = area(p);
	const int aq = area(q);
	if(ap != aq)return ap < aq;
	else
	{
		const auto& [px, py] = p;
		const auto& [qx, qy] = q;
		return (0 < (px * qy - py * qx));
	}
}
} // namespace m9