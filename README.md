# これはなに

[まぐげんがー](https://twitter.com/gengar094kypro)の競プロライブラリです。

# 構造

## [C++](https://github.com/094-gengar/library/tree/main/cpp)
- TODO
- 下のC++_oldを書き直して作ったので、ほぼ内容が同じ

## [C++_old](https://github.com/094-gengar/library/tree/main/old_lib/cpp)
- 以前まで使っていたライブラリ

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

## C++以外の言語のライブラリ→コンテストで使ったことがないので正しく動くかどうかの保証がありません
