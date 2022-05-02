struct Deque(T)
{
	import std.range, std.algorithm, std.conv, std.format;
private:
	T[] frontData = [];
	T[] backData = [];
	size_t frontSize = 0, backSize = 0;
	ptrdiff_t beginIdx = 0, endIdx = 0;
public:
	this(T[] data)
	{
		this([], data, 0, data.length, 0, cast(ptrdiff_t)(data.length), false);
	}
	bool empty() const @property { return beginIdx == endIdx; }
	size_t length() const @property { return cast(size_t)(endIdx - beginIdx); }
	void clear()
	{
		beginIdx = endIdx = 0;
		frontData = [];
		backData = [];
		frontSize = backSize = 0;
	}
	ref T front() @property in { assert(!empty); } do
	{
		return this[0];
	}
	ref T front(T value) @property in { assert(!empty); } do
	{
		return (this[0] = value);
	}
	ref T back() @property in { assert(!empty); } do
	{
		return this[$ - 1];
	}
	ref T back(T value) @property in { assert(!empty); } do
	{
		return (this[$ - 1] = value);
	}
	void insertFront(T value)
	{
		if(beginIdx > 0)backData[beginIdx - 1] = value;
		else
		{
			if(frontSize >= frontData.length)resizeFront();
			frontData[frontSize++] = value;
		}
		beginIdx--;
	}
	void insertBack(T value)
	{
		if(endIdx < 0)frontData[-endIdx - 1] = value;
		else
		{
			if(backSize >= backData.length)resizeBack();
			backData[backSize++] = value;
		}
		endIdx++;
	}
	void removeFront() in { assert(!empty); } do
	{
		if(beginIdx >= 0) {}
		else
		{
			assert(frontSize > 0);
			frontSize--;
		}
		beginIdx++;
	}
	void removeBack() in { assert(!empty); } do
	{
		if(endIdx <= 0) {}
		else
		{
			assert(backSize > 0);
			backSize--;
		}
		endIdx--;
	}
	alias popBack = removeBack;
	alias popFront = removeFront;
	typeof(this) save() @property
	{
		return typeof(this)(frontData, backData, frontSize, backSize, beginIdx, endIdx, true);
	}
	alias dup = save;
	typeof(this) opOpAssign(string op)(T value) if(op == "~")
	{
		this.insertBack(value);
		return this;
	}
	ref T opIndex(size_t index) in { assert(0 <= index && index < length); } do
	{
		ptrdiff_t _idx = beginIdx + cast(ptrdiff_t)(index);		
		return (_idx >= 0 ? backData[_idx] : frontData[-_idx - 1]);
	}
	typeof(this) opIndex(size_t[2] indices) in { assert(0 <= indices[0] && indices[1] <= length); } do
	{
		ptrdiff_t newBeginIdx = beginIdx + cast(ptrdiff_t)(indices[0]);
		ptrdiff_t newEndIdx = beginIdx + cast(ptrdiff_t)(indices[1]);
		size_t newFrontSize = clamp(-newBeginIdx, 0, frontSize);
		size_t newBackSize = clamp(newEndIdx, 0, backSize);
		return typeof(this)(frontData, backData, newFrontSize, newBackSize, newBeginIdx, newEndIdx, false);
	}
	typeof(this) opIndex() { return this; }
	ref T opIndexAssign(T value, size_t index) in { assert(0 <= index && index < length); } do
	{
		ptrdiff_t _idx = cast(ptrdiff_t)(index) - beginIdx;
		return ((_idx >= 0 ? backData[_idx] : frontData[-_idx - 1]) = value);
	}
	typeof(this) opIndexAssign(T value, size_t[2] indices) in { assert(0 <= indices[0] && indices[1] <= length); } do
	{
		ptrdiff_t _beginIdx = beginIdx + cast(ptrdiff_t)(indices[0]);
		ptrdiff_t _endIdx = beginIdx + cast(ptrdiff_t)(indices[1]);
		frontData[clamp(-_endIdx, 0, frontSize) .. clamp(-_beginIdx, 0, frontSize)] = value;
		backData[clamp(_beginIdx, 0, backSize) .. clamp(_endIdx, 0, backSize)] = value;
		return this;
	}
	typeof(this) opIndexAssign(T value)
	{
		backData[0 .. backSize] = value;
		frontData[0 .. frontSize] = value;
		return this;
	}
	typeof(this) opIndexOpAssign(string op)(T value, size_t[2] indices) in {
		assert(0 <= indices[0] && indices[1] <= length);
	} do
	{
		ptrdiff_t _beginIdx = beginIdx + cast(ptrdiff_t)(indices[0]);
		ptrdiff_t _endIdx = beginIdx + cast(ptrdiff_t)(indices[1]);
		mixin(q{
			frontData[clamp(-_endIdx, 0, frontSize) .. clamp(-_beginIdx, 0, frontSize)] %s= value;
		}.format(op));
		mixin(q{
			backData[clamp(_beginIdx, 0, backSize) .. clamp(_endIdx, 0, backSize)] %s= value;	
		}.format(op));
		return this;
	}
	typeof(this) opIndexOpAssign(string op)(T value)
	{
		mixin(q{
			frontData[0..frontSize] %s= value;
		}.format(op));
		mixin(q{
			backData[0..backSize] %s= value;
		}.format(op));
		return this;
	}
	size_t opDollar(size_t dim : 0)()
	{
		return length;
	}
	size_t[2] opSlice(size_t dim : 0)(size_t start, size_t end) in { assert(0 <= start && end <= length); } do
	{
		return [start, end];
	}
	bool opEquals(S : T)(Deque!S other)
	{
		if(this.length != other.length)return false;
		foreach(i; 0..this.length)if(this[i] != other[i])return false;
		return true;
	}
	bool opEquals(S : T)(S[] other)
	{
		if(this.length != other.length)return false;
		foreach(i; 0..this.length)if(this[i] != other[i])return false;
		return true;
	}
	string toString() const
	{
		auto xs = frontData[clamp(-endIdx, 0, frontSize) .. clamp(-beginIdx, 0, frontSize)];
		auto ys = backData[clamp(beginIdx, 0, backSize) .. clamp(endIdx, 0, backSize)];
		return "Deque(%s)".format(xs.retro.map!(to!T).array ~ ys);
	}
private:
	this(T[] frontData, T[] backData, size_t frontSize, size_t backSize, ptrdiff_t beginIdx, ptrdiff_t endIdx,
		bool shouldDuplicate)
	{
		this.frontSize = frontSize;
		this.backSize = backSize;
		this.frontData = shouldDuplicate ? frontData.dup : frontData[0 .. clamp(-beginIdx, 0, $)];
		this.backData = shouldDuplicate ? backData.dup : backData[0 .. clamp(endIdx, 0, $)];
		this.beginIdx = beginIdx;
		this.endIdx = endIdx;
	}
	void resizeFront() { frontData.length = max(frontSize * 2, 1); }
	void resizeBack() { backData.length = max(backSize * 2, 1); }
	invariant
	{
		assert(frontSize <= frontData.length);
		assert(backSize <= backData.length);
		assert(max(0, -beginIdx) == cast(ptrdiff_t)(frontSize));
		assert(beginIdx <= endIdx);
		assert(max(0, endIdx) == cast(ptrdiff_t)(backSize));
	}
}
@safe pure unittest
{
	import std.range;
	assert(isInputRange!(Deque!long));
	assert(isForwardRange!(Deque!long));
	assert(isBidirectionalRange!(Deque!long));
	assert(isRandomAccessRange!(Deque!long));
}
@safe pure unittest
{
	Deque!long xs = [1, 2, 3];
	assert(xs.length == 3);
	assert(xs.front == 1 && xs.back == 3);
	assert(xs[0] == 1 && xs[1] == 2 && xs[2] == 3);
	assert(xs == [1, 2, 3]);
	size_t i = 0;
	foreach(x; xs)assert(x == ++i);
	xs.front = 4;
	xs[1] = 5;
	xs.back = 6;
	assert(xs == [4, 5, 6]);
	xs.removeBack;
	xs.removeBack;
	assert(xs == [4]);
	xs.insertFront(3);
	xs.insertFront(2);
	xs.insertFront(1);
	assert(xs == [1, 2, 3, 4]);
	xs.insertBack(5);
	xs ~= 6;
	assert(xs == [1, 2, 3, 4, 5, 6]);
	xs.removeFront;
	assert(xs == [2, 3, 4, 5, 6]);
	xs.clear;
	assert(xs.empty);
	xs.insertBack(1);
	assert(!xs.empty);
	assert(xs == [1]);
	xs[0]++;
	assert(xs == [2]);
}
@safe pure unittest
{
	Deque!long xs = [1, 2, 3];
	assert(xs[] == [1, 2, 3]);
	assert((xs[0 .. 2] = 0) == [0, 0, 3]);
	assert((xs[0 .. 2] += 1) == [1, 1, 3]);
	assert((xs[] -= 2) == [-1, -1, 1]);
	Deque!long ys = xs[0 .. 2];
	assert(ys == [-1, -1]);
	ys[0] = 5;
	assert(ys == [5, -1]);
	assert(xs == [5, -1, 1]);
}
@safe pure unittest
{
	import std.algorithm, std.array;
	Deque!long xs = [10, 5, 8, 3];
	assert(sort!"a < b"(xs).equal([3, 5, 8, 10]));
	assert(xs == [3, 5, 8, 10]);
	Deque!long ys = sort!"a > b"(xs).array;
	assert(ys == [10, 8, 5, 3]);
}
@safe pure unittest
{
	int[] xs = [1, 2, 3];
	Deque!int ys = [1, 2, 3];
	Deque!long zs = [1, 2, 3];
	assert(xs == ys);
	assert(xs == zs);
	assert(ys == zs);
	ys.removeFront;
	assert(ys != zs);
	ys.insertFront(1);
	assert(ys == zs);
}