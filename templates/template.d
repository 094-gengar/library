void main()
{
	
}

import std.conv, std.functional, std.range, std.stdio, std.string;
	import std.algorithm, std.array, std.bigint, std.bitmanip, std.complex,
std.container, std.math, std.mathspecial, std.numeric, std.regex, std.typecons;
import core.bitop, core.stdc.stdlib;
class EOFException : Throwable { this() { super("EOF"); } }
string[] _tokens;
string readToken()
{
	for(; _tokens.empty;) { if(stdin.eof) { throw new EOFException; } _tokens = readln.split; }
	auto token = _tokens.front; _tokens.popFront;
	return token;
}
int readInt() { return readToken.to!int; }
long readLong() { return readToken.to!long; }
real readReal() { return readToken.to!real; }
struct PII { int x, y; }
struct PLL { long x, y; }
bool chmin(T)(ref T t, in T f) { if(t > f) { t = f; return true; } else { return false; } }
bool chmax(T)(ref T t, in T f) { if(t < f) { t = f; return true; } else { return false; } }
int binarySearch(alias pred, T)(in T[] as)
{
	int l = -1, h = cast(int)(as.length);
	while(h - l > 1) { const mid = (l + h) / 2; (unaryFun!pred(as[mid]) ? h : l) = mid; }
	return h;
}
int lowerBound(T)(in T[] as, T val) { return as.binarySearch!(a => (a >= val)); }
int upperBound(T)(in T[] as, T val) { return as.binarySearch!(a => (a > val)); }
const INF = 0x1fffffffffffffff;
const MOD = 1000_000_007;
const MOD2 = 998_244_353;