# Playing the game

`tools/play.py` builds the runtime (docs/runtime.md) with a window in front of it, and starts
it: both screens, live input, the DS's frame rate and the save written back to a file. Windows
only for now.

```sh
python tools/native.py               # once, and after a change to src/ (Native and Clean forms)
python tools/play.py                 # build, then play; the save is %APPDATA%\acwwdecomp\acww.sav
python tools/play.py my-town.sav     # play with this save file
python tools/play.py --build-only    # only build; prints the program's path
```

The ROM is the one `tools/extract.py` checked (`extract/adm-kr.nds`). The program is written to
the runtime's build directory (`ACWW_RUNTIME_OUT`, else `build/runtime`) as `acww-play.exe`,
with `acww-play.cfg` beside it naming the ROM, the module list, the symbols and the Native policy
it runs with; it can be started without the script, and `acww-play.exe --help` lists its
options.

## Forms

| `--form` | Program | Runs |
|---|---|---|
| `clean` (default) | `acww-play.exe` | Native code with every Clean version in its function's place (as `tools/run.py --native=all --clean`), the ROM's code for the libraries and the functions `runtime/native-reference.txt` keeps |
| `native` | `acww-play-native.exe` | the matching sources compiled for the PC, the ROM's code for the rest |
| `reference` | `acww-play-reference.exe` | every function as the ROM's code in the interpreter |

`acww-play.exe --reference` also runs the interpreter alone. The Native and Clean forms run
without the Reference's timing record (`tools/run.py --no-timing`): their code takes no
emulated time, so frames that depend on how long the game's code runs (the clouds, a 3D scene
drawn every second or third frame) can differ from a Reference run, while the game itself goes
the same way: a scene recorded from a town save leaves the player at the same place at the same
frame in both. Drawing runs on its own thread in every form (`runtime/render.h`).

The program prints the frame rate every five seconds, with how much of the time the emulation
was busy; on the machine this was written on, every form keeps the DS's 59.83 frames a second
with the emulation busy a fifth to a third of the time. Unpaced (`--fast`), a scene from a town
save (`runtime/recordings/scenes/house-exit.txt`, 4,300 frames) ran at about 200 frames a second
with Clean code, 205 with Native code and 205 to 270 as Reference: the crossings between Native
code and the library code, which is always interpreted, cost about what the interpreter saves.

## Keys

| DS | PC |
|---|---|
| +Control Pad | arrow keys |
| A, B, X, Y | X, Z, S, A |
| L, R | Q, W |
| START | Enter |
| SELECT | Shift or Backspace |
| touch screen | left mouse button on the lower screen (a drag that leaves it stays at its edge) |

Tab held runs as fast as the PC can, F12 saves the screens as a PNG beside the save file. A
press shorter than a frame still reaches the game (it is held for two frames). The window can be
resized; the screens are drawn at the largest whole multiple of their size that fits.

## The save

The save file is a 256 KB flash image, the format emulators write as `.sav`. At start the
program loads it into the save chip if it exists; if it does not, the chip starts erased and the
game begins a new town. When the game writes to the chip, the program writes the whole image
back to the file once the writes have stopped for half a second, by writing `SAVE.tmp` and
putting it in the file's place, and once more at exit. Closing the window lets the game finish
a save in progress first (up to three seconds). The first time it replaces a file that existed,
the original is kept as `SAVE.bak`. `--read-only` never writes; no other file is written.

The clock is the PC's (`--rtc "YYYY-MM-DD HH:MM:SS"` starts it at a fixed moment instead).

## Not there yet

- **Sound.** The ARM7 is simulated at its protocol (`runtime/arm7.c`): the sound driver's
  command lists (PXI tag 7) are acknowledged, and nothing runs the sound hardware the ARM7
  drives, so there is nothing to play. With `RUN_SEQUENCER=1` (`tools/run.py --sequencer`,
  `runtime/sequencer.h`) the ARM7's sequence player runs the sequences' commands, tempo and
  variables, which some of the game waits on (the end of K.K.'s show, the town tune editor's
  playback), but takes no channel for a note. Sound needs the notes played on the DS's sixteen
  sound channels, from the banks' instruments and wave archives.
- **Linux.** The window is Win32 (`runtime/play.c`).
- Wireless play (local and Wi-Fi) is not emulated, as in the headless runs.

## Checking it

The headless runs do not change: the front end only adds hooks that are empty without it
(`run_frame_hook` in `runtime/run.h`, `frame_output_hook` in `runtime/frame.h`, `input_live` in
`runtime/input.h`, `arm7_backup` in `runtime/arm7.h`). `ACWW_BACKGROUND=1` opens the window
without taking the focus, and the window takes key and mouse messages posted to it (window class
`AcwwPlay`), so a script can play it and capture it with `PrintWindow`; `--frames N` quits after
N frames, `--input FILE` adds a recording (runtime/input.h) under the live input.
