#ifdef COMPRO
#include <vector>
#include <queue>
#include <cassert>

namespace m9::compro {
	template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
	std::vector<T> dijkstra_base(std::vector<std::vector<T>> graph, T s) {
		auto len = graph.size();
		assert(0 <= s and s < len);
		std::vector<T> dist(len, std::numeric_limits<T>::max() / 2);
		std::priority_queue<pair<T, T>, std::vector<pair<T, T>>, std::greater<>> pq{};
		dist[s] = 0;
		pq.emplace(dist[s], s);
		while (not pq.empty()) {
			const auto [c1, e1] = pq.top(); pq.pop();
			if (c1 > dist[e1]) continue;
			for (const auto& [cedge, e2] : graph[e1]) {
				if (dist[e2] > dist[e1] + cedge) {
					dist[e2] = dist[e1] + cedge;
					pq.emplace(dist[e2], e2);
				}
			}		
		}
		return dist;
	}
} // namespace m9::compro

#endif