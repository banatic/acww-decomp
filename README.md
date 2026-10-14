Animal Crossing: Wild World (Korea)
===================================

[![Build Status]][actions]

[Build Status]: https://github.com/banatic/acww-decomp/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/banatic/acww-decomp/actions/workflows/build.yml

A decompilation of the ARM9 code of *Animal Crossing: Wild World*, Korean release (`ADMK`).
It does not contain any game assets, code or disassembly; you need your own copy of the game
to build it.

> [!IMPORTANT]
> **This repository contains the game's own code only.** The libraries the game links
> against (NitroSDK, NitroSystem, NitroDWC, NitroWiFi, the GameSpy SDK, the Metrowerks C
> library and runtime: 4,083 functions, about 590 KB) are not included. Library versions are
> listed in [libs/README.md](libs/README.md).

## Status

Each of the 25,247 game functions has a C or C++ source that compiles with the original
compiler to the ROM's exact bytes, and whose calls and pointers resolve to the ROM's targets.
The sources are still one file per function, and the data sections still come from the ROM.
Work in progress: linking the whole program with the original linker, and regrouping the
functions into their original source files. [docs/verification.md](docs/verification.md)
describes what is checked and what is not yet.

The target ROM:

- `ADMK` (Korea), SHA-1 `1fffd601d3439e37cd934e72d08e487a93fc449b`

Setup instructions are in [INSTALL.md](INSTALL.md) and contribution guidelines in
[CONTRIBUTING.md](CONTRIBUTING.md).

Thanks to [ds-decomp](https://github.com/AetiasHax/ds-decomp),
[objdiff](https://github.com/encounter/objdiff), and the
[zeldaret](https://github.com/zeldaret), [pret](https://github.com/pret) and
[ACreTeam](https://github.com/ACreTeam/ac-decomp) projects.

Released under [CC0 1.0](LICENSE). Not affiliated with Nintendo.
