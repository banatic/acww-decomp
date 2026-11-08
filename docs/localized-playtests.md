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
without modifying the save. Five synthetic tests reject a corrupt secondary bank, wrong
names with valid checksums, blank chips and truncated files. Storage integrity is separate
from actually loading the game. A fixture test also checks that setup changes only its declared
fields and the bank checksums.

A separate Clean process loaded that private save with clock `2005-11-23 12:20:00` and
`runtime/recordings/localization/spanish-reload.txt` through frame 4794. It completed the
bedroom prompts, returned to the same house exterior and opened the town map: both accented
names remained visible. This was a game load, not a save-byte inspection. Reproduce it after
stopping the first session (on Windows the running executable cannot be rebuilt):

```sh
python tools/drive.py es-new stop
python tools/drive.py start es-load --form clean --rom build/localized-clean/es-grammar/game.nds --localized es --spanish-grammar --rtc "2005-11-23 12:20:00" --save build/localized-clean/new-town.sav --prefix runtime/recordings/localization/spanish-reload.txt --until 4794
```

## Prepared shop, letter and fishing scenarios

For the following cases, a copy of the new-town save was explicitly prepared. This setup
makes the part-time job inactive, supplies 10000 bells, equips rod 0x1374, and places apple
0x1518 and paper 0x1020 in pockets 0 and 1. It preserves the other bank fields and recomputes
both checksums. This is fixture preparation, not evidence of completing the job or obtaining
these items during the new-game recording. Input saves are never modified and fixture output
must be a new file. The generator reproduces the actual test input exactly: SHA-256
`059e77fb73182ce1cbcd81e514d36edba8942c8d443d669bcea76b11473a4ccf`.

```sh
python tools/localized_playtest_fixture.py build/localized-clean/new-town.sav build/localized-clean/equipped.sav
python tools/drive.py start es-cases --form clean --rom build/localized-clean/es-grammar/game.nds --localized es --spanish-grammar --rtc "2005-11-23 12:20:00" --save build/localized-clean/equipped.sav --prefix runtime/recordings/localization/spanish-shop-letter-fish.txt --until 39102
python tools/drive.py es-cases save build/localized-clean/after-cases.sav
```

Observed in the actual Clean run:

| Case | Evidence |
|---|---|
| Store sale | Apple moved to the sale box, 500-bell offer accepted; wallet rose from 10000 to 10500 |
| Store purchase | A shovel (0x1369) entered pocket 0; wallet returned to 10000 after the 500-bell purchase |
| Letter writing | Entered U+00E1, U+00F1 and U+00FC, completed the letter and reopened it with the same body |
| Letter posting | Moved it into the post office outbox, confirmed, and scheduled it for 24 November 2005 |
| Fishing | Cast normally; observed approach, nibble and bite states; pressed A at frame 37518, caught kind 1 and accepted its dialogue; item 0x12e9 entered pocket 1 |
| Persistence | Saved and quit at frame 39102; both banks valid, with the caught fish and dated letter stored |
| Letter delivery | A new Clean process with clock 2005-11-24 12:00:00 and the reload recording through 4794 put the letter in mailbox slot 0, state 0x42 (received, marked), retaining the three body codepoints; the fish remained in pocket 1 |

A separate replay of the entire 39102-frame prepared-case recording produced a byte-identical
256 KiB chip, including both valid banks, the fish and dated letter.

The final saved chip's SHA-256 is
`224ec9a5b6404211601ecd7a9102ccaa3aea7ae9eedcf4f28d02e895219f0a4e`.
The dated letter before the next-day load has date bytes `18 0b 05 00`; its body begins
`e1 00 f1 00 fc 00 00 00`. Delivery was checked in the game's mailbox record after the
next-day startup, together with the visible new-mail marker on the house's mailbox.
No fish state, letter record or wallet was modified while executing these cases. Runtime
memory was read to observe the bite and verify the outcomes; only ordinary game inputs
caused the sale, purchase, writing, posting, catch and saves.

## Localization failures found

These functional results do not mean every displayed string is Spanish. The capture message
still uses a Korean fallback archive. Item names/metadata still come from Korean fixed-record
files, outside the BMG conversion: for example, paper names are Korean and a name in the shop's
purchase dialogue was empty. Those need a separate resource/runtime correction. The original
name capacities also limit longer translated speaker names. These are recorded failures,
not scenarios silently treated as fully localized.
