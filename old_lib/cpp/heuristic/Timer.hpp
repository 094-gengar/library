#include <chrono>

namespace m9 {
struct Timer {
private:
	std::chrono::system_clock::time_point m_start;
public:
	Timer() : m_start(std::chrono::system_clock::time_point::min()) { (*this).start(); }
	void clear() { m_start = std::chrono::system_clock::time_point::min(); }
	bool is_started() const { return (m_start.time_since_epoch() != std::chrono::system_clock::duration(0)); }
	void start() { m_start = std::chrono::system_clock::now(); }
	unsigned long long get_time()
	{
		if(is_started())
		{
			std::chrono::system_clock::duration diff;
			diff = std::chrono::system_clock::now() - m_start;
			return (unsigned long long)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() + 50;
		}
		return 0;
	}
} timer;
} // namespace m9
using m9::timer;