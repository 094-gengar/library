import sequtils

type
  dsu = tuple[
    n: int,
    a: seq[int]]

proc init(uf: ref dsu, siz: int): void =
  uf.n = siz
  uf.a = newSeqWith[int](uf.n, -1)

proc root(uf: ref dsu, x: int): int = 
  assert(x < uf.n)
  result = if uf.a[x] < 0: x else: uf.a[x] = uf.root(uf.a[x]); uf.a[x]

proc merge(uf: ref dsu, x: int, y: int): void = 
  assert(x < uf.n)
  assert(y < uf.n)
  var rx = uf.root(x)
  var ry = uf.root(y)
  if rx == ry: return
  if uf.a[rx] > uf.a[ry]: swap(rx, ry)
  uf.a[rx] += uf.a[ry]
  uf.a[ry] = rx

proc same(uf: ref dsu, x: int, y: int): bool = uf.root(x) == uf.root(y)

proc size(uf: ref dsu, x: int): int = 
  assert(x < uf.n)
  return -uf.a[uf.root(x)]
