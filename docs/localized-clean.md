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

The Spanish build replaces 1,657 script files, twelve font files and four title files. It
deliberately retains 134 original script files: 43 have different message counts, and 91 have
incompatible legacy encodings. Their paths are listed in `report.json`. It does not guess how
to renumber their dialogue branches. Even files with equal counts still need broader semantic
verification: matching counts do not prove every regional script uses the same indices.

European group-11 grammar tags do not have equivalent implementations in the Korean game.
The converter currently removes state-only grammar tags and chooses the first explicit
alternative where the tag carries alternatives. These approximations are counted by tag kind
in the report. Gender, articles, capitalization and inflection are therefore incomplete.

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
