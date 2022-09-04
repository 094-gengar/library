T[] divisorList(T)(in T N) {
	import std.algorithm : sort;
	auto result = new int[](0);
	for (T i = 1; i * i <= N; i++) {
		if (N % i == 0) {
			result ~= i;
			if (i * i != N) result ~= N / i;
		}
	}
	result.sort;
	return result;
}

unittest
{
	assert(divisorList(12) == [1, 2, 3, 4, 6, 12]);
	assert(divisorList(57) == [1, 3, 19, 57]);
}