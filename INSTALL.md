# Installation

## Requirements

- Python 3.11 or newer (no packages needed).
- A dump of the Korean ROM, SHA-1 `1fffd601d3439e37cd934e72d08e487a93fc449b`.
- The Metrowerks CodeWarrior for DS compiler (`mwccarm`), which is not distributed here.
  Put it under `tools/mwccarm/` so that `tools/mwccarm/1.2/base/mwccarm.exe` exists, or set
  `MWCC_ROOT`. A few library functions also need the `1.2/sp2` and `1.2/sp2p3` drops. On
  Linux and macOS, install [wibo](https://github.com/decompals/wibo) and set
  `MWCC_WRAPPER=wibo`.

## Building

```sh
cp /path/to/game.nds extract/
python tools/extract.py      # checks the SHA-1 and splits the ARM9 modules into build/
python tools/verify.py       # compiles everything and checks it against the ROM
python tools/relink.py       # rebuilds each module and compares SHA-1s
```

Objects are cached, so later runs only recompile what changed. To check part of the tree, pass
paths: `python tools/verify.py src/ov003 src/main`.

Other tools:

- `tools/lint.py`: checks that need neither the ROM nor the compiler; CI runs it.
- `tools/report.py`: writes the objdiff-format progress report that decomp.dev reads.
- `tools/quality.py`: lists sources that still need cleaning up.
- `tools/rename_symbol.py`: renames a symbol in the table and every source.
