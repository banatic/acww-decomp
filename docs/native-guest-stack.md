# Observable ROM stack storage in Native calls

The house collider at `ov004:0223df88` creates four `Vec` centers and assigns
their x and z components. It does not initialize y. The ROM later reads those
y words while calculating collisions. Filling the host locals with the usual
uninitialized-memory pattern changes the collision result.

This is observable stack reuse, not an unspecified value to choose freely.
The ROM's `ov004:0220dd80` stores its incoming r3 at body SP + 0x14 before
its first call. On a later path that word becomes one of the house collider's
center y components. Its value must come from the current call's argument;
neither a fixed scale nor a value from the Reference run supplies it.

## Tracking calls

`native_profile.py` gives every Native table entry an i386 wrapper. Registered
Clean functions and legacy Clean adapters receive wrappers through
`native_clean_profile.py`. Direct calls, recursive calls, tail relocations and
function pointers retain those public entries. Clean names alias their wrappers.
The function table index identifies an entry independently of overlapping
overlay addresses or identical host bodies.

Each wrapper saves the actual host return address and reports entry. Its return
stub restores that address without changing eax, edx, or an x87 result. This
also preserves a hidden-result `ret $4`. The return hook uses integer registers
only. The caller PC stays in an active stack slot until `ret`; no value needed
after restoring ESP is left below it. Linux fixtures inject a signal after
every register restore and overwrite expired below-SP storage to check this.
The wrapper fixtures also exercise recursion, narrow results,
direct Clean calls and absolute Clean function pointers. When hooks are absent,
wrappers retain the ordinary differential-check behavior.

The runtime maintains a separate call context for each host fiber and IRQ.
Each interpreter-to-Native crossing anchors the context at the interpreter's
current SP. A nested crossing saves and restores that anchor. A known entry
subtracts its audited ROM frame extent from its parent's guest SP. Unknown
ancestors invalidate the calculation. Requesting a slot through such an
ancestor stops with the exact path; it never guesses an extent.

Compact Clean wrappers share their entry/return code. This keeps the linked
host text and initialized data below the runtime's DS-address boundary.
Native body mappings retain the actual body start for fault-offset diagnosis.

## Audited extents and effects

`native_stack.py` records whole-function ROM SHA256 and size guards for these
constant extents. The furniture pull in the house (scene house-pull) reaches the collider's
producer through two more states, 0222a28c and 022297d8, and the consumer through 0223df48;
the other 30 callers of 0201100c, through which the producer is reached, were audited with
them: each saves registers with one push and reserves its frame with one sub at entry, and
its only other SP change is the matching add before its single pop sequence. Reachable control flow, including the two bounded Thumb
switch tables and the literal tail trampoline, was inspected. Each listed
function has one call-site extent; stack adjustments and restored returns
were checked across its reachable paths.

| Module | Function | Extent |
| --- | --- | --- |
| autoload_2 | 020ee834 | 0x010 |
| autoload_2 | 020ee934 | 0x008 |
| autoload_2 | 020ee964 | 0x008 |
| autoload_2 | 020ee9a0 | 0x008 |
| autoload_2 | 020eea4c | 0x010 |
| itcm | 01ffd14c | 0x018 |
| itcm | 01ffd44c | 0x020 |
| main | 02004c0c | 0x008 |
| main | 020058e4 | 0x028 |
| main | 02008304 | 0x008 |
| main | 020095f4 | 0x010 |
| main | 020096ac | 0x018 |
| main | 02009fe4 | 0x008 |
| main | 0200c200 | 0x008 |
| main | 0200c954 | 0x008 |
| main | 0200c9ec | 0x008 |
| main | 0200cc44 | 0x010 |
| main | 0200d1e4 | 0x010 |
| main | 0201100c | 0x050 |
| main | 02030ebc | 0x060 |
| main | 02031288 | 0x0d0 |
| main | 02032aa8 | 0x010 |
| main | 02033678 | 0x098 |
| ov003 | 0220d2a4 | 0x008 |
| ov003 | 0220d6d4 | 0x008 |
| ov003 | 0220d8f4 | 0x008 |
| ov003 | 0220dbec | 0x008 |
| ov003 | 0220e938 | 0x008 |
| ov003 | 0220ea78 | 0x008 |
| ov003 | 02210fa0 | 0x018 |
| ov003 | 022119f0 | 0x018 |
| ov003 | 02211db0 | 0x010 |
| ov003 | 02212308 | 0x010 |
| ov003 | 022124c4 | 0x020 |
| ov003 | 02212884 | 0x010 |
| ov003 | 02213b28 | 0x028 |
| ov003 | 02215394 | 0x010 |
| ov003 | 02215bf8 | 0x010 |
| ov003 | 02215d1c | 0x010 |
| ov003 | 0221615c | 0x008 |
| ov003 | 022166f8 | 0x010 |
| ov003 | 02216bfc | 0x010 |
| ov003 | 02216eec | 0x018 |
| ov003 | 022172c4 | 0x008 |
| ov003 | 02218ff0 | 0x080 |
| ov004 | 0220dd80 | 0x0a0 |
| ov004 | 022297d8 | 0x008 |
| ov004 | 02229860 | 0x018 |
| ov004 | 02229a7c | 0x008 |
| ov004 | 02229bec | 0x008 |
| ov004 | 02229f60 | 0x008 |
| ov004 | 0222a28c | 0x008 |
| ov004 | 0223d610 | 0x000 |
| ov004 | 0223d63c | 0x020 |
| ov004 | 0223db08 | 0x0d8 |
| ov004 | 0223de70 | 0x040 |
| ov004 | 0223df48 | 0x018 |
| ov004 | 0223df88 | 0x2e0 |
| ov004 | 0223e1f0 | 0x018 |

The producer entry hook reproduces its r3 spill at +0x14 for both Native and
its Clean replacement, `PushBox_OnSideHit`. A source-hash-guarded PC copy of
the consumer uses guest storage at +0x28 for its four centers. It obtains the
slot after its four collider constructor calls, before assigning the centers.
The Clean consumer, `HouseRoach_Move` in `clean/ov004/house_roach.c`, sets the
centers' Y words to 0 (its `BUG:` note), which changes the collision result
(the house scene, frame 4199, with every Clean function in place). The mixed
Native/Clean build compiles a source-hash-guarded copy of that file
(`native_stack.clean_copy`) whose centers use the same guest slot, requested at
the same point. The original sources and Clean implementations remain unchanged.

For example, consumer entry from root SP 0x027e2f04 through extents
0 + 0x40 + 0x18 + 0x2e0 puts its body at 0x027e2bcc. Its y words are
0x027e2bf8, 0x027e2c04, 0x027e2c10 and 0x027e2c1c. A producer path through
0200cc44 or 0200d1e4 has body SP 0x027e2bfc and spills at 0x027e2c10.
These are examples derived from an anchor, not hardcoded runtime addresses.

`native_abi.py` additionally proves word counts for scalar/pointer arguments
of supported free-function definitions. The Native-to-Reference bridge writes
only the actual stack arguments for such signatures, so unused host words do
not erase guest stack residue. Unsupported or ambiguous ABIs keep the existing
bridge behavior. This does not change the bridge's call-SP selection.

## Verification and limits

With `ACWW_RUNTIME_OUT` configured as described in the Native brief:

```
python tools/test_native_abi.py
python tools/test_native_stack.py
python tools/test_native_profile.py
python tools/test_native_clean_profile.py
```

The stack tests check the real ROM and source guards, reject mutated proofs,
distinguish an unknown frame from a valid zero-sized frame, and check the PC
copy's placement. The wrapper tests compile, rewrite, link and execute actual
production wrappers on each host. These checks supplement the full Native,
differential, recording and scene gates.

This implements the audited effects above, not a complete ARM stack emulator.
New observable stack dependencies require their own ROM/source audit. Changed
guarded inputs fail validation rather than silently reusing stale metadata.
`RUN_NATIVE_CALL_TRACE=0220dd80,0223df88` reports distinct live paths, anchors,
computed body SPs and incoming arguments for diagnosis. It does not enable or
disable the stack effects, and paths after a divergence do not prove that the
Reference took the same path.
