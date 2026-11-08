# Experimental European resources in Clean

The Clean implementation targets the Korean executable and its addresses. It cannot use
the European executable's addresses. This opt-in experiment keeps all 153 Korean executable
modules byte for byte and imports compatible text and font resources from a user's European
ROM. Clean still runs the game functions; this does not substitute Reference for Clean.

This is a partial localization of the Korean release, not a complete native European port.
It changes the game's resources deliberately and is separate from the project's original-ROM
fidelity checks. Neither original dump is modified.

An optional Latin accent page is available with `--latin-keyboard`. This changes only three
read-only character tables in overlay 95 and three keyboard graphics, leaving all function
instructions unchanged. Without this flag, all 153 executable modules stay byte-identical;
with it, 152 modules do, and overlay 95 differs only inside the reported character tables.

## Running

First set up the Korean ROM normally (`tools/setup.py`, INSTALL.md). With the same compiler
environment, on Windows:

```sh
python tools/play.py --localize es --european path/to/european.nds
python tools/play.py --localize es --european path/to/european.nds --latin-keyboard
python tools/play.py --localize es --european path/to/european.nds --latin-keyboard --spanish-grammar
```

The language codes are `en`, `fr`, `de`, `es`, and `it`. Both dumps are checked by SHA-1:

- Korean ADMK revision 0: `1fffd601d3439e37cd934e72d08e487a93fc449b`.
- European ADMP revision 0: `858da57a18852e75304e423519dde6a548d5264b`.

`tools/localize_clean.py --european EUROPE.nds --language es` generates the resources alone,
without a compiler. Output stays under ignored `build/localized-clean/<language>/`:
`game.nds` and `report.json`. Do not upload these files: they contain original game resources.
No game resources or ROM-derived fixtures are distributed in this change.

The playable program is `build/adm-kr/runtime/acww-play-es.exe` (and a matching `.cfg`),
separate from the normal Clean program. The configuration still uses the Korean modules,
symbols, and Clean policy. Its default save is `%APPDATA%/acwwdecomp/localized-clean/acww.sav`,
shared across these five language choices and separate from the normal Korean save. An explicit
save path on the command line overrides it. Keep this save separate from European-ROM saves.

## Conversion and limits

The two releases have the same 1,791 script filenames. The converter expands European
one-byte characters into the Korean two-byte format, expands and aligns message control-tag
headers, and rebuilds INF1 offsets and DAT1 sizes. Original Korean per-message attributes and
indices are kept. Font glyphs are combined by character code, retaining Korean fallback glyphs
and using the European glyphs for Western characters, including accents. Compressed donor
font images are unpacked: the Korean glyph renderer reads its image file directly. The four
compatible title graphics are imported from the chosen European language too.

The Spanish build replaces 1,659 script files, twelve font files and four title files. Two
string archives (`st_password` and `st_sweet`) have extra empty European tail entries; these
can be dropped without shifting any of the Korean indices. It deliberately retains 132 original
script files: 41 still require message-index mapping, 90 are legacy archives whose contents
are identical across all five European languages, and one belongs to the documented unreachable
test actor. Their paths are listed in `report.json`; [localization-audit.md](localization-audit.md)
describes the evidence and the limits of that classification. It does not guess how to renumber
dialogue branches. Even files with equal counts still need broader semantic
verification: matching counts do not prove every regional script uses the same indices.

European group-11 grammar tags do not have equivalent implementations in the Korean game.
The converter currently removes state-only grammar tags and chooses the first explicit
alternative where the tag carries alternatives. These approximations are counted by tag kind
in the report. Gender, articles, capitalization and inflection are therefore incomplete.

`--spanish-grammar` is an opt-in replacement for this approximation, currently for Clean/es
only. It preserves numeric gender/article metadata and the UTF-16 alternatives in group-11
tags. Dialogues and letter/notice-board decoding select alternatives using the current player
or the referenced text object's gender; absent or invalid gender does not default to masculine.
The text's primary/secondary article indices are honored, with state 2 suppressing the article.
The six Spanish article texts are loaded into the reader's existing persistent small-text
cache. Capitalization follows the European Western character-code table, including accents.

These rules were read from the European executable: the dialogue handlers at `0206af8c` and
`0206afe8`, their article selection at `0206b0cc`, the corresponding mail handlers around
`0203d1d8`, and the case table used at `02050360`. In the Korean implementation the respective
grammar handlers are empty. The added code is guarded by `ACWW_GRAMMAR=es`; the front end sets
it from `grammar=es` in the generated configuration and clears it otherwise. Original source
files under `src/` are untouched; normal Clean behavior remains the original contract.

The resource output and executable have separate names (`es-grammar/game.nds` and
`acww-play-es-grammar.exe`), so they do not replace the first-form adaptation. Generated reports
distinguish preserved grammar tags from approximated ones. Grammar support cannot supply
missing translations or repair regional message-index differences. Full event and item-name
coverage is still pending; a successfully rendered greeting is not evidence of all grammar paths.

Without `--latin-keyboard`, the Korean keyboard and its character composition logic remain
Korean; select the Latin tab when entering a Western name. The optional accent page replaces
the third (symbols) tab with 30 Western accent characters, including lower/upper case Spanish
vowels, n with tilde, u with diaeresis and inverted punctuation. Key labels are generated from
the user's European font, rather than shipped as assets. Both normal and chat layouts use the
same key codes and labels. Existing backspace, newline and space keys are retained; fullwidth
English punctuation is normalized to its Western character code. The first two tabs still
provide Hangul and English lower/upper case. Other regional layouts, embedded strings, graphics and item
metadata are not comprehensively localized. Original sound and multiplayer limitations remain.
This experiment must not be presented as a fully translated or fully verified European port.

## Verification

`python tools/test_localize_clean.py` and `python tools/test_latin_keyboard.py` use synthetic
containers, messages, character tables and glyphs only.
The generator also compares all decompressed executable modules before and after resource
replacement and refuses to write output if one changed. Header capacity, used size and CRC
are updated; code, overlay IDs, file IDs and filenames are retained.

Local Spanish validation with both user-supplied ROMs:

- All 153 executable modules stayed byte-identical, and runtime boot verification matched.
- The title greeting rendered in Spanish with 25,251 Clean replacements registered; the
  runtime reported actual calls into Clean functions.
- A 13,760-frame run using `runtime/recordings/new-game.txt`, with Reference timing recorded
  and replayed in Clean, gave identical frame sequences:
  `6deaaa492ca813727071351573d5d21e981147f5`.

The last check is an equivalence check on this input, not a complete-playthrough claim. The
original recording's Korean input timing does not complete the localized town-name keyboard;
both forms remain there. Subsequent gameplay, all grammar alternatives and every retained
file still need dedicated coverage.

The optional Latin keyboard has a separate 14,900-frame recording,
`runtime/recordings/localization/latin-keyboard.txt`. It clears the town-name field, opens the
third tab and inserts three accented characters. The labels and resulting characters were
inspected visually. With the Spanish resources and `--latin-keyboard`, Reference and Clean
both give frame sequence SHA-1 `f8638c7bb1c3960d83981b372d7254ae744f04e6` when Reference
timing is recorded/replayed. The five synthetic keyboard tests also check normal/chat label
alignment, signed-safe accent codes, unchanged command keys, and the explicit data ranges.

The six grammar tests validate preservation of both gender forms, numeric metadata,
capitalization/article states, oversized-tag rejection, and the compiled C selectors on male,
female, neutral, empty, malformed and unknown inputs. A 15,000-frame localized Clean run
completed without errors. A synthetic in-game greeting verified the capitalization path;
before the player exists, its gender alternative is deliberately omitted. With grammar off,
the original 1,300-frame title recording still gives expected frame sequence SHA-1
`69297d7d46a0d122090aec6da585046bf2227aaf` in both Reference and Clean.
