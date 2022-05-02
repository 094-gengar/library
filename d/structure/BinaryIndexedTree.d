// 0-indexed
struct BinaryIndexedTree(T)
{
private:
	int N;
	auto BIT = new T[](0);
public:
	this(int n, T init = 0)
	{
		N = n;
		BIT = new T[](N + 1);
		BIT[] = init;
	}
	T sum(int i)
	{
		T result = 0;
		for(; i > 0; i -= i & -i)result += BIT[i - 1];
		return result;
	}
	T sum(int l, int r) { return (sum(r) - sum(l)); }
	void add(int i, T a)
	{
		for(i++; i <= N; i += i & -i)BIT[i - 1] += a;
	}
	int lowerBountBIT(T k)
	{
		if(k <= 0)return 0;
		int result = 0, i = 1;
		for(; (i << 1) <= N;)i <<= 1;
		for(; i; i >>= 1)if(result + i <= N && BIT[result + i] < k)k -= BIT[result += i];
		return result;
	}
}
@safe pure unittest
{
	auto tr = BinaryIndexedTree!long(5);
	foreach(i; 0..5)tr.add(i, i + 1);
	assert(tr.sum(0, 5) == 15);
	assert(tr.sum(2, 4) == 7);
	tr.add(3, 10);
	assert(tr.sum(0, 5) == 25);
	assert(tr.sum(0, 3) == 6);
}