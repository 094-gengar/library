// つかいかた：
// Trie<26, 'a'> trie;
// trie.insert("atcoder");
// trie.search("atcoder")   -> true
// trie.search("at")        -> false
// trie.search_prefix("at") -> true

#ifdef COMPRO
#include <string>
#include <algorithm>
#include <vector>

namespace m9::compro {
	template <int Bsz> struct trie_impl {
		int16_t c{};
		int common;
		std::vector<int> child, accept;
		trie_impl(int16_t c) : c(c), common(0) {
			child.assign(Bsz, -1);
		}
	};

	template <int Bsz, int16_t Bchar> struct Trie {
		using node = trie_impl<Bsz>;
		std::vector<node> nodes{};
		int root = 0;

		Trie() {
			nodes.emplace_back(node(root));
		}

		void insert(const std::string& word, int word_id) {
			unsigned len = word.length();
			int node_id = 0;
			for (size_t i = 0; i < len; i++) {
				int16_t c = word[i] - Bchar;
				int& next_id = nodes[node_id].child[c];
				if (next_id == -1) {
					next_id = nodes.size();
					nodes.emplace_back(node(c));
				}
				nodes[node_id].common++;
				node_id = next_id;
			}
			nodes[node_id].common++;
			nodes[node_id].accept.emplace_back(word_id);
		}

		void insert(const std::string& word) {
			insert(word, nodes[0].common);
		}

		bool search(const std::string& word, bool prefix = false) {
			unsigned len = word.length();
			int node_id = 0;
			for (size_t i = 0; i < len; i++) {
				int16_t c = word[i] - Bchar;
				int& next_id = nodes[node_id].child[c];
				if (next_id == -1) { return false; }
				node_id = next_id;
			}
			return prefix or (nodes[node_id].accept.size() > 0);
		}

		bool search_prefix(const std::string& prefix) {
			return search(prefix, true);
		}

		int count() const {
			return (nodes.front().common);
		}

		long long size() const {
			return nodes.size();
		}
	};
} // namespace m9::compro

#endif