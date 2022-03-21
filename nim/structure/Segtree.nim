import bitops

type 
  Segtree = tuple[
      segfunc: proc(x: int, y: int): int,
      ide_ele: int,
      size: int,
      tree: seq[int]]

proc init(seg: ref Segtree, init_val: seq[int], segfunc: proc(x: int, y: int): int, ide_ele: int) =
  var n: int = len(init_val)
  seg.segfunc = segfunc
  seg.ide_ele = ide_ele
  seg.size = 1 shl (fastLog2(n-1) + 1)
  seg.tree = newSeq[int](2*seg.size)
  for i in 0..<2*seg.size: seg.tree[i] = seg.ide_ele
  for i in 0..<n:
    seg.tree[seg.size + i] = init_val[i]
  for i in countdown(seg.size-1, 0):
    seg.tree[i] = seg.segfunc(seg.tree[2*i], seg.tree[2*i+1])

proc update(seg: ref Segtree, k: int, x: int) = 
  var kps: int = k + seg.size
  seg.tree[kps] = x
  while kps > 1:
    seg.tree[kps shr 1] = seg.segfunc(seg.tree[kps], seg.tree[kps xor 1])
    kps = kps shr 1

proc query(seg: ref Segtree, l: int, r: int): int =
  result = seg.ide_ele
  var lps: int = l + seg.size
  var rps: int = r + seg.size
  while lps < rps:
    if (bitand(lps, 1)) != 0:
      result = seg.segfunc(result, seg.tree[lps])
      lps += 1
    if (bitand(rps, 1)) != 0:
      result = seg.segfunc(result, seg.tree[rps-1])
    lps = lps shr 1
    rps = rps shr 1


proc segfunc(x: int , y: int): int = x + y

let ide_ele: int = 0
