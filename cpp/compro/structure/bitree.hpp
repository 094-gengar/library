#ifdef COMPRO
#include <vector>
#include <cassert>

namespace m9::compro {
	template <class T> struct BITree {
		int sz;
		std::vector<T> tree;

		BITree(int sz, T x = (T)(0)) : sz(sz), tree(sz + 1, x) {}

		T sum(int i) {
			assert(0 <= i and i <= sz);
			T res = 0;
			for (; i > 0; i -= i & -i) res += tree[i];
			return res;
		}

		T sum(int l, int r) {
			return sum(r) - sum(l);
		}

		void add(int i, T a) {
			assert(0 <= i and i < sz);
			for (i++; i <= sz; i += i & -i) tree[i] += a;
		}
	};
}

#endif