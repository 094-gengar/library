#include <random>
#include <ctime>

struct RandInt
{
private:
	std::mt19937 mt;
public:
	RandInt() { mt.seed((unsigned int)time(0)); }
	unsigned int next() { return mt(); }
	unsigned int roll(int high)
	{
		std::uniform_int_distribution<unsigned int> die(0, high - 1);
		return die(mt);
	}
} ri;
