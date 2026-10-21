# Verification

`tools/verify.py` compiles every source and runs two checks against the ROM.

**BYTES.** The function compiles to the ROM's instructions, with the fields the linker fills in
(call offsets, absolute pointers) masked out. This is the usual matching criterion.

**LINK.** Every relocation in the object is resolved through the symbol table in `config/` and
must produce exactly what the ROM has at that site: each `bl` reaches the ROM's call target and
each pointer is the ROM's pointer. String literals and static data that the file defines are
compared with the ROM too. BYTES cannot see a call to the wrong function or a pointer to a
global that does not exist, because those are the masked fields; LINK can.

`tools/link.py` links the whole program with the original linker, mwldarm, the way the game was
built. Each source whose object can stand alone (its code, and any data it defines, have a
place in the ROM) is linked as its own translation unit; the rest of each module comes from
objects that [ds-decomp](https://github.com/AetiasHax/ds-decomp) cuts out of the ROM. dsd's
module check then compares every linked module with the ROM byte for byte. The tool lists why
each remaining source cannot be linked yet; most of those are functions that shared a source
file, and data, with their neighbours.

A file passes when both checks pass. A match that needs a construct no one would write on
purpose (a redundant mask, a dead branch) carries a `FAKEMATCH` comment explaining it.

## Status (2026-10-21)

| | Game code (`src/`) | With the libraries |
|---|---:|---:|
| Functions | 25,251 | 29,334 |
| BYTES | 25,251 | 29,334 |
| LINK | 25,251 | 29,334 |
| Linked with mwldarm, modules match the ROM | 25,251 | |
| `FAKEMATCH` | 17 | |

Not covered yet: regrouping functions into their original source files, the data sections
(most still come from the ROM through ds-decomp's objects), the ARM7 binary, and pointers into
`.bss` (nothing to compare). Most names are still placeholders.
