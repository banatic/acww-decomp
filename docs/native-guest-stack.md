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
| autoload_2 | 020e9744 | 0x038 |
| autoload_2 | 020e9868 | 0x038 |
| autoload_2 | 020ee834 | 0x010 |
| autoload_2 | 020ee934 | 0x008 |
| autoload_2 | 020ee964 | 0x008 |
| autoload_2 | 020ee9a0 | 0x008 |
| autoload_2 | 020eea4c | 0x010 |
| autoload_2 | 020f5e50 | 0x010 |
| autoload_2 | 020f9948 | 0x018 |
| autoload_2 | 020f9b50 | 0x010 |
| autoload_2 | 020f9d00 | 0x018 |
| autoload_2 | 020f9ea4 | 0x018 |
| itcm | 01ffd14c | 0x018 |
| itcm | 01ffd44c | 0x020 |
| main | 020040bc | 0x018 |
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
| main | 0201ce68 | 0x010 |
| main | 0202f3e4 | 0x020 |
| main | 0202f464 | 0x070 |
| main | 020288bc | 0x018 |
| main | 02030ebc | 0x060 |
| main | 02031078 | 0x028 |
| main | 02031288 | 0x0d0 |
| main | 02031bb8 | 0x058 |
| main | 02032aa8 | 0x010 |
| main | 02033678 | 0x098 |
| main | 02066dc4 | 0x018 |
| main | 020671b0 | 0x010 |
| main | 020673e0 | 0x050 |
| main | 02067504 | 0x008 |
| main | 02068144 | 0x010 |
| main | 0206823c | 0x010 |
| main | 020a9ba0 | 0x008 |
| main | 020b39bc | 0x030 |
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
| ov004 | 0220fc98 | 0x020 |
| ov004 | 02210abc | 0x018 |
| ov004 | 02214c50 | 0x018 |
| ov004 | 02214d34 | 0x018 |
| ov004 | 022150b8 | 0x010 |
| ov004 | 02215298 | 0x010 |
| ov004 | 02215374 | 0x008 |
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
| ov004 | 0223f218 | 0x228 |

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

The museum's insect room, `ov004:0223f218` (scene museum-halls), does the same with the
three cases of its room: it adds three collision boxes whose `Vec` centres, at body SP + 0x18,
get x and z and keep the stack's y, which becomes the height of the cases' walls and tops in
the collision lists (0x021c3bac, 0x021c4030). It saves five registers and reserves 0x214
bytes at entry, so every call is at entry SP - 0x228, and it is reached from the scheduler
through 020ee934, 020ee9a0, 020ee834, 01ffd14c and 01ffd44c. A source-hash-guarded PC copy
takes the centres from that guest slot after its three box constructors, and the mixed
Native/Clean build compiles a copy of `clean/ov004/museum_insects.c` whose `InsectRoom_Update`
(which sets the y words to 0, its `BUG:` note) uses the same slot. From anchor SP 0x027e2f5c
the body is at 0x027e2cdc and the y words at 0x027e2cf8, 0x027e2d04 and 0x027e2d10; the
ROM's leftover there made a case 0x0211aa0c high (its top 0x02120a0c), where the PC's stack
gave -1 and the Clean code 0.

The insect room's other two y words come from the field actor's move of the same frame, which
reaches its walls (02033678) and the ground under it (02031bb8) from 0201100c through 02031288
(scene museum-insects; both at the depth of the room's frame). 02033678 keeps three points at
body SP + 0x24 to + 0x3b and, for each wall it tests, stores the position and the pushed point
in one of three pairs of `Vec`s at + 0x3c to + 0x83 that nothing reads (`volatile` in the
matching source): their z words are the y words of the room's first two cases. 02031bb8 calls
02031078 with the addresses of its three out-values (body SP + 4 to + 0xc); 02031078 holds the
second's address in r4 and calls the ground's height function, 020b39bc, by its vtable, and
that function's entry push (r4-r7, lr) stores it where the third case's y word is. The PC copies
keep 02033678's locals and 02031bb8's out-values at their ROM slots where the frame is proved
(`native_guest_stack_slot_if`: both run on many paths), 02031078 says what it holds in r4-r6,
and 020b39bc's push is audited (SAVES). The Clean versions (`CollisionWalls_PushOut`, which
does not store the pairs, `CollisionQuery_IsRaisedOrPost` and `CollisionQuery_PostAt`) are
compiled in the mixed build from copies with the same slots and registers. From anchor SP
0x027e2f5c the walls' body is at 0x027e2c9c and the ground's at 0x027e2d4c; the ROM's run made
the cases 0x027e2d54 + 0x6000 and 0x0001b029 + 0x6000 high, where the PC's stack gave other
stack addresses and 0.

The house's cockroach (0223df88, above) reads the same frames when a villager walks in the
player's house (scene flea-buyer): the y word of a keep-out box's centre at 0x027e2c10 is the z
of the second direction of a wall's span test, 0202f464 (called by the near-wall push 0202f3e4
from the field actor's walls), which keeps its two directions, two points and two square
segments at body SP + 0 to + 0x63. Its PC copy and the copy of `CollisionSegment_SpansPoint` keep
them at those slots where the frame is proved; the ROM's -0x1000 made the box's top 0x9000,
where the PC's stack gave 0 and 0xa000.

## Saved registers

A function's entry push stores its caller's r4-r11 on the ROM's stack, where later code can
read them as leftovers; the ROM's code also hands them on unchanged to whatever it calls. Native
code has no such registers, and a call from Native code into the ROM's code (the bridge) used to
hand the callee the interpreter's registers at the last crossing. The guest frames now carry
r4-r11 where they are known:

- a PC copy says what the ROM's code puts in a register at the point it does so
  (`native_guest_register(owner, reg, value)`, checked against the active frame's owner);
- a function whose entry push is audited (`native_stack.SAVES`, the push's register list, which
  `test_native_stack.py` reads from the ROM's first instruction) keeps its caller's known
  registers that it does not save, since its code cannot change them; its frame, when proved,
  gets the caller's known values of those it saves at the push's addresses below its entry SP;
  any other function starts with none known;
- the bridge hands the ROM's callee the known registers of the calling frame, the others as
  before.

The policy's last column carries the push (bit 16 set, bits 0-15 the register list).

## The room music cue

A room object with music in a villager's house (scenes villager-birthday, sick-villager,
letter-errand) updates its cue from its update: 02210abc calls 02215374 by its vtable, then
022150b8, then 02214c50 or 02214d34 by its state table, then 02215298, 020040bc and the cue's
update 020f9ea4, which calls 020f9d00, 020f9b50 (which calls 020f5e50) and 020f9948. The first
update finds the cue's handle without a player, so NNS_SndPlayerReadVariable writes nothing:

- 020f9d00 stores into the cue (bytes 0xb-0xe) its frame's words at body SP + 4 to + 0xb. In
  the ROM these are r5 and r6 of the object's matrix code, func_ov004_0220fc98 (the object, and
  its turn or its mount's z), which MTX_Concat43's entry push saved there when 020e9744 and
  020e9868 called it just before, from the same depth.
- 020f9948 goes on from body SP + 0 and + 2 (layouts other than 1 and 3): r5 of 020f9b50, its
  `pos`, which is the address of 020040bc's copy of the position at that function's body SP;
  020f5e50's entry push saved it there.

The PC copies (`native_stack.CUE_EDITS`) keep 020040bc's position, 020f9d00's six variables and
020f9948's two at their ROM slots, and say where 0220fc98 (r4-r7), 020e9744 and 020e9868 (r4)
and 020f9b50 (r4-r6) set their registers. MTX_Concat43 then gets the ROM's r4-r7 from the bridge,
and 020f5e50's audited push stores 020f9b50's r4 and r5. From anchor SP 0x027e2f5c the position
is at 0x027e2e94 and both cue functions' bodies at 0x027e2e64. The Clean versions
(`MusicCue_ReadVariables`, `MusicCue_Progress`, their `BUG:` notes, which read 0) are compiled in
the mixed build from copies (`native_stack.CLEAN_CUE_EDITS`) with the same slots and registers,
as are `SoundCue_UpdateAt`, `MusicCue_ApplyPosition`, `RoomObject_BuildMatrix`, `Mtx43_RotateY`
and `Mtx43_Translate`.

## A talk's reply

A talk's reply, 020288bc (reached from the talk update 020a9ba0 through 0206823c, 02068144,
02066dc4, 020671b0, 02067504 by its vtable and 0201ce68 by a member pointer), calls the line
function of the choice with the address of its line (body SP + 4) and says the line when it has a
text, its message byte at body SP + 0. The letter errand's line function (02027cc8, scene
letter-errand) writes no line, and the ROM reads what its stack held: the text walker that
020673e0, called by 020671b0 just before, had at its body SP + 0, at 0x24 and 0x28 (the talk
object and 0). The ROM then copies 25 bytes from the talk object's start as the message's text;
the PC's stack gave -1 and the PC copy faulted in strncpy. The copy of 020288bc keeps its locals
at their slot. 020673e0 runs on many paths, so its copy asks for its slot with
`native_guest_stack_slot_if`, which gives 0 where the frame is not proved, and keeps the walker
on the PC's stack there. `VillagerTalkOffer_Reply` (its `BUG:` note: a line of 0) and
`TalkObject_RunAnswerText` are compiled from copies with the same slots.

The catchphrase's "type it again" (scene villager-habit-retype) goes the same way: its line
function, `VillagerTalkNickname_AskHabitTextLine` (0202adc8), opens the keyboard and writes no
line, and the ROM names the message file after the talk object's first bytes.

## Argument words

`native_abi.py` additionally proves word counts for scalar/pointer arguments
of supported free-function definitions. The Native-to-Reference bridge writes
only the actual stack arguments for such signatures, so unused host words do
not erase guest stack residue. Unsupported or ambiguous ABIs keep the existing
bridge behavior. This does not change the bridge's call-SP selection.
The library sources are not distributed (`libs/README.md`), so `tools/run.py`
keeps the library functions' counts in `runtime/library-arguments.txt` when it
reads them and uses that file in a checkout without them. Without it, every
Native call into library code (`FX_MulFunc` among them) copied the whole host
extent onto the ROM's stack, and in the house scene those words became the
collider centres' y components: a checkout without `libs/` (CI's Linux one)
diverged at frame 3422 where one with them agreed.

Assembly definitions have no proven count, so a Native call into one copied the whole extent
too. `native_abi.STACKLESS_ASM` lists the assembly library functions with at most four
parameters whose ROM code never names the stack pointer, calls nothing and branches only inside
itself (`test_native_abi.py` derives the list from the ROM with capstone): they read nothing
from the stack, and the bridge writes no stack words for them. In scene villager-habit-retype a
Native call into `MI_CpuFill8` from 0202aea0 had covered the reply's unset line (below) with
host words, among them the line's own address.

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
