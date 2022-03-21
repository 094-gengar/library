import sequtils, algorithm, math, tables, sets, strutils, times

proc getchar(): char {.importcpp: "getchar_unlocked", header: "<cstdio>", discardable.}
proc scanf(formatstr: cstring) {.header: "<cstdio>", varargs.}
proc printf(formatstr: cstring) {.header: "<cstdio>", varargs.}

proc scan(): int = scanf("%d", addr result)
proc input(): string = stdin.readLine

{.emit: """/*TYPESECTION*/

""".}

proc solve(): void {.importcpp: "solve(@)", nodecl.}

solve()