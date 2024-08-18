#ifdef COMPRO
#include <chrono>

namespace m9::compro::timer {
	struct timer_struct {
		timer_struct() noexcept : m_start(std::chrono::system_clock::time_point::min()) { this->start(); }
		void clear() noexcept { m_start = std::chrono::system_clock::time_point::min(); }
		bool is_started() const noexcept { return m_start.time_since_epoch() != std::chrono::system_clock::duration(0); }
		void start() noexcept { m_start = std::chrono::system_clock::now(); }
		unsigned long long get_time() {
			if (is_started()) {
				std::chrono::system_clock::duration diff;
				diff = std::chrono::system_clock::now() - m_start;
				return (unsigned long long)(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() + 50);
			}
			return 0;
		}
	private:
		std::chrono::system_clock::time_point m_start;
	} tmr;
} // namespace m9::compro::timer
namespace m9::compro { using timer::tmr; } // namespace m9::compro

#endif