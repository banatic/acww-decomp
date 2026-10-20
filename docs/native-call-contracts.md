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
