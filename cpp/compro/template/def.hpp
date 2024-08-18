#ifdef COMPRO
#pragma GCC optimize("O3")
#define _OVERLOAD(_1, _2, _3, name, ...) name
#define _REP0(q) for ([[maybe_unused]] long long _ = 0; _ < (q); _++)
#define _REP1(i, n) for (long long i = 0; i < (n); i++)
#define _REP2(i, a, b) for (long long i = (a); i < (b); i++)
#define REP(...) _OVERLOAD(__VA_ARGS__, _REP2, _REP1, _REP0)(__VA_ARGS__)
#define FOR(e, v) for (auto&& e : v)
#define CFOR(e, v) for (const auto& e : v)
#define M_P make_pair
#define M_T make_tuple
#define CAUTO const auto&
#define ALL(x) begin(x), end(x)
#define SORT(x) sort(ALL(x))
#define RSORT(x) ({ sort(ALL(x)); reverse(ALL(x)); })
#define UNIQUE(x) x.erase(unique(ALL(x)), end(x))
#define L_B(v, e) distance(begin(v), lower_bound(ALL(v), (e)));
#define U_B(v, e) distance(begin(v), upper_bound(ALL(v), (e)));

#endif