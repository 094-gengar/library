#ifdef COMPRO
#include <vector>
#include <cassert>

namespace m9::compro {
	struct Dsu {
		Dsu(int n) : _sz(n), _a(n) {
			for (size_t i = 0; i < _sz; i++) _a[i] = -1;
		}

		int leader(int x) {
			assert(x < _sz); return (_a[x] < 0 ? x : (_a[x] = leader(_a[x])));
		}
		
		bool same(int x, int y) {
			assert(x < _sz); assert(y < _sz);
			return leader(x) == leader(y);
		}
		
		void merge(int x, int y) {
			assert(x < _sz); assert(y < _sz);
			x = leader(x), y = leader(y);
			if (x == y) return;
			if (_a[x] > _a[y]) std::swap(x, y);
			_a[x] += _a[y], _a[y] = x;
		}
		
		int size(int x) {
			assert(x < _sz);
			return -_a[leader(x)];
		}
		
		std::vector<std::vector<int>> groups() {
			std::vector<int> root_buf(_sz), group_size(_sz);
			for (size_t i = 0; i < _sz; i++) group_size[root_buf[i] = leader(i)]++;
			std::vector<std::vector<int>> result(_sz);
			for (size_t i = 0; i < _sz; i++) result[i].reserve(group_size[i]);
			for (size_t i = 0; i < _sz; i++) result[root_buf[i]].emplace_back(i);
			result.erase(remove_if(begin(result), end(result), \
				[&](const std::vector<int>& v) -> bool { return v.empty(); }), end(result));
			return result;
		}

	private:
		int _sz;
		std::vector<int> _a;
	};
} // namespace m9::compro

#endif