#ifdef COMPRO
#ifdef ONLINE_JUDGE
#	define dbg(...) void(0)
#else
#	define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
#endif
namespace m9::compro {
	template <class Car, class... Cdr> void debug_impl(const char* s, Car&& car, Cdr&&... cdr) {
		constexpr const char* open_bracket = (sizeof...(cdr) == 0 ? "" : "(");
		constexpr const char* close_bracket = (sizeof...(cdr) == 0 ? "" : ")");
#ifdef FASTIO
		wt(open_bracket, s, close_bracket, " : ", open_bracket, std::forward<Car>(car));
		(wt(", ", std::forward<Cdr>(cdr)), ...);
		wt(close_bracket, '\n');
#else
		std::cerr << open_bracket << s << close_bracket << " : " << open_bracket << std::forward<Car>(car);
		((std::cerr << ", " << std::forward<Cdr>(cdr)), ...);
		std::cerr << close_bracket << "\n";
#endif 
	}
} // namespace m9::compro

#endif