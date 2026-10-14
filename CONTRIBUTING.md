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

The symbol table (`config/adm-kr/arm9/<module>/symbols.txt`) names each function the way its
source emits it: the plain name for C, the mangled name for C++, exactly as mwcc mangles it
(copy it from the compiled object, never write it by hand):

```
_ZN18Obj_ov128_0229cbc019func_ov128_0229c700Ev kind:function(thumb,size=0x24) addr:0x0229c700
```

A source that defines a member function says which symbol it emits on the third header line:
` * compiler-emitted symbol: <mangled name>`. Every use of a function must use that same name.
`config/adm-kr/arm9/aliases.txt` lists the names some sources still use instead (mostly C++
names, from vtables, of functions still defined in C); those sources cannot be linked yet, and
the list only shrinks.

## Fake matches

If the only matching source needs something nobody would write on purpose, say so in one line
after the header:

```c
/* FAKEMATCH: the redundant mask keeps r1 live across the call */
```

Replacing a `FAKEMATCH` with a natural source that still verifies is always welcome;
`python tools/quality.py` lists the files that need the most work.

## Clean code

`clean/` holds readable versions of game functions (see [docs/runtime.md](docs/runtime.md)).
A Clean function has the same interface as the original (the same parameters and result, so
the runtime can call either), and the same behaviour by the contract in docs/runtime.md; its
body, names and types are free.

- Group functions by subsystem, one file per subsystem: `clean/<module>/<subsystem>.c` with a
  header beside it. Say above each function which game function it is (`/* func_0209dcdc */`).
- Name things by what the code shows they do. When the purpose is not known, keep the name
  neutral (`Calendar_PeriodA`) rather than guessing.
- Keep the game's odd behaviour and mark it: `QUIRK:` for something unusual but intended,
  `BUG:` for a defect kept as it is, `HW:` for an order the hardware needs, `REQUIRES:` for a
  precondition the game always meets.
- Read the game's data by its symbol (`extern const u16 data_020d1b04[19];`); the build places
  it at its DS address.
- Every Clean function needs a check in `tests/clean/<module>/<subsystem>.c`:
  `DIFF_CHECK(<symbol>, "<module>", <address> | <1 for Thumb>, <result bits>, <follow calls>,
  <generator>, <caller>)`. The generator writes entry states the game can produce (valid dates,
  real object layouts), not arbitrary bytes. `python tools/diffcheck.py` must pass.
