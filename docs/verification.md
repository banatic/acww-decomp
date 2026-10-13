# Verification

`tools/verify.py` compiles every source and runs two checks against the ROM.

**BYTES.** The function compiles to the ROM's instructions, with the fields the linker fills in
(call offsets, absolute pointers) masked out. This is the usual matching criterion.

**LINK.** Every relocation in the object is resolved through the symbol table in `config/` and
must produce exactly what the ROM has at that site: each `bl` reaches the ROM's call target and
each pointer is the ROM's pointer. String literals and static data that the file defines are
compared with the ROM too. BYTES cannot see a call to the wrong function or a pointer to a
global that does not exist, because those are the masked fields; LINK can.

`tools/relink.py` places the compiled functions at their addresses, applies relocations the way
the linker does, and compares the SHA-1 of each module image with the ROM's. Data sections are
not decompiled yet, so bytes outside functions are copied from the ROM; the report says how much
of each module came from sources.

A file passes when both checks pass. A match that needs a construct no one would write on
purpose (a redundant mask, a dead branch) carries a `FAKEMATCH` comment explaining it.

## Status (2026-10-13)

| | Game code (`src/`) | With the libraries |
|---|---:|---:|
| Functions | 25,247 | 29,330 |
| BYTES | 25,247 | 29,330 |
| LINK | 25,247 | 29,330 |
| `FAKEMATCH` | 17 | |

With the libraries present, all 153 module images relink to the ROM's SHA-1. Without them
(this repository), library functions are taken from the ROM and counted as not decompiled.

Not covered yet: the ARM7 binary, the data sections, a rebuild with the original linker, and
pointers into `.bss` (nothing to compare). Most names are still placeholders.
