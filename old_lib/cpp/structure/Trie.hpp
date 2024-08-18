// つかいかた：
// m9::Trie<26, 'a'> trie;
// trie.insert("atcoder");
// trie.search("atcoder")   -> true
// trie.search("at")        -> false
// trie.search_prefix("at") -> true

#include <string>
#include <algorithm>
#include <vector>

namespace m9 {
template<int BAND_SIZE> struct TrieSub {
	int16_t C{};
	int common;
	std::vector<int> child;
	std::vector<int> accept{};
	TrieSub(int16_t C) : C(C), common(0)
	{
		child.assign(BAND_SIZE, -1);
	}
};

template<int BAND_SIZE, int16_t BASE_CHAR> struct Trie {
	using Node = TrieSub<BAND_SIZE>;
	std::vector<Node> Nodes{};
	int root{0};

	Trie() { Nodes.emplace_back(Node(root)); }
	void insert(const std::string& word, int word_id)
	{
		int len = word.length();
		int node_id{0};
		for(int i{0}; i < len; i++)
		{
			int16_t c = (int16_t)(word[i]) - BASE_CHAR;
			int& next_id = Nodes[node_id].child[c];
			if(next_id == -1)
			{
				next_id = (int)(Nodes.size());
				Nodes.emplace_back(Node(c));
			}
			Nodes[node_id].common++;
			node_id = next_id;
		}
		Nodes[node_id].common++;
		Nodes[node_id].accept.emplace_back(word_id);
	}

	void insert(const std::string& word)
	{
		insert(word, Nodes[0].common);
	}

	bool search(const std::string& word, bool prefix = false)
	{
		int len = word.length();
		int node_id{0};
		for(int i{0}; i < len; i++)
		{
			int16_t C = (int16_t)(word[i]) - BASE_CHAR;
			int& next_id = Nodes[node_id].child[C];
			if(next_id == -1) { return false; }
			node_id = next_id;
		}
		return (prefix || (Nodes[node_id].accept.size() > 0));
	}

	bool search_prefix(const std::string& prefix)
	{
		return search(prefix, true);
	}

	int count() const { return (Nodes.front().common); }
	long long size() const { return Nodes.size(); }
};
} // namespace m9
