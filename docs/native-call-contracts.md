# Audited Native call words

Some member-pointer boundaries pass more ARM words than their source parameter
count suggests. `tools/native_contract.py` guards complete original source and
ROM bodies before adding a contract to the generated runtime policy.

| Entry | ARM words in order |
| --- | --- |
| `01ffd44c` | object pointer, a.function, a.adjustment, b.function, b.adjustment, c.function, c.adjustment |
| `02034e28` | object pointer, function, adjustment |
| `0202dbf0` | object pointer, Pair.first, Pair.second |
| `0207fc7c` | hidden output pointer, unused unsigned argument, category |

The last optional policy column contains a word count in bits 0 through 7 and
pointer roles in bits 8 through 23. Zero preserves the existing untyped policy.
The count must agree with the bridge's argument-word count and cannot exceed
16. Pointer bits outside that count, malformed optional fields, ambiguous
addresses and overlay contracts are rejected. The four audited addresses are
permanently resident and unambiguous.

Member target words, adjustments and other scalar words compare exactly,
including Thumb bits, negative adjustments and high-bit values. Only an
explicit pointer role can use a readable PC object instead of a mapped
Reference object. Null or different DS pointers do not receive that exemption.
This pointer comparison does not prove equality of pointed-to object contents;
the function/body and memory checks still have to establish that behavior.

Both call-in and call-out checks cover all contract words. Entry hashes also
include the stack words. An audited argument mismatch terminates the run,
instead of treating an integer's magnitude as evidence that it is a PC address.

## Trace attachments

Ordinary crossings retain their ten-word (40-byte) disk format. Only calls
whose audited argument count exceeds four add `CROSS_ARGUMENTS` records. Each
attachment has the following ten unsigned 32-bit words:

| Word | Meaning |
| --- | --- |
| 0 | Parent stream |
| 1 | `CROSS_ARGUMENTS` |
| 2 | Parent function, Thumb bit clear |
| 3 | One-based physical parent record index |
| 4 | Parent kind: call or call-out |
| 5 | First argument word index, starting at 4 |
| 6 | Number of payload words, from 1 through 3 |
| 7 through 9 | Argument values; unused payload must be zero |

Attachments immediately follow their parent in consecutive groups of three
words. Loading verifies the complete sequence before constructing stream lists.
Missing, duplicate, reordered, truncated, wrong-parent and wrong-stream records
are rejected. An intervening IRQ or another thread cannot satisfy an attachment.
Attachments are not independent crossings and do not advance hardware time.

`python tools/test_native_contract.py` checks the actual writer, loader,
comparator, call-in path and generated policy. It includes register/stack
mutations, the maximum bounded word count, malformed attachments and metadata,
and an explicit host-object pointer case on both supported platforms.

These descriptions are ARM contracts. They must not be substituted for a PC
structure-return convention: the output pointer, return registers and hidden
argument cleanup also require the corresponding ABI adapter and body tests.

## Remaining member-pointer copies

`native_pmf_boundary.checked_copy` validates 204 unchanged sources, their header
closures, their original ROM bodies, and 426 method constants pinned in
`runtime/native-member-boundary.json`. Each constant was independently resolved
by both host compilers and compared with a literal referenced by its ROM owner.
The declarations cover multiple member types, named parameters, inline parameters,
arrays and pointers to members. Shared header types are emitted as PC header
copies. Original files stay unchanged.

The returned header copies precede the original include directory and their
names and contents are part of the build cache key. `native.py` selects the
validated copies and connects the aggregate-return adapters below. Successful
standalone compilation does not establish game replay equivalence.

`func_02013948` calls a member returning an eight-byte `Pair`. Its ARM instruction
at `0201398c` supplies the hidden output pointer in r0; adjusted `this`, the
explicit pointer and the incoming stack argument occupy r1-r3. A source-specific
`NativeMemberCall` specialization emits exactly that explicit output-pointer
call. The host compiler handles the local C++ return to the caller. No DS call
uses the host's aggregate-return convention. Other aggregate results are rejected
by the default template until they have their own audited adapter.

`python tools/test_native_pmf_boundary.py` validates the full pinned input set,
rejects changed sources, headers, ROM bodies and constants, and compares the
actual ARM Pair caller with its PC copy in 4,320 cases on each platform. The
fixture checks full surrounding object memory and call order, all seven table
targets, ARM/Thumb targets, signed adjustments, null and virtual calls, invalid
indices, the fifth input argument and signed output fields. Callback bodies are
controlled; this test is not a replacement for the full game gate.

The same test compares `func_0201f40c` with its PC copy in 512 cases. At ARM
instruction `0201f45e`, r0 retains `p->unk_12C` for `func_020819bc`; the matching
source omits this argument from its declaration and call. The guarded PC copy
makes that argument explicit. The test uses both actual flag-reader bodies and
checks early return, all table-selection branches, callback dispatch, the fifth
cleanup argument, full object memory and call order. Only this exact repaired
call is exempted from the short-declaration keep rule.

Two owners initialize local arrays that separate ROM pointer tables reference:
`ov054/func_ov054_022608ac.cpp` and `ov147/func_ov147_0229942c.cpp`. The PC compiler
otherwise discards these unused local arrays' writes, leaving their DS storage
uninitialized. Their nine table addresses, guard words and external aliases are
pinned in the manifest and checked against original ROM literals. The PC copies
write the shared DS storage and preserve each guard word's other bits. Clearing
the guard, including on an overlay reload, permits initialization again.

`python tools/test_native_member_shared.py` compares both actual ARM owners with
their PC copies: 720 cases for ov054 and 1,128 for ov147 on each platform. It
checks all nine tables, mixed initialized/uninitialized guards, high guard bits,
repeated initialization, object memory and callback order. The `--baseline`
mode verifies that the former copies fail the shared-storage comparison.

Three local dispatch tables have zero key placeholders in their matching
sources, although the ROM initializes those words to nonzero keys: ov049
`02261848`, ov051 `022604a8`, and ov068 `02274358`. Their function bodies only
initialize the member-pointer fields. A guarded PC copy supplies the original
ROM keys, with the complete table bytes, owner literal, row count and layout
pinned in `keyed_tables`. The original sources remain unchanged. The copy
asserts a 12-byte row and a member field at offset four.

`python tools/test_native_member_keyed.py` compares all three actual ARM owners
with their PC copies in 2,048 cases each. It covers every byte-sized mode,
signed callback arguments, callbacks that change the mode and cause subsequent
rows to execute, object memory, and callback order. The original zero-key
copies must fail the same fixture. These tests supplement the full game gate.

The state table owned by `ov147/func_ov147_0229a634.cpp` has no external ROM
alias, but its initialized DS bytes survive after another overlay replaces its
owner. Keeping only a PC copy leaves four RAM words different during new-game.
Its `retained_storage` entry pins the original table and guard literals; the
same guarded DS copy preserves those writes, without changing RAM comparison.
The shared-storage fixture also compares this actual owner in 432 cases per
host, with every state, guard bits, repeated resets, full storage/object memory,
callback targets and order. The former private copy must fail the comparison.

## Clean entry visibility

Object-level entry renaming happens after optimization. On Windows, Clang can
already have omitted an argument to a visible Clean callee that does not use
it. The entry hook then observes unrelated stack data, and a redirected call
cannot recover the original argument. This affected the fog reset/apply call.

`native_clean_profile.source_copy` separates registered definitions from their
public declarations before compiling a PC copy. Calls and function pointers
keep the public names, while definitions use the existing `native_body_` names.
The compiler sees each public callee as external, so runtime entry wrappers can
observe or redirect the complete call. Original Clean files are unchanged.

`python tools/test_native_clean_arguments.py` checks 4,096 optimized calls on
each host, including ignored arguments, indirect calls and tail returns. The
old Windows object rewrite fails the same argument comparison; the separated
copies pass. Full Clean recording and scene gates remain required.

## Aggregate dispatch

`native_aggregate.py` validates four source/header closures and ROM bodies before
assigning dedicated return kinds. `native_aggregate.c` implements both directions
at the production Native/Reference dispatch boundary:

| Entry | Result and ARM convention |
| --- | --- |
| `02013304` | Three-byte structure, packed into r0 as byte1, byte0, byte2 |
| `020404b4` | Four-byte union in r0; third argument is a four-byte aggregate |
| `0207fc7c` | Eight-byte Pair through the first argument; second in r0, first in r1 |
| `020afa48` | Four-byte structure in r0, little-endian byte order |

The adapters preserve each host compiler's actual return convention, including
Linux hidden output pointers and callee stack cleanup. A guarded PC copy of
`ov050/func_ov050_02261ed0.cpp` adapts its scalar declaration of `020afa48` to the
actual structure result before extracting the word the ARM caller uses.

The Clean `EventCalendar_ScheduleKey` returns a scalar instead of the Native
union. Typed bridges preserve both caller conventions when either version is
selected and when Reference execution is forced. The Clean PC build checks
the exact scalar type and prototype; original Clean files are unchanged.

`python tools/test_native_aggregate.py` runs actual ROM and PC bodies through
the production dispatch, OS fault and trampoline paths. It checks 640 body
cases, 160 scalar-extraction cases, and four modes with 1,000 bridge cases each
on both hosts. Controlled helper bodies and a bounded interpreter loop make
ABI errors reproducible; full recording and scene gates remain required.

## Scheduler stack frames

Newly Native scheduler callbacks reach the existing house collision stack slot.
The runtime requires a proved frame extent for every Native ancestor; it still
rejects unknown frames rather than guessing a guest address. Seven additional
ROM-hash-pinned extents describe the actual SP at the scheduler's calls:

| Entry | Call-site extent in bytes |
| --- | --- |
| `020ee834` | 16 |
| `020ee934` | 8 |
| `020ee964` | 8 |
| `020ee9a0` | 8 |
| `020eea4c` | 16 |
| `01ffd14c` | 24 |
| `01ffd44c` | 32 |

`01ffd14c` briefly uses 28 bytes through `ip`, then restores SP to entry minus
24 before calling `01ffd44c`. Its `fp`-relative epilogue restores entry SP.
The two conditional list dispatchers also have balanced early-return paths.
The extents in `native_stack.py` describe call sites, not maximum stack use.

`python tools/test_native_member_frames.py` executes the original ARM bodies
in 448 cases with 1,143 observed calls per host. It checks call-site SP, balanced
returns, preserved registers, scheduler flags, direct/virtual member pointers,
signed receiver adjustments, null and empty lists, and dispatcher outcomes.
Seven negative controls corrupt one owner's expected extent at a time and must
fail at its actual call. `python tools/test_native_stack.py` additionally rejects
changed ROM bytes and sizes. Full recordings and scene gates remain required.

## Audited PC copies for arguments and locals

`tools/native_args.py` holds two more kinds of guarded PC copy, each pinned by the
source's SHA-256 and justified by ROM addresses in the table:

- `PASSED`: a call that passes fewer arguments than the callee reads, where the ROM's
  call leaves values the source names in the next registers (the caller's own incoming
  arguments, or a local just computed there). The copy declares the callee with those
  arguments and passes them: func_0200c8c0 and func_02096484 (their r0 and r1 to
  func_020778b0), func_ov094_0229b048 and func_ov094_0229b088 (the value a "%d" format
  takes, which the source leaves out of sprintf).
- `EDITS`: exact replacements where the matching source relies on what the ROM's code does
  beyond C: three-byte local arrays that func_0209df64 fills with four bytes (the ROM's frame
  has the fourth; the PC's may not), char parameters that the ROM's code uses as the whole
  register and a caller passes a pointer to (func_0205f120, func_ov123_0229ab18), and a
  shift by a register count of 32 or more (func_020ad0c0).

`python tools/test_native_args.py` checks that every copy applies, that a changed source is
rejected, and the passed arguments.

## Narrow parameters given a word

Where a caller's declaration has a pointer (or a word) and the definition takes a char or a
short, the ROM's callee trusts the caller to have extended the register; the PC's definition
keeps only the low bits. 85 declarations name 55 such parameters. Each was audited against the
ROM's callee and, where the callee uses more than the low bits, its callers:

- Wrong, fixed by a word-typed PC copy (`tools/native_args.py` EDITS): func_0205f120 (r2),
  func_ov123_0229ab18 (r0) and func_ov094_0229a898 (r0): it keeps r0 in r6 and passes it on to
  func_ov094_0229a888, and func_ov103_0229cc70, func_ov104_0229d830, func_ov105_0229d49c,
  func_ov106_0229d104 and func_ov108_0229cbbc pass a pointer there.
- The ROM's code uses only the low bits (stores them with strb/strh, masks them, shifts them
  out, or cuts the result to the narrow type): 0200a6f0 r2, 02015800 r1, 02034bd4 r3,
  02056fcc r2, 02077a54 r1, 02077a8c r0 (and with a 16-bit mask), 02077ca8 r1, 02078380 r1,
  02078460 r1, 020785dc r2, 02084dc8 r2, 02091494 r2, 020a5718 r1, 020a5c20 r1, 020a6248 r1,
  020af004 r1, 020b3f58 r0, 0207094c r1, 02001b1c/02001b54/02001b8c/02001bc4 r0, 020036ec r1,
  020508fc r2 (the result is cut to 16 bits), 02052fdc r0 (the sum is cut to 8 bits at
  02052fe2), 020881fc r1, ov003_022122fc r2, ov004_0220cfec r1, ov004_02233dc0 r1,
  ov096_0229f7ac r0, ov103_0229cde8 r0, ov106_0229d340 r0.
- Stack arguments, which the callee loads with ldrh/ldrsh: 0200c904 (5th), 02019d0c (6th),
  02044df8 (6th), 02048cb8 (4th), ov003_022131c8 (4th), ov004_0223362c (6th),
  ov004_02240f2c (4th).
- The callee uses the whole register, but no ROM caller passes more than the narrow value:
  02001c08 (0 and 1); 020f0f7c (func_020041bc's callers narrow to a byte first); 02035148
  (func_02035638's callers pass constants and halfword loads); 0203fda0 (item IDs: constants
  and byte loads, a word compared with 0x63); 0204f8ec (constants and byte loads; a key no
  entry has ends in OS_Terminate); 0209a498 (byte loads); 0209c410 (func_0209bee8 calls it
  only after func_0209c38c checked the whole register below 8); 0209c470 (func_0209c020
  passes func_0209c4a8's result, at most 8); ov003_02225b24 (0x1520); ov096_0229f7ac r1 and
  ov096_0229f90c (byte fields at 0xb3-0xb9, behind func_ov096_0229f830's whole-register
  check); ov103_0229cde8 r1 (behind func_ov103_0229cdfc, 0xb-0x14 on the whole register);
  ov127_022996c8 (byte loads at 0xb0 and 0xb3).

## Calls into the middle of other code

dsd splits a few loops in two: a stub of four bytes (set a register, branch to the loop's
test), named with a size-0 `_unk` symbol, and the loop's body from its start, a function of
its own with a source. `ENTRIES` in `tools/native_args.py` lists the three (func_02050bdc_unk,
func_02051c8c_unk, func_020b4950_unk), pinned by the ROM bytes from the stub to the body's
end. A Native caller reaches the stub through the Reference, as any call to ROM code; when the
loop goes round, the stub's code branches to the body's start, which runs as its Native with
the registers the ROM's code has there (each body's source takes all of them). A caller is
released when its declaration passes the registers the stub reads: func_020b47d0 declares the
string only, and its PC copy passes its `size` on in r1, as the ROM's call leaves it
(`PASSED`). That releases the 28 callers.

## Structure results by value

`CALLERS` in `tools/native_aggregate.py` covers the callers of functions their sources declare
returning a structure, each pinned by the source's SHA-256 with the ROM addresses:

- Declarations with the definition's layout, adapted at the crossings by the return kinds
  above: func_02012e58 (func_02013304) and func_020401b8 (func_020404b4). func_020401b8 itself
  returns a four-byte union in r0, which its callers declare as int: its PC copy returns the
  union's word (RET_32).
- Callers whose callee returns a scalar: func_0203ff98 (func_0204019c, func_02040180 return
  int, stored as the structure's word), func_02065604 and func_020656ac (func_020bbf00 returns
  a short, stored as the colour's halfword).
- The library's FS_GetOverlayFileID returns its 8-byte FSFileID through r0: func_0204f934's
  copy passes the result's address and the overlay's information as the ROM's code does
  (0204f972-0204f976). `CLEAN_CALLERS` gives OverlaySlots_Load (clean/main/overlay_slots.c)
  the same PC copy, compiled by tools/run.py.
- Virtual methods returning a structure, which mwccarm calls with the result's address in r0
  and `this` in r1: func_0205b270 (slots 1 and 2 of vtables 020dd3a4 and 020dd3b8, C functions
  (out, unused, index)), func_ov009_02263c84, func_ov009_02263e58 and func_ov009_022650d0
  (slot 45, func_ov009_02262ec4 (out, this) in Obj_ov009_022658dc's vtable, which writes three
  words). The copies call the slot as a C function with those arguments.
