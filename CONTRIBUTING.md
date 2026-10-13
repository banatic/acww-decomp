# Contributing

Every ARM9 function already has a matching source. Most of the remaining work is naming,
typing and making the code read like code someone wrote.

## Checking your change

Run `python tools/verify.py <files>` and make sure every file you touched is `ok`. Both checks
in [docs/verification.md](docs/verification.md) have to pass; paste the summary line into the
pull request. Run `python tools/lint.py` as well (CI runs it).

## Source files

Each function lives in `src/<module>/<symbol>.c` (`.cpp` where only C++ reproduces the code).
Library code is not part of this repository (see [libs/README.md](libs/README.md)).
The first comment is read by the tools, so keep its format:

```c
/* func_0207e16c @ 0x0207e16c, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */
```

- Format with clang-format 22.1.8 (`pip install clang-format==22.1.8`) and the repository's
  `.clang-format`; CI checks it. `pre-commit install` runs it on every commit.
- Use the types in `include/types.h` rather than declaring your own.
- Unknown struct fields are `unk_XX` (XX = offset in hex), padding is `pad_XX`.
- Callees and globals use the names in `config/adm-kr/arm9/**/symbols.txt`. To name something,
  run `python tools/rename_symbol.py <module> <address> <old> <new>`, which updates the table,
  every use and the file name together.
- Declare RAM symbols `extern` instead of writing their addresses as numbers. Hardware
  registers (`0x04xxxxxx`) as numbers are fine.
- Keep comments short and about why. English only; game text goes in as byte escapes
  (`"\xb0\xa1"`).

## C++

Much of the game is C++. Classes without a known name are named after their vtable, like
functions: `Obj_<address>` in main and the autoloads, `Obj_ov<NNN>_<address>` in overlays
(`Base_...` for bases without a vtable of their own). Each class is declared once, in
`include/cpp/<module>/<Class>.h`. Member functions keep the name of the function they are:
`Obj_ov128_0229cbc0::func_ov128_0229c700()`.

The symbol table names functions in C. The C++ name of a function or vtable goes in
`config/adm-kr/arm9/<module>/cpp.txt`, one row per name, exactly as mwcc mangles it (copy it
from the compiled object, never write it by hand):

```
_ZN18Obj_ov128_0229cbc019func_ov128_0229c700Ev kind:function(thumb) addr:0x0229c700
```

A source that defines a member function says which symbol it emits on the third header line:
` * compiler-emitted symbol: <mangled name>`.

## Fake matches

If the only matching source needs something nobody would write on purpose, say so in one line
after the header:

```c
/* FAKEMATCH: the redundant mask keeps r1 live across the call */
```

Replacing a `FAKEMATCH` with a natural source that still verifies is always welcome;
`python tools/quality.py` lists the files that need the most work.
