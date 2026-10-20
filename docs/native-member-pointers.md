# Native member-pointer boundary

runtime/native_member.h and tools/native_pmf.py translate only audited PC source
copies. Shared game memory retains the ROM encoding. Unsupported construction,
passing and return forms remain Reference until their boundaries are audited.

## Verified representation

The ROM implementation of func_ov049_02262a94 indexes data_ov049_02263640 with
idx << 4. It reads the callable word at offset 0 and the adjustment word at
offset 4. The latter is arithmetic-shifted right once to adjust this, and its
low bit selects a virtual lookup. Two further words belong to the table entry,
not the member pointer. This case needs an encoding conversion, not a conversion
from an assumed 12-byte member pointer to an 8-byte one.

NativeMember is a trivial two-word aggregate. Its bound call applies the signed
this adjustment, reads a virtual target at the ROM's byte offset when requested,
and calls the DS address through the existing Native fault dispatcher. A direct
Thumb target keeps bit zero. No host member-pointer encoding enters shared RAM.
The audited ROM null checks test the callable word alone; the helper does too.
Raw assignment, including assignment from __ptmf_null, preserves both words.

## Audited copies

Each source digest and exact declaration is checked before translation. The
copied types assert size, alignment and trivial copying. These initial cases
also check their surrounding fields and table stride:

| Source | ROM evidence | Layout checked in the PC copy |
|---|---|---|
| func_ov049_02262a94 | 02262a9e scales the index by 16; 02262aa2/02262aa8 load the two words; 02262aaa shifts the adjustment and 02262aae tests its low bit; 02262abc calls the result | PMFEntry stride 16, padding begins at 8 |
| func_02013518 | 0201351c loads the table at self+0x28; 02013522/02013528 load the words; 0201352a shifts the adjustment and 02013530 tests the low bit; 0201353e calls with the existing r1 argument | PMF size 8, object field at 0x28 |
| func_0201cfe4 | 0201d020 and 0201d054 test callbacks at 0xc0 and 0xc8; both calls decode the signed adjustment and virtual bit; 0201d07c through 0201d08a copy two words from __ptmf_null | PMF size 8, callbacks at 0xc0/0xc8, trailing flag at 0x15a |

runtime/native-member-sources.txt adds 186 source-digest-guarded copies. Each has
one member type, one member call, no inherited class or local member-pointer
construction, and a ROM body of at most 0x80 bytes. The ROM audit found one signed
adjustment shift and one indirect BLX per body. Opcode-count checks are regression
guards, not substitutes for the pointer's dataflow audit.

Five entries also declare and assign __ptmf_null: ov046/02261590, ov051/02260f94,
ov070/0227986c, ov073/02278f98 and ov076/02278fa8. Their field and external null
declarations use the same NativeMember type. A mismatched null type or another
external member-pointer variable is rejected.

The 189 compiled copies do not imply 189 newly enabled functions. Independent
Reference reasons, such as an argument-count mismatch, remain in force.

## ROM tables and constants declared extern

The link edits write a block-scope static table as mwccarm lowers it: the source
declares the ROM's guard word and table extern at their DS addresses and fills the
table under the guard; a `&Class::method` constant becomes the ROM's named 8-byte
datum. The PC copy then reads and writes the ROM's own table, so Native and the
interpreted body share one table and one guard, as two ROM callers would.

runtime/native-member-boundary.json pins such a source with two more fields, which
tools/native_pmf_boundary.py checks against the ROM before translating:

- `rom_tables`: per table, its address, entry count, guard, and the body's literal
  pool words naming both (`table_literal`, `guard_literal`); the source must declare
  the table extern with that count and the guard as an extern int.
- `rom_constants`: per constant, the two ROM words (callable, adjustment). Each was
  checked against the ROM's data relocation, which names the target function, and
  its Thumb bit against that function's symbol; where the relocation allows several
  overlays at one address, every one must have a function there.

Where an edit replaced an audited `&Class::method` constant, the replacing datum is
at the constant's audited literal address and holds the same words (0206ac64,
0206d26c, ov068 02274358, ov122 022a2110, ov138 0229d27c). Several ROM tables run
into data the ROM names separately: 02013c34's three entries at 021c1574 overlap an
object __sinit_020c4270 registers at 021c157c. The ROM's index bound reads there;
the PC copy, which uses the same addresses, does too.

Fourteen sources declare the guard (and, in thirteen, the table) as block-scope statics left
uninitialized, and fill the table under the guard as the ROM's code does. `rom_statics` pins
each one's DS address and the body's literal naming it; the PC copy refers to that storage
instead of a static of its own. The ROM keeps them in the overlay's .bss, which loading the
overlay again clears, so the table is filled again: a private guard stayed set while the
DS table was cleared, and the insect list's func_ov115_0229e6b4 called a null member.

`pmf = 0` in func_0201c8fc stores both zero words: ROM 0201c912-0201c91c copies
__ptmf_null (zero in .bss). NativeMember's assignment from a null constant does
the same.

Seven audited functions stay Reference (runtime/native-reference.txt): 0203637c,
02039f98, 02057d90, 02058634, 0205927c, 020aad9c and 020b8b88. Their Clean versions
call the handlers directly and do not write the ROM's guard and table, which a
`--clean` run compares (the title and new-game runs reach the first two and the last).

Three keyed tables (ov049 02261848, ov051 022604a8, ov068 02274358) now write the
ROM's keys in the source. keyed_copy accepts them only when they equal the pinned
ROM keys (the zero placeholders of the earlier sources are still substituted).

## Validation and remaining forms

tools/test_native_pmf.py compiles all 189 exact copies and the 345 boundary copies, and
rejects changed source digests. tests/native/member_pointer.cpp checks the generic boundary's direct and
virtual calls, signed adjustments, null tests, raw copying and Thumb-bit retention.
tests/native/member_null.cpp executes the five actual null-assignment copies,
checking their fields, callbacks and clearing assignments. Full Windows and Linux
recording, scene and differential gates remain required for the linked build.

Function-local tables initialized with &Class::method, member pointers passed as
parameters or returned by value, arbitrary casts, pointer arithmetic and inherited
virtual adjustments require separate audits of construction and both sides of
the boundary. They are not enabled by recognizing member-pointer syntax alone.
