# これはなに

[まぐげんがー](https://twitter.com/gengar094kypro)の競プロライブラリです。

# 構造

## [cpp/compro](https://github.com/094-gengar/library/tree/main/cpp/compro/)

- [graph](https://github.com/094-gengar/library/blob/main/cpp/compro/graph)
	- [acl_scc.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/graph/acl_scc.hpp)（ACLの強連結成分分解）
	- [dijkstra.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/graph/dijkstra.hpp)（ダイクストラ法）
	- [lca.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/graph/lca.hpp)（最小共通祖先 / Lowest Common Ancestor）
- [heuristic](https://github.com/094-gengar/library/blob/main/cpp/compro/heuristic)
	- [randint.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/heuristic/randint.hpp)（乱数）
	- [timer.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/heuristic/timer.hpp)（タイマー）
- [io](https://github.com/094-gengar/library/blob/main/cpp/compro/io)
	- [fastio.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/io/fastio.hpp)（`read`と`putchar_unlocked`を使った高速入出力）
- [math](https://github.com/094-gengar/library/blob/main/cpp/compro/math)
	- [combination.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/math/combination.hpp)（`nCr`, `nPr`, `nHr`）
	- [crt.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/math/crt.hpp)（中国剰余定理）
	- [divisor_list.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/math/divisor_list.hpp)（約数列挙）
	- [modint.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/math/modint.hpp)（ACLの実装に寄せて書いたmodint）
	- [modpow.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/math/modpow.hpp)（`mod_pow`, `mod_inv`）
	- [prime_factor.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/math/prime_factor.hpp)（素因数分解）
- [string](https://github.com/094-gengar/library/blob/main/cpp/compro/string)
	- [rolling_hash.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/string/rolling_hash.hpp)（ロリハ）
	- [trie.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/string/trie.hpp)（Trie木 / Retrieval Tree）
- [structure](https://github.com/094-gengar/library/blob/main/cpp/compro/structure)
	- [bitree.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/structure/bitree.hpp)（Binary Indexed Tree / Fenwick Tree）
	- [dsu.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/structure/dsu.hpp)（UnionFind木 / Disjoint Set Union）
	- [segtree.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/structure/segtree.hpp)（セグメント木 / Segment Tree）

- [template](https://github.com/094-gengar/library/blob/main/cpp/compro/template)
	- [constant.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/template/constant.hpp)（定数の定義系）
	- [debug.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/template/debug.hpp)（デバッグ出力）
	- [def.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/template/def.hpp)（`#define`マクロ系）
	- [fn.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/template/fn.hpp)（`chmin`, `chmax`, `gcd`, `lcm`）
	- [type.hpp](https://github.com/094-gengar/library/blob/main/cpp/compro/template/type.hpp)（`using ll = long long`等）

- 下の`old_lib/cpp`を書き直して作ったので、ほぼ内容が同じ

## [old_lib/cpp](https://github.com/094-gengar/library/tree/main/old_lib/cpp)
- 以前まで使っていたライブラリ

<!--


- [graph](https://github.com/094-gengar/library/tree/main/old_lib/cpp/graph)
	 - [Graph.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/graph/Graph.hpp)  （ダイクストラとかBFSとかをやる）
	- [SCC.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/graph/SCC.hpp) （強連結成分分解）-> よくわからないのでACLを使いましょう
	- [LCA.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/graph/LCA.hpp) （最小共通祖先 / Lowest Common Ancestor）

- [heuristic](https://github.com/094-gengar/library/tree/main/old_lib/cpp/heuristic)
	- [Randint.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/heuristic/RandInt.hpp) （`std::mt19937`を使った乱数生成）
	- [Timer.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/heuristic/Timer.hpp)（`std::chrono`を使った時間計測）

- [io](https://github.com/094-gengar/library/tree/main/old_lib/cpp/io)
	- [FastIO.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/io/FastIO.hpp)（`read`と`putchar_unlocked`を使った高速入出力  `std::cin`, `std::cout`のおよそ2~5倍の実行速度）

- [math](https://github.com/094-gengar/library/tree/main/old_lib/cpp/math)
	- [Argsort.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/math/Argsort.hpp) （偏角ソートをするときに`std::sort`に渡す関数）
	- [Combination.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/math/Combination.hpp) （`nCr`, `nPr`, `nHr`などを前計算あり`O(1)`で求める）
	- [DivisorList.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/math/DivisorList.hpp) （約数列挙。返り値は`std::vector<T>`型）
	- [ModInt.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/other/Integers.hpp)  （**※Integers.hppに移動しました** modint。ACLの方が高性能）
	- [PrimeFactor.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/math/PrimeFactor.hpp) （素因数分解。`O(sqrt(N))`）
	- [PrimeFactorPollard.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/math/PrimeFactorPollard.hpp)  （ポラードのρ法を使った素因数分解。補助関数として`IP (is_prime)`, `PM (pow_mod)`がある）

- [other](https://github.com/094-gengar/library/blob/main/old_lib/cpp/other)
	- [Integers.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/other/Integers.hpp) （符号あり128bit整数のラッパー`cent_t`と`i8 ~ i64`, `u8 ~ u64`を定義 + modint）

	- [others.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/other/others.hpp) （競プロ用のテンプレート。includeのテンプレ、マクロ、デバッグとか）

	- [gridtoInt.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/other/gridtoInt.hpp) （グリッドに数字を割り振る便利関数。後でothers.hppに統合するかも？）

- [structure](https://github.com/094-gengar/library/tree/main/old_lib/cpp/structure)
	- [BinaryIndexedTree.hpp](https://github.com/094-gengar/library/tree/main/old_lib/cpp/structure/BinaryIndexedTree.hpp) （BIT / Fenwick tree。0-Indexed。）
	- [CompressVec.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/CompressVec.hpp) （`std::vector`を渡すと座標圧縮してくれる）
	- [Cumsum.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/Cumsum.hpp) （累積和）
	- [RollingHash.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/RollingHash.hpp) （ローリングハッシュ。法はデフォルトが`1e9 + 7`、好きな数にもできる）
	- [SegmentTree.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/SegmentTree.hpp) （セグメント木。`struct{ using valueType = SomeType; static SomeType op(SomeType a, SomeType b){}; static inline SomeType id{}; }`みたいな構造体でモノイドを定義してる）
	- [Trie.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/Trie.hpp) （Trie木 / Prefix Tree）
	- [UndoUnionFind.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/UndoUnionFind.hpp) （操作取消可能UF。再帰数え上げの時とかに使う。）
	- [UnionFind.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/UnionFind.hpp) （ユニオンファインド。`groups()`もある。）
	- [WeightedUnionFind.hpp](https://github.com/094-gengar/library/blob/main/old_lib/cpp/structure/WeightedUnionFind.hpp) （重み付きUF。）
-->

## C++以外の言語のライブラリ→コンテストで使ったことがないので正しく動くかどうかの保証がありません
