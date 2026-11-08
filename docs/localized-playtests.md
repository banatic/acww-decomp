# Localized Clean gameplay checks

These checks use generated Spanish resources, the Latin keyboard and opt-in Spanish grammar.
They are functional checks of the localized Clean build, not a Reference-equivalence claim.
Original Korean code modules and their symbols remain the execution base. Private ROMs,
rendered screenshots and save files stay under `build/` and must not be committed.

## Reproduce the new-game save

First generate the matching resources with `tools/play.py --form clean --localize es
--european YOUR_EUROPEAN_DUMP --latin-keyboard --spanish-grammar --build-only`, using the
supported Korean dump and compiler setup documented in INSTALL.md and localized-clean.md.
Then drive a fresh game with no input save:

```sh
python tools/drive.py start es-new --form clean --rom build/localized-clean/es-grammar/game.nds --localized es --spanish-grammar --rtc "2005-11-23 12:00:00" --prefix runtime/recordings/localization/spanish-new-game-save.txt --until 39358
python tools/drive.py es-new png build/localized-clean/saved.png
python tools/drive.py es-new save build/localized-clean/new-town.sav
```

`save` exports the chip exactly as the game left it. It does not trigger a game save, and
refuses to overwrite any existing file. The recording reaches the game's Save and Quit
confirmation, after visiting the house and completing the initial Nook conversation. A
chip exported earlier in creation has no valid town banks; successful export alone is
not evidence that the game saved. Explicit input saves are read only by the driver.

The driver defaults to Reference. `--form clean` builds Clean, keeps a session-specific
policy and sets Native execution explicitly. `--rom` chooses generated resources while
symbols and code modules remain Korean. `--localized` enables bounded name plates;
`--spanish-grammar` requires Clean/es and matching resources. The Native watchdog treats
an intentional command pause as progress, while still checking for a stalled running game.
A stopped process reports its exit codes and drains its remaining output into `run.log`.

## Observed checks

On Windows x86 Clean, the fresh recording completed through frame 39358. The player name
contains U+00F1 and the town name U+00E1; both were entered using the Latin keyboard and
were visibly retained in subsequent dialogue. The town generated, the town hall tutorial
completed, the player walked to and entered the house, Nook's initial conversation completed,
and Save and Quit performed 1490 writes to the chip.

The exported chip is 262144 bytes. Both 0x173fc-byte banks have setup marker 0x32, zero
halfword checksum sums and the expected names at the actual town/first-player fields.
The export's SHA-256 is `a62d5ef8c305d752785b0abc845725fbf24ed42aabbcdc339fc7bd6974d43be3`.
`tools/check_localized_save.py SAVE --player NAME --town NAME` checks these storage conditions
without modifying the save. Four synthetic tests reject a corrupt secondary bank, wrong
names with valid checksums, blank chips and truncated files. Storage integrity is separate
from actually loading the game.

A separate Clean process loaded that private save with clock `2005-11-23 12:20:00` and
`runtime/recordings/localization/spanish-reload.txt` through frame 4794. It completed the
bedroom prompts, returned to the same house exterior and opened the town map: both accented
names remained visible. This was a game load, not a save-byte inspection. Reproduce it after
stopping the first session (on Windows the running executable cannot be rebuilt):

```sh
python tools/drive.py es-new stop
python tools/drive.py start es-load --form clean --rom build/localized-clean/es-grammar/game.nds --localized es --spanish-grammar --rtc "2005-11-23 12:20:00" --save build/localized-clean/new-town.sav --prefix runtime/recordings/localization/spanish-reload.txt --until 4794
```

Store interaction, fishing and letter checks are still in progress; this document does not
claim those scenarios have passed. Short speaker names and the seven-character
boundary were inspected; the original name capacities still limit longer translated names.
