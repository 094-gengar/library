import std.typecons;

Tuple!(T, T)[] primeFactor(T)(T N)
{
	auto result = new Tuple!(T, T)[](0);
	for(T i = 2; i * i <= N; i++)
	{
		if(N % i)continue;
		T tmp = 0;
		while(N % i == 0)tmp++, N /= i;
        result ~= tuple(i, tmp);
    }
    if(N != 1)result ~= tuple(N, 1);
    return result;
}

unittest
{
	assert(primeFactor(13) == [tuple(13, 1)]);
	assert(primeFactor(57) == [tuple(3, 1), tuple(19, 1)]);
}