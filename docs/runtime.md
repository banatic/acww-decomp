# Running the game

This project aims to run the game from its sources: every function can execute as the ROM's own
code, as its matching source compiled for the PC, or as a readable rewrite, and all three must
behave the same. This document is the plan. Nothing in it exists yet unless it says so.

Performance work and changes to how the game plays (higher resolutions, frame interpolation,
online services) belong to a separate port project that builds on this one. Here, the measure
is faithfulness.

## Three implementations per function

| | What it is | Where it comes from |
|---|---|---|
| **Reference** | The ROM's ARM/Thumb code, run by an interpreter | the ROM |
| **Native** | The matching source, compiled for the PC | `src/` |
| **Clean** | A readable implementation with the same behaviour | `clean/` |

A registry maps each function address to the implementations it has:

```c
REGISTER(0x0201a3c0, func_0201a3c0, Villager_SetFriendship);
```

At run time each function uses the best one allowed (Clean, else Native, else Reference); a
setting can force any function, module or the whole program back to Reference. Calls between
implementations go through the registry, so a Clean function can call ROM code and the other way
round.

Native is the matching source as it is, compiled for a 32-bit x86 process whose memory holds the
DS's main RAM at its real address (0x02000000), so pointers and structure layouts are the DS's.
Where the matching source relies on behaviour that C leaves undefined, the difference is made
explicit in the source behind `AVOID_UB`, never silently.

## What Clean may change

Clean is judged by behaviour, not by text. Its contract with the Reference is, for the same
memory and arguments on entry:

- the same return value;
- the same writes to memory outside the function's own stack frame (address and value);
- the same calls, to the same functions, with the same arguments, in the same order;
- the same accesses to hardware registers, in the same order.

Register use, instruction order, stack temporaries, inlining and repeated computation are not
part of the contract. Everything a matching source does only to make the compiler produce the
ROM's bytes (`FAKEMATCH` constructs, extra temporaries, `volatile` used for scheduling) is dropped.

Odd behaviour that is part of the contract stays, and is said out loud with one of these tags:

| Tag | For | Example |
|---|---|---|
| `QUIRK:` | behaviour that looks unusual but is the game's | a 16-bit truncation, a fixed-point rounding step |
| `BUG:` | a defect of the original, kept | an off-by-one, a read of an uninitialised field |
| `HW:` | an order the hardware depends on | register writes that must not be reordered |
| `REQUIRES:` | a precondition the game always meets, outside which Clean may differ | a pointer the game never passes as null |

A `BUG:` that has an obvious fix gets it behind `BUGFIX`, off by default. Clean is written as C
without undefined behaviour and is compiled with `-fwrapv -fno-strict-aliasing`; ARM behaviour
that C does not define (shifts by 32 or more, unaligned loads, signed overflow) goes through
named helpers. Structures come from `include/`, shared with Native, with their offsets checked by
`static_assert`.

## How a Clean function is accepted

A differential check runs Reference and Clean from the same recorded entry states and compares
everything in the contract. Calls out of the function are answered from the recording, so the
check covers one function at a time. Entry states come from playing the game (recorded at
function entry) and from inputs generated within the types' ranges.

When they differ, either Clean is wrong and is fixed, or the difference is the game's and is
made explicit with a tag. A difference that only appears in states the game cannot produce is
written down as `REQUIRES:`. Clean is never bent just to pass a test.

## The runtime

- **Memory**: main RAM, the TCMs, VRAM and the overlay regions at their DS addresses; overlays
  loaded from the ROM as the game asks for them.
- **CPU**: an ARMv5TE interpreter for ARM and Thumb code, used for the Reference and for any
  function without another implementation.
- **Hardware**: the DS's 2D and 3D graphics at their native resolution, sound, input, the clock
  and save memory, written to behave like the hardware.
- **Checks**: function-level differential checks, and scene-level checks that run the same input
  recording with different implementation choices and compare frames and memory.

## Milestones

Each milestone is done when all of its checks pass in CI.

**M1: Reference and Clean, one function at a time.** Done: `runtime/` (interpreter, memory, loader,
the check), `tools/diffcheck.py`, and the first Clean function in `clean/main/slots.c`.
- `runtime/` builds as a 32-bit program on Windows (clang) and Linux (gcc), with main RAM, the
  TCMs and the ARM9 modules loaded at their DS addresses.
- The interpreter runs ARM and Thumb code: any function the ROM has, called with given registers
  and memory, until it returns.
- `tools/diffcheck.py` runs every registered Clean function against its Reference on generated
  entry states and compares the contract above.
- At least one Clean function is registered and passes.

**M2: Native on the PC.** In progress: `tools/native.py` compiles 25,242 of the 25,247 sources
for 32-bit x86 and points their references at the game's memory (`tools/objrewrite.py`);
`python tools/diffcheck.py --native` runs every function that calls nothing as Native against
its Reference on random states (6,340 agree; 34 differ, each listed with its reason in
`tests/native/known.txt`: shifts by 32 or more and unaligned loads, which random states produce
and the game may not).
- Every game source compiles for 32-bit x86 (clang and gcc), with the differences behind
  `AVOID_UB`.
- Every function that calls nothing (a leaf) runs as Native against its Reference in the
  differential check; the ones that differ are listed with the reason (an interpreter bug,
  undefined behaviour, or a source to fix) until none are left.

**M3: The game starts, as Reference.** Done: `tools/run.py` boots the ROM's own code (the
interpreter with banked registers and exceptions, `runtime/io.c` for the hardware, the 2D and 3D
engines in `gpu2d.c` and `gpu3d.c`, the ARM7 side at its protocol in `arm7.c`) to the title;
`runtime/recordings/title-start.txt` gives the same 1,300 frames on every run and host, which
CI checks against `title-start.sha1`.
- The hardware layer (interrupts, timers, DMA, the file system from the ROM, 2D and 3D graphics
  at native resolution, input) runs the game's own boot code to the title screen.
- A recorded input sequence reaches the same title-screen frames on every run.

**M4: The game starts, as Native.** In progress: on Windows,
`tools/run.py ... --native=all --expect runtime/recordings/title-start.sha1` runs 23,885
functions as Native and gives the Reference's 1,300 frames, with RAM at six points equal apart
from words that hold PC addresses (function pointers and stack addresses the PC code keeps).
`runtime/native_run.c` dispatches between the two: Reference code calling a Native function, a
Native function calling the ROM's code through the interpreter (`native_tramp.S`), and a trace of
the Reference run's crossings that gives Native code the Reference's timing. 1,326 functions stay
Reference: those `tools/native.py` finds by reading the sources (member function pointers,
virtual calls with no known address, calls to a function's middle), and those listed with a
reason in `runtime/native-reference.txt` (hardware access, calls with fewer arguments than the
callee takes, undefined behaviour). Linux does not pass yet, and neither run is in CI.
- The same recording run with Native for every function that has a source gives the same frames
  and the same RAM at chosen points as the Reference run.

**M5: Clean, one subsystem at a time.** In progress: eleven subsystems of `main` in
`clean/main/` (180 functions) pass their function-level checks, and on Windows the M4
recording run with `--clean` (each Clean function in place of its Native one, `tools/run.py`)
gives the Reference's frames and RAM. The recording found what random entry states had not: callers that
ask the calendar about month 0 or 13, which the game's tables answer from their neighbouring
bytes (`clean/main/calendar.c`), and a fifth argument that a check placed where the game does
not (`diff_stack` in `runtime/diffcheck.h`). A Clean function need not call what the ROM's code
calls: the Reference run records nothing of its calls out (`runtime/native_run.c`).
- Clean functions are added by subsystem; each passes the function-level check and the M4
  recording. The progress map counts them.
