Animal Crossing: Wild World (Korea)
===================================

[![Build Status]][actions]

[Build Status]: https://github.com/banatic/acww-decomp/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/banatic/acww-decomp/actions/workflows/build.yml

A decompilation of the ARM9 code of *Animal Crossing: Wild World*, Korean release (`ADMK`).
It does not contain any game assets, code or disassembly; you need your own copy of the game
to build it.

![The game running on a PC from this repository](https://raw.githubusercontent.com/banatic/acww-decomp/media/screens.webp)

*The runtime playing the game's own code from recorded input (`tools/run.py`): the title, the
taxi, the name keyboard, arriving in town, fishing, shaking a tree, catching an insect, digging,
K.K. on a Saturday night and the observatory.*

> [!IMPORTANT]
> **This repository contains the game's own code only.** The libraries the game links
> against (NitroSDK, NitroSystem, NitroDWC, NitroWiFi, the GameSpy SDK, the Metrowerks C
> library and runtime: 4,083 functions, about 590 KB) are not included. Library versions are
> listed in [libs/README.md](libs/README.md).

## Status

![Decompilation progress](https://raw.githubusercontent.com/banatic/acww-decomp/progress/progress-decomp.svg)

*Decompilation: blue is Matching, green is Linked.*

![Clean code progress](https://raw.githubusercontent.com/banatic/acww-decomp/progress/progress-clean.svg)

*Clean code: gold is checked by function, purple is checked in a run, grey is read only.*

CI draws both maps from each build of `main` (`tools/progress_map.py`). Each function counts at
the highest level it has reached:

- **Matching**: a C or C++ source that compiles with the original compiler (mwccarm) to the
  ROM's exact bytes, and whose calls and pointers resolve to the ROM's targets.
- **Linked**: Matching, and the whole program, linked with the original linker, also reproduces
  the module byte for byte.
- **Checked by function**: the Clean version (a readable rewrite) agrees with the ROM's code on
  generated inputs; this covers the functions that call nothing.
- **Checked in a run**: the Clean version ran in a recorded play run whose frames and memory
  match the ROM's code.
- **Read only**: the Clean version has been checked only by reading it against its matching
  source.

All 25,251 game functions have a matching source and a Clean version, and the whole program,
linked with the original linker, reproduces every module of the ROM. The sources are still one
file per function, and the data sections still come from the ROM; regrouping the functions into
their original source files is in progress. [docs/verification.md](docs/verification.md)
describes what is checked and what is not yet.

## Quick start: your own ROM

You need your own dump of the Korean cartridge, Python 3.11+ and a 32-bit C compiler (on
Windows: LLVM's clang and the Visual Studio Build Tools; [INSTALL.md](INSTALL.md)). Then:

```sh
python tools/setup.py path/to/your-game.nds          # check the ROM, build, self-test
python tools/play.py                                 # play (Windows)
```

`setup.py` checks the dump (header, region, SHA-1; a trimmed dump is padded back), extracts it
under `extract/` and `build/`, builds the PC program, and plays two recordings with the ROM's
code, the matching sources and the Clean rewrites to show this machine gives the project's
frames bit for bit. The ROM is only read; nothing taken from it leaves your machine. Matching
the original compiler's output (`--matching`) also needs mwccarm (INSTALL.md).

## Running the game from its sources

The game also runs on a PC from this repository, with each function as the ROM's code in an
interpreter (Reference), as its matching source compiled for the PC (Native), or as its Clean
version. Runs are compared with the Reference frame by frame. See
[docs/runtime.md](docs/runtime.md). `python tools/play.py` builds it with a window, live input and
the save written back, to play (Windows; [docs/play.md](docs/play.md)).

The target ROM:

- `ADMK` (Korea), SHA-1 `1fffd601d3439e37cd934e72d08e487a93fc449b`

Setup instructions are in [INSTALL.md](INSTALL.md) and contribution guidelines in
[CONTRIBUTING.md](CONTRIBUTING.md).

Thanks to [ds-decomp](https://github.com/AetiasHax/ds-decomp),
[objdiff](https://github.com/encounter/objdiff), and the
[zeldaret](https://github.com/zeldaret), [pret](https://github.com/pret) and
[ACreTeam](https://github.com/ACreTeam/ac-decomp) projects.

Released under [CC0 1.0](LICENSE). Not affiliated with Nintendo.
