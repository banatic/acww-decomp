# Versions

The project started from one ROM, the Korean release (`ADMK`, revision 0). Animal Crossing: Wild
World was also released in North America (`ADME`), Europe (`ADMP`), Japan (`ADMJ`) and Australia
(`ADMU`), and those releases are to be added as **versions** of the same decompilation, the way
pokeemerald, sm64 and the Zelda decompilations cover several releases:

- There is **one source tree**. A function that is the same in every release has one source and
  one Clean version, used by all of them.
- Only what differs is split: a short difference inside a function by a version condition
  (`#ifdef VERSION_EU`), a function or file that exists in some releases only by a source that
  says which versions it belongs to.
- **Each version has its own configuration** (symbols, splits, relocations, ROM hash), its own
  build, its own Reference runs, recordings, scenes and expected frames, and is checked on its
  own exactly as the Korean ROM is checked today.
- **Clean does what the ROM of its version does.** A Clean function built for the European
  version behaves as the European ROM's code, and for the Korean version as the Korean ROM's.
  It never chooses a language, a text table or a keyboard of another release at run time, and
  never adds behaviour that no ROM has. Localization is the other releases themselves: the
  Spanish texts are whatever the European ROM holds and does with them.

This document describes the design. Phase 1 (done) made the version a setting of every tool;
the steps after it are listed under "Migration".

## The version setting

Each version has a short name: `adm-kr` today, and `adm-us`, `adm-eu`, `adm-jp`, `adm-au` as they
come (a later revision of a release gets a suffix: `adm-eu-r1`). Every tool works on one
version at a time, chosen by

```
python tools/<tool>.py --version adm-kr ...       # on any tool's command line
ACWW_VERSION=adm-kr python tools/<tool>.py ...    # or in the environment
```

and `adm-kr` when neither names one. `tools/versions.py` is the only place that turns the name
into paths; `tools/common.py` repeats them (`C.VERSION`, `C.CONFIG`, `C.BUILD`, `C.ROM`,
`C.RECORDINGS`) for the tools that import it. The `--version` option is taken off the command
line before the tool reads its own options, and the choice is put in `ACWW_VERSION`, so a tool
that starts others (`tools/gate.py`, `tools/scenes.py`, `tools/setup.py`) runs them on the same
version. A name without a `config/<name>/` is refused.

With the default every path is the one the tools used before there were versions, so every
output is the same as before, byte for byte: the build, the Reference cache's keys, the scenes'
frames, the `.sha1` files and the coverage lists. CI names its version once (`ACWW_VERSION` in
`.github/workflows/build.yml`).

## Layout per version

| | Path | Committed |
|---|---|---|
| ROM hash | `<version>.sha1` (`adm-kr.sha1`) | yes |
| ROM facts for `tools/setup.py` | `tools/versions.py`, `KNOWN` (game code, revision, used size) | yes |
| Symbols, splits, relocations | `config/<version>/arm9/` | yes |
| The ROM, checked copy | `extract/<version>.nds`, and `extract/<version>/` for ds-decomp | no |
| Build, Native objects, runs | `build/<version>/` | no |
| Recordings, expected frames, scenes, driven checks, coverage lists | `runtime/recordings/` for `adm-kr`; `runtime/recordings/<version>/` for the others | yes |
| Seed save for the scenes | outside the repository (`ACWW_SCENE_SEED`), one per version | never |

The Korean recordings stay where they are until the branches that change them have landed;
moving them to `runtime/recordings/adm-kr/` is then a rename that changes no file's content
(step 2 below). The shared object cache (`build/cache`) needs no split: its keys are the
contents that make an object, and the Reference cache's key holds the ROM's bytes.

## What depends on the version

The survey of phase 1. *Neutral*: the same for every version. *Per-version data*: a file or
table each version has its own copy of. *Per-version code*: code that is written for the Korean
ROM and needs a version condition, a per-version file, or a lookup by name.

| What | Where | Kind | State |
|---|---|---|---|
| Config, build, ROM and SHA-1 paths | `tools/common.py`, `extract.py`, `setup.py`, `run.py`, `link.py`, `gate.py` | per-version data | through `tools/versions.py` |
| Recordings directory | `scenes.py`, `driven.py`, `coverage.py`, `drive.py`, `progress_map.py`, `affected.py`, `gate.py`, `setup.py` | per-version data | through `C.RECORDINGS` |
| CI paths, artifact name | `.github/workflows/build.yml` | per-version data | `ACWW_VERSION` |
| ROM check (game code, revision, trimmed size and SHA-1) | `tools/setup.py` | per-version data | `KNOWN` in `tools/versions.py` |
| `config/adm-kr/arm9/config.yaml` | its `build/adm-kr`, `extract/adm-kr` paths | per-version data | correct as it is (each version's file names its own) |
| Symbol tables, relocs, delinks, aliases, absolute | `config/adm-kr/arm9/**` (29,339 functions) | per-version data | one copy per version, same names |
| Source headers: name, address, size, ISA, module, compiler | `src/`, `libs/` (5,940 sources) | per-version data inside shared files | the header is the Korean version's; see "Names and addresses" |
| Placeholder names `func_<address>` | 25,717 of the functions, file names, `CLEAN_AS` keys | neutral (an identifier) | the address is the Korean one; no tool reads an address out of a name |
| `CLEAN_AS(func_<address>, Name)` | `clean/` (25,251 registrations) | neutral by name | the address comes from the version's symbol table |
| Native tables keyed by function key (`module/name`) | `runtime/native-reference.txt`, `native-member-*`, `native-aggregate.json`, `tests/native/known.txt` | mostly neutral (properties of the source) | stay shared; a version that disagrees gets an entry of its own |
| Native tables holding ROM addresses or hashes | `runtime/native-private.txt`, `native-rom-statics.json`, `compiler-helpers.txt`, `library-arguments.txt`, `library-signatures.txt` | per-version data | move to a per-version home (step 4) |
| Hand tables of addresses in the Native tools | `tools/native_stack.py`, `native_abi.py`, `native_args.py`, `native_contract.py`, `native_publish.py`, ... | per-version data keyed by Korean address | key by name (step 4) |
| SDK and game addresses in the runtime | `runtime/run.c` (`SDK_AUTOLOAD_DONE`, thread info), `native_run.c` (thread list, worker job, HBlank stores), `wifi.c` (SSL shims), `wm.c`, `drive.c` | per-version code | a generated header from the version's symbols (step 3) |
| ARM7 high-level emulation | `runtime/arm7.c`, `sequencer.c`, `wm.c` (read from the Korean ARM7 binary) | per-version code, probably near neutral | check against each version's ARM7 |
| Firmware language | `runtime/boot.c` (language 7, Korean) | per-version data | from the version (Japanese 0, English 1, ...) |
| Addresses in tools | `tools/run.py` (`func_020404b4`), `driven.py` (`OS_SleepThread`, heap vtables), `common.py` (`LIBRARY_RANGES`) | per-version data | by name, or per version |
| Interpreter self-test | `runtime/tests/arm_test.c` (the ROM's own leaf functions at Korean addresses) | per-version code | runs on `build/<version>/rom`; Korean cases only for `adm-kr` |
| Scene saves and offsets | `tools/scenes.py` (`SEED_SHA256`, field offsets in the save) | per-version data | a table per version when a second version has scenes |
| Recordings and every `.sha1` | `runtime/recordings/**` | per-version data | never shared: each ROM records its own |
| Korean-only behaviour | Hangul keyboard (`ov095/soft_keyboard_hangul.c`), particles (`main/mail_particles.c`), voice by syllable (`autoload_2/voice.c`), ... | per-version code | the other versions have their own (kana, Latin) |
| Structure layouts, save layout | `include/`, `clean/*.h` | mostly neutral | text buffer sizes may differ; checked per version by the build |
| Interpreter, renderer, input, compiler wrappers, lint | `runtime/arm*.c`, `gpu*.c`, `tools/lint.py`, ... | neutral | |

## Names and addresses

A function's **name** is what ties the versions together. Each version's `symbols.txt` lists the
same names at that version's addresses:

```
config/adm-kr/arm9/autoload_2/symbols.txt:  Countdown_Tick16 kind:function(arm,size=0x18) addr:0x020e8840
config/adm-eu/arm9/autoload_2/symbols.txt:  Countdown_Tick16 kind:function(arm,size=0x18) addr:0x020e9a20
```

This is an illustration: the function is still called `func_020e8840`, and the European address
is made up. So the name -> address table of a version is its own symbol table, and nothing else is needed to
find a function in another release. A function that has no counterpart in a version is simply
not in that version's table; one that only that version has gets a name of its own there.

Most functions still have a placeholder name, `func_<address>` or `func_ov<NNN>_<address>`, made
from the Korean address. Those stay as they are: in another version's table `func_020e8840` is
just a name at that version's address. No tool reads an address out of a name (checked in phase
1), and the rule stays: an address always comes from the version's symbol table. The name audit
replaces placeholders with real names over time, and `tools/rename_symbol.py` renames in every
version's table at once.

Who is who across releases is found once, when a version is added, by a matching tool that pairs
each function of the new ROM with a Korean one (same instructions apart from relocated words,
same callers and callees), and writes the new `symbols.txt` with the Korean names. Pairs it is
unsure of are checked by hand; a function that does not pair keeps a placeholder made from its
own address (`func_020e9a20`, which cannot clash with a Korean placeholder at the same address,
since `tools/rename_symbol.py` refuses a taken name).

What uses the names:

- `CLEAN_AS(func_020e8840, Countdown_Tick16)` names the symbol; `tools/run.py` and
  `tools/diffcheck.py` look its address up in the current version's table. A Clean source whose
  symbol is not in the version is not registered for it.
- The source headers (`func_020e8840 @ 0x020e8840, 0x18 bytes, ARM, module autoload_2`) give the
  Korean version's address, size and module. For another version the tools take them from that
  version's symbol table by the name; the header's values are a convenience for readers and stay
  the Korean ones (step 5).
- Function keys (`autoload_2/func_020e8840`) in the runtime's tables are module and name; a module
  is the same overlay in every version unless a release renumbers its overlays (an open
  question below).

## Version-specific code

There are two ways to say that code belongs to some versions only.

**A version condition**, for a difference of a few lines inside a function. The build defines
exactly one of `VERSION_KR`, `VERSION_US`, `VERSION_EU`, `VERSION_JP`, `VERSION_AU`, for
mwccarm (`src/`) and for the PC compiler (Native and Clean) alike (an illustration):

```c
#ifdef VERSION_KR
    count = HangulParticle_Choose(text);
#else
    count = 0;
#endif
```

**A per-version source**, for a function or a file that one release has and another has not, or
that differs throughout. The source says which versions it belongs to in its header, and the
tools leave it out of every other version:

```c
/* soft_keyboard_hangul: 12 functions, module ov095
 * mwccarm 1.2/base -O4,s
 * versions: adm-kr
 * ...
 */
```

Without a `versions:` line a source is in every version. Clean files take the same line in their
first comment. When one function differs throughout, each version gets a source of its own with
the same name, and each lists the versions it is for: the tools refuse two sources of one name
for the same version.

The rule for Clean: **a Clean function does exactly what its version's ROM does.** A difference
between versions is written as the ROM has it, under the version condition, and is checked by
that version's Reference runs, scenes and driven calls. A Clean function never reads a setting to
choose between releases' behaviour while it runs. A language that the European ROM itself chooses
at run time (by the firmware's language) is chosen the same way in its Clean code, because the
ROM does that; a language that only another release has is not.

## Matching per version

`tools/verify.py` compiles each source with mwccarm and compares it with the version's ROM at the
address its symbol table gives, so a source can match in one version and not yet in another; the
progress map and report count each version separately. A shared source must match in every
version it belongs to; when the code differs, the difference goes in a version condition until
it matches in both.

The releases may have been built with a different compiler revision or different options for
some files. The source header keeps the compiler the Korean version needs, and a version that
needs another one says so in an extra header line of its own:

```c
 * mwccarm 1.2/base -O4,s
 * adm-jp: mwccarm 1.2/sp2 -O4,s
```

The SDK libraries (`libs/`) are likely the largest per-version difference (other SDK builds); a
library file that differs is a per-version source like any other.

`tools/link.py` links each version with its own `config/<version>/` into `build/<version>/`, and
`dsd check modules` compares the result with that version's ROM.

## Checks per version

Every check runs per version, on that version's ROM and recordings: the function-level check
(`tools/diffcheck.py`), the title and new-game recordings, the scenes and the driven checks, and
`tools/gate.py` (whose logs go to `build/<version>/gate/`). Each version records its own input
recordings and `.sha1` files; they are never shared, because the releases' timing and text
differ. A change to shared code runs the gate of every version that has a configuration; a
change inside one version's condition or file needs that version's gate only.

## Adding a version

The outline of the guide a contributor will follow:

1. Dump the cartridge and note its SHA-1; add `<version>.sha1` and the version's entry in
   `tools/versions.py` (`KNOWN`: game code, revision, used size and trimmed SHA-1).
2. `python tools/setup.py PATH.nds --version <version>` checks and extracts it to
   `extract/<version>.nds` and `build/<version>/rom/`.
3. Make `config/<version>/arm9/` with ds-decomp (`dsd init`), then run the matching tool to name
   its functions after the Korean ones; review the pairs it is unsure of.
4. `python tools/verify.py --version <version>`: the shared sources that match as they are, and
   the ones that need a version condition or a source of their own.
5. Record the title and new-game recordings for the version (`runtime/recordings/<version>/`) and
   their `.sha1` from the Reference run; then the Native and Clean runs must give the same.
6. Add the version's runtime addresses (they come from its symbol table once step 3 of the
   migration is done) and its firmware language, and a CI job for it.
7. Scenes come later, with a seed save of that release.

## Dumps known so far

| Version | Game code | Revision | SHA-1 | Used size | Trimmed SHA-1 | ARM9 size | Overlays |
|---|---|---|---|---|---|---|---|
| `adm-kr` | `ADMK` | 0 | `1fffd601d3439e37cd934e72d08e487a93fc449b` | `0x1f533c4` | `f987baf1db78b9b8c92a98877c62df71f9d049d3` | `0xcf31c` | 148 |
| USA | `ADME` | 1 | `77fde3e30e1e6068395d1f96ea63be569b61c351` | `0x1f98bfc` | `22bf1eac11590f3dcc85268846eaadf32a6a0ab9` | `0xcd448` | 148 |

Both are 32 MiB dumps padded with `0xff` after the used size. The USA dump is revision 1 (a
revision 0 exists as well). Both have 148 ARM9 overlays; whether the overlays hold the same
code under the same numbers is checked when the USA configuration is made.

## Migration

The order of the remaining steps. Each one keeps the Korean outputs as they are; none changes a
`.sha1`.

1. **The setting** (phase 1, done): `tools/versions.py`, every tool's paths, CI,
   `tools/rename_symbol.py` across versions, this document.
2. **Per-version homes for the Korean data**, after the in-flight scene and driven branches have
   landed: `runtime/recordings/` to `runtime/recordings/adm-kr/` (a rename; `C.RECORDINGS` then
   always names the version's directory).
3. **Runtime addresses by name**: `tools/run.py` writes `build/<version>/runtime/symbols.h` from
   the version's symbol table (`#define SYM_OSi_ThreadInfo 0x02204270u`, ...), and `runtime/run.c`,
   `native_run.c`, `wifi.c`, `wm.c` and `drive.c` use it instead of literal addresses; the same
   for the addresses in `tools/run.py`, `tools/driven.py` and `tools/common.py`.
4. **Native tables**: the hand tables in `tools/native_*.py` keyed by name instead of Korean
   address; the tables holding ROM ranges and hashes (`native-private.txt`,
   `native-rom-statics.json`, `compiler-helpers.txt`, `library-*.txt`) moved under a per-version
   directory.
5. **Addresses from the table**: the tools take a source's address, size and module from the
   version's symbol table by name rather than from its header (for `adm-kr` they are the same,
   which the lint checks).
6. **The version define** (`VERSION_KR`) on every compile, and the `versions:` header line read
   by `tools/common.py`. Adding the define changes every compile's key in the object cache once;
   the objects are the same.
7. **The second version**: its config, matching tool, recordings and CI job, as in "Adding a
   version".

## Open questions

- Which releases first, and is each one revision 0 (or are there later revisions to name)?
- Do the releases number their overlays the same? If not, a module name (`ov097`) in function
  keys and file paths is not shared, and keys need a per-version module map.
- The European cartridge: one ROM with several languages, or one ROM per language? Several
  ROMs would be several versions (`adm-eu-en`, `adm-eu-es`, ...).
- The macro names (`VERSION_KR` or `GAME_VERSION == VERSION_KR`) and the header line's form
  (`versions: adm-kr`) before any source uses them.
- Whether placeholder names should be renamed to a version-free form (`fn_<id>`) before the second
  version is added, or kept as Korean-address identifiers as proposed.
- Where the localization contributor's work goes: as the European version's Clean once that
  version's configuration and recordings exist.
