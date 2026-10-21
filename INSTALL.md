# Installation

## Requirements

- Python 3.11 or newer (no packages needed).
- A dump of the Korean ROM, SHA-1 `1fffd601d3439e37cd934e72d08e487a93fc449b`.
- The Metrowerks CodeWarrior for DS compiler (`mwccarm`), which is not distributed here.
  Put it under `tools/mwccarm/` so that `tools/mwccarm/1.2/base/mwccarm.exe` exists, or set
  `MWCC_ROOT`. A few library functions also need the `1.2/sp2` and `1.2/sp2p3` drops. On
  Linux and macOS, install [wibo](https://github.com/decompals/wibo) and set
  `MWCC_WRAPPER=wibo`.
- [ds-decomp](https://github.com/AetiasHax/ds-decomp) `dsd` v0.12.1 for the whole-program
  link: put the release binary at `build/tools/dsd` (`dsd.exe` on Windows) or set `DSD`.

## Setting up from your ROM

```sh
python tools/setup.py path/to/game.nds     # ROM check, extract, PC build, self-test
python tools/setup.py --check              # the self-test again
python tools/setup.py game.nds --matching  # also tools/verify.py and tools/link.py (mwccarm)
```

The self-test plays `runtime/recordings/title-start.txt` and `new-game.txt` in the interpreter,
with every matching source compiled for the PC and with every Clean rewrite, and compares the
frames with the expected ones (`--quick`: the title recording only). Only the matching check
needs mwccarm and dsd. A wrong file is named for what it is: not a DS ROM, a damaged header,
another region (ADME, ADMJ, ADMP, ...), another revision, or a bad dump of this one.

## Building

```sh
cp /path/to/game.nds extract/
python tools/extract.py      # checks the SHA-1 and splits the ARM9 modules into build/
python tools/verify.py       # compiles everything and checks it against the ROM
python tools/link.py         # links the program with the original linker, compares modules
```

Objects are cached, so later runs only recompile what changed. To check part of the tree, pass
paths: `python tools/verify.py src/ov003 src/main`.

Other tools:

- `tools/lint.py`: checks that need neither the ROM nor the compiler; CI runs it.
- `tools/report.py`: writes a progress report in objdiff's report format.
- `tools/quality.py`: lists sources that still need cleaning up.
- `tools/rename_symbol.py`: renames a symbol in the table and every source.
