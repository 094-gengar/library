// #include <vector>
// #include <map>
// #include <random>

// namespace m9 {

// using namespace std;
// using ll = long long; 

// struct zobrist_hash {
// 	map<ll, ll> mp;
// 	std::mt19937_64 mt;
// 	std::uniform_int_distribution<ll> randrange;
// 	zobrist_hash() {
// 		mt.seed((unsigned)time(0));
// 	}
// 	vector<ll> hashed_vec(vector<ll>& a) {
// 		size_t len = a.size();
// 		vector<ll> res(len);
// 		for (size_t i = 0; i < len; i++) {
// 			if (not mp.count(a[i])) {
// 				mp[a[i]] = randrange(mt);
// 			}
// 			res[i] = mp[a[i]];
// 		}
// 		return res;
// 	}
// 	ll zobrist_hashing(vector<ll>& a) {
		
// 	}
// };

// }