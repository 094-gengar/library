#ifdef COMPRO
#include <random>
#include <ctime>

namespace m9::compro::rand {
	struct randint_struct {
		std::mt19937_64 mt;
		randint_struct() noexcept { mt.seed((unsigned int)(time(0))); }
		unsigned long long randint() { return mt(); }
		unsigned long long randrange(unsigned long long u) { // [0..u)
			std::uniform_int_distribution<unsigned long long> rng(0, u - 1);
			return rng(mt);
		}
	} rd;
} // namespace m9::compro::rand
namespace m9::compro { using rand::rd; } // namespace m9::compro

#endif