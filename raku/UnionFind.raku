# initialize
my $n = 1000000;
my @a[$n];
for 0..$n-1 -> $i { @a[$i] = -1; }

sub root(Int $x) {
	@a[$x] < 0 ?? $x !! (@a[$x] = root(@a[$x]));
}

sub merge(Int $x, Int $y) {
	my $rx = root($x);
	my $ry = root($y);
	return if $rx == $ry;
	($rx, $ry) = ($ry, $rx) if @a[$rx] > @a[$ry];
	@a[$rx] += @a[$ry];
	@a[$ry] = $rx;
}

sub same(Int $x, Int $y) {
	root($x) == root($y);
}