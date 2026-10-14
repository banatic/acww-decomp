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

**M1: Reference and Clean, one function at a time.**
- `runtime/` builds as a 32-bit program on Windows (clang) and Linux (gcc), with main RAM, the
  TCMs and the ARM9 modules loaded at their DS addresses.
- The interpreter runs ARM and Thumb code: any function the ROM has, called with given registers
  and memory, until it returns.
- `tools/diffcheck.py` runs every registered Clean function against its Reference on generated
  entry states and compares the contract above.
- At least one Clean function is registered and passes.

**M2: Native on the PC.**
- Every game source compiles for 32-bit x86 (clang and gcc), with the differences behind
  `AVOID_UB`.
- Every function that calls nothing (a leaf) runs as Native against its Reference in the
  differential check; the ones that differ are listed with the reason (an interpreter bug,
  undefined behaviour, or a source to fix) until none are left.

**M3: The game starts, as Reference.**
- The hardware layer (interrupts, timers, DMA, the file system from the ROM, 2D and 3D graphics
  at native resolution, input) runs the game's own boot code to the title screen.
- A recorded input sequence reaches the same title-screen frames on every run.

**M4: The game starts, as Native.**
- The same recording run with Native for every function that has a source gives the same frames
  and the same RAM at chosen points as the Reference run.

**M5: Clean, one subsystem at a time.**
- Clean functions are added by subsystem; each passes the function-level check and the M4
  recording. The progress map counts them.
